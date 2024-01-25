// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//             Constants                 //
// ------------------------------------- //

#define TRADE_ITEMS_PAGE_LIMIT 4

// ------------------------------------- //
//             Enums                     //
// ------------------------------------- //

static enum e_tradeItemsTypes {
    TYPE_MONEY, TYPE_HOUSE, TYPE_BUSINESS, TYPE_DRUGS, TYPE_MATERIALS, TYPE_VEHICLE
}

static enum e_tradeItemsInfo {
    e_tradeItemsTypes:itemType, itemModel, itemValue
} 

// ------------------------------------- //
//             Variables                 //
// ------------------------------------- //

static  
    PlayerText:tradePlayerTDs[MAX_PLAYERS][12] = {{PlayerText:-1, ...}, ...},
    PlayerText:tradeItemsTDs[MAX_PLAYERS][16] = {{PlayerText:-1, ...}, ...},
    Vector:tradeItems[MAX_PLAYERS],
    tradeDelay[MAX_PLAYERS],
    tradeReadyDelay[MAX_PLAYERS],
    tradeWith[MAX_PLAYERS] = {-1, ...},
    tradeInviter[MAX_PLAYERS] = {-1, ...},
    tradeItemsCount[MAX_PLAYERS],
    tradeItemsIndex[MAX_PLAYERS][2],
    tradeItemsPageCount[MAX_PLAYERS][2],
    bool:tradeItemsInserted[MAX_PLAYERS][e_tradeItemsTypes - e_tradeItemsTypes:1],
    bool:tradePlayerReady[MAX_PLAYERS],
    Timer:tradeTimer[MAX_PLAYERS],
    tradePersonalVehiclesCount[MAX_PLAYERS],
    tradeItemsMoney[MAX_PLAYERS][2],
    tradeTimerSeconds[MAX_PLAYERS];

static const Float:tradeItemsPositions[][] = {
    {51.525474, 109.124595, 166.026626, 223.230117},
    {355.997314, 412.900787, 470.304290, 527.403076}
};

// ------------------------------------- //
//             Functions                 //
// ------------------------------------- //

static destroyTradeTextdraws(const playerid) {
    for(new i = 0; i < sizeof tradeItemsTDs[]; ++i) {
        playerTextDrawDestroy(playerid, tradeItemsTDs[playerid][i]);
        playerTextDrawDestroy(tradeWith[playerid], tradeItemsTDs[tradeWith[playerid]][i]);

        if(i < sizeof tradePlayerTDs[]) {
            playerTextDrawDestroy(playerid, tradePlayerTDs[playerid][i]);
            playerTextDrawDestroy(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][i]);
        }
    }
}

static cancelTrade(const playerid) {
    VECTOR_clear(tradeItems[playerid]);
    VECTOR_clear(tradeItems[tradeWith[playerid]]);

    destroyTradeTextdraws(playerid);

    CancelSelectTextDraw(tradeWith[playerid]);
    TogglePlayerControllableEx(tradeWith[playerid], true);

    CancelSelectTextDraw(playerid);
    TogglePlayerControllableEx(playerid, true);

    tradeWith[tradeWith[playerid]] = tradeWith[playerid] = -1;
}

static clearTradeItems(const playerid) {
    VECTOR_clear(tradeItems[playerid]);

    new i;

    for(i = 0; i < tradeItemsPageCount[playerid][0]; ++i) {
        PlayerTextDrawHide(playerid, tradeItemsTDs[playerid][i]);
        PlayerTextDrawHide(playerid, tradeItemsTDs[playerid][i + 8]);
    }

    for(i = 0; i < tradeItemsPageCount[tradeWith[playerid]][1]; ++i) {
        PlayerTextDrawHide(tradeWith[playerid], tradeItemsTDs[tradeWith[playerid]][i + 4]);
        PlayerTextDrawHide(tradeWith[playerid], tradeItemsTDs[tradeWith[playerid]][i + 12]);
    }

    tradeItemsPageCount[playerid][0] = tradeItemsPageCount[tradeWith[playerid]][1] = tradeItemsCount[playerid] = 
    tradePersonalVehiclesCount[playerid] = tradePersonalVehiclesCount[tradeWith[playerid]] = 0;

    tradeItemsIndex[playerid][0] = tradeItemsIndex[tradeWith[playerid]][1] = -1;

    memset(tradeItemsInserted[playerid], false);
}

static updateTradeItem(const playerid, const userID, const item[e_tradeItemsInfo], const textdrawidx) {
    gString[0] = EOS;

    switch(item[itemType]) {
        case TYPE_MONEY: {
            format(gString, sizeof gString, "$%s", formatMoney(tradeItemsMoney[userID][0], tradeItemsMoney[userID][1]));
        }
        case TYPE_HOUSE: {
            format(gString, sizeof gString, "house %d", HouseInfo[item[itemValue]][hID]);
        }
        case TYPE_BUSINESS: {
            format(gString, sizeof gString, "business %d", bizzInfo[item[itemValue]][bID]);
        }
        case TYPE_DRUGS: {
            format(gString, sizeof gString, "%d drugs", item[itemValue]);
        }
        case TYPE_MATERIALS: {
            format(gString, sizeof gString, "%d materials", item[itemValue]);
        }
        case TYPE_VEHICLE: {
            strcat(gString, aVehicleNames[personalVehiclesInfo[item[itemValue]][pv_ModelID] - 400]);
        }
    }

    PlayerTextDrawSetString(playerid, tradeItemsTDs[playerid][textdrawidx + 8], gString);
    PlayerTextDrawShow(playerid, tradeItemsTDs[playerid][textdrawidx + 8]);

    PlayerTextDrawSetPreviewModel(playerid, tradeItemsTDs[playerid][textdrawidx], item[itemModel]);
    PlayerTextDrawShow(playerid, tradeItemsTDs[playerid][textdrawidx]);
}

static showTradeItems(const playerid, const userID, &index_start) {
    new 
        idx = playerid != userID,
        item[e_tradeItemsInfo];

    tradeItemsPageCount[playerid][idx] = 0;

    for(;;) {
        VECTOR_get_arr(tradeItems[userID], index_start, item);

        updateTradeItem(playerid, userID, item, (idx * 4) + tradeItemsPageCount[playerid][idx]);

        if(++tradeItemsPageCount[playerid][idx] == TRADE_ITEMS_PAGE_LIMIT) 
            return 1;

        if(index_start == getTradeItemsCount(userID) - 1)
            break;

        else 
            index_start ++;
    }

    for(new i = tradeItemsPageCount[playerid][idx]; i < 4; ++i) {
        PlayerTextDrawHide(playerid, tradeItemsTDs[playerid][i + (idx * 4)]);
        PlayerTextDrawHide(playerid, tradeItemsTDs[playerid][8 + i + (idx * 4)]);
    }

    return 1;
}

static insertTradeItem(const playerid, e_tradeItemsTypes:type, model, value) { 
    new item[e_tradeItemsInfo];

    item[itemType] = type;
    item[itemModel] = model;
    item[itemValue] = value;

    VECTOR_push_back_arr(tradeItems[playerid], item);

    tradeItemsCount[playerid] ++;

    if(type != TYPE_VEHICLE)
        tradeItemsInserted[playerid][type] = true;

    if(tradeItemsPageCount[playerid][0] < TRADE_ITEMS_PAGE_LIMIT) {
        updateTradeItem(playerid, playerid, item, tradeItemsPageCount[playerid][0]);

        tradeItemsPageCount[playerid][0] ++;
        tradeItemsIndex[playerid][0] ++;
    }

    if(tradeItemsPageCount[tradeWith[playerid]][1] < TRADE_ITEMS_PAGE_LIMIT) {
        updateTradeItem(tradeWith[playerid], playerid, item, 4 + tradeItemsPageCount[tradeWith[playerid]][1]);

        tradeItemsPageCount[tradeWith[playerid]][1] ++;
        tradeItemsIndex[tradeWith[playerid]][1] ++;
    }
}

static exchangeTradeItem(const playerid, const e_tradeItemsTypes:type, const value) {
    switch(type) {
        case TYPE_MONEY: {
            substractBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1]);
            addBankMoney(tradeWith[playerid], playerInfo[tradeWith[playerid]][pBankStore], playerInfo[tradeWith[playerid]][pBank], tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1]);

            gString[0] = EOS;
            format(gString, sizeof gString, "- $%s", formatMoney(tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1]));

            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
        case TYPE_HOUSE: {
            HouseInfo[value][hOwnerID] = playerInfo[tradeWith[playerid]][pSQLID];
            HouseInfo[value][hOwnerGameID] = tradeWith[playerid];
            HouseInfo[value][hPrice] = 0;
            strcpy(HouseInfo[value][hOwnerName], GetName(tradeWith[playerid]), MAX_PLAYER_NAME);

            playerInfo[tradeWith[playerid]][pHouse] = value;

            playerInfo[playerid][pHouse] = -1;

            playerInfo[playerid][pSpawnType] = SPAWN_TYPE_NORMAL;

            if(playerInfo[tradeWith[playerid]][pRent] != -1)
                removeHouseRenter(tradeWith[playerid]);

            gQuery[0] = EOS; 
            mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users`, `server_houses` SET `server_houses`.`OwnerID` = %d, `server_houses`.`OwnerName` = '%e', `server_houses`.`Price` = 0, `server_users`.`House` = %d, `server_users`.`Rent` = -1 WHERE `server_houses`.`ID` = %d AND `server_users`.`ID` = %d", playerInfo[tradeWith[playerid]][pSQLID], GetName(tradeWith[playerid]), HouseInfo[value][hID], HouseInfo[value][hID], playerInfo[tradeWith[playerid]][pSQLID]); 
            mysql_tquery(SQL, gQuery, "", "");

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `SpawnType` = 1, `House` = -1 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "", "");

            updateHouseLabel(value);

            gString[0] = EOS;
            format(gString, sizeof gString, "- House %d", HouseInfo[value][hID]);
            
            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
        case TYPE_BUSINESS: {
            bizzInfo[value][bOwnerSQLID] = playerInfo[tradeWith[playerid]][pSQLID];
            bizzInfo[value][bOwnerGameID] = tradeWith[playerid];
            bizzInfo[value][bPrice] = 0;
            strcpy(bizzInfo[value][bOwnerName], GetName(tradeWith[playerid]), MAX_PLAYER_NAME);

            playerInfo[tradeWith[playerid]][pBusiness] = value;
            playerInfo[playerid][pBusiness] = -1;

            gQuery[0] = EOS; 
            mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users`, `server_business` SET `server_business`.`OwnerSQLID` = %d, `server_business`.`OwnerName` = '%e', `server_business`.`Price` = 0, `server_users`.`Business` = %d WHERE `server_business`.`ID` = %d AND `server_users`.`ID` = %d", playerInfo[tradeWith[playerid]][pSQLID], GetName(tradeWith[playerid]), bizzInfo[value][bID], bizzInfo[value][bID], playerInfo[tradeWith[playerid]][pSQLID]); 
            mysql_tquery(SQL, gQuery, "", "");

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Business` = -1 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "", "");

            updateBusinessLabel(value);

            gString[0] = EOS;
            format(gString, sizeof gString, "- Business %d", bizzInfo[value][bID]);
            
            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
        case TYPE_DRUGS: {
            playerInfo[playerid][pDrugs] -= value;
            playerInfo[tradeWith[playerid]][pDrugs] += value;

            va_mysql_tquery("UPDATE `server_users` SET `Drugs` = CASE WHEN `ID` = %d THEN %d WHEN `ID` = %d THEN %d END WHERE `ID` IN (%d, %d)", playerInfo[playerid][pSQLID], playerInfo[playerid][pDrugs], playerInfo[tradeWith[playerid]][pSQLID], playerInfo[tradeWith[playerid]][pDrugs], playerInfo[playerid][pSQLID], playerInfo[tradeWith[playerid]][pSQLID]);

            gString[0] = EOS;
            format(gString, sizeof gString, "- %d drugs", value);
            
            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
        case TYPE_MATERIALS: {
            playerInfo[playerid][pMaterials] -= value;
            playerInfo[tradeWith[playerid]][pMaterials] += value;

            va_mysql_tquery("UPDATE `server_users` SET `Materials` = CASE WHEN `ID` = %d THEN %d WHEN `ID` = %d THEN %d END WHERE `ID` IN (%d, %d)", playerInfo[playerid][pSQLID], playerInfo[playerid][pMaterials], playerInfo[tradeWith[playerid]][pSQLID], playerInfo[tradeWith[playerid]][pMaterials], playerInfo[playerid][pSQLID], playerInfo[tradeWith[playerid]][pSQLID]);

            gString[0] = EOS;
            format(gString, sizeof gString, "- %d materials", value);
            
            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
        case TYPE_VEHICLE: {
            setPersonalVehicleOwner(value, tradeWith[playerid]);

            gString[0] = EOS;
            format(gString, sizeof gString, "- %s (ID %d, %.0fkm, %d days, %d/%d colors)", aVehicleNames[personalVehiclesInfo[value][pv_ModelID] - 400], personalVehiclesInfo[value][pv_ID], personalVehiclesInfo[value][pv_Odometer], (gettime() - personalVehiclesInfo[value][pv_Days]) / 86400, personalVehiclesInfo[value][pv_ColorOne], personalVehiclesInfo[value][pv_ColorTwo]);
            
            SCM(playerid, -1, gString);
            SCM(tradeWith[playerid], -1, gString);
        }
    }
    return 1;
}

static showTradePersonalVehicles(const playerid, &index_start) {
    gDialog = "Vehicle\tID\tInfo (odometer, days, colors)\n";

    new count;

    for(new Pointer:i, val; VECTOR_foreach_cmp(personalVehicles[playerid], index_start, i); ++index_start) {
        val = MEM_get_val(i);

        format(gDialog, sizeof gDialog, "%s%s\t%d\t%.0fkm, %d, %d/%d\n", gDialog, aVehicleNames[personalVehiclesInfo[val][pv_ModelID] - 400], personalVehiclesInfo[val][pv_ID], personalVehiclesInfo[val][pv_Odometer], (gettime() - personalVehiclesInfo[val][pv_Days]) / 86400, personalVehiclesInfo[val][pv_ColorOne], personalVehiclesInfo[val][pv_ColorTwo]);

        dialogPersonalVehicles[playerid][count++] = val;

        if(count == 10) {
            if(VECTOR_size(personalVehicles[playerid]) > index_start + 1) 
                strcat(gDialog, "> Next Page\n");
            
            break;
        }
    }

    if(index_start >= 10) 
        strcat(gDialog, "< Previous Page");

    return Dialog_Show(playerid, TRADEADDPERSONALVEHICLES, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Add Personal Vehicles", gDialog, "Select", "Exit");
}

static haveTradePersonalVehicle(const playerid, const value) {
    new item[e_tradeItemsInfo];

    item[itemType] = TYPE_VEHICLE;
    item[itemValue] = value;
    item[itemModel] = personalVehiclesInfo[value][pv_ModelID];

    return VECTOR_find_arr(tradeItems[playerid], item) != INVALID_VECTOR_INDEX;
}

startPlayersTrade(const playerid, const userID) {
    tradeWith[playerid] = userID;
    tradeWith[userID] = playerid;

    tradeItemsPageCount[playerid][0] = tradeItemsPageCount[playerid][1] = 
    tradeItemsPageCount[userID][0] = tradeItemsPageCount[userID][1] = 
    tradeItemsCount[playerid] = tradeItemsCount[userID] = 
    tradePersonalVehiclesCount[playerid] = tradePersonalVehiclesCount[userID] = 0;

    tradeItemsIndex[playerid][0] = tradeItemsIndex[playerid][1] = 
    tradeItemsIndex[userID][0] = tradeItemsIndex[userID][1] = 
    tradeInviter[playerid] = tradeInviter[userID] = -1;

    tradePlayerReady[playerid] = tradePlayerReady[userID] = false;

    memset(tradeItemsInserted[playerid], false);
    memset(tradeItemsInserted[userID], false);

    TogglePlayerControllableEx(playerid, false);
    TogglePlayerControllableEx(userID, false);

    SelectTextDraw(playerid, -1);
    SelectTextDraw(userID, -1);

    // Textdraws

    tradePlayerTDs[playerid][0] = CreatePlayerTextDraw(playerid, 51.761856, 149.166763, "box");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][0], 0.000000, 5.689605);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][0], 279.399414, 0.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][0], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][0], 0x00000065);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][0], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][0], 1);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][0]);

    tradePlayerTDs[userID][0] = CreatePlayerTextDraw(userID, 51.761856, 149.166763, "box");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][0], 0.000000, 5.689605);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][0], 279.399414, 0.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][0], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][0], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][0], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][0], 0x00000065);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][0], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][0], 0);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][0], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][0], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][0], 1);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][0]);

    tradePlayerTDs[playerid][1] = CreatePlayerTextDraw(playerid, 356.103424, 149.166763, "box");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][1], 0.000000, 5.689605);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][1], 583.725891, 0.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][1], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][1], 0x00000065);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][1], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][1], 1);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][1]);

    tradePlayerTDs[userID][1] = CreatePlayerTextDraw(userID, 356.103424, 149.166763, "box");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][1], 0.000000, 5.689605);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][1], 583.725891, 0.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][1], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][1], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][1], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][1], 0x00000065);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][1], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][1], 0);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][1], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][1], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][1], 1);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][1]);

    tradePlayerTDs[playerid][2] = CreatePlayerTextDraw(playerid, 165.815734, 134.016708, "your items (page: 1)");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][2], 0.293644, 1.121665);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][2], 0.000000, 227.737945);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][2], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][2], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][2], 8388863);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][2], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][2], 3);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][2], 1);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][2]);

    tradePlayerTDs[userID][2] = CreatePlayerTextDraw(userID, 165.815734, 134.016708, "your items (page: 1)");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][2], 0.293644, 1.121665);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][2], 0.000000, 227.737945);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][2], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][2], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][2], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][2], 8388863);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][2], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][2], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][2], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][2], 3);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][2], 1);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][2]);

    gString[0] = EOS;
    format(gString, sizeof gString, "%s's items (page: 1)", GetName(playerid));

    tradePlayerTDs[userID][3] = CreatePlayerTextDraw(userID, 469.906097, 134.016708, gString);
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][3], 0.293644, 1.121665);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][3], 0.000000, 227.628005);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][3], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][3], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][3], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][3], 8388863);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][3], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][3], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][3], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][3], 3);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][3], 1);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][3]);

    gString[0] = EOS;
    format(gString, sizeof gString, "%s's items (page: 1)", GetName(userID));

    tradePlayerTDs[playerid][3] = CreatePlayerTextDraw(playerid, 469.906097, 134.016708, gString);
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][3], 0.293644, 1.121665);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][3], 0.000000, 227.628005);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][3], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][3], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][3], 8388863);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][3], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][3], 3);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][3], 1);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][3]);

    tradePlayerTDs[playerid][4] = CreatePlayerTextDraw(playerid, 272.233093, 200.101257, ">");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][4], 0.398124, 1.815832);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][4], 281.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][4], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][4], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][4], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][4], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][4]);

    tradePlayerTDs[playerid][5] = CreatePlayerTextDraw(playerid, 49.813209, 200.101257, "<");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][5], 0.398124, 1.815832);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][5], 60.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][5], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][5], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][5], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][5], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][5]);

    tradePlayerTDs[playerid][6] = CreatePlayerTextDraw(playerid, 354.238098, 200.101257, "<");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][6], 0.398124, 1.815832);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][6], 364.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][6], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][6], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][6], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][6], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][6]);

    tradePlayerTDs[playerid][7] = CreatePlayerTextDraw(playerid, 576.400634, 200.101257, ">");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][7], 0.398124, 1.815832);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][7], 586.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][7], 1);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][7], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][7], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][7], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][7]);

    tradePlayerTDs[userID][4] = CreatePlayerTextDraw(userID, 272.233093, 200.101257, ">");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][4], 0.398124, 1.815832);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][4], 281.000000, 10.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][4], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][4], -1);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][4], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][4], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][4], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][4], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][4], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][4], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][4]);

    tradePlayerTDs[userID][5] = CreatePlayerTextDraw(userID, 49.813209, 200.101257, "<");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][5], 0.398124, 1.815832);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][5], 60.000000, 10.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][5], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][5], -1);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][5], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][5], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][5], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][5], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][5], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][5], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][5]);

    tradePlayerTDs[userID][6] = CreatePlayerTextDraw(userID, 354.238098, 200.101257, "<");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][6], 0.398124, 1.815832);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][6], 364.000000, 10.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][6], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][6], -1);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][6], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][6], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][6], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][6], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][6], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][6], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][6]);

    tradePlayerTDs[userID][7] = CreatePlayerTextDraw(userID, 576.400634, 200.101257, ">");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][7], 0.398124, 1.815832);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][7], 586.000000, 10.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][7], 1);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][7], -1);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][7], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][7], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][7], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][7], 1);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][7], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][7], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][7]);

    tradePlayerTDs[playerid][8] = CreatePlayerTextDraw(playerid, 318.579925, 169.367706, "CLEAR ITEMS");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][8], 0.187758, 1.139165);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][8], 10.000000, 52.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][8], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][8], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][8], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][8], 8388863);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][8], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][8], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][8], 2);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][8], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][8]);

    tradePlayerTDs[playerid][9] = CreatePlayerTextDraw(playerid, 318.579925, 185.768707, "READY");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][9], 0.187758, 1.139165);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][9], 10.000000, 32.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][9], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][9], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][9], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][9], 932573439);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][9], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][9], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][9], 2);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][9], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][9]);

    tradePlayerTDs[playerid][10] = CreatePlayerTextDraw(playerid, 318.579925, 152.666687, "ADD ITEM");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][10], 0.187758, 1.139165);
    PlayerTextDrawTextSize(playerid, tradePlayerTDs[playerid][10], 10.000000, 38.000000);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][10], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][10], -1);
    PlayerTextDrawUseBox(playerid, tradePlayerTDs[playerid][10], 1);
    PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][10], 8388863);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][10], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][10], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][10], 2);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, tradePlayerTDs[playerid][10], true);
    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][10]);

    tradePlayerTDs[userID][8] = CreatePlayerTextDraw(userID, 318.579925, 169.367706, "CLEAR ITEMS");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][8], 0.187758, 1.139165);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][8], 10.000000, 52.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][8], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][8], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][8], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][8], 8388863);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][8], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][8], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][8], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][8], 2);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][8], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][8], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][8]);

    tradePlayerTDs[userID][9] = CreatePlayerTextDraw(userID, 318.579925, 185.768707, "READY");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][9], 0.187758, 1.139165);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][9], 10.000000, 32.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][9], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][9], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][9], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][9], 932573439);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][9], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][9], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][9], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][9], 2);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][9], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][9], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][9]);

    tradePlayerTDs[userID][10] = CreatePlayerTextDraw(userID, 318.579925, 152.666687, "ADD ITEM");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][10], 0.187758, 1.139165);
    PlayerTextDrawTextSize(userID, tradePlayerTDs[userID][10], 10.000000, 38.000000);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][10], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][10], -1);
    PlayerTextDrawUseBox(userID, tradePlayerTDs[userID][10], 1);
    PlayerTextDrawBoxColor(userID, tradePlayerTDs[userID][10], 8388863);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][10], 0);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][10], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][10], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][10], 2);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][10], 1);
    PlayerTextDrawSetSelectable(userID, tradePlayerTDs[userID][10], true);
    PlayerTextDrawShow(userID, tradePlayerTDs[userID][10]);

    tradePlayerTDs[playerid][11] = CreatePlayerTextDraw(playerid, 318.285736, 132.338973, "TRADE IN: 10");
    PlayerTextDrawLetterSize(playerid, tradePlayerTDs[playerid][11], 0.219150, 1.273333);
    PlayerTextDrawAlignment(playerid, tradePlayerTDs[playerid][11], 2);
    PlayerTextDrawColor(playerid, tradePlayerTDs[playerid][11], -1);
    PlayerTextDrawSetOutline(playerid, tradePlayerTDs[playerid][11], 1);
    PlayerTextDrawBackgroundColor(playerid, tradePlayerTDs[playerid][11], 255);
    PlayerTextDrawFont(playerid, tradePlayerTDs[playerid][11], 2);
    PlayerTextDrawSetProportional(playerid, tradePlayerTDs[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, tradePlayerTDs[playerid][11], 0);

    tradePlayerTDs[userID][11] = CreatePlayerTextDraw(userID, 318.285736, 132.338973, "TRADE IN: 10");
    PlayerTextDrawLetterSize(userID, tradePlayerTDs[userID][11], 0.219150, 1.273333);
    PlayerTextDrawAlignment(userID, tradePlayerTDs[userID][11], 2);
    PlayerTextDrawColor(userID, tradePlayerTDs[userID][11], -1);
    PlayerTextDrawSetOutline(userID, tradePlayerTDs[userID][11], 1);
    PlayerTextDrawBackgroundColor(userID, tradePlayerTDs[userID][11], 255);
    PlayerTextDrawFont(userID, tradePlayerTDs[userID][11], 2);
    PlayerTextDrawSetProportional(userID, tradePlayerTDs[userID][11], 1);
    PlayerTextDrawSetShadow(userID, tradePlayerTDs[userID][11], 0);

    // Items

    new i, x;

    for(i = 0, x = 4; i < sizeof tradeItemsPositions[]; ++i, ++x) {
        tradeItemsTDs[playerid][i] = CreatePlayerTextDraw(playerid, tradeItemsPositions[0][i], 148.416580, "");
        PlayerTextDrawLetterSize(playerid, tradeItemsTDs[playerid][i], 0.000000, 0.000000);
        PlayerTextDrawTextSize(playerid, tradeItemsTDs[playerid][i], 56.240200, 52.419929);
        PlayerTextDrawAlignment(playerid, tradeItemsTDs[playerid][i], 1);
        PlayerTextDrawColor(playerid, tradeItemsTDs[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, tradeItemsTDs[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, tradeItemsTDs[playerid][i], 0x00000085);
        PlayerTextDrawFont(playerid, tradeItemsTDs[playerid][i], 5);
        PlayerTextDrawSetProportional(playerid, tradeItemsTDs[playerid][i], 0);
        PlayerTextDrawSetPreviewRot(playerid, tradeItemsTDs[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
        PlayerTextDrawSetPreviewVehCol(playerid, tradeItemsTDs[playerid][i], 1, 1);

        tradeItemsTDs[playerid][x] = CreatePlayerTextDraw(playerid, tradeItemsPositions[1][i], 148.416580, "");
        PlayerTextDrawLetterSize(playerid, tradeItemsTDs[playerid][x], 0.000000, 0.000000);
        PlayerTextDrawTextSize(playerid, tradeItemsTDs[playerid][x], 56.240200, 52.419929);
        PlayerTextDrawAlignment(playerid, tradeItemsTDs[playerid][x], 1);
        PlayerTextDrawColor(playerid, tradeItemsTDs[playerid][x], -1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawSetOutline(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawBackgroundColor(playerid, tradeItemsTDs[playerid][x], 0x00000085);
        PlayerTextDrawFont(playerid, tradeItemsTDs[playerid][x], 5);
        PlayerTextDrawSetProportional(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawSetPreviewRot(playerid, tradeItemsTDs[playerid][x], 0.000000, 0.000000, 0.000000, 1.000000);
        PlayerTextDrawSetPreviewVehCol(playerid, tradeItemsTDs[playerid][x], 1, 1);

        tradeItemsTDs[userID][i] = CreatePlayerTextDraw(userID, tradeItemsPositions[0][i], 148.416580, "");
        PlayerTextDrawLetterSize(userID, tradeItemsTDs[userID][i], 0.000000, 0.000000);
        PlayerTextDrawTextSize(userID, tradeItemsTDs[userID][i], 56.240200, 52.419929);
        PlayerTextDrawAlignment(userID, tradeItemsTDs[userID][i], 1);
        PlayerTextDrawColor(userID, tradeItemsTDs[userID][i], -1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][i], 0);
        PlayerTextDrawSetOutline(userID, tradeItemsTDs[userID][i], 0);
        PlayerTextDrawBackgroundColor(userID, tradeItemsTDs[userID][i], 0x00000085);
        PlayerTextDrawFont(userID, tradeItemsTDs[userID][i], 5);
        PlayerTextDrawSetProportional(userID, tradeItemsTDs[userID][i], 0);
        PlayerTextDrawSetPreviewRot(userID, tradeItemsTDs[userID][i], 0.000000, 0.000000, 0.000000, 1.000000);
        PlayerTextDrawSetPreviewVehCol(userID, tradeItemsTDs[userID][i], 1, 1);

        tradeItemsTDs[userID][x] = CreatePlayerTextDraw(userID, tradeItemsPositions[1][i], 148.416580, "");
        PlayerTextDrawLetterSize(userID, tradeItemsTDs[userID][x], 0.000000, 0.000000);
        PlayerTextDrawTextSize(userID, tradeItemsTDs[userID][x], 56.240200, 52.419929);
        PlayerTextDrawAlignment(userID, tradeItemsTDs[userID][x], 1);
        PlayerTextDrawColor(userID, tradeItemsTDs[userID][x], -1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawSetOutline(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawBackgroundColor(userID, tradeItemsTDs[userID][x], 0x00000085);
        PlayerTextDrawFont(userID, tradeItemsTDs[userID][x], 5);
        PlayerTextDrawSetProportional(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawSetPreviewRot(userID, tradeItemsTDs[userID][x], 0.000000, 0.000000, 0.000000, 1.000000);
        PlayerTextDrawSetPreviewVehCol(userID, tradeItemsTDs[userID][x], 1, 1);
    }

    for(i = 0, x = 8; i < sizeof tradeItemsPositions[]; ++i, ++x) {
        tradeItemsTDs[playerid][x] = CreatePlayerTextDraw(playerid, tradeItemsPositions[0][i] + 28.505989, 194.383819, "");
        PlayerTextDrawLetterSize(playerid, tradeItemsTDs[playerid][x], 0.135753, 0.736666);
        PlayerTextDrawAlignment(playerid, tradeItemsTDs[playerid][x], 2);
        PlayerTextDrawColor(playerid, tradeItemsTDs[playerid][x], -1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawSetOutline(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawBackgroundColor(playerid, tradeItemsTDs[playerid][x], 255);
        PlayerTextDrawFont(playerid, tradeItemsTDs[playerid][x], 2);
        PlayerTextDrawSetProportional(playerid, tradeItemsTDs[playerid][x], 1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][x], 0);

        tradeItemsTDs[userID][x] = CreatePlayerTextDraw(userID, tradeItemsPositions[0][i] + 28.505989, 194.383819, "");
        PlayerTextDrawLetterSize(userID, tradeItemsTDs[userID][x], 0.135753, 0.736666);
        PlayerTextDrawAlignment(userID, tradeItemsTDs[userID][x], 2);
        PlayerTextDrawColor(userID, tradeItemsTDs[userID][x], -1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawSetOutline(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawBackgroundColor(userID, tradeItemsTDs[userID][x], 255);
        PlayerTextDrawFont(userID, tradeItemsTDs[userID][x], 2);
        PlayerTextDrawSetProportional(userID, tradeItemsTDs[userID][x], 1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][x], 0);
    }

    for(i = 0, x = 12; i < sizeof tradeItemsPositions[]; ++i, ++x) {
        tradeItemsTDs[playerid][x] = CreatePlayerTextDraw(playerid, tradeItemsPositions[1][i] + 28.505989, 194.383819, "");
        PlayerTextDrawLetterSize(playerid, tradeItemsTDs[playerid][x], 0.135753, 0.736666);
        PlayerTextDrawAlignment(playerid, tradeItemsTDs[playerid][x], 2);
        PlayerTextDrawColor(playerid, tradeItemsTDs[playerid][x], -1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawSetOutline(playerid, tradeItemsTDs[playerid][x], 0);
        PlayerTextDrawBackgroundColor(playerid, tradeItemsTDs[playerid][x], 255);
        PlayerTextDrawFont(playerid, tradeItemsTDs[playerid][x], 2);
        PlayerTextDrawSetProportional(playerid, tradeItemsTDs[playerid][x], 1);
        PlayerTextDrawSetShadow(playerid, tradeItemsTDs[playerid][x], 0);

        tradeItemsTDs[userID][x] = CreatePlayerTextDraw(userID, tradeItemsPositions[1][i] + 28.505989, 194.383819, "");
        PlayerTextDrawLetterSize(userID, tradeItemsTDs[userID][x], 0.135753, 0.736666);
        PlayerTextDrawAlignment(userID, tradeItemsTDs[userID][x], 2);
        PlayerTextDrawColor(userID, tradeItemsTDs[userID][x], -1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawSetOutline(userID, tradeItemsTDs[userID][x], 0);
        PlayerTextDrawBackgroundColor(userID, tradeItemsTDs[userID][x], 255);
        PlayerTextDrawFont(userID, tradeItemsTDs[userID][x], 2);
        PlayerTextDrawSetProportional(userID, tradeItemsTDs[userID][x], 1);
        PlayerTextDrawSetShadow(userID, tradeItemsTDs[userID][x], 0);
    }
}

static getTradeItemsCount(const playerid) 
    return tradeItemsCount[playerid];

isPlayerInTrade(const playerid)
    return tradeWith[playerid] != -1;

getTradeInvite(const playerid)
    return tradeInviter[playerid]; 

// ------------------------------------- //
//             Callbacks                 //
// ------------------------------------- //

function OnTradeTimerIsDone(const playerid) {
    new 
        i, 
        item[e_tradeItemsInfo];

    SCM(playerid, COLOR_GREEN, "(Trade): {ffffff}Your traded items:");
    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s's traded items:", GetName(playerid));

    for(i = 0; i < tradeItemsCount[playerid]; ++i) {
        VECTOR_get_arr(tradeItems[playerid], i, item);

        exchangeTradeItem(playerid, item[itemType], item[itemValue]);
    }

    SCM(playerid, -1, "");
    SCM(tradeWith[playerid], -1, "");

    SCM(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}Your traded items:");
    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}%s's traded items:", GetName(tradeWith[playerid]));

    for(i = 0; i < tradeItemsCount[tradeWith[playerid]]; ++i) {
        VECTOR_get_arr(tradeItems[tradeWith[playerid]], i, item);

        exchangeTradeItem(tradeWith[playerid], item[itemType], item[itemValue]);
    }

    cancelTrade(playerid);
    return 1;
}

// ------------------------------------- //
//             Timers                    //
// ------------------------------------- //

timer tradeTimerCountdown[1000](playerid) {
    if(--tradeTimerSeconds[playerid]) {
        gString[0] = EOS;
        format(gString, sizeof gString, "TRADE IN: %d", tradeTimerSeconds[playerid]);

        PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][11], gString);
        PlayerTextDrawSetString(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][11], gString);
    }
    else {
        stop tradeTimer[playerid];
        tradeTimer[tradeWith[playerid]] = Timer: 0;

        OnTradeTimerIsDone(playerid);
    }
    return 1;
}

// ------------------------------------- //
//             Commands                  //
// ------------------------------------- //

YCMD:trade(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 3) 
        return sendError(playerid, "Trebuie sa ai minim level 3 pentru a folosi aceasta comanda.");

    if(tradeDelay[playerid] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a folosi iar aceasta comanda.", tradeDelay[playerid] - gettime());

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/trade <playerid/name>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face asta asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 3.0))
        return sendError(playerid, "Nu esti in apropierea acelui player.");

    if(playerInfo[userID][pLevel] < 3) 
        return sendError(playerid, "Jucatorul respectiv nu are minim level 3.");

    if(isPlayerInTrade(userID))
        return sendError(playerid, "Acel player este deja intr-un trade.");

    tradeInviter[userID] = playerid; 

    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You invited player %s (%d) for a trade. Wait for him to accept the invite.", GetName(userID), userID);
    SCMf(userID, COLOR_GREEN, "(Trade): {ffffff}Player %s (%d) invited you for a trade. Accept his invitation by writing command [/accept %d trade].", GetName(playerid), playerid, playerid);
    
    tradeDelay[playerid] = gettime() + 60;
    return 1;
}

// ------------------------------------- //
//             Dialogs                   //
// ------------------------------------- //

Dialog:TRADEADDITEM(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInTrade(playerid))
        return 1;
    
    switch(listitem) {
        case 0: {
            if(tradeItemsInserted[playerid][TYPE_MONEY])
                return sendError(playerid, "Ai plasat deja bani.");

            if(tradeItemsInserted[tradeWith[playerid]][TYPE_MONEY])
                return sendError(playerid, "Acel player a plasat deja bani.");

            if(!playerInfo[playerid][pBankStore] && !playerInfo[playerid][pBank]) 
                return sendError(playerid, "Nu ai bani suficienti.");

            Dialog_Show(playerid, TRADEADDMONEY, DIALOG_STYLE_INPUT, "SERVER: Add Money", "Enter below the value of money you want to trade:", "Add", "Cancel");
        }
        case 1: {
            if(playerInfo[playerid][pHouse] == -1)
                return sendError(playerid, "Nu ai o casa.");

            if(tradeItemsInserted[playerid][TYPE_HOUSE])
                return sendError(playerid, "Ai plasat deja casa.");

            if(playerInfo[tradeWith[playerid]][pHouse] != -1)
                return sendError(playerid, "Acel player are deja o casa.");

            insertTradeItem(playerid, TYPE_HOUSE, 1272, playerInfo[playerid][pHouse]);

            SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added house %d.", HouseInfo[playerInfo[playerid][pHouse]][hID]);
            SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added house %d.", GetName(playerid), HouseInfo[playerInfo[playerid][pHouse]][hID]);
        }
        case 2: {
            if(playerInfo[playerid][pBusiness] == -1)
                return sendError(playerid, "Nu ai un business.");

            if(tradeItemsInserted[playerid][TYPE_BUSINESS])
                return sendError(playerid, "Ai plasat deja un business.");

            if(playerInfo[tradeWith[playerid]][pBusiness] != -1)
                return sendError(playerid, "Acel player are deja un business.");

            insertTradeItem(playerid, TYPE_BUSINESS, 1274, playerInfo[playerid][pBusiness]);

            SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added business %d.", bizzInfo[playerInfo[playerid][pBusiness]][bID]);
            SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added business %d.", GetName(playerid), bizzInfo[playerInfo[playerid][pBusiness]][bID]);
        }
        case 3: {
            if(tradeItemsInserted[playerid][TYPE_DRUGS]) 
                return sendError(playerid, "Ai plasat deja droguri.");

            if(tradeItemsInserted[tradeWith[playerid]][TYPE_DRUGS])
                return sendError(playerid, "Acel player a plasat deja droguri.");

            if(!playerInfo[playerid][pDrugs])
                return sendError(playerid, "Nu ai droguri.");

            Dialog_Show(playerid, TRADEADDDRUGS, DIALOG_STYLE_INPUT, "SERVER: Add Drugs", "Enter below the value of drugs you want to trade:", "Add", "Cancel");
        }
        case 4: {
            if(tradeItemsInserted[playerid][TYPE_MATERIALS]) 
                return sendError(playerid, "Ai plasat deja materiale.");

            if(tradeItemsInserted[tradeWith[playerid]][TYPE_MATERIALS])
                return sendError(playerid, "Acel player a plasat deja materiale.");

            if(!playerInfo[playerid][pMaterials])
                return sendError(playerid, "Nu ai materiale.");

            Dialog_Show(playerid, TRADEADDMATS, DIALOG_STYLE_INPUT, "SERVER: Add Materials", "Enter below the value of materials you want to trade:", "Add", "Cancel");
        }
        case 5: {
            if(!VECTOR_size(personalVehicles[playerid]))
                return sendError(playerid, "Nu ai vehicule personale.");

            pageIndexPersonalVehicles[playerid] = 0;
            showTradePersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
        }
    }
    return 1;
}

Dialog:TRADEADDMONEY(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInTrade(playerid))
        return 1;

    if(tradeItemsInserted[playerid][TYPE_MONEY])
        return sendError(playerid, "Ai plasat deja bani.");

    if(tradeItemsInserted[tradeWith[playerid]][TYPE_MONEY])
        return sendError(playerid, "Acel player a plasat deja bani.");

    if(!isnumeric(inputtext) || strlen(inputtext) > 20)
        return Dialog_Show(playerid, TRADEADDMONEY, DIALOG_STYLE_INPUT, "SERVER: Add Money", "Enter below the value of money you want to trade:", "Add", "Cancel");

    delimiteMoneyFromString(tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1], inputtext);

    if(tradeItemsMoney[playerid][0] > playerInfo[playerid][pBankStore] || (tradeItemsMoney[playerid][0] >= playerInfo[playerid][pBankStore] && tradeItemsMoney[playerid][1] > playerInfo[playerid][pBank]) || (tradeItemsMoney[playerid][0] <= 0 && tradeItemsMoney[playerid][1] <= 0))
        return Dialog_Show(playerid, TRADEADDMONEY, DIALOG_STYLE_INPUT, "SERVER: Add Money", "Enter below the value of money you want to trade:\n\n{ff0000}Invalid amount of money!", "Add", "Cancel");

    insertTradeItem(playerid, TYPE_MONEY, 1212, -1);

    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added $%s money.", formatMoney(tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1]));
    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added $%s money.", GetName(playerid), formatMoney(tradeItemsMoney[playerid][0], tradeItemsMoney[playerid][1]));
    return 1;
}

Dialog:TRADEADDDRUGS(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInTrade(playerid))
        return 1;

    if(tradeItemsInserted[playerid][TYPE_DRUGS]) 
        return sendError(playerid, "Ai plasat deja droguri.");

    if(tradeItemsInserted[tradeWith[playerid]][TYPE_DRUGS])
        return sendError(playerid, "Acel player a plasat deja droguri.");

    new drugs; if(sscanf(inputtext, "d", drugs))
        return Dialog_Show(playerid, TRADEADDDRUGS, DIALOG_STYLE_INPUT, "SERVER: Add Drugs", "Enter below the value of drugs you want to trade:", "Add", "Cancel");

    if(drugs <= 0 || drugs > playerInfo[playerid][pDrugs])
        return Dialog_Show(playerid, TRADEADDDRUGS, DIALOG_STYLE_INPUT, "SERVER: Add Drugs", "Enter below the value of drugs you want to trade:\n\n{ff0000}Invalid amount of drugs!", "Add", "Cancel");

    insertTradeItem(playerid, TYPE_DRUGS, 1279, drugs);

    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added %s drugs.", formatNumber(drugs));
    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added %s drugs.", GetName(playerid), formatNumber(drugs));
    return 1;
}

Dialog:TRADEADDMATS(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInTrade(playerid))
        return 1;

    if(tradeItemsInserted[playerid][TYPE_MATERIALS]) 
        return sendError(playerid, "Ai plasat deja materiale.");

    if(tradeItemsInserted[tradeWith[playerid]][TYPE_MATERIALS])
        return sendError(playerid, "Acel player a plasat deja materiale.");

    new mats; if(sscanf(inputtext, "d", mats))
        return Dialog_Show(playerid, TRADEADDMATS, DIALOG_STYLE_INPUT, "SERVER: Add Materials", "Enter below the value of materials you want to trade:", "Add", "Cancel");

    if(mats <= 0 || mats > playerInfo[playerid][pMaterials])
        return Dialog_Show(playerid, TRADEADDMATS, DIALOG_STYLE_INPUT, "SERVER: Add Materials", "Enter below the value of materials you want to trade:\n\n{ff0000}Invalid amount of materials!", "Add", "Cancel");

    insertTradeItem(playerid, TYPE_MATERIALS, 1575, mats);

    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added %s materials.", formatNumber(mats));
    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added %s materials.", GetName(playerid), formatNumber(mats));
    return 1;
}

Dialog:TRADEADDPERSONALVEHICLES(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInTrade(playerid))
        return 1;

    if(inputtext[0] == '>') {
        pageIndexPersonalVehicles[playerid] ++;
        return showTradePersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
    }
    else if(inputtext[0] == '<') { 
        pageIndexPersonalVehicles[playerid] = ((pageIndexPersonalVehicles[playerid] / 10) * 10) - 10;
        return showTradePersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
    }

    if(tradePersonalVehiclesCount[playerid] >= playerInfo[tradeWith[playerid]][pVehiclesSlots] - VECTOR_size(personalVehicles[tradeWith[playerid]]))
        return sendError(playerid, "Acel player nu are suficiente sloturi pentru vehicule.");

    if(haveTradePersonalVehicle(playerid, dialogPersonalVehicles[playerid][listitem]))
        return sendError(playerid, "Ai adaugat deja acest vehicul.");

    insertTradeItem(playerid, TYPE_VEHICLE, personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ModelID], dialogPersonalVehicles[playerid][listitem]);
    
    tradePersonalVehiclesCount[playerid] ++;

    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You added vehicle %s (ID %d, %.0fkm, %d days, %d/%d colors).", aVehicleNames[personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ModelID] - 400], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ID], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_Odometer], (gettime() - personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_Days]) / 86400, personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ColorOne], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ColorTwo]);
    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s added vehicle %s (ID %d, %.0fkm, %d days, %d/%d colors).", GetName(playerid), aVehicleNames[personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ModelID] - 400], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ID], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_Odometer], (gettime() - personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_Days]) / 86400, personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ColorOne], personalVehiclesInfo[dialogPersonalVehicles[playerid][listitem]][pv_ColorTwo]);
    return 1;
}

// ------------------------------------- //
//             Hooks                     //
// ------------------------------------- //

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    if(isPlayerInTrade(playerid)) {
        if(Dialog_IsOpened(playerid))
            return 1;

        if(playertextid == tradePlayerTDs[playerid][8]) {
            if(!getTradeItemsCount(playerid))
                return 1;

            if(tradePlayerReady[playerid])
                return sendError(playerid, "Nu poti face asta deoarece esti pregatit pentru incheierea negocierii.");

            if(tradeItemsIndex[playerid][0] >= TRADE_ITEMS_PAGE_LIMIT)
                PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][2], "your items (page: 1)");

            if(tradeItemsIndex[tradeWith[playerid]][1] >= TRADE_ITEMS_PAGE_LIMIT) {
                gString[0] = EOS;
                format(gString, sizeof gString, "%s's items (page: 1)", GetName(playerid));
                PlayerTextDrawSetString(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][3], gString);
            }

            clearTradeItems(playerid);

            SCM(playerid, COLOR_GREEN, "(Trade): {ffffff}You cleared all your items successfully.");
            SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}%s cleared his items.", GetName(playerid));
        }
        else if(playertextid == tradePlayerTDs[playerid][9]) {
            if(!tradePlayerReady[playerid]) {
                if(!getTradeItemsCount(playerid)) 
                    return sendError(playerid, "Trebuie sa ai minim 1 item plasat la negociere.");

                if(tradeReadyDelay[playerid] > gettime())
                    return 1;

                tradePlayerReady[playerid] = true;

                PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][9], 0xFF0000FF);
                PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][9], "CANCEL");
                PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][9]);

                gString[0] = EOS;
                format(gString, sizeof gString, "(Trade): {ffffff}%s is ready. (%d/2)", GetName(playerid), 1 + _:tradePlayerReady[tradeWith[playerid]]);

                SCM(tradeWith[playerid], COLOR_GREEN, gString);
                SCM(playerid, COLOR_GREEN, gString);

                if(tradePlayerReady[tradeWith[playerid]]) {
                    tradeTimerSeconds[playerid] = 10;

                    PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][11], "TRADE IN: 10");
                    PlayerTextDrawSetString(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][11], "TRADE IN: 10");
                    PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][11]);
                    PlayerTextDrawShow(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][11]);

                    tradeTimer[playerid] = tradeTimer[tradeWith[playerid]] = repeat tradeTimerCountdown(playerid); 
                }
            }
            else {
                tradePlayerReady[playerid] = false;

                PlayerTextDrawBoxColor(playerid, tradePlayerTDs[playerid][9], 932573439);
                PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][9], "READY");
                PlayerTextDrawShow(playerid, tradePlayerTDs[playerid][9]);

                if(tradePlayerReady[tradeWith[playerid]]) {
                    tradePlayerReady[tradeWith[playerid]] = false;

                    PlayerTextDrawHide(playerid, tradePlayerTDs[playerid][11]);
                    PlayerTextDrawHide(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][11]);

                    PlayerTextDrawBoxColor(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][9], 932573439);
                    PlayerTextDrawSetString(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][9], "READY");
                    PlayerTextDrawShow(tradeWith[playerid], tradePlayerTDs[tradeWith[playerid]][9]);

                    stop tradeTimer[playerid];
                    tradeTimer[tradeWith[playerid]] = Timer: 0;

                    SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}Trade countdown has been stopped by %s.", GetName(playerid));
                    SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}Trade countdown has been stopped by %s.", GetName(playerid));
                }

                tradeReadyDelay[playerid] = gettime() + 2;
            }
        }
        else if(playertextid == tradePlayerTDs[playerid][10]) {
            if(tradePlayerReady[playerid])
                return sendError(playerid, "Nu poti face asta deoarece esti pregatit pentru incheierea negocierii.");

            Dialog_Show(playerid, TRADEADDITEM, DIALOG_STYLE_LIST, "SERVER: Add Item", "Money (from bank)\nHouse\nBusiness\nDrugs\nMaterials\nPersonal Vehicles", "Add", "Cancel");
        }
        else if(playertextid == tradePlayerTDs[playerid][5] && tradeItemsIndex[playerid][0] >= TRADE_ITEMS_PAGE_LIMIT) {
            tradeItemsIndex[playerid][0] = ((tradeItemsIndex[playerid][0] / TRADE_ITEMS_PAGE_LIMIT) * TRADE_ITEMS_PAGE_LIMIT) - TRADE_ITEMS_PAGE_LIMIT;

            gString[0] = EOS;
            format(gString, sizeof gString, "your items (page: %d)", (tradeItemsIndex[playerid][0] / TRADE_ITEMS_PAGE_LIMIT) + 1);
            PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][2], gString);

            showTradeItems(playerid, playerid, tradeItemsIndex[playerid][0]);
        }
        else if(playertextid == tradePlayerTDs[playerid][4] && getTradeItemsCount(playerid) > tradeItemsIndex[playerid][0] + 1) {
            tradeItemsIndex[playerid][0] ++;

            gString[0] = EOS;
            format(gString, sizeof gString, "your items (page: %d)", (tradeItemsIndex[playerid][0] / TRADE_ITEMS_PAGE_LIMIT) + 1);
            PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][2], gString);
            
            showTradeItems(playerid, playerid, tradeItemsIndex[playerid][0]);
        }
        else if(playertextid == tradePlayerTDs[playerid][6] && tradeItemsIndex[playerid][1] >= TRADE_ITEMS_PAGE_LIMIT) {
            tradeItemsIndex[playerid][1] = ((tradeItemsIndex[playerid][1] / TRADE_ITEMS_PAGE_LIMIT) * TRADE_ITEMS_PAGE_LIMIT) - TRADE_ITEMS_PAGE_LIMIT;
            
            gString[0] = EOS;
            format(gString, sizeof gString, "%s's items (page: %d)", GetName(tradeWith[playerid]), (tradeItemsIndex[playerid][1] / TRADE_ITEMS_PAGE_LIMIT) + 1);
            PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][3], gString);

            showTradeItems(playerid, tradeWith[playerid], tradeItemsIndex[playerid][1]);
        } 
        else if(playertextid == tradePlayerTDs[playerid][7] && getTradeItemsCount(tradeWith[playerid]) > tradeItemsIndex[playerid][1] + 1) {
            tradeItemsIndex[playerid][1] ++;

            gString[0] = EOS;
            format(gString, sizeof gString, "%s's items (page: %d)", GetName(tradeWith[playerid]), (tradeItemsIndex[playerid][1] / TRADE_ITEMS_PAGE_LIMIT) + 1);
            PlayerTextDrawSetString(playerid, tradePlayerTDs[playerid][3], gString);
            
            showTradeItems(playerid, tradeWith[playerid], tradeItemsIndex[playerid][1]);
        }
    }
    return 1;
}

hook OP_ClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == INVALID_TEXT_DRAW && isPlayerInTrade(playerid)) {
        if(Dialog_IsOpened(playerid) || tradeTimer[playerid] != Timer: 0) 
            return SelectTextDraw(playerid, -1);

        SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}The trade has been canceled by %s.", GetName(playerid));
        SCM(playerid, COLOR_GREEN, "(Trade): {ffffff}You canceled the trade.");

        cancelTrade(playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(isPlayerInTrade(playerid)) {
        VECTOR_clear(tradeItems[playerid]);
        VECTOR_clear(tradeItems[tradeWith[playerid]]);

        destroyTradeTextdraws(playerid);

        stop tradeTimer[playerid];
        tradeTimer[tradeWith[playerid]] = Timer: 0;

        tradeWith[tradeWith[playerid]] = -1;

        CancelSelectTextDraw(tradeWith[playerid]);
        TogglePlayerControllableEx(tradeWith[playerid], true);

        SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}The trade has been canceled because %s has been disconnected from server.", GetName(playerid));
    } 
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if(isPlayerInTrade(playerid)) {
        SCMf(tradeWith[playerid], COLOR_GREEN, "(Trade): {ffffff}The trade has been canceled because %s died.", GetName(playerid));
        SCM(playerid, COLOR_GREEN, "(Trade): {ffffff}The trade has been canceled because you died.");

        stop tradeTimer[playerid];
        tradeTimer[tradeWith[playerid]] = Timer: 0;

        cancelTrade(playerid);
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
    tradeDelay[playerid] = tradeReadyDelay[playerid] = -1;
    return 1;
}