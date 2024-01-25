// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_BUSINESS 27

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

new const bizzTypeName[][] = {
    "Bank", "Clothes Store", "Gun Shop", "24/7", "Food Shop", "Sex Shop", "Bar", "CNN", "GYM", "Casino", "Pay & Spray", "Vehicle Rent", "Gas Station", "Mod Shop", "Bet House"
};

static const bizzIconIDs[] = {
    52, 45, 6, 17, 10, 38, 49, 16, 54, 25, 63, 55, 27, 27, 25
};

enum e_businessInfo {
    bID, bType, bBalance, bLevel, bPrice, bFee, bOwnerSQLID, bOwnerName[MAX_PLAYER_NAME], bOwnerGameID, 
    Float: bX, Float: bY, Float: bZ, Float: bExitX, Float: bExitY, Float: bExitZ,
    bPickup, bIcon, Text3D: bLabel, bDescription[50], bool: bLocked
}

new bizzInfo[MAX_BUSINESS][e_businessInfo];

// ------------------------------------- //
//            Query Functions            //
// ------------------------------------- //

query_function load_business() {
    serverStuff[business] = cache_num_rows();

    if(!serverStuff[business])
        return print("[MYSQL INFO] No business were found in the database.");

    for(new i = 0; i < serverStuff[business]; i++) {
        bizzInfo[i][bID] = i + 1;

        bizzInfo[i][bType] = cache_get_field_content_int(i, "Type");
        bizzInfo[i][bBalance] = cache_get_field_content_int(i, "Balance");
        bizzInfo[i][bLevel] = cache_get_field_content_int(i, "Level");
        bizzInfo[i][bPrice] = cache_get_field_content_int(i, "Price");
        bizzInfo[i][bFee] = cache_get_field_content_int(i, "Fee");
        bizzInfo[i][bOwnerSQLID] = cache_get_field_content_int(i, "OwnerSQLID");
        bizzInfo[i][bLocked] = bool:cache_get_field_content_int(i, "Locked");
        
        bizzInfo[i][bX] = cache_get_field_content_float(i, "X");
        bizzInfo[i][bY] = cache_get_field_content_float(i, "Y");
        bizzInfo[i][bZ] = cache_get_field_content_float(i, "Z");

        bizzInfo[i][bExitX] = cache_get_field_content_float(i, "ExitX");
        bizzInfo[i][bExitY] = cache_get_field_content_float(i, "ExitY");
        bizzInfo[i][bExitZ] = cache_get_field_content_float(i, "ExitZ");

        cache_get_field_content(i, "OwnerName", bizzInfo[i][bOwnerName], SQL, MAX_PLAYER_NAME);
        cache_get_field_content(i, "Description", bizzInfo[i][bDescription], SQL, 51);
    
        bizzInfo[i][bPickup] = CreateDynamicPickup(1239, 23, bizzInfo[i][bX], bizzInfo[i][bY], bizzInfo[i][bZ], 0, 0);
        pickupInfo[bizzInfo[i][bPickup]][pk_Bizz] = i;

        bizzInfo[i][bLabel] = CreateDynamic3DTextLabel("", -1, bizzInfo[i][bX], bizzInfo[i][bY], bizzInfo[i][bZ], 3.5);
        updateBusinessLabel(i);

        bizzInfo[i][bIcon] = CreateDynamicMapIcon(bizzInfo[i][bX], bizzInfo[i][bY], bizzInfo[i][bZ], bizzIconIDs[bizzInfo[i][bType] - 1], -1, -1, -1, -1, 70.0);
    }
    return printf("[MYSQL LOADED] Business loaded: %d", serverStuff[business]);
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

updateBusinessLabel(const bid) {
    gString[0] = EOS; 
    format(gString, sizeof gString, "Business {1C8A15}#%d\n{1C8A15}%s\n{FFFFFF}Owned by {1C8A15}%s\n{FFFFFF}Type: {1C8A15}%s\n{FFFFFF}Fee: {1C8A15}$%s", bizzInfo[bid][bID], bizzInfo[bid][bDescription], bizzInfo[bid][bOwnerName], bizzTypeName[bizzInfo[bid][bType] - 1], formatNumber(bizzInfo[bid][bFee]));

    if(bizzInfo[bid][bPrice] != 0)
        format(gString, sizeof gString, "%s\n{FFFFFF}Level: {1C8A15}%d\n{FFFFFF}This business is for sell.\nPrice: {1C8A15}$%s\n{FFFFFF}Type {1C8A15}[/buybizz]{FFFFFF} for buy this business.", gString, bizzInfo[bid][bLevel], formatNumber(bizzInfo[bid][bPrice]));

    switch(bizzInfo[bid][bType]) {
        case 11: strcat(gString, "\n{ffffff}Press {1C8A15}'H'{ffffff} to repair your vehicle.");
        case 13: strcat(gString, "\n{ffffff}Type {1C8A15}[/fill]{ffffff} if you want to fuel up your vehicle.");
    }

    return UpdateDynamic3DTextLabelText(bizzInfo[bid][bLabel], -1, gString);
}

playerEnterBusiness(const playerid, const bid) {
    switch(bizzInfo[bid][bType]) {
        case 1: SetPlayerInterior(playerid, 0), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /deposit, /transfer, /balance, /withdraw.");
        case 2: SetPlayerInterior(playerid, 15), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /clothes.");
        case 3: SetPlayerInterior(playerid, 4);
        case 4: SetPlayerInterior(playerid, 17), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /buy.");
        case 5: SetPlayerInterior(playerid, 10), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /eat.");
        case 6: SetPlayerInterior(playerid, 3), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /buytoys.");
        case 7: SetPlayerInterior(playerid, 17), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /drink.");
        case 8: SetPlayerInterior(playerid, 10);
        case 9: SetPlayerInterior(playerid, 5), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /changestyle.");
        case 10: SetPlayerInterior(playerid, 10), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /dice.");
        case 15: SetPlayerInterior(playerid, 3), SCM(playerid, COLOR_WHITE, "The available commands for this business are as follows: /lotto");
    }

    SetPlayerPos(playerid, bizzInfo[bid][bExitX], bizzInfo[bid][bExitY], bizzInfo[bid][bExitZ]); 
    SetPlayerVirtualWorld(playerid, bizzInfo[bid][bID]); 

    TogglePlayerControllableEx(playerid, false); 
    defer freezeTimer[2000](playerid);

    playerVars[playerid][var_inbizz] = bid;

    if(playerInfo[playerid][pBusiness] != bid) {
        substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, bizzInfo[bid][bFee], false); 
        bizzInfo[bid][bBalance] += bizzInfo[bid][bFee];
        
        va_GameTextForPlayer(playerid, "~R~-$%s", 2500, 1, formatNumber(bizzInfo[bid][bFee]));

        va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[bid][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[bid][bID], playerInfo[playerid][pSQLID]);
    }
    return playerVars[playerid][var_bizz_delay] = gettime() + 5;
}

playerLeaveBusiness(const playerid, const bid) {
    SetPlayerInterior(playerid, 0);
    SetPlayerPos(playerid, bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ]); 
    SetPlayerVirtualWorld(playerid, 0); 

    playerVars[playerid][var_inbizz] = -1;
    return 1;
}

getNearbyBusiness(const playerid, const Float:range, const type = -1) {
    new 
        nearbyPickup[1] = -1,
        Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerid, X, Y, Z);
    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, range);

    if(nearbyPickup[0] == -1)
        return -1;
    
    if(type == -1 || type == bizzInfo[pickupInfo[nearbyPickup[0]][pk_Bizz]][bType])
        return pickupInfo[nearbyPickup[0]][pk_Bizz];
    
    return -1;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:editbizz(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai acces la aceasta comanda."); 

    new bizzid, value; gString[0] = EOS; if(sscanf(params, "ds[64]d", bizzid, gString, value))
        return sendUsage(playerid, "/editbizz <bizzid> <tag> <value>"), SCM(playerid, COLOR_GREY, "Available tags: price, level, ownerid (-1 = AdmBot), locked (0/1), position.");

    if(serverStuff[business] < bizzid || bizzid <= 0)
        return sendError(playerid, "Acel business este inexistent.");

    bizzid --;

    if(!strcmp(gString, "price") || !strcmp(gString, "level")) {
        new const priceString = !strcmp(gString, "price");

        if(priceString) {
            bizzInfo[bizzid][bPrice] = value;
            va_mysql_tquery("UPDATE `server_business` SET `Price` = %d WHERE `ID` = %d", value, bizzInfo[bizzid][bID]);
            SCMf(playerid, -1, "The business %d was edited succesfully. (price: %d)", bizzInfo[bizzid][bID], value);
        }
        else {
            bizzInfo[bizzid][bLevel] = value;
            va_mysql_tquery("UPDATE `server_business` SET `Level` = %d WHERE `ID` = %d", value, bizzInfo[bizzid][bID]);
            SCMf(playerid, -1, "The business %d was edited succesfully. (level: %d)", bizzInfo[bizzid][bID], value);
        }
    }
    else if(!strcmp(gString, "ownerid")) {
        if(value == -1) {
            bizzInfo[bizzid][bOwnerSQLID] = -1; 
            strcpy(bizzInfo[bizzid][bOwnerName], "AdmBot");

            va_mysql_tquery("UPDATE `server_users`, `server_business` SET `server_business`.`OwnerSQLID` = -1, `server_business`.`OwnerName` = 'AdmBot', `server_users`.`Business` = %d WHERE `server_business`.`ID` = %d AND `server_users`.`Business` = %d", bizzInfo[bizzid][bID], bizzInfo[bizzid][bID], bizzInfo[bizzid][bID]);

            return updateBusinessLabel(bizzid);
        }

        if(!IsPlayerLogged(value))
            return sendError(playerid, "Acel player nu este logat.");

        bizzInfo[bizzid][bOwnerSQLID] = playerInfo[value][pSQLID];
        bizzInfo[bizzid][bOwnerGameID] = value;
        strcpy(bizzInfo[bizzid][bOwnerName], playerInfo[value][pName], MAX_PLAYER_NAME);
        playerInfo[value][pBusiness] = bizzid;

        gQuery[0] = EOS; 
        mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users`, `server_business` SET `server_business`.`OwnerSQLID` = %d, `server_business`.`OwnerName` = '%e', `server_users`.`Business` = %d WHERE `server_business`.`ID` = %d AND `server_users`.`ID` = %d", playerInfo[value][pSQLID], playerInfo[value][pName], bizzInfo[bizzid][bID], bizzInfo[bizzid][bID], playerInfo[value][pSQLID]); 
        mysql_tquery(SQL, gQuery, "", "");
        
        SCMf(playerid, -1, "The business %d was edited succesfully. (owner: %s)", bizzInfo[bizzid][bID], GetName(value));
    }
    else if(!strcmp(gString, "locked")) {
        if(value < 0 || value > 1)
            return sendError(playerid, "Invalid value! (ex. 0 / 1)");

        bizzInfo[bizzid][bLocked] = bool:value;

        va_mysql_tquery("UPDATE `server_business` SET `Locked` = %d WHERE `ID` = %d", value, bizzInfo[bizzid][bID]);

        SCMf(playerid, -1, "The business %d was edited succesfully. (locked: %s)", bizzInfo[bizzid][bID], !value ? "no" : "yes");
    }
    else if(!strcmp(gString, "position")) {
        GetPlayerPos(playerid, bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ]); 
        
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, bizzInfo[bizzid][bPickup], bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ]);
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, bizzInfo[bizzid][bLabel], bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ]);
        Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, bizzInfo[bizzid][bIcon], bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ]);

        va_mysql_tquery("UPDATE `server_business` SET `X` = %f, `Y` = %f, `Z` = %f WHERE `ID` = %d", bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ], bizzInfo[bizzid][bID]);

        SCMf(playerid, -1, "Position for business %d was succesfully edited. (X: %0.2f | Y: %0.2f | Z: %0.2f)", bizzInfo[bizzid][bID], bizzInfo[bizzid][bX], bizzInfo[bizzid][bY], bizzInfo[bizzid][bZ]);
        return 1;
    }
    else return sendUsage(playerid, "/editbizz <bizzid> <tag> <value>"), SCM(playerid, COLOR_GREY, "Available tags: price, level, ownerid (-1 = AdmBot), locked (0/1), position.");

    return updateBusinessLabel(bizzid);
}

YCMD:createbizz(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai acces la aceasta comanda."); 

    new
        type, level, price, bid = serverStuff[business]; 

    if(sscanf(params, "ddd", type, level, price) || type < 1 || type > 15) {
        sendUsage(playerid, "/createbizz <type> <level> <price>");
        SCM(playerid, COLOR_GREY, "Types: 1 - bank, 2 - clothes, 3 - gun shop, 4 - 24/7, 5 - food shop, 6 - sex shop, 7 - bar, 8 - cnn, 9 - gym, 10 - casino, 11 - pns ..."); 
        return SCM(playerid, COLOR_GREY, "... 12 - vehicle rent, 13 - gas station, 14 - mod shop, 15 - bet house");
    }

    GetPlayerPos(playerid, bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ]);

    bizzInfo[bid][bID] = bid;
    bizzInfo[bid][bType] = type; 
    bizzInfo[bid][bBalance] = 0;
    bizzInfo[bid][bLevel] = level; 
    bizzInfo[bid][bPrice] = price; 
    bizzInfo[bid][bFee] = 500;
    bizzInfo[bid][bOwnerSQLID] = bizzInfo[bid][bOwnerGameID] = -1;
    bizzInfo[bid][bExitX] = bizzInfo[bid][bExitY] = bizzInfo[bid][bExitZ] = 0.0;
    bizzInfo[bid][bLocked] = false;

    switch(type) {
        case 1: {
            bizzInfo[bid][bExitX] = 2306.00;
            bizzInfo[bid][bExitY] = -16.0000;
            bizzInfo[bid][bExitZ] = 27.0000;
        }
        case 2: {
            bizzInfo[bid][bExitX] = 207.738;
            bizzInfo[bid][bExitY] = -109.02;
            bizzInfo[bid][bExitZ] = 1005.13;
        }
        case 3: {
            bizzInfo[bid][bExitX] = 285.6794;
            bizzInfo[bid][bExitY] = -86.0604;
            bizzInfo[bid][bExitZ] = 1001.5229;
        }
        case 4: {
            bizzInfo[bid][bExitX] = -25.9021;
            bizzInfo[bid][bExitY] = -187.6596;
            bizzInfo[bid][bExitZ] = 1003.5469;
        }
        case 5: {
            bizzInfo[bid][bExitX] = 363.3676;
            bizzInfo[bid][bExitY] = -74.8260;
            bizzInfo[bid][bExitZ] = 1001.5078;
        }
        case 6: {
            bizzInfo[bid][bExitX] = -100.5016;
            bizzInfo[bid][bExitY] = -24.5300;
            bizzInfo[bid][bExitZ] = 1000.7188;
        }
        case 7: {
            bizzInfo[bid][bExitX] = 493.390991;
            bizzInfo[bid][bExitY] = -22.722799;
            bizzInfo[bid][bExitZ] = 1000.679687;
        }
        case 9: {
            bizzInfo[bid][bExitX] = 772.111999;
            bizzInfo[bid][bExitY] = -3.898649;
            bizzInfo[bid][bExitZ] = 1000.728820;
        }
        case 10: {
            bizzInfo[bid][bExitX] = 2018.4803;
            bizzInfo[bid][bExitY] = 1017.8185;
            bizzInfo[bid][bExitZ] = 996.8750;
        }
        case 15: {
            bizzInfo[bid][bExitX] = 833.9165; 
            bizzInfo[bid][bExitY] = 7.4893;
            bizzInfo[bid][bExitZ] = 1004.1797; 
        }
    }

    bizzInfo[bid][bIcon] = CreateDynamicMapIcon(bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ], bizzIconIDs[bizzInfo[bid][bType] - 1], -1, -1, -1, -1, 70.0);

    bizzInfo[bid][bPickup] = CreateDynamicPickup(1239, 23, bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ], 0, 0);
    pickupInfo[bizzInfo[bid][bPickup]][pk_Bizz] = bid - 1;

    bizzInfo[bid][bLabel] = CreateDynamic3DTextLabel("", -1, bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ], 3.5);

    strcpy(bizzInfo[bid][bOwnerName], "AdmBot"); 
    strcpy(bizzInfo[bid][bDescription], "Lurk Business");

    updateBusinessLabel(bid);

    ++serverStuff[business]; 

    va_mysql_tquery("INSERT INTO `server_business` (Type, Level, Price, X, Y, Z, ExitX, ExitY, ExitZ) VALUES (%d, %d, %d, %f, %f, %f, %f, %f, %f)", type, level, price, bizzInfo[bid][bX], bizzInfo[bid][bY], bizzInfo[bid][bZ], bizzInfo[bid][bExitX], bizzInfo[bid][bExitY], bizzInfo[bid][bExitZ]);

    SCMf(playerid, COLOR_GREY, "* You created succesfully a new business. (bID: %d, bType: %d)", bizzInfo[bid][bID], type);
    return 1;
}

YCMD:gotobizz(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai acces la aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/gotobusiness <id>");

    new id = strval(params);

    if(serverStuff[business] < id || id <= 0)
        return sendError(playerid, "Acel business nu exista pe server.");

    id --;

    SetPlayerPos(playerid, bizzInfo[id][bX], bizzInfo[id][bY], bizzInfo[id][bZ]); 
    SetPlayerInterior(playerid, 0); 
    SetPlayerVirtualWorld(playerid, 0);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s has teleported to business #%d.", GetName(playerid), bizzInfo[id][bID]);
    return 1;
}

YCMD:buybizz(playerid, params[], help) {
    if(playerInfo[playerid][pBusiness] != -1)
        return sendError(playerid, "Ai deja un business.");

    new const bizzid = getNearbyBusiness(playerid, 2.0);

    if(bizzid == -1)
        return 1;

    if(bizzInfo[bizzid][bPrice] == 0)
        return sendError(playerid, "Acest business nu este de vanzare.");

    if(GetMoney(playerid) < bizzInfo[bizzid][bPrice] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai destui bani pentru a cumpara aceasta afacere.");

    if(playerInfo[playerid][pLevel] < bizzInfo[bizzid][bLevel])
        return sendError(playerid, "Nu ai level-ul necesar pentru a cumpara acest business. Ai nevoie de minim level %d.", bizzInfo[bizzid][bLevel]);

    new const price = bizzInfo[bizzid][bPrice];

    if(bizzInfo[bizzid][bOwnerSQLID] != -1) {
        if(bizzInfo[bizzid][bOwnerGameID] == -1) {
            va_mysql_tquery("UPDATE `server_users` SET `Business` = -1, `Money` = `Money` + %d, `MoneyStore` = IF(`Money` >= 1000000000, `MoneyStore` + 1, `MoneyStore`), `Money` = IF(`Money` >= 1000000000, `Money` - 1000000000, `Money`) WHERE `ID` = %d", price, bizzInfo[bizzid][bOwnerSQLID]);
            
            insertEmail(_, bizzInfo[bizzid][bOwnerName], _, "%s purchased your business. Price: $%s.", GetName(playerid), formatNumber(price));
        }
        else {
            if(isPlayerInTrade(bizzInfo[bizzid][bOwnerGameID]))
                return sendError(playerid, "Nu poti face asta deoarece acel player este in cursul unei negocieri.");

            addMoney(bizzInfo[bizzid][bOwnerGameID], GetMilliards(bizzInfo[bizzid][bOwnerGameID]), GetMoney(bizzInfo[bizzid][bOwnerGameID]), 0, price, false);

            playerInfo[bizzInfo[bizzid][bOwnerGameID]][pBusiness] = -1;

            va_mysql_tquery("UPDATE `server_users` SET `Business` = -1, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[bizzInfo[bizzid][bOwnerGameID]][pMoneyStore], playerInfo[bizzInfo[bizzid][bOwnerGameID]][pMoney], playerInfo[bizzInfo[bizzid][bOwnerGameID]][pSQLID]);
            
            SCMf(bizzInfo[bizzid][bOwnerGameID], COLOR_YELLOW, "* %s purchased your business for $%s.", GetName(playerid), formatNumber(price));

            insertEmail(bizzInfo[bizzid][bOwnerGameID], bizzInfo[bizzid][bOwnerName], _, "%s purchased your business. Price: $%s.", GetName(playerid), formatNumber(price));
        }
    }

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price, false);

    playerInfo[playerid][pBusiness] = bizzid;

    bizzInfo[bizzid][bOwnerGameID] = playerid;
    bizzInfo[bizzid][bOwnerSQLID] = playerInfo[playerid][pSQLID]; 
    bizzInfo[bizzid][bPrice] = 0;

    strcpy(bizzInfo[bizzid][bOwnerName], GetName(playerid), MAX_PLAYER_NAME);

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_business`, `server_users` SET server_business.OwnerName = '%e', server_business.OwnerSQLID = %d, server_business.Price = 0, server_users.MoneyStore = %d, server_users.Money = %d, server_users.Business = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[bizzid][bOwnerName], bizzInfo[bizzid][bOwnerSQLID], playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], bizzInfo[bizzid][bID], bizzInfo[bizzid][bID], playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", ""); 

    updateBusinessLabel(bizzid); 

    return SCMf(playerid, COLOR_YELLOW, "* You purchased business %d for $%s succesfully!", bizzInfo[bizzid][bID], formatNumber(price));
}

YCMD:sellbizztostate(playerid, params[], help) {
    if(playerInfo[playerid][pBusiness] == -1)
        return sendError(playerid, "Nu ai un business.");

    return Dialog_Show(playerid, BUSINESSSELLTOSTATE, DIALOG_STYLE_MSGBOX, "SERVER: Sell Business", "Esti sigur ca vrei sa iti vinzi business-ul (id: %d) la stat pentru $5.000.000?", "Ok", "Cancel", bizzInfo[playerInfo[playerid][pBusiness]][bID]);
}

YCMD:bmenu(playerid, params[], help) {
    if(playerInfo[playerid][pBusiness] == -1)
        return sendError(playerid, "Nu ai un business.");

    return Dialog_Show(playerid, BUSINESSMENU, DIALOG_STYLE_LIST, "SERVER: Business Menu", "Business Description\nBusiness Lock\nSet Fee\nBusiness Balance\nSet Sell Price", "Select", "Cancel");
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:BUSINESSMENU(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const bizzid = playerInfo[playerid][pBusiness];

    switch(listitem) {
        case 0: {
            Dialog_Show(playerid, BUSINESSMENU1, DIALOG_STYLE_INPUT, "SERVER: Business Description", "Introdu descrierea pe care vrei sa o setezi la afacerea ta:", "Set", "Cancel");
        }
        case 1: { 
            if(bizzInfo[bizzid][bExitX] == 0) 
                return sendError(playerid, "Nu ai acces la aceasta functie pentru acest tip de business.");

            bizzInfo[bizzid][bLocked] = !bizzInfo[bizzid][bLocked]; 
         
            va_mysql_tquery("UPDATE `server_business` SET `Locked` = %d WHERE `ID` = %d", bizzInfo[bizzid][bLocked], bizzInfo[bizzid][bID]);
        
            SCM(playerid, COLOR_GREY, bizzInfo[bizzid][bLocked] ? "* Afacerea ta a fost incuiata." : "* Afacerea ta a fost descuiata.");
        }
        case 2: { 
            Dialog_Show(playerid, BUSINESSMENU2, DIALOG_STYLE_INPUT, "SERVER: Business Fee", "Introdu taxa la intrare in afacere pe care vrei sa o setezi:", "Set", "Cancel");
        }
        case 3: { 
            if(bizzInfo[bizzid][bBalance] <= 0)
                return sendError(playerid, "Nu ai bani in afacere.");

            Dialog_Show(playerid, BUSINESSBALANCE, DIALOG_STYLE_INPUT, "SERVER: Business Balance", "Balanta afacerii in momentul acesta este de $%s.\nIntrodu suma de bani pe care vrei sa o scoti:", "Withdraw", "Cancel", formatNumber(bizzInfo[bizzid][bBalance]));
        }
        case 4: { 
            Dialog_Show(playerid, BUSINESSSELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell Business", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi afacerea\n(daca introduci $0, afacerea nu se va pune la vanzare):", "Set", "Cancel");
        }
    }
    return 1;
}

Dialog:BUSINESSSELLPRICE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, BUSINESSSELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell Business", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi afacerea\n(daca introduci $0, afacerea nu se va pune la vanzare):", "Set", "Cancel");

    new const money = strval(inputtext);

    if(money < 0 || money >= 999999999) {
        sendError(playerid, "Suma de bani trebuie sa fie cuprinsa intre $0 si $999.999.999."); 
        return Dialog_Show(playerid, BUSINESSSELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell Business", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi afacerea\n(daca introduci $0, afacerea nu se va pune la vanzare):", "Set", "Cancel");
    }

    if(money == bizzInfo[playerInfo[playerid][pBusiness]][bPrice]) {
        sendError(playerid, "Pretul afacerii este deja $%s.", formatNumber(money)); 
        return Dialog_Show(playerid, BUSINESSSELLPRICE, DIALOG_STYLE_INPUT, "SERVER: Sell Business", "Introdu mai jos suma de bani cu care vrei sa-ti vinzi afacerea\n(daca introduci $0, afacerea nu se va pune la vanzare):", "Set", "Cancel");
    }

    bizzInfo[playerInfo[playerid][pBusiness]][bPrice] = money; 
    va_mysql_tquery("UPDATE `server_business` SET `Price` = %d WHERE `ID` = %d", money, bizzInfo[playerInfo[playerid][pBusiness]][bID]); 

    updateBusinessLabel(playerInfo[playerid][pBusiness]); 

    return SCMf(playerid, COLOR_GREY, "* You changed succesfully the sell price for your business to $%s.", formatNumber(money));
}

Dialog:BUSINESSBALANCE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, BUSINESSBALANCE, DIALOG_STYLE_INPUT, "SERVER: Business Balance", "Balanta afacerii in momentul acesta este de $%s.\nIntrodu suma de bani pe care vrei sa o scoti:", "Withdraw", "Cancel", formatNumber(bizzInfo[playerInfo[playerid][pBusiness]][bBalance]));

    new const money = strval(inputtext);

    if(money > bizzInfo[playerInfo[playerid][pBusiness]][bBalance] || money <= 0)
        return sendError(playerid, "Nu ai aceasta suma de bani in afacere.");

    bizzInfo[playerInfo[playerid][pBusiness]][bBalance] -= money; 

    addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, money, false);

    va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[playerInfo[playerid][pBusiness]][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[playerInfo[playerid][pBusiness]][bID], playerInfo[playerid][pSQLID]);

    return SCMf(playerid, COLOR_YELLOW, "* Ai scos $%s bani din afacerea ta. Acum mai sunt $%s bani in afacere.", formatNumber(money), formatNumber(bizzInfo[playerInfo[playerid][pBusiness]][bBalance]));
}

Dialog:BUSINESSMENU2(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, BUSINESSMENU2, DIALOG_STYLE_INPUT, "SERVER: Business Fee", "Introdu taxa la intrare in afacere pe care vrei sa o setezi:", "Set", "Cancel");

    new const fee = strval(inputtext);

    if(fee < 1 || fee > 5000) {
        Dialog_Show(playerid, BUSINESSMENU2, DIALOG_STYLE_INPUT, "SERVER: Business Fee", "Introdu taxa la intrare in afacere pe care vrei sa o setezi:", "Set", "Cancel"); 
        return sendError(playerid, "Taxa trebuie sa fie cuprinsa intre $0 si $5.000.");
    }

    bizzInfo[playerInfo[playerid][pBusiness]][bFee] = fee; 

    va_mysql_tquery("UPDATE `server_business` SET `Fee` = %d WHERE `ID` = %d", fee,bizzInfo[playerInfo[playerid][pBusiness]][bID]); 

    updateBusinessLabel(playerInfo[playerid][pBusiness]); 

    return SCMf(playerid, COLOR_GREY, "* You changed the business's fee on $%s.", formatNumber(fee));
}

Dialog:BUSINESSMENU1(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const length = strlen(inputtext);

    if(length < 5 || length > 40)
        return sendError(playerid, "Descrierea trebuie sa fie cuprinsa intre 5 si 40 caractere.");

    for(new i = 0; inputtext[i]; ++i) {
        if(inputtext[i] == '{' || inputtext[i] == '}')
            return Dialog_Show(playerid, BUSINESSMENU1, DIALOG_STYLE_INPUT, "SERVER: Business Description", "Introdu descrierea pe care vrei sa o setezi la afacerea ta:", "Set", "Cancel");
    }

    strcpy(bizzInfo[playerInfo[playerid][pBusiness]][bDescription], inputtext);

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_business` SET `Description` = '%e' WHERE `ID` = %d", inputtext, bizzInfo[playerInfo[playerid][pBusiness]][bID]); 
    mysql_tquery(SQL, gQuery, "", "");

    updateBusinessLabel(playerInfo[playerid][pBusiness]); 

    return SCM(playerid, COLOR_GREY, "* Descrierea afacerii tale a fost setata cu succes.");
}

Dialog:BUSINESSSELLTOSTATE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(isPlayerInTrade(playerid))
        return sendError(playerid, "Nu poti face asta deoarece esti in cursul unei negocieri.");

    new const bizzid = playerInfo[playerid][pBusiness];

    strcpy(bizzInfo[bizzid][bOwnerName], "AdmBot"); 
    strcpy(bizzInfo[bizzid][bDescription], "Lurk Business"); 

    bizzInfo[bizzid][bPrice] = 50000000; 
    bizzInfo[bizzid][bFee] = 5000;
    bizzInfo[bizzid][bLocked] = false;
    bizzInfo[bizzid][bOwnerSQLID] = playerInfo[playerid][pBusiness] = -1;

    addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, 5000000, false);

    va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.OwnerSQLID = -1, server_business.OwnerName = 'AdmBot', server_business.Fee = 5000, server_business.Description = 'Lurk Business', server_business.Price = 50000000, server_business.Locked = 0, server_users.Business = -1, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], bizzInfo[bizzid][bID], playerInfo[playerid][pSQLID]);
    
    updateBusinessLabel(bizzid); 

    return SCMf(playerid, COLOR_YELLOW, "* Ti-ai vandut business-ul %d cu succes la stat si ai primit $5.000.000.", bizzInfo[bizzid][bID]);
}