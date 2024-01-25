// ------------------------------------- //
//             Constants                 //
// ------------------------------------- //

#define MAX_HOUSES 199
#define RENTERS_DIALOG_PAGE_LIMIT 10

// ------------------------------------- //
//          Variables and enums          //
// ------------------------------------- //

enum e_houseInfo {
    hID, hBalance, hInterior, hOwnerID, hLevel, hRentPrice, hPrice, hIcon, hOwnerGameID, hDrugs,
    Float: hX, Float: hY, Float: hZ, Float: hExitX, Float: hExitY, Float: hExitZ,
    hDescription[50], hOwnerName[MAX_PLAYER_NAME],
    Text3D: hText, hPickup, bool: hLocked, hRentersCount
}

new 
    HouseInfo[MAX_HOUSES][e_houseInfo];

static enum e_rentersInfo {
    rSQLID, rName[MAX_PLAYER_NAME]
}

static 
    Vector:houseRenters[MAX_HOUSES],
    pageIndexHouseRenters[MAX_PLAYERS],
    selectedRenter[MAX_PLAYERS][e_rentersInfo];

// ------------------------------------- //
//              Query Functions          //
// ------------------------------------- //

query_function load_houses() {
    serverStuff[houses] = cache_num_rows();

    if(!serverStuff[houses])
        return print("[MYSQL INFO] No houses were found in the database.");

    for(new i = 0; i < serverStuff[houses]; ++i) {
        HouseInfo[i][hID] = i + 1;

        HouseInfo[i][hBalance] = cache_get_field_content_int(i, "Balance");
        HouseInfo[i][hInterior] = cache_get_field_content_int(i, "Interior");
        HouseInfo[i][hOwnerID] = cache_get_field_content_int(i, "OwnerID");
        HouseInfo[i][hLevel] = cache_get_field_content_int(i, "Level");
        HouseInfo[i][hRentPrice] = cache_get_field_content_int(i, "RentPrice");
        HouseInfo[i][hPrice] = cache_get_field_content_int(i, "Price");
        HouseInfo[i][hLocked] = bool:cache_get_field_content_int(i, "Locked");
        HouseInfo[i][hDrugs] = cache_get_field_content_int(i, "Drugs");

        HouseInfo[i][hX] = cache_get_field_content_float(i, "X");
        HouseInfo[i][hY] = cache_get_field_content_float(i, "Y");
        HouseInfo[i][hZ] = cache_get_field_content_float(i, "Z");

        HouseInfo[i][hExitX] = cache_get_field_content_float(i, "ExitX");
        HouseInfo[i][hExitY] = cache_get_field_content_float(i, "ExitY");
        HouseInfo[i][hExitZ] = cache_get_field_content_float(i, "ExitZ");

        cache_get_field_content(i, "OwnerName", HouseInfo[i][hOwnerName], SQL, MAX_PLAYER_NAME);
        cache_get_field_content(i, "Description", HouseInfo[i][hDescription], SQL, 50);

        HouseInfo[i][hPickup] = CreateDynamicPickup(HouseInfo[i][hOwnerID] != -1 ? 1272 : 1273, 23, HouseInfo[i][hX], HouseInfo[i][hY], HouseInfo[i][hZ], 0, 0);
        pickupInfo[HouseInfo[i][hPickup]][pk_House] = i;

        HouseInfo[i][hText] = CreateDynamic3DTextLabel("", -1, HouseInfo[i][hX], HouseInfo[i][hY], HouseInfo[i][hZ], 3.5);

        HouseInfo[i][hIcon] = CreateDynamicMapIcon(HouseInfo[i][hX], HouseInfo[i][hY], HouseInfo[i][hZ], HouseInfo[i][hOwnerID] != -1 ? 32 : 31, -1, -1, -1, -1, 70.0);
    
        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT `ID`, `Name` FROM `server_users` WHERE `Rent` = %d", HouseInfo[i][hID]);
        mysql_tquery(SQL, gQuery, "loadHouseRenters", "d", i);
    }

    return printf("[MYSQL LOADED] Houses loaded: %d", serverStuff[houses]);
}

query_function loadHouseRenters(const houseid) {
    new const rows = cache_num_rows();

    if(!rows) {
        updateHouseLabel(houseid);
        return 1;
    }

    new renters[e_rentersInfo];

    for(new i = 0; i < rows; ++i) {
        renters[rSQLID] = cache_get_field_content_int(i, "ID");

        cache_get_field_content(i, "Name", renters[rName], SQL, MAX_PLAYER_NAME);

        VECTOR_push_back_arr(houseRenters[houseid], renters);
    }

    HouseInfo[houseid][hRentersCount] = rows;

    updateHouseLabel(houseid);
    return 1;
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

updateHouseLabel(const houseid) {
    gString[0] = EOS;
    format(gString, sizeof gString, "House {1C8A15}#%d\n%s\n{FFFFFF}Owned by {1C8A15}%s\n{FFFFFF}Level: {1C8A15}%d\n{FFFFFF}Tenants: {1C8A15}%d\n", HouseInfo[houseid][hID], HouseInfo[houseid][hDescription], HouseInfo[houseid][hOwnerName], HouseInfo[houseid][hLevel], HouseInfo[houseid][hRentersCount]);

    if(HouseInfo[houseid][hRentPrice] != 0)
        format(gString, sizeof gString, "%s{FFFFFF}Rentable, for {1C8A15}$%s\n", gString, formatNumber(HouseInfo[houseid][hRentPrice]));

    if(HouseInfo[houseid][hPrice] != 0)
        format(gString, sizeof gString, "%s{FFFFFF}This house is for sell.\nPrice: {1C8A15}$%s\n{FFFFFF}Type {1C8A15}[/buyhouse]{FFFFFF} for buy this house.\n", gString, formatNumber(HouseInfo[houseid][hPrice]));

    return UpdateDynamic3DTextLabelText(HouseInfo[houseid][hText], -1, gString);
}

playerEnterHouse(const playerid, houseid) {
    SetPlayerInterior(playerid, HouseInfo[houseid][hInterior]); 
    SetPlayerPos(playerid, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY], HouseInfo[houseid][hExitZ]); 
    SetPlayerVirtualWorld(playerid, HouseInfo[houseid][hID]); 
    SetPlayerFacingAngle(playerid, 0.0); 
    SetPVarInt(playerid, "in_hq", 1);

    TogglePlayerControllableEx(playerid, false); 
    defer freezeTimer[2000](playerid); 

    playerVars[playerid][var_inhouse] = houseid;
    playerVars[playerid][var_house_delay] = gettime() + 5;
    return 1;
}

playerLeaveHouse(const playerid, const houseid) {
    SetPlayerPos(playerid, HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]); 
    SetPlayerInterior(playerid, 0); 
    SetPlayerVirtualWorld(playerid, 0); 
    SetPVarInt(playerid, "in_hq", 0);

    playerVars[playerid][var_inhouse] = -1;
    return 1;
}

getNearbyHouse(const playerid, const Float:range) {
    new 
        nearbyPickup[1] = -1,
        Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerid, X, Y, Z);
    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, range);

    if(nearbyPickup[0] == -1)
        return -1;
    
    return pickupInfo[nearbyPickup[0]][pk_House];
}

showHouseRenters(const playerid, const houseid, &index_start) {
    gDialog = "#\tName\tStatus\n";

    for(new renters[e_rentersInfo]; index_start < HouseInfo[houseid][hRentersCount]; ++index_start) {
        VECTOR_get_arr(houseRenters[houseid], index_start, renters);

        format(gDialog, sizeof gDialog, "%s%d.\t%s\t%s\n", gDialog, index_start + 1, renters[rName], MAP_contains_val(playersSQLID, renters[rSQLID]) ? "Online" : "Offline");

        if(index_start % RENTERS_DIALOG_PAGE_LIMIT == RENTERS_DIALOG_PAGE_LIMIT - 1) {
            if(HouseInfo[houseid][hRentersCount] > index_start + 1)
                strcat(gDialog, "> Next Page\n");

            break;
        }
    }

    if(index_start > RENTERS_DIALOG_PAGE_LIMIT) 
        strcat(gDialog, "< Previous Page");

    gString[0] = EOS;
    format(gString, sizeof gString, "SERVER: Renters (page: %d)", (index_start / RENTERS_DIALOG_PAGE_LIMIT) + 1);

    return Dialog_Show(playerid, HOUSERENTERS, DIALOG_STYLE_TABLIST_HEADERS, gString, gDialog, "Select", "Cancel");
}

removeHouseRenter(const playerid) {
    new rentData[e_rentersInfo];

    rentData[rSQLID] = playerInfo[playerid][pSQLID];
    strcat(rentData[rName], GetName(playerid));

    VECTOR_remove_arr(houseRenters[playerInfo[playerid][pRent]], rentData);

    HouseInfo[playerInfo[playerid][pRent]][hRentersCount] --;
    updateHouseLabel(playerInfo[playerid][pRent]);

    playerInfo[playerid][pRent] = -1;
}

addHouseRenter(const playerid, const houseid) {
    new rentData[e_rentersInfo];

    rentData[rSQLID] = playerInfo[playerid][pSQLID];
    strcat(rentData[rName], GetName(playerid));

    VECTOR_push_back_arr(houseRenters[houseid], rentData);

    HouseInfo[houseid][hRentersCount] ++;
    updateHouseLabel(houseid);

    playerInfo[playerid][pRent] = houseid;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:sellhousetostate(playerid, params[], help) {
    if(playerInfo[playerid][pHouse] == -1)
        return sendError(playerid, "Nu ai o casa.");

    return Dialog_Show(playerid, HOUSESELLTOSTATE, DIALOG_STYLE_MSGBOX, "SERVER: Sell House", "Esti sigur ca vrei sa iti vinzi casa (id: %d) la stat pentru $5.000.000?", "Ok", "Cancel", HouseInfo[playerInfo[playerid][pHouse]][hID]);
}

YCMD:gotohouse(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai acces la aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/gotohouse <houseid>");

    new houseid = strval(params);

    if(serverStuff[houses] < houseid || houseid <= 0)
        return sendError(playerid, "Acea casa nu exista pe server.");

    houseid --;

    SetPlayerPos(playerid, HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]); 
    SetPlayerVirtualWorld(playerid, 0); 
    SetPlayerInterior(playerid, 0); 
    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s has teleported to house #%d.", GetName(playerid), HouseInfo[houseid][hID]);
}

YCMD:edithouse(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai acces la aceasta comanda.");

    new houseid, value; gString[0] = EOS; if(sscanf(params, "ds[64]d", houseid, gString, value)) {
        sendUsage(playerid, "/edithouse <houseid> <tag> <value>"); 
        return SCM(playerid, COLOR_GREY, "Available tags: price, level, ownerid (-1 = AdmBot), locked (0/1), position.");
    }

    if(serverStuff[houses] < houseid || houseid <= 0)
        return sendError(playerid, "Acea casa este inexistenta.");

    houseid --;

    if(!strcmp(gString, "price") || !strcmp(gString, "level")) {
        new const bool:priceStr = bool:!strcmp(gString, "price");

        if(priceStr) {
            HouseInfo[houseid][hPrice] = value;
            va_mysql_tquery("UPDATE `server_houses` SET `Price` = %d WHERE `ID` = %d", value, HouseInfo[houseid][hID]),
            SCMf(playerid, -1,"The house %d was edited succesfully. (price: %d)", HouseInfo[houseid][hID], value);
        }
        else {
            HouseInfo[houseid][hLevel] = value;
            va_mysql_tquery("UPDATE `server_houses` SET `Level` = %d WHERE `ID` = %d", value, HouseInfo[houseid][hID]);
            SCMf(playerid, -1, "The house %d was edited succesfully. (level: %d)", HouseInfo[houseid][hID], value);
        }
    }
    else if(!strcmp(gString, "ownerid")) {
        if(value == -1) {
            HouseInfo[houseid][hOwnerID] = -1; 
            strcpy(HouseInfo[houseid][hOwnerName], "AdmBot");

            va_mysql_tquery("UPDATE `server_users`, `server_houses` SET `server_houses`.`OwnerID` = -1, `server_houses`.`OwnerName` = 'AdmBot', `server_users`.`House` = -1 WHERE `server_houses`.`ID` = %d AND `server_users`.`House` = %d", HouseInfo[houseid][hID], HouseInfo[houseid][hID]); 

            return updateHouseLabel(houseid);
        }

        if(!IsPlayerLogged(value))
            return sendError(playerid, "Acel player nu este logat.");

        HouseInfo[houseid][hOwnerID] = playerInfo[value][pSQLID];
        HouseInfo[houseid][hOwnerGameID] = value;
        playerInfo[value][pHouse] = houseid;
        strcpy(HouseInfo[houseid][hOwnerName], GetName(value), MAX_PLAYER_NAME);

        gQuery[0] = EOS; 
        mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users`, `server_houses` SET `server_houses`.`OwnerID` = %d, `server_houses`.`OwnerName` = '%e', `server_users`.`House` = %d WHERE `server_houses`.`ID` = %d AND `server_users`.`ID` = %d", playerInfo[value][pSQLID], playerInfo[value][pName], HouseInfo[houseid][hID], HouseInfo[houseid][hID], playerInfo[value][pSQLID]); 
        mysql_tquery(SQL, gQuery, "", "");

        SCMf(playerid, -1, "The house %d was edited succesfully. (owner: %s)", HouseInfo[houseid][hID], GetName(value));
    }
    else if(!strcmp(gString, "locked")) {
        if(value < 0 || value > 1)
            return sendError(playerid, "Invalid value! (ex. 0 / 1)");

        HouseInfo[houseid][hLocked] = bool:value;

        va_mysql_tquery("UPDATE `server_houses` SET `Locked` = %d WHERE `ID` = %d", value, HouseInfo[houseid][hID]);

        SCMf(playerid, -1, "The house %d was edited succesfully. (locked: %s)", HouseInfo[houseid][hID], !value ? "no" : "yes");
    }
    else if(!strcmp(gString, "position")) {
        GetPlayerPos(playerid, HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]); 

        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, HouseInfo[houseid][hPickup], HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]);
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, HouseInfo[houseid][hText], HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]);
        Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, HouseInfo[houseid][hIcon], HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]);

        va_mysql_tquery("UPDATE `server_houses` SET `X` = %f, `Y` = %f, `Z` = %f WHERE `ID` = %d", HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ], HouseInfo[houseid][hID]);

        SCMf(playerid, -1, "Position for house %d was succesfully edited. (X: %0.2f | Y: %0.2f | Z: %0.2f)", HouseInfo[houseid][hID], HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]);
        return 1;
    }
    else return sendUsage(playerid, "/edithouse <houseid> <tag> <value>"), SCM(playerid, COLOR_GREY, "Available tags: price, level, ownerid (999 = AdmBot), locked (0/1), position.");

    return updateHouseLabel(houseid);
}

YCMD:buyhouse(playerid, params[], help) {
    if(playerInfo[playerid][pHouse] != -1)
        return sendError(playerid, "Ai deja o casa.");

    if(playerInfo[playerid][pRent] != -1)
        return sendError(playerid, "Nu poti cumpara o casa deoarece stai in chirie, foloseste /unrentroom.");

    new const houseid = getNearbyHouse(playerid, 2.0);

    if(houseid == -1)
        return 1;

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]))
        return 1;

    if(HouseInfo[houseid][hPrice] == 0)
        return sendError(playerid, "Aceasta casa nu este de vanzare.");

    if(GetMoney(playerid) < HouseInfo[houseid][hPrice] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai banii necesari pentru a cumpara aceasta casa.");

    if(playerInfo[playerid][pLevel] < HouseInfo[houseid][hLevel])
        return sendError(playerid, "Nu ai level-ul necesar pentru a cumpara aceasta casa. Iti trebuie level %d.", HouseInfo[houseid][hLevel]);

    new const price = HouseInfo[houseid][hPrice];

    if(HouseInfo[houseid][hOwnerID] != -1) {
        if(HouseInfo[houseid][hOwnerGameID] == -1) {
            va_mysql_tquery("UPDATE `server_users` SET `SpawnType` = 1, `House` = -1, `Money` = `Money` + %d, `MoneyStore` = IF(`Money` >= 1000000000, `MoneyStore` + 1, `MoneyStore`), `Money` = IF(`Money` >= 1000000000, `Money` - 1000000000, `Money`) WHERE `ID` = %d", price, HouseInfo[houseid][hOwnerID]);

            insertEmail(_, HouseInfo[houseid][hOwnerName], _, "%s purchased your house. Price: $%s.", GetName(playerid), formatNumber(price));
        }
        else {
            if(isPlayerInTrade(HouseInfo[houseid][hOwnerGameID]))
                return sendError(playerid, "Nu poti face asta deoarece acel player este in cursul unei negocieri.");
            
            addMoney(HouseInfo[houseid][hOwnerGameID], GetMilliards(HouseInfo[houseid][hOwnerGameID]), GetMoney(HouseInfo[houseid][hOwnerGameID]), 0, price, false);
            
            playerInfo[HouseInfo[houseid][hOwnerGameID]][pHouse] = -1;
            playerInfo[HouseInfo[houseid][hOwnerGameID]][pSpawnType] = SPAWN_TYPE_NORMAL;

            va_mysql_tquery("UPDATE `server_users` SET `SpawnType` = 1, `House` = -1, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[HouseInfo[houseid][hOwnerGameID]][pMoneyStore], playerInfo[HouseInfo[houseid][hOwnerGameID]][pMoney], playerInfo[HouseInfo[houseid][hOwnerGameID]][pSQLID]);
            
            SCMf(HouseInfo[houseid][hOwnerGameID], COLOR_YELLOW, "* %s purchased your house for $%s.", GetName(playerid), formatNumber(price));

            insertEmail(HouseInfo[houseid][hOwnerGameID], HouseInfo[houseid][hOwnerName], _, "%s purchased your house. Price: $%s.", GetName(playerid), formatNumber(price));
        }
    }

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price, false);

    strcpy(HouseInfo[houseid][hOwnerName], GetName(playerid), MAX_PLAYER_NAME);
    playerInfo[playerid][pHouse] = houseid;
    HouseInfo[houseid][hOwnerGameID] = playerid;
    HouseInfo[houseid][hOwnerID] = playerInfo[playerid][pSQLID];
    HouseInfo[houseid][hPrice] = 0;
    
    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_houses`, `server_users` SET server_houses.OwnerName = '%e', server_houses.OwnerID = %d, server_houses.Price = 0, server_users.MoneyStore = %d, server_users.Money = %d, server_users.House = %d WHERE server_houses.ID = %d AND server_users.ID = %d", HouseInfo[houseid][hOwnerName], HouseInfo[houseid][hOwnerID], GetMilliards(playerid), GetMoney(playerid), HouseInfo[houseid][hID], HouseInfo[houseid][hID], playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", ""); 

    updateHouseLabel(houseid); 
    Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseInfo[houseid][hPickup], E_STREAMER_MODEL_ID, 1272);
    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, HouseInfo[houseid][hIcon], E_STREAMER_TYPE, 32);

    return SCMf(playerid, COLOR_YELLOW, "* You purchased house %d for $%s succesfully!", HouseInfo[houseid][hID], formatNumber(price));
}

YCMD:hmenu(playerid, params[], help) {
    if(playerInfo[playerid][pHouse] == -1)
        return sendError(playerid, "Nu detii o casa.");

    return Dialog_Show(playerid, HOUSEMENU, DIALOG_STYLE_LIST, "SERVER: House Menu", "House Description\nHouse Lock\nSet Rent Price\nRenters\nHouse Balance\nSet Sell Price\nManage House Drugs", "Select", "Cancel");
}

YCMD:rentroom(playerid, params[], help) {
    if(playerInfo[playerid][pRent] != -1)
        return sendError(playerid, "Esti deja intr-o chirie, tasteaza /unrentroom.");

    if(playerInfo[playerid][pHouse] != -1)
        return sendError(playerid, "Nu poti sta in chirie deoarece detii o casa.");

    new houseid = getNearbyHouse(playerid, 2.0);

    if(houseid == -1)
        return 1;

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, HouseInfo[houseid][hX], HouseInfo[houseid][hY], HouseInfo[houseid][hZ]))
        return 1;

    if(HouseInfo[houseid][hRentPrice] == 0)
        return sendError(playerid, "Aceasta casa nu permite chiriasi.");

    if(GetMoney(playerid) < HouseInfo[houseid][hRentPrice] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai destui bani pentru a sta in chirie aici.");

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, HouseInfo[houseid][hRentPrice], false);
    va_GameTextForPlayer(playerid, "~R~-$%d", 2500, 1, HouseInfo[houseid][hRentPrice]);

    addHouseRenter(playerid, houseid);

    playerInfo[playerid][pSpawnType] = SPAWN_TYPE_HOUSE; 
    HouseInfo[houseid][hBalance] += HouseInfo[houseid][hRentPrice];

    va_mysql_tquery("UPDATE `server_houses`, `server_users` SET server_houses.Balance = %d, server_users.Rent = %d, server_users.SpawnType = 2, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_houses.ID = %d AND server_users.ID = %d", HouseInfo[houseid][hBalance], HouseInfo[houseid][hID], playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], HouseInfo[houseid][hID], playerInfo[playerid][pSQLID]);
    
    return SCMf(playerid, COLOR_GREY, "* Felicitari! Acum esti unul dintre chiriasii casei %d.", HouseInfo[houseid][hID]);
}

YCMD:unrentroom(playerid, params[], help) {
    if(playerInfo[playerid][pRent] == -1)
        return 1; 

    removeHouseRenter(playerid);

    playerInfo[playerid][pSpawnType] = SPAWN_TYPE_NORMAL;

    va_mysql_tquery("UPDATE `server_users` SET `Rent` = -1, `SpawnType` = 1 WHERE `ID` = %d", playerInfo[playerid][pSQLID]); 
    
    return SCM(playerid, COLOR_GREY, "* Acum nu mai esti chirias.");
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:HOUSESELLPRICE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, HOUSESELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell House", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi casa,\ndaca introduci $0, casa nu se va pune la vanzare:", "Set", "Cancel");

    new const money = strval(inputtext);

    if(money < 0 || money >= 999999999) {
        sendError(playerid, "Suma de bani trebuie sa fie cuprinsa intre $0 si $999.999.999."); 
        return Dialog_Show(playerid, HOUSESELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell House", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi casa,\ndaca introduci $0, casa nu se va pune la vanzare:", "Set", "Cancel");
    }

    if(money == HouseInfo[playerInfo[playerid][pHouse]][hPrice]) {
        sendError(playerid, "Pretul casei este deja $%s.", formatNumber(money)); 
        return Dialog_Show(playerid, HOUSESELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell House", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi casa,\ndaca introduci $0, casa nu se va pune la vanzare:", "Set", "Cancel");
    }

    HouseInfo[playerInfo[playerid][pHouse]][hPrice] = money; 

    va_mysql_tquery("UPDATE `server_houses` SET `Price` = %d WHERE `ID` = %d", money, HouseInfo[playerInfo[playerid][pHouse]][hID]); 

    updateHouseLabel(playerInfo[playerid][pHouse]); 

    return SCMf(playerid, COLOR_GREY, "* You changed succesfully the sell price for your house to $%s.", formatNumber(money));
}

Dialog:HOUSESELLTOSTATE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(isPlayerInTrade(playerid))
        return sendError(playerid, "Nu poti face asta deoarece esti in cursul unei negocieri.");

    new const houseid = playerInfo[playerid][pHouse];

    strcpy(HouseInfo[houseid][hOwnerName], "AdmBot"); 
    strcpy(HouseInfo[houseid][hDescription], "The State House"); 
    
    HouseInfo[houseid][hPrice] = 10000000; 
    HouseInfo[houseid][hRentPrice] = 500; 
    HouseInfo[houseid][hLocked] = false; 
    HouseInfo[houseid][hOwnerID] = HouseInfo[houseid][hOwnerGameID] = playerInfo[playerid][pHouse] = -1; 
    playerInfo[playerid][pSpawnType] = SPAWN_TYPE_NORMAL;
    
    va_mysql_tquery("UPDATE `server_houses`, `server_users` SET server_houses.OwnerID = -1, server_houses.OwnerName = 'AdmBot', server_houses.Description = 'The State House', server_houses.Price = 10000000, server_houses.Locked = 0, server_users.House = -1, server_users.SpawnType = 1, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_houses.ID = %d AND server_users.ID = %d", GetMilliards(playerid), GetMoney(playerid), HouseInfo[houseid][hID], playerInfo[playerid][pSQLID]);
    
    updateHouseLabel(houseid); 
    Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseInfo[houseid][hPickup], E_STREAMER_MODEL_ID, 1273);
    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, HouseInfo[houseid][hIcon], E_STREAMER_TYPE, 31);

    return SCMf(playerid, COLOR_YELLOW, "* Ti-ai vandut casa %d cu succes la stat si ai primit $5.000.000.", HouseInfo[houseid][hID]);
}

Dialog:HOUSEMENU(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const houseid = playerInfo[playerid][pHouse];

    switch(listitem) {
        case 0: {
            Dialog_Show(playerid, HOUSEMENU1, DIALOG_STYLE_INPUT, "SERVER: House Description", "Introdu descrierea pe care vrei sa o setezi la casa ta:", "Set", "Cancel");
        }
        case 1: {
            HouseInfo[houseid][hLocked] = !HouseInfo[houseid][hLocked]; 

            va_mysql_tquery("UPDATE `server_houses` SET `Locked` = %d WHERE `ID` = %d", HouseInfo[houseid][hLocked], HouseInfo[houseid][hID]);

            SCM(playerid, COLOR_GREY, HouseInfo[houseid][hLocked] ? "* Casa ta a fost incuiata." : "* Casa ta a fost descuiata."); 
        }
        case 2: {
            Dialog_Show(playerid, HOUSEMENU2, DIALOG_STYLE_INPUT, "SERVER: Rent Price", "Introdu suma de bani (0 = fara) pentru chiria casei tale:", "Set", "Cancel");
        }
        case 3: {
            if(!HouseInfo[houseid][hRentersCount])
                return sendError(playerid, "Casa ta nu are chiriasi.");

            pageIndexHouseRenters[playerid] = 0;
            showHouseRenters(playerid, houseid, pageIndexHouseRenters[playerid]);
        }
        case 4: {
            if(playerVars[playerid][var_inhouse] != playerInfo[playerid][pHouse])
                return sendError(playerid, "Trebuie sa fii in casa ta pentru a face asta.");

            if(HouseInfo[houseid][hBalance] <= 0)
                return sendError(playerid, "Nu ai bani in casa.");

            Dialog_Show(playerid, HOUSEBALANCE, DIALOG_STYLE_INPUT, "SERVER: House Balance", "Balanta casei in momentul acesta este de $%s.\nIntrodu suma de bani pe care vrei sa o scoti:", "Withdraw", "Cancel", formatNumber(HouseInfo[houseid][hBalance]));
        }
        case 5: {
            Dialog_Show(playerid, HOUSESELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell House", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi casa\n(daca introduci $0, casa nu se va pune la vanzare):", "Set", "Cancel");
        }
        case 6: {
            Dialog_Show(playerid, HOUSEMANAGEDRUGS, DIALOG_STYLE_LIST, "SERVER: Manage House Drugs", "Withdraw Drugs\nDeposit Drugs", "Select", "Back");
        }
    }
    return 1;
}

Dialog:HOUSEMANAGEDRUGS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return Dialog_Show(playerid, HOUSEMENU, DIALOG_STYLE_LIST, "SERVER: House Menu", "House Description\nHouse Lock\nSet Rent Price\nRenters\nHouse Balance\nSet Sell Price\nManage House Drugs", "Select", "Cancel");

    if(playerVars[playerid][var_inhouse] != playerInfo[playerid][pHouse])
        return sendError(playerid, "Trebuie sa fii in casa ta pentru a face asta.");

    if(!listitem) {
        if(HouseInfo[playerInfo[playerid][pHouse]][hDrugs] <= 0)
            return sendError(playerid, "Nu ai droguri depozitate in casa.");
        
        SetPVarInt(playerid, "choosedListitem", !listitem);

        return Dialog_Show(playerid, HOUSEDRUGS, DIALOG_STYLE_INPUT, "SERVER: Withdraw Drugs", "In momentul acesta sunt %d droguri depozitate.\nIntrodu suma de droguri pe care vrei sa o scoti:", "Withdraw", "Cancel", HouseInfo[playerInfo[playerid][pHouse]][hDrugs]);
    }

    SetPVarInt(playerid, "choosedListitem", !listitem);

    return Dialog_Show(playerid, HOUSEDRUGS, DIALOG_STYLE_INPUT, "SERVER: Deposit Drugs", "In momentul acesta sunt %d droguri depozitate.\nIntrodu suma de droguri pe care vrei sa o depozitezi:", "Deposit", "Cancel", HouseInfo[playerInfo[playerid][pHouse]][hDrugs]);
}

Dialog:HOUSEDRUGS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return DeletePVar(playerid, "choosedListitem");

    new const drugs = strval(inputtext);

    if(GetPVarInt(playerid, "choosedListitem")) {
        if(!isnumeric(inputtext) || drugs < 1)
            return Dialog_Show(playerid, HOUSEDRUGS, DIALOG_STYLE_INPUT, "SERVER: Withdraw Drugs", "In momentul acesta sunt %d droguri depozitate.\nIntrodu suma de droguri pe care vrei sa o scoti:", "Withdraw", "Cancel", HouseInfo[playerInfo[playerid][pHouse]][hDrugs]);

        if(drugs > HouseInfo[playerInfo[playerid][pHouse]][hDrugs])
            return sendError(playerid, "Nu sunt destule droguri in casa.");

        HouseInfo[playerInfo[playerid][pHouse]][hDrugs] -= drugs; 
        playerInfo[playerid][pDrugs] += drugs;

        SCMf(playerid, COLOR_YELLOW, "* Ai extras %d droguri din casa ta. Acum au mai ramas %d droguri depozitate in casa.", drugs, HouseInfo[playerInfo[playerid][pHouse]][hDrugs]);
    }
    else {
        if(!isnumeric(inputtext) || drugs < 1)
            return Dialog_Show(playerid, HOUSEDRUGS, DIALOG_STYLE_INPUT, "SERVER: Deposit Drugs", "In momentul acesta sunt %d droguri depozitate.\nIntrodu suma de droguri pe care vrei sa o depozitezi:", "Deposit", "Cancel", HouseInfo[playerInfo[playerid][pHouse]][hDrugs]);

        if(drugs > playerInfo[playerid][pDrugs])
            return sendError(playerid, "Nu ai destule droguri in mana.");

        playerInfo[playerid][pDrugs] -= drugs;
        HouseInfo[playerInfo[playerid][pHouse]][hDrugs] += drugs; 

        SCMf(playerid, COLOR_YELLOW, "* Ai depozitat %d droguri in casa ta.", drugs);
    } 

    va_mysql_tquery("UPDATE `server_users`, `server_houses` SET server_users.Drugs = %d, server_houses.Drugs = %d WHERE server_users.ID = %d AND server_houses.ID = %d", playerInfo[playerid][pDrugs], HouseInfo[playerInfo[playerid][pHouse]][hDrugs], playerInfo[playerid][pSQLID], HouseInfo[playerInfo[playerid][pHouse]][hID]);

    DeletePVar(playerid, "choosedListitem"); 
    return 1;
}

Dialog:HOUSEBALANCE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, HOUSEBALANCE, DIALOG_STYLE_INPUT, "SERVER: House Balance", "Balanta casei in momentul acesta este de $%s.\nIntrodu suma de bani pe care vrei sa o scoti:", "Withdraw", "Cancel", formatNumber(HouseInfo[playerInfo[playerid][pHouse]][hBalance]));

    new const money = strval(inputtext);

    if(money > HouseInfo[playerInfo[playerid][pHouse]][hBalance] || money < 1)
        return sendError(playerid, "Nu ai aceasta suma de bani in casa.");

    HouseInfo[playerInfo[playerid][pHouse]][hBalance] -= money;

    addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, money, false);
    
    va_mysql_tquery("UPDATE `server_houses`, `server_users` SET server_houses.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_houses.ID = %d AND server_users.ID = %d", HouseInfo[playerInfo[playerid][pHouse]][hBalance], GetMilliards(playerid), GetMoney(playerid), HouseInfo[playerInfo[playerid][pHouse]][hID], playerInfo[playerid][pSQLID]);

    return SCMf(playerid, COLOR_YELLOW, "* Ai extras $%s bani din casa ta. Acum mai sunt $%s bani in casa.", formatNumber(money), formatNumber(HouseInfo[playerInfo[playerid][pHouse]][hBalance]));
}

Dialog:HOUSERENTERS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(inputtext[0] == '>') {
        pageIndexHouseRenters[playerid] ++;
        return showHouseRenters(playerid, playerInfo[playerid][pHouse], pageIndexHouseRenters[playerid]);
    }
    else if(inputtext[0] == '<') {
        pageIndexHouseRenters[playerid] = ((pageIndexHouseRenters[playerid] / RENTERS_DIALOG_PAGE_LIMIT) * RENTERS_DIALOG_PAGE_LIMIT) - RENTERS_DIALOG_PAGE_LIMIT;
        return showHouseRenters(playerid, playerInfo[playerid][pHouse], pageIndexHouseRenters[playerid]);
    }

    VECTOR_get_arr(houseRenters[playerInfo[playerid][pHouse]], ((pageIndexHouseRenters[playerid] / RENTERS_DIALOG_PAGE_LIMIT) * RENTERS_DIALOG_PAGE_LIMIT) + listitem, selectedRenter[playerid]);

    return Dialog_Show(playerid, HOUSERENTERS1, DIALOG_STYLE_MSGBOX, "SERVER: Renters", "Esti sigur ca vrei sa-l dai afara pe %s din chirie?", "Kick", "Cancel", selectedRenter[playerid][rName]);
}

Dialog:HOUSERENTERS1(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(MAP_contains_val(playersSQLID, selectedRenter[playerid][rSQLID])) {
        new const renterid = MAP_get_val_val(playersSQLID, selectedRenter[playerid][rSQLID]);

        playerInfo[renterid][pRent] = -1; 
        playerInfo[renterid][pSpawnType] = SPAWN_TYPE_NORMAL; 

        SCMf(renterid, COLOR_YELLOW, "* Ai fost dat afara din chirie de %s.", GetName(playerid));
    }

    VECTOR_remove_arr(houseRenters[playerInfo[playerid][pHouse]], selectedRenter[playerid]);

    HouseInfo[playerInfo[playerid][pHouse]][hRentersCount] --;
    updateHouseLabel(playerInfo[playerid][pHouse]);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Rent` = -1, `SpawnType` = 1 WHERE `ID` = %d", selectedRenter[playerid][rSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");

    return SCMf(playerid, COLOR_YELLOW, "* L-ai dat afara cu succes pe %s din chirie.", selectedRenter[playerid][rName]);
}

Dialog:HOUSEMENU1(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const length = strlen(inputtext);

    if(length < 5 || length > 40)
        return sendError(playerid, "Descrierea trebuie sa fie cuprinsa intre 5 si 40 caractere.");

    for(new i = 0; inputtext[i]; ++i) {
        if(inputtext[i] == '{' || inputtext[i] == '}')
            return Dialog_Show(playerid, HOUSEMENU1, DIALOG_STYLE_INPUT, "SERVER: House Description", "Introdu descrierea pe care vrei sa o setezi la casa ta:", "Set", "Cancel");
    }

    strcpy(HouseInfo[playerInfo[playerid][pHouse]][hDescription], inputtext); 

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_houses` SET `Description` = '%e' WHERE `ID` = %d", inputtext, HouseInfo[playerInfo[playerid][pHouse]][hID]);
    mysql_tquery(SQL, gQuery, "", "");

    updateHouseLabel(playerInfo[playerid][pHouse]);

    return SCM(playerid, COLOR_GREY, "* Descrierea casei tale a fost setata cu succes.");
}

Dialog:HOUSEMENU2(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, HOUSEMENU2, DIALOG_STYLE_INPUT, "SERVER: Rent Price", "Introdu suma de bani (0 = fara) pentru chiria casei tale:", "Set", "Cancel");

    new const rentPrice = strval(inputtext);

    if(rentPrice > 5000 || rentPrice < 0)
        return sendError(playerid, "Pretul chiriei trebuie sa fie cuprins intre $0 si $5000.");

    HouseInfo[playerInfo[playerid][pHouse]][hRentPrice] = rentPrice; 

    va_mysql_tquery("UPDATE `server_houses` SET `RentPrice` = %d WHERE `ID` = %d", HouseInfo[playerInfo[playerid][pHouse]][hRentPrice], HouseInfo[playerInfo[playerid][pHouse]][hID]); 

    updateHouseLabel(playerInfo[playerid][pHouse]); 

    return SCMf(playerid, COLOR_GREY, "* Chiria a fost setata cu succes la $%s.", formatNumber(rentPrice));
}
