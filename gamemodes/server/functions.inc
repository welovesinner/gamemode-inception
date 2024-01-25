// ------------------------------------- //
//              Textdraws                //
// ------------------------------------- //

loadServerTextdraws() {
    /*LogoTD = TextDrawCreate(592.342895, 431.216674, "RPG.Lurk.RO");
    TextDrawLetterSize(LogoTD, 0.320819, 1.465832);
    TextDrawAlignment(LogoTD, 2);
    TextDrawColor(LogoTD, -1);
    TextDrawSetOutline(LogoTD, 1);
    TextDrawBackgroundColor(LogoTD, 255);
    TextDrawFont(LogoTD, 3);
    TextDrawSetProportional(LogoTD, 1);
    TextDrawSetShadow(LogoTD, 0);*/

    LogoTD[0] = TextDrawCreate(562.980468, 426.366851, "I~W~~H~nception");
    TextDrawLetterSize(LogoTD[0], 0.532256, 1.845000);
    TextDrawAlignment(LogoTD[0], 1);
    TextDrawColor(LogoTD[0], 478811647);
    TextDrawSetShadow(LogoTD[0], 0);
    TextDrawSetOutline(LogoTD[0], 1);
    TextDrawBackgroundColor(LogoTD[0], 255);
    TextDrawFont(LogoTD[0], 0);
    TextDrawSetProportional(LogoTD[0], 1);
    TextDrawSetShadow(LogoTD[0], 0);

    LogoTD[1] = TextDrawCreate(623.582824, 426.400512, "ro");
    TextDrawLetterSize(LogoTD[1], 0.532256, 1.845000);
    TextDrawAlignment(LogoTD[1], 1);
    TextDrawColor(LogoTD[1], -1);
    TextDrawSetShadow(LogoTD[1], 0);
    TextDrawSetOutline(LogoTD[1], 1);
    TextDrawBackgroundColor(LogoTD[1], 255);
    TextDrawFont(LogoTD[1], 0);
    TextDrawSetProportional(LogoTD[1], 1);
    TextDrawSetShadow(LogoTD[1], 0);

    LogoTD[2] = TextDrawCreate(620.609130, 427.583892, ".");
    TextDrawLetterSize(LogoTD[2], 0.532256, 1.845000);
    TextDrawAlignment(LogoTD[2], 1);
    TextDrawColor(LogoTD[2], -1);
    TextDrawSetShadow(LogoTD[2], 0);
    TextDrawSetOutline(LogoTD[2], 1);
    TextDrawBackgroundColor(LogoTD[2], 255);
    TextDrawFont(LogoTD[2], 0);
    TextDrawSetProportional(LogoTD[2], 1);
    TextDrawSetShadow(LogoTD[2], 0);

    serverClockTD = TextDrawCreate(577.273742, 15.366563, "20:00:00");
    TextDrawLetterSize(serverClockTD, 0.385475, 1.699165);
    TextDrawAlignment(serverClockTD, 2);
    TextDrawColor(serverClockTD, -1);
    TextDrawSetOutline(serverClockTD, 1);
    TextDrawBackgroundColor(serverClockTD, 255);
    TextDrawFont(serverClockTD, 3);
    TextDrawSetProportional(serverClockTD, 1);
    TextDrawSetShadow(serverClockTD, 0);

    serverDateTD = TextDrawCreate(577.142395, 30.083286, "05.02.2022");
    TextDrawLetterSize(serverDateTD, 0.251324, 1.128332);
    TextDrawAlignment(serverDateTD, 2);
    TextDrawColor(serverDateTD, -1);
    TextDrawSetOutline(serverDateTD, 1);
    TextDrawBackgroundColor(serverDateTD, 255);
    TextDrawFont(serverDateTD, 3);
    TextDrawSetProportional(serverDateTD, 1);
    TextDrawSetShadow(serverDateTD, 0);

    ReportsTD = TextDrawCreate(273.000000, 437.022430, "REPORTS: ~r~0~w~~h~ / CHEATERS: ~r~0");
    TextDrawLetterSize(ReportsTD, 0.178500, 0.884443);
    TextDrawAlignment(ReportsTD, 1);
    TextDrawColor(ReportsTD, -1);
    TextDrawSetOutline(ReportsTD, 1);
    TextDrawBackgroundColor(ReportsTD, 255);
    TextDrawFont(ReportsTD, 2);
    TextDrawSetProportional(ReportsTD, 1);
    TextDrawSetShadow(ReportsTD, 0);

    AStatsTD = TextDrawCreate(322.415832, 2.089158, "ticks: ~r~198 ~W~~H~mysql: ~G~0");
    TextDrawLetterSize(AStatsTD, 0.250999, 1.058665);
    TextDrawAlignment(AStatsTD, 2);
    TextDrawColor(AStatsTD, -1);
    TextDrawSetOutline(AStatsTD, 1);
    TextDrawBackgroundColor(AStatsTD, 255);
    TextDrawFont(AStatsTD, 3);
    TextDrawSetProportional(AStatsTD, 1);
    TextDrawSetShadow(AStatsTD, 0);

    SafezoneTD = TextDrawCreate(328.000000, 18.266658, "~G~safe-zone");
    TextDrawLetterSize(SafezoneTD, 0.355500, 1.407109);
    TextDrawAlignment(SafezoneTD, 1);
    TextDrawColor(SafezoneTD, -1);
    TextDrawSetOutline(SafezoneTD, 1);
    TextDrawBackgroundColor(SafezoneTD, 144);
    TextDrawFont(SafezoneTD, 3);
    TextDrawSetProportional(SafezoneTD, 1);
    TextDrawSetShadow(SafezoneTD, 0);

    LoginQueueTD[0] = TextDrawCreate(-2.825771, 162.000030, "box");
    TextDrawLetterSize(LoginQueueTD[0], 0.000000, 9.203514);
    TextDrawTextSize(LoginQueueTD[0], 640.000000, 0.000000);
    TextDrawAlignment(LoginQueueTD[0], 1);
    TextDrawColor(LoginQueueTD[0], -1);
    TextDrawUseBox(LoginQueueTD[0], 1);
    TextDrawBoxColor(LoginQueueTD[0], -182969376);
    TextDrawSetOutline(LoginQueueTD[0], 0);
    TextDrawBackgroundColor(LoginQueueTD[0], -80069991);
    TextDrawFont(LoginQueueTD[0], 1);
    TextDrawSetProportional(LoginQueueTD[0], 1);
    TextDrawSetShadow(LoginQueueTD[0], 0);

    LoginQueueTD[1] = TextDrawCreate(323.776031, 152.483322, "Login Queue");
    TextDrawLetterSize(LoginQueueTD[1], 0.365329, 1.349166);
    TextDrawAlignment(LoginQueueTD[1], 2);
    TextDrawColor(LoginQueueTD[1], -1);
    TextDrawSetOutline(LoginQueueTD[1], 1);
    TextDrawBackgroundColor(LoginQueueTD[1], 255);
    TextDrawFont(LoginQueueTD[1], 3);
    TextDrawSetProportional(LoginQueueTD[1], 1);
    TextDrawSetShadow(LoginQueueTD[1], 0);

    LoginQueueTD[2] = TextDrawCreate(324.818878, 233.017791, "players in login queue: 16");
    TextDrawLetterSize(LoginQueueTD[2], 0.206345, 1.174999);
    TextDrawAlignment(LoginQueueTD[2], 2);
    TextDrawColor(LoginQueueTD[2], -1);
    TextDrawSetOutline(LoginQueueTD[2], 1);
    TextDrawBackgroundColor(LoginQueueTD[2], 255);
    TextDrawFont(LoginQueueTD[2], 2);
    TextDrawSetProportional(LoginQueueTD[2], 1);
    TextDrawSetShadow(LoginQueueTD[2], 0);
    return 1;
}

destroyServerTextdraws() {
    textDrawDestroy(serverDateTD); 
    textDrawDestroy(AStatsTD); 
    textDrawDestroy(ReportsTD); 
    textDrawDestroy(LogoTD[0]); 
    textDrawDestroy(LogoTD[1]); 
    textDrawDestroy(LogoTD[2]); 
    textDrawDestroy(serverClockTD); 
    textDrawDestroy(SafezoneTD);
    textDrawDestroy(LoginQueueTD[0]); 
    textDrawDestroy(LoginQueueTD[1]); 
    textDrawDestroy(LoginQueueTD[2]);
    return 1;
}

playerTextDrawDestroy(const playerid, &PlayerText:textdraw) {
    if(textdraw != PlayerText: -1) {
        PlayerTextDrawDestroy(playerid, textdraw); 
        textdraw = PlayerText: -1;
        return 1;
    }
    return 0;
}

textDrawDestroy(&Text:textdraw) {
    if(textdraw != Text: -1) {
        TextDrawDestroy(textdraw); 
        textdraw = Text: -1;
        return 1;
    }
    return 0;
}

// ------------------------------------- //
//   Functions called by db queries      //
// ------------------------------------- //

query_function checkDatabaseAccount(const playerid, const name[]) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Acest cont nu a fost gasit in baza de date.");

    gString[0] = EOS;
    cache_get_field_content(0, "LastLogin", gString, SQL, sizeof gString);

    return Dialog_Show(playerid, NULL, DIALOG_STYLE_MSGBOX, "SERVER: Account Info", "Name: %s\nSQLID: %d\nLevel: %d\nAdmin: %d\nHelper: %d\nLast Login: %s\nHours Played: %0.2f\nWarns: %d/3\nJob: %s\nHouse: %d\nBusiness: %d\nMoney: $%s\nBank: $%s", "Ok", "", name, cache_get_field_content_int(0, "ID"), cache_get_field_content_int(0, "Level"), cache_get_field_content_int(0, "Admin"), cache_get_field_content_int(0, "Helper"), gString, cache_get_field_content_float(0, "Hours"), cache_get_field_content_int(0, "Warn"), !cache_get_field_content_int(0, "Job") ? "None" : va_return(jobInfo[cache_get_field_content_int(0, "Job") - 1][j_Name]), cache_get_field_content_int(0, "House"), cache_get_field_content_int(0, "Business"), formatMoney(cache_get_field_content_int(0, "MoneyStore"), cache_get_field_content_int(0, "Money")), formatMoney(cache_get_field_content_int(0, "BankStore"), cache_get_field_content_int(0, "Bank")));
}

query_function forceNameChange(const playerid, const inputtext[]) {
    if(!IsPlayerConnected(playerid))
        return 1;

    new const success = SetPlayerName(playerid, inputtext);
    SetPlayerName(playerid, GetName(playerid));

    if(cache_num_rows() || success != 1 || strlen(inputtext) < 3)
        return Dialog_Show(playerid, FORCENAMECHANGE, DIALOG_STYLE_INPUT, "SERVER: Force Name Change", "Enter a new nickname in the box below:\n{FF0000}Nickname must be not used and needs to have 3 - 24 characters long and only contain valid characters.", "Ok", "Kick");

    if(playerInfo[playerid][pHouse] != -1) {
        strcpy(HouseInfo[playerInfo[playerid][pHouse]][hOwnerName], inputtext);
        updateHouseLabel(playerInfo[playerid][pHouse]);
    }

    if(playerInfo[playerid][pBusiness] != -1) {
        strcpy(bizzInfo[playerInfo[playerid][pBusiness]][bOwnerName], inputtext); 
        updateBusinessLabel(playerInfo[playerid][pBusiness]); 
    }

    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Name` = '%e' WHERE `ID` = %d", inputtext, playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Referral` = '%e' WHERE `Referral` = '%e'", inputtext, GetName(playerid));
    mysql_tquery(SQL, gQuery, "", "");
    
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_houses` SET `OwnerName` = '%e' WHERE `OwnerName` = '%e' AND `OwnerID` = %d", inputtext, GetName(playerid), playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_friends` SET `FriendName` = '%e' WHERE `FriendName` = '%e' AND `FriendSQLID` = %d", inputtext, GetName(playerid), playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_business` SET `OwnerName` = '%e' WHERE `OwnerName` = '%e' AND `OwnerSQLID` = %d", inputtext, GetName(playerid), playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_bans` SET `Name` = '%e' WHERE `Name` = '%e' AND `PlayerSQLID` = %d", inputtext, GetName(playerid), playerInfo[playerid][pSQLID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    SCM(playerid, COLOR_CLIENT, "SERVER: Your nickname was changed succesfully. You need to reconnect with the new nickname on the server to apply the changes."); 
    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s changed his nickname via [/forcenamechange] to %s.", GetName(playerid), inputtext);
    
    defer delayedKick(playerid); 
    return 1;
}

query_function loadChatLogsForPlayer(const playerid, const userid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Nu au fost gasite loguri in baza de date.");

    gDialog[0] = gString[0] = EOS;

    for(new i, j = cache_num_rows(); i != j; i++) {
        cache_get_field_content(i, "Text", gString, SQL, MAX_PLAYER_NAME);

        format(gDialog, sizeof gDialog, "%s* %s: %s\n", gDialog, GetName(userid), gString);
    }
    return Dialog_Show(playerid, NULL, DIALOG_STYLE_MSGBOX, "SERVER: Chat Logs", gDialog, "Exit", "");
}

query_function checkPlayerIP(const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    new const rows = cache_num_rows();

    if(!rows)
        return SCM(playerid, COLOR_GREY, "Nothing found in database."); 

    new 
        full_message[256], name[24];

    for(new i; i < rows; ++i) {
        cache_get_field_content(i, "Name", name, SQL, 24);

        format(full_message, sizeof full_message, "%s%s [ID %d], ", full_message, name, cache_get_field_content_int(i, "ID"));
    }

    full_message[strlen(full_message) - 2] = '.';

    sendSplittedMessageToPlayer(playerid, -1, -1, full_message); 

    return SCMf(playerid, COLOR_GREY, "Accounts found: %d", rows);
}

query_function setAdminOffline(const playerid, const name[], const level) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Acel player nu a fost gasit in baza de date.");

    if(cache_get_field_content_int(0, "Admin") > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti face asta pe acel player deoarece are grad mai mare decat al tau.");

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's (offline) admin level to %d.", GetName(playerid), name, level);

    insertEmail(_, name, _, "%s setted (offline) your admin level to %d.", GetName(playerid), level);
    
    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Admin` = %d, `PlayersHelped` = 0 WHERE `Name` = '%e'", level, name); 
    mysql_tquery(SQL, gQuery, "", "");
    return 1;
}

query_function setHelperOffline(const playerid, const name[], const level) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Acel player nu a fost gasit in baza de date.");

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's (offline) helper level to %d.", GetName(playerid), name, level);

    insertEmail(_, name, _, "%s setted (offline) your helper level to %d.", GetName(playerid), level);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Helper` = %d, `PlayersHelped` = 0 WHERE `Name` = '%e'", level, name);
    mysql_tquery(SQL, gQuery, "", "");
    return 1;
}

query_function checkBannedPlayer(const playerid, const name[], const reason[]) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Player-ul respectiv nu a fost gasit in lista celor banati.");

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s unbanned player %s, reason: %s", GetName(playerid), name, reason); 

    va_mysql_tquery("UPDATE `server_bans` SET `Active` = 0 WHERE `ID` = %d", cache_get_field_content_int(0, "ID"));
    return 1;
}

query_function checkStaffCategory(const playerid, const listitem) {
    if(!IsPlayerConnected(playerid))
        return 1;

    new 
        name[MAX_PLAYER_NAME], lastlogin[64],
        rows = cache_num_rows();

    if(listitem) {
        if(!rows)
            return sendError(playerid, "Nu au fost gasiti helperi in baza de date.");

        gDialog[0] = EOS;

        gDialog = "Name\tStatus [last login]\tHWarns\tRaport\n";

        for(new i; i < rows; i++) {
            cache_get_field_content(i, "Name", name, SQL, MAX_PLAYER_NAME);
            cache_get_field_content(i, "LastLogin", lastlogin, SQL, sizeof lastlogin);

            format(gDialog, sizeof gDialog, "%s(%d) %s\t%s [%s]\t%d/3\t%d (effectued)\n", gDialog, cache_get_field_content_int(i, "Helper"), name, !cache_get_field_content_int(i, "Status") ? "offline" : "online", lastlogin, cache_get_field_content_int(i, "HelperWarns"), cache_get_field_content_int(i, "PlayersHelped"));
        }
        return Dialog_Show(playerid, NULL, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Helpers", gDialog, "Exit", "");
    }
    
    if(!rows)
        return sendError(playerid, "Nu au fost gasiti admini in baza de date.");

    gDialog[0] = EOS;

    gDialog = "Name\tStatus [last login]\tAWarns\tRaport\n";

    for(new i; i < rows; i++) {
        cache_get_field_content(i, "Name", name, SQL, MAX_PLAYER_NAME);
        cache_get_field_content(i, "LastLogin", lastlogin, SQL, sizeof lastlogin);

        format(gDialog, sizeof gDialog, "%s(%d) %s\t%s [%s]\t%d/3\t%d (effectued)\n", gDialog, cache_get_field_content_int(i, "Admin"), name, !cache_get_field_content_int(i, "Status") ? "offline" : "online", lastlogin, cache_get_field_content_int(i, "AdminWarns"), cache_get_field_content_int(i, "PlayersHelped"));
    }
    return Dialog_Show(playerid, NULL, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Admins", gDialog, "Exit", "");
} 

query_function checkBanStatus(const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows()) {
        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof(gQuery), "SELECT * FROM `server_users` WHERE `Name` = '%e' LIMIT 1", GetName(playerid)); 
        return mysql_tquery(SQL, gQuery, "checkPlayerAccount", "dd", playerid, raceCheckThreads[playerid]);
    }

    new permanently = cache_get_field_content_int(0, "Permanent"), days = cache_get_field_content_int(0, "Days");

    if(permanently || days > gettime()) {
        new str[65];

        cache_get_field_content(0, "AdminName", str, SQL, MAX_PLAYER_NAME);
        SCMf(playerid, COLOR_LIGHTRED, "(Ban System) You are banned %s from this server by admin %s.", permanently ? "permanently" : "temporary", str);

        cache_get_field_content(0, "Reason", str, SQL, 64);
        SCMf(playerid, COLOR_LIGHTRED, "(Ban System) Ban reason: %s", str);

        cache_get_field_content(0, "Date", str, SQL, 32);
        SCMf(playerid, COLOR_LIGHTRED, "(Ban System) Ban date: %s", str);

        if(!permanently) 
            SCMf(playerid, COLOR_LIGHTRED, "(Ban System) Ban expires in %d days.", ((days - gettime()) / 86400)+1);

        SCM(playerid, COLOR_LIGHTRED, "(Ban System) If you think you have been unfairly banned, you can make a unban ticket on: panel.Lurk.ro.");

        GameTextForPlayer(playerid, "Banned", 6000, 2);

        defer delayedKick(playerid);
        return 0;
    }
    else if(days < gettime() && !permanently) {
        va_mysql_tquery("UPDATE `server_bans` SET `Active` = 0 WHERE `ID` = %d", cache_get_field_content_int(0, "ID")); 
        SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s was unbanned because the temporary ban has expired.", GetName(playerid)); 
        SCM(playerid, COLOR_CLIENT, "SERVER: {ffffff}Your ban has expired automatically.");
    }

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof(gQuery), "SELECT * FROM `server_users` WHERE `Name` = '%e' LIMIT 1", GetName(playerid));
    return mysql_tquery(SQL, gQuery, "checkPlayerAccount", "dd", playerid, raceCheckThreads[playerid]);
}

query_function banOfflineAccount(const playerid, const days, const reason[], const name[]) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows())
        return sendError(playerid, "Contul respectiv nu exista.");

    if(cache_get_field_content_int(0, "Admin") > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra unui admin mai mare decat tine.");

    if(!days) 
        sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s (offline) has been banned by %s permanently, reason: %s.", name, GetName(playerid), reason);
    
    else 
        sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s (offline) has been banned by %s for %d days, reason: %s.", name, GetName(playerid), days, reason);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_bans` (Name, PlayerSQLID, AdminName, AdminSQLID, Reason, Days, Permanent, Date, Active) VALUES ('%e', %d, '%e', %d, '%e', %d, %d, '%e', 1)", name, cache_get_field_content_int(0, "ID"), GetName(playerid), playerInfo[playerid][pSQLID], reason, days == 0 ? 0 : gettime() + days * 86400, !days, getDateTime());
    mysql_tquery(SQL, gQuery, "", "");

    return playerVars[playerid][var_ban_delay] = gettime() + 60;   
}

query_function searchPlayerNameInDB(const playerid, const name[]) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(!cache_num_rows() || !strcmp(name, GetName(playerid))) 
        return Dialog_Show(playerid, REFERRAL, DIALOG_STYLE_INPUT, "SERVER: Referral", "Insert in the box below the name of the player who brought you on the server:\n{FF0000}Invalid player name.", "Ok", "Cancel");

    SCMf(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your referral is: %s", name);

    strcpy(playerInfo[playerid][pReferral], name, MAX_PLAYER_NAME);
    playerInfo[playerid][pReferralSQLID] = cache_get_field_content_int(0, "ID");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `EMail` = '%e', `Gender` = %d, `Age` = %d, `Skin` = %d, `Referral` = '%e', `ReferralSQLID` = %d, `Tutorial` = 1 WHERE `ID` = %d", playerInfo[playerid][pEMail], playerInfo[playerid][pGender], playerInfo[playerid][pAge], playerInfo[playerid][pSkin], playerInfo[playerid][pReferral], playerInfo[playerid][pReferralSQLID], playerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");

    TogglePlayerSpectating(playerid, false);
    
    clearChat(playerid, 3); 

    SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}You are successfully registered!");
    SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Welcome, %s.", GetName(playerid));

    SCM(playerid, COLOR_YELLOW, "* You need to set a 4-digits pin, recommended for your account security.");
    showPlayerPinTextdraws(playerid, PIN_SET_TYPE);
    return 1;
}

query_function buyPhoneNumber(const playerid, number) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(cache_num_rows()) {
        number = random(999999 - 100000 + 1) + 100000;

        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT (ID) FROM `server_users` WHERE `PhoneNumber` = %d LIMIT 1", number);
        return mysql_tquery(SQL, gQuery, "buyPhoneNumber", "dd", playerid, number);
    }

    if(playerInfo[playerid][pPhoneNumber] != 0)
        MAP_remove_val(phoneNumbers, playerInfo[playerid][pPhoneNumber]);

    playerInfo[playerid][pPhoneNumber] = number;
    MAP_insert_val_val(phoneNumbers, playerInfo[playerid][pPhoneNumber], playerid);

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, buyShop[2], false);

    va_mysql_tquery("UPDATE `server_users` SET `PhoneNumber` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", number, GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pSQLID]);
    
    playerVars[playerid][var_buy_delay] = gettime() + 5;

    return SCMf(playerid, COLOR_GREEN, "(Shop): {ffffff}You purchased a new phone for $1.500. Your actual number is: %d.", number);
}

query_function onPlayerRegister(const playerid, race_check) {
    if(raceCheckThreads[playerid] != race_check)
        return Kick(playerid);

    Queue_RemoveFrontValue(loginQueue);
    pickNextPlayerFromLoginQueue(true);

    stop playerInfo[playerid][pLoginTimer];

    Iter_Clear(playerSkins[playerid]);

    playerInfo[playerid][pSQLID] = cache_insert_id(); 

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `LastLogin` = '%e', `Status` = 1, `PlayerID` = %d WHERE `ID` = %d", getDateTime(), playerid, playerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");

    Iter_Add(serverPlayers, playerid); 

    MAP_insert_str_val(playersNames, GetName(playerid), playerid);
    MAP_insert_val_val(playersSQLID, playerInfo[playerid][pSQLID], playerid);

    playerTextdraws[playerid][NameTD] = CreatePlayerTextDraw(playerid, 85.072502, 430.5, GetName(playerid));
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][NameTD], 0.180731, 1.121665);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][NameTD], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][NameTD], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][NameTD], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][NameTD], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][NameTD], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][NameTD], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][NameTD], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][NameTD]);

    SetPlayerScore(playerid, playerInfo[playerid][pLevel]);

    SetSpawnInfo(playerid, 1, playerInfo[playerid][pSkin], 479.7054, -1498.8781, 20.4735, 268.9406, -1, -1, -1, -1, -1, -1);

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, playerInfo[playerid][pMoney]);

    clearChat(playerid, 65);

    SCM(playerid, COLOR_GREEN, "SERVER: {FFFFFF}Complete the next dialogs with correct sentences.");
    Dialog_Show(playerid, EMAIL, DIALOG_STYLE_INPUT, "SERVER: Register", "Enter your e-mail address below:", "Ok", "");

    return SendStaff(COLOR_LIGHTRED, "Registration: %s (%d) just registered the game. (#%d - IP: %s)", GetName(playerid), playerid, playerInfo[playerid][pSQLID], encryptIPAddress(GetPlayerIP(playerid)));
}

query_function checkPlayerAccount(const playerid, race_check) { 
    if(raceCheckThreads[playerid] != race_check)
        return Kick(playerid);

    playerInfo[playerid][pLoginTimer] = defer loginTimer(playerid);

    if(cache_num_rows()) {
        playerInfo[playerid][pSQLLoginCache] = cache_save();

        cache_get_field_content(0, "Password", playerInfo[playerid][pPassword], SQL, 65);

        SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Welcome back, %s!", GetName(playerid));
        SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}Because you have a registered account, you will need to log in.");
        SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}You have 30 seconds to enter your password in the box below.");
        return Dialog_Show(playerid, LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "%s, please enter your account password below.\nYou have only 30 seconds available, else you will being kicked.", "Login", "Quit", GetName(playerid));
    }

    SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Welcome, %s!", GetName(playerid));
    SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}Your account isn't registered, you need to enter a password in the box below.");
    SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}You have 30 seconds to enter a password in the box below.");
    return Dialog_Show(playerid, REGISTER, DIALOG_STYLE_PASSWORD, "SERVER: Register", "Hello %s,\nWelcome to rpg.Lurk.ro! Please enter a password for register your account.", "Register", "Quit", GetName(playerid));
}

// ------------------------------------- //
//              Useful for server        //
// ------------------------------------- //

function onPlayerLogin(const playerid) {
    Queue_RemoveFrontValue(loginQueue);
    pickNextPlayerFromLoginQueue(true);

    playerInfo[playerid][pLoginTries] = 0;
    stop playerInfo[playerid][pLoginTimer];

    cache_set_active(playerInfo[playerid][pSQLLoginCache]);

    strcpy(gString, playerInfo[playerid][pName]);
    cache_get_field_content(0, "Name", playerInfo[playerid][pName], SQL, MAX_PLAYER_NAME);

    if(strcmp(gString, playerInfo[playerid][pName]) != 0) {
        SetPlayerName(playerid, playerInfo[playerid][pName]);
    }

    cache_get_field_content(0, "EMail", playerInfo[playerid][pEMail], SQL, 128);
    cache_get_field_content(0, "Referral", playerInfo[playerid][pReferral], SQL, MAX_PLAYER_NAME);

    playerInfo[playerid][pSQLID] = cache_get_field_content_int(0, "ID");
    playerInfo[playerid][pTutorial] = bool:cache_get_field_content_int(0, "Tutorial");
    playerInfo[playerid][pGender] = cache_get_field_content_int(0, "Gender");
    playerInfo[playerid][pAge] = cache_get_field_content_int(0, "Age");
    playerInfo[playerid][pSkin] = cache_get_field_content_int(0, "Skin");
    playerInfo[playerid][pAdmin] = cache_get_field_content_int(0, "Admin");
    playerInfo[playerid][pHelper] = cache_get_field_content_int(0, "Helper");
    playerInfo[playerid][pLevel] = cache_get_field_content_int(0, "Level");
    playerInfo[playerid][pWantedLevel] = cache_get_field_content_int(0, "playerWantedLevel");
    playerInfo[playerid][pJailTime] = cache_get_field_content_int(0, "playerJailTime");
    
	cache_get_field_content(0, "playerCrime1", playerInfo[playerid][pCrime1]);
	cache_get_field_content(0, "playerCrime2", playerInfo[playerid][pCrime2]);
	cache_get_field_content(0, "playerCrime3", playerInfo[playerid][pCrime3]);

    if(playerInfo[playerid][pWantedLevel] > 0) {
		playerInfo[playerid][pWantedExpire] = 300;

		PlayerTextDrawSetString(playerid, ptd_wanted, "wanted expires in ~g~10:00 minutes");
		PlayerTextDrawShow(playerid, ptd_wanted);
		SetPlayerWantedLevel(playerid, playerInfo[playerid][pWantedLevel]);
	}

    playerInfo[playerid][pGroup] = cache_get_field_content_int(0, "playerGroup");
    playerInfo[playerid][pGroupRank] = cache_get_field_content_int(0, "playerGroupRank");
    playerInfo[playerid][pFactionWarns] = cache_get_field_content_int(0, "playerFactionWarns");
    playerInfo[playerid][pFactionPunish] = cache_get_field_content_int(0, "playerFactionPunish");
    playerInfo[playerid][pGroupJoin] = cache_get_field_content_int(0, "playerGroupJoin");
    playerInfo[playerid][pFactionRaport1] = cache_get_field_content_int(0, "FactionRaport1");
    playerInfo[playerid][pFactionRaport2] = cache_get_field_content_int(0, "FactionRaport2");
    playerInfo[playerid][pFactionRaport3] = cache_get_field_content_int(0, "FactionRaport3");
    playerInfo[playerid][pRaportPlaying] = cache_get_field_content_int(0, "RaportPlaying");
    playerInfo[playerid][pRespectPoints] = cache_get_field_content_int(0, "RespectPoints");
    playerInfo[playerid][pReferralSQLID] = cache_get_field_content_int(0, "ReferralSQLID");
    playerInfo[playerid][pReferralRespectPoints] = cache_get_field_content_int(0, "ReferralRespectPoints");
    playerInfo[playerid][pReferralCash] = cache_get_field_content_int(0, "ReferralCash");
    playerInfo[playerid][pMoney] = cache_get_field_content_int(0, "Money");
    playerInfo[playerid][pMoneyStore] = cache_get_field_content_int(0, "MoneyStore");
    playerInfo[playerid][pBank] = cache_get_field_content_int(0, "Bank");
    playerInfo[playerid][pBankStore] = cache_get_field_content_int(0, "BankStore");
    playerInfo[playerid][pHours] = cache_get_field_content_float(0, "Hours");
    playerInfo[playerid][pSeconds] = cache_get_field_content_float(0, "Seconds");
    playerInfo[playerid][pMute] = (gettime() + cache_get_field_content_int(0, "Mute"));
    playerInfo[playerid][pReportMute] = (gettime() + cache_get_field_content_int(0, "ReportMute"));
    playerInfo[playerid][pQuestionMute] = (gettime() + cache_get_field_content_int(0, "QuestionMute"));
    playerInfo[playerid][pWarn] = cache_get_field_content_int(0, "Warn");
    playerInfo[playerid][pRent] = cache_get_field_content_int(0, "Rent");
    playerInfo[playerid][pSpawnType] = e_pSpawnTypes:cache_get_field_content_int(0, "SpawnType");
    playerInfo[playerid][pHouse] = cache_get_field_content_int(0, "House");
    playerInfo[playerid][pBusiness] = cache_get_field_content_int(0, "Business");
    playerInfo[playerid][pPhoneBook] = bool:cache_get_field_content_int(0, "PhoneBook");
    playerInfo[playerid][pPhoneNumber] = cache_get_field_content_int(0, "PhoneNumber");
    playerInfo[playerid][pPhoneCredit] = cache_get_field_content_int(0, "PhoneCredit");
    playerInfo[playerid][pWalkieTalkie] = bool:cache_get_field_content_int(0, "WalkieTalkie");
    playerInfo[playerid][pFrequency] = cache_get_field_content_int(0, "Frequency");
    playerInfo[playerid][pFightingStyle] = cache_get_field_content_int(0, "FightingStyle");
    playerInfo[playerid][pJob] = cache_get_field_content_int(0, "Job");
    playerInfo[playerid][pFishermanSkill] = cache_get_field_content_int(0, "FishermanSkill");
    playerInfo[playerid][pFarmerSkill] = cache_get_field_content_int(0, "FarmerSkill");
    playerInfo[playerid][pFiremanSkill] = cache_get_field_content_int(0, "FiremanSkill");
    playerInfo[playerid][pBusDriverSkill] = cache_get_field_content_int(0, "BusDriverSkill");
    playerInfo[playerid][pHunterSkill] = cache_get_field_content_int(0, "HunterSkill"); 
    playerInfo[playerid][pCourierSkill] = cache_get_field_content_int(0, "CourierSkill");   
    playerInfo[playerid][pDrugs] = cache_get_field_content_int(0, "Drugs");
    playerInfo[playerid][pDrugsDealerSkill] = cache_get_field_content_int(0, "DrugsDealerSkill");
    playerInfo[playerid][pMaterials] = cache_get_field_content_int(0, "Materials");
    playerInfo[playerid][pArmsDealerSkill] = cache_get_field_content_int(0, "ArmsDealerSkill");
    playerInfo[playerid][pTruckerSkill] = cache_get_field_content_int(0, "TruckerSkill");
    playerInfo[playerid][pRepairKits] = cache_get_field_content_int(0, "RepairKits");
    playerInfo[playerid][pDayQuest] = cache_get_field_content_int(0, "DayQuest");
    playerInfo[playerid][pPin] = cache_get_field_content_int(0, "Pin");
    playerInfo[playerid][pVehiclesSlots] = cache_get_field_content_int(0, "VehiclesSlots");
    playerInfo[playerid][pTOGPay] = bool:cache_get_field_content_int(0, "TOGPay");
    playerInfo[playerid][pTOGSurf] = bool:cache_get_field_content_int(0, "TOGSurf");
    playerInfo[playerid][pDrivingLicense] = cache_get_field_content_int(0, "DrivingLicense");
    playerInfo[playerid][pWeaponLicense] = cache_get_field_content_int(0, "WeaponLicense");
    playerInfo[playerid][pFlyLicense] = cache_get_field_content_int(0, "FlyLicense");
    playerInfo[playerid][pBoatLicense] = cache_get_field_content_int(0, "BoatLicense");
    playerInfo[playerid][pPremiumPoints] = cache_get_field_content_int(0, "PremiumPoints");
    playerInfo[playerid][pHeadValue] = cache_get_field_content_int(0, "HeadValue");

    clearChat(playerid, 65);

    if(playerInfo[playerid][pTutorial]) {
        TogglePlayerSpectating(playerid, false);

        new LastLogin[64]; 

        cache_get_field_content(0, "LastLogin", LastLogin, SQL, 64);

        SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Welcome back, %s!", GetName(playerid)); 
        SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Your last connection was %s.", LastLogin);

        loadSkins(playerid);

        loadPlayerHUD(playerid);

        SetPlayerFightingStyle(playerid, playerInfo[playerid][pFightingStyle]);
         if(playerInfo[playerid][pHeadValue] >= 10000) Iter_Add(Contracts, playerid);
        if(playerInfo[playerid][pPhoneNumber] != 0)
            MAP_insert_val_val(phoneNumbers, playerInfo[playerid][pPhoneNumber], playerid);

        if(cache_get_field_content_int(0, "TOGWalkieTalkie") && playerInfo[playerid][pWalkieTalkie] && playerInfo[playerid][pFrequency] != 0)
            Iter_Add(serverFrequency[playerInfo[playerid][pFrequency]], playerid);

        if(playerInfo[playerid][pRent] != -1) 
            playerInfo[playerid][pRent] --;

        if(playerInfo[playerid][pHouse] != -1) { 
            playerInfo[playerid][pHouse] --;
            HouseInfo[playerInfo[playerid][pHouse]][hOwnerGameID] = playerid;
        }

        if(playerInfo[playerid][pBusiness] != -1) {
            playerInfo[playerid][pBusiness] --;
            bizzInfo[playerInfo[playerid][pBusiness]][bOwnerGameID] = playerid;
        }

        if(playerInfo[playerid][pAdmin] >= 1) {
            Iter_Add(serverAdmins, playerid);
            Iter_Add(serverStaff, playerid);

            playerInfo[playerid][pPlayersHelped] = cache_get_field_content_int(0, "PlayersHelped");
            playerInfo[playerid][pTOGFind] = bool:cache_get_field_content_int(0, "TOGFind");
            playerInfo[playerid][pAdminWarns] = cache_get_field_content_int(0, "AdminWarns");

            playerInfo[playerid][pHUDAdminStats] = bool:cache_get_field_content_int(0, "HUDAdminStats");

            if(playerInfo[playerid][pHUDAdminStats]) {
                TextDrawShowForPlayer(playerid, ReportsTD);

                if(playerInfo[playerid][pAdmin] > 4) 
                    TextDrawShowForPlayer(playerid, AStatsTD);
            }

            SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}You are a %d level admin. There are %d admins online.", playerInfo[playerid][pAdmin], Iter_Count(serverAdmins));
            SendStaff(COLOR_HELPERCHAT, "(HelloBot): Admin %s just logged in.", GetName(playerid));
        }

        if(playerInfo[playerid][pHelper] >= 1) {
            Iter_Add(serverStaff, playerid);
            Iter_Add(serverHelpers, playerid);

            playerInfo[playerid][pPlayersHelped] = cache_get_field_content_int(0, "PlayersHelped");
            playerInfo[playerid][pHelperWarns] = cache_get_field_content_int(0, "HelperWarns");
            
            SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}You are a %d level helper. There are %d helpers online.", playerInfo[playerid][pHelper], Iter_Count(serverHelpers));
            SendStaff(COLOR_HELPERCHAT, "(HelloBot): Helper %s just logged in.", GetName(playerid));
        }
        if(playerInfo[playerid][pGroup] > 0) 
        {
            SendGroupMessage(playerInfo[playerid][pGroup], COLOR_TEAL, "[GROUP] {ffffff}%s from your group has just logged in.", GetName(playerid));
            SCMf(playerid, COLOR_TEAL, "Group MOTD: {ffffff}%s",  groupVariables[playerInfo[playerid][pGroup]][gMOTD]);
        }

        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT `FriendName`, `FriendSQLID` FROM `server_friends` WHERE `PlayerSQLID` = %d LIMIT "#MAX_FRIENDS"", playerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gQuery, "loadPlayerFriends", "dd", playerid, playerInfo[playerid][pSQLID]);

        if(playerInfo[playerid][pLevel] >= 3) {
            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_personal_vehicles` WHERE `OwnerID` = %d", playerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "loadPlayerVehicles", "dd", playerid, playerInfo[playerid][pSQLID]);
        }

        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_users_emails` WHERE `To` = %d", playerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gQuery, "loadPlayerEmails", "dd", playerid, playerInfo[playerid][pSQLID]);

        loadPlayerQuests(playerid);

        if(playerInfo[playerid][pPin] != -1) {
            playerInfo[playerid][pLoginTimer] = defer pinTimer(playerid);
            SCM(playerid, COLOR_YELLOW, "* You have 20 seconds available to enter your pin.");
            showPlayerPinTextdraws(playerid, PIN_LOGIN_TYPE);
        }
        else {
            SCM(playerid, COLOR_YELLOW, "* Because you don't have a pin setted, you need to set a 4-digits pin recommended for your account security.");
            showPlayerPinTextdraws(playerid, PIN_SET_TYPE);
        }
    }
    else {
        SCM(playerid, COLOR_GREEN, "SERVER: {FFFFFF}Complete the next dialogs with correct sentences.");
        Dialog_Show(playerid, EMAIL, DIALOG_STYLE_INPUT, "SERVER: Register", "Enter your e-mail address below:", "Ok", "");
    }

    cache_delete(playerInfo[playerid][pSQLLoginCache]);
    playerInfo[playerid][pSQLLoginCache] = Cache: 0;

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `LastLogin` = '%e', `Status` = 1, `PlayerID` = %d WHERE `ID` = %d", getDateTime(), playerid, playerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");
        
    Iter_Add(serverPlayers, playerid); 

    MAP_insert_str_val(playersNames, GetName(playerid), playerid);
    MAP_insert_val_val(playersSQLID, playerInfo[playerid][pSQLID], playerid);

    playerTextdraws[playerid][NameTD] = CreatePlayerTextDraw(playerid, 85.072502, 430.5, GetName(playerid));
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][NameTD], 0.180731, 1.121665);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][NameTD], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][NameTD], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][NameTD], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][NameTD], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][NameTD], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][NameTD], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][NameTD], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][NameTD]);

    SetPlayerScore(playerid, playerInfo[playerid][pLevel]);

    SetSpawnInfo(playerid, 1, playerInfo[playerid][pSkin], 479.7054, -1498.8781, 20.4735, 268.9406, -1, -1, -1, -1, -1, -1);
    SetPlayerColorEx(playerid);

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetMoney(playerid) <= 999999998 && GetMilliards(playerid) < 1 ? GetMoney(playerid) : 999999999);
    return 1;
}

function giveReferralPlayerRewards(const playerid, const userid) {
    new     
        cash = 8000 + random(4000),
        rp = 1 + random(2);

    if(userid == -1) {
        if(cache_get_field_content_int(0, "ReferralRespectPoints") > 50 || cache_get_field_content_int(0, "ReferralCash") > 50000000)
            return 1;
    }
    else { 
        if(playerInfo[userid][pReferralRespectPoints] > 50 || playerInfo[userid][pReferralRespectPoints] > 50000000)
            return sendSplittedMessageToPlayer(userid, COLOR_GREEN, -1, "(Referral): {ffffff}%s has reached level %d, you need to collect your rewards from [/refstats] to receive your rewards next time.", GetName(playerid), playerInfo[playerid][pLevel]);
    
        sendSplittedMessageToPlayer(userid, COLOR_GREEN, -1, "(Referral): {ffffff}%s has reached level %d, your referral reward is: $%s, %d respect points. (added to /refstats)", GetName(playerid), playerInfo[playerid][pLevel], formatNumber(cash), rp);

        playerInfo[userid][pReferralCash] += cash;
        playerInfo[userid][pReferralRespectPoints] += rp;
    }

    return va_mysql_tquery("UPDATE `server_users` SET `ReferralCash` = `ReferralCash` + %d, `ReferralRespectPoints` = `ReferralRespectPoints` + %d WHERE `ID` = %d", cash, rp, playerInfo[playerid][pReferralSQLID]);
}

loadPlayerHUD(const playerid) {
    playerInfo[playerid][pHUDFps] = bool:cache_get_field_content_int(0, "HUDFps");
    playerInfo[playerid][pHUDDMG] = bool:cache_get_field_content_int(0, "HUDDMG");
    playerInfo[playerid][pHUDShowAHp] = bool:cache_get_field_content_int(0, "HUDShowAHp");
    playerInfo[playerid][pHUDSpeedometer] = bool:cache_get_field_content_int(0, "HUDSpeedometer");

    if(playerInfo[playerid][pHUDFps]) {
        playerTextdraws[playerid][FpsTD] = CreatePlayerTextDraw(playerid, 2.000000, 432.044616, "~y~...");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][FpsTD], 0.400000, 1.600000);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][FpsTD], 1);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][FpsTD], -16776961);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][FpsTD], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][FpsTD], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][FpsTD], 3);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][FpsTD], 1);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][FpsTD]);
    }

    if(playerInfo[playerid][pHUDDMG]) {
        playerTextdraws[playerid][DMG] = CreatePlayerTextDraw(playerid, 145.000000, 320.666809, "");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][DMG], 0.240500, 0.921776);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][DMG], 1);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][DMG], -1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][DMG], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][DMG], 1);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][DMG], 1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][DMG], 1);
    }

    if(playerInfo[playerid][pHUDShowAHp]) {
        playerTextdraws[playerid][HealthTD] = CreatePlayerTextDraw(playerid, 577.500000, 64.310974, "...");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][HealthTD], 0.238500, 1.276444);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][HealthTD], 2);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][HealthTD], -1);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][HealthTD], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][HealthTD], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][HealthTD], 2);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][HealthTD], 1);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][HealthTD]);

        playerVars[playerid][var_healtharmourhudtimer] = repeat healthArmourHUDUpdate(playerid);
    }
    return 1;
}

function spectatePlayer(const playerid, const userID) {
    playerTextdraws[playerid][SpecTD] = CreatePlayerTextDraw(playerid, 318.100006, 316.933410, "loading...");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][SpecTD], 0.288553, 1.338277);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][SpecTD], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][SpecTD], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][SpecTD], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][SpecTD], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][SpecTD], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][SpecTD], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][SpecTD], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][SpecTD]);

    TogglePlayerSpectating(playerid, true);

    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(userID)); 
    SetPlayerInterior(playerid, GetPlayerInterior(userID));

    if(IsPlayerInAnyVehicle(userID))
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userID));

    else PlayerSpectatePlayer(playerid, userID);

    playerVars[playerid][var_SpectatePlayer] = userID;
    playerVars[userID][var_spectateMe] = playerid; 
    playerVars[playerid][var_spectateseconds] = gettime() + 300;
    
    new Float:health;
    GetPlayerHealth(playerid, health); 

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {FFFFFF}%s is spectating %s (%d)%s.", GetName(playerid), GetName(userID), userID, reportInfo[userID][rReportType] == REPORT_TYPE_STUCK ? " (stuck)" : reportInfo[userID][rReported] == 1 ? " (reported for DM/Cheats)" : "");
    
    if(playerInfo[userID][pAFKSeconds] > 9) {
        SCMf(playerid, COLOR_PINK, "[SPEC] %s (%d) | Level %d | Health: %0.2f | Seconds: %.0f | Ping: %d | FPS: %d | AFK: yes (for %d seconds)", GetName(userID), userID, playerInfo[userID][pLevel], health, playerInfo[userID][pSeconds], GetPlayerPing(userID), playerVars[userID][var_FPS], playerInfo[userID][pAFKSeconds]);
    }
    else {
        SCMf(playerid, COLOR_PINK, "[SPEC] %s (%d) | Level %d | Health: %0.2f | Seconds: %.0f | Ping: %d | FPS: %d | AFK: no", GetName(userID), userID, playerInfo[userID][pLevel], health, playerInfo[userID][pSeconds], GetPlayerPing(userID), playerVars[userID][var_FPS]);
    }
    
    SCM(playerid, COLOR_PINK, "* Press 'SPACE' to pick a random player.");

    playerVars[playerid][var_spectatetimer] = repeat spectateTimer(playerid);

    if(reportInfo[userID][rReportType] == REPORT_TYPE_STUCK || reportInfo[userID][rReported]) {
        playerInfo[playerid][pPlayersHelped] ++;

        va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    }

    if(reportInfo[userID][rReportType] == REPORT_TYPE_STUCK) { 
        reportInfo[userID][rReportType] = REPORT_TYPE_DELETED;
        reportInfo[userID][rReportText][0] = EOS;

        Iter_Remove(serverReports, userID);
    }

    if(reportInfo[userID][rReported]) {
        reportInfo[userID][rReported] = 0;

        if(Iter_Remove(serverReports, reportInfo[userID][rReportedBy]) != INVALID_ITERATOR_SLOT) {
            reportInfo[reportInfo[userID][rReportedBy]][rReportText][0] = EOS;
            reportInfo[reportInfo[userID][rReportedBy]][rReportType] = REPORT_TYPE_DELETED; 
            reportInfo[reportInfo[userID][rReportedBy]][rReportedPlayer] = reportInfo[userID][rReportedBy] = -1;
        }
    }
    return 1;
}

checkVehicleRadio(const vehicleid, const playerid) {
    if(!vehicleVars[vehicleid][var_carRadio])
        return 1;

    ++ radioListeners[vehicleVars[vehicleid][var_carRadio] - 1];
    return PlayAudioStreamForPlayer(playerid, radioSelected[vehicleVars[vehicleid][var_carRadio] - 1][0]);
}

function PlayAudioStreamForPlayers(const vehicleid, url[]) {
    new 
        count, modelid = GetVehicleModel(vehicleid) - 400;

    foreach(new i : playersInVehicles) {
        if(GetPlayerVehicleID(i) != vehicleid) 
            continue;

        if(++count == aVehicleSeatsCount[modelid])
            break;

        PlayAudioStreamForPlayer(i, url); 
        ++ radioListeners[vehicleVars[vehicleid][var_carRadio] - 1];
    }
    return 1;
}

function StopAudioStreamForPlayers(const vehicleid) {
    new 
        count, modelid = GetVehicleModel(vehicleid) - 400;

    foreach(new i : playersInVehicles) {
        if(GetPlayerVehicleID(i) != vehicleid) 
            continue;

        if(++count == aVehicleSeatsCount[modelid])
            break;

        StopAudioStreamForPlayer(i); 
        -- radioListeners[vehicleVars[vehicleid][var_carRadio] - 1];
    }
    return 1;
}

function showPlayerStatsToPlayer(const playerid, const userID) {
    new 
        house_str[12] = "no";

    SCM(playerid, COLOR_GREEN, "___________________________________________________");
    SCMf(playerid, COLOR_WHITE, "*** %s (%d) ***", GetName(userID), userID);
    SCMf(playerid, COLOR_GREEN, "General: {ffffff}%0.2f hours played, warns: %d/3", playerInfo[userID][pHours], playerInfo[userID][pWarn]);
    SCMf(playerid, COLOR_GREEN, "Account: {ffffff}level: %d (%d/%d rp), gender: %s, age: %d, referral: %s, phone: %s (credit: %d), job: %s", playerInfo[userID][pLevel], playerInfo[userID][pRespectPoints], (playerInfo[userID][pLevel] * 3), (playerInfo[userID][pGender] == FEMALE_GENDER) ? "female" : "male", playerInfo[userID][pAge], playerInfo[userID][pReferral] == '-' ? "none" : va_return(playerInfo[userID][pReferral]), playerInfo[userID][pPhoneNumber] != 0 ? va_return("%d", playerInfo[userID][pPhoneNumber]) : "none", playerInfo[userID][pPhoneCredit], playerInfo[userID][pJob] == 0 ? "None" : va_return(jobInfo[playerInfo[userID][pJob] - 1][j_Name]));
    
    gString = "no";

    if(playerInfo[userID][pRent] != -1) 
        format(gString, sizeof gString, "yes, %d", HouseInfo[playerInfo[userID][pRent]][hID]);

    SCMf(playerid, COLOR_GREEN, "Economy: {ffffff}money $%s (cash), $%s (bank), house renter (%s)", formatMoney(playerInfo[userID][pMoneyStore], playerInfo[userID][pMoney]), formatMoney(playerInfo[userID][pBankStore], playerInfo[userID][pBank]), gString);
    
    if(playerInfo[userID][pHouse] != -1) 
        format(house_str, sizeof house_str, "yes, %d", HouseInfo[playerInfo[userID][pHouse]][hID]);
    
    gString = "no";

    if(playerInfo[userID][pBusiness] != -1) 
        format(gString, sizeof gString, "yes, %d", bizzInfo[playerInfo[userID][pBusiness]][bID]);
        
    SCMf(playerid, COLOR_GREEN, "Properties: {ffffff}house (%s), business (%s), personal vehicles: %d/%d", house_str, gString, VECTOR_size(personalVehicles[userID]), playerInfo[userID][pVehiclesSlots]);
    
    gString[0] = EOS; 

    if(playerInfo[userID][pHouse] != -1) 
        format(gString, sizeof gString, "drugs (%dg in hand, %dg in house)", playerInfo[userID][pDrugs], HouseInfo[playerInfo[userID][pHouse]][hDrugs]);
    
    else format(gString, sizeof gString, "drugs (%dg in hand)", playerInfo[userID][pDrugs]);
    
    SCMf(playerid, COLOR_GREEN, "Other: {ffffff}%s, materials (%d), repair kits (%d)", gString, playerInfo[userID][pMaterials], playerInfo[userID][pRepairKits]);
    SCMf(playerid, COLOR_GREEN, "Other: {ffffff}premium points (%d)", playerInfo[userID][pPremiumPoints]);

    if(playerInfo[userID][pAdmin]) 
        SCMf(playerid, COLOR_GREEN, "Admin Info: {ffffff}interior %d, vw %d, %.0f active seconds, sqlid: %d", GetPlayerInterior(userID), GetPlayerVirtualWorld(userID), playerInfo[userID][pSeconds], playerInfo[userID][pSQLID]);
    
    SCM(playerid, COLOR_GREEN, "___________________________________________________");
    return 1;
}

function showLicenses(const playerid, const userID) {
    static enum s_l_e_licensesStructure {
        licenseName[16],
        e_pInfo:licenseIdx
    }

    static const licensesStructure[][s_l_e_licensesStructure] = {
        {"Driving", pDrivingLicense},
        {"Fly", pFlyLicense},
        {"Weapon", pWeaponLicense},
        {"Boat", pBoatLicense}
    };

    SCMf(userID, COLOR_GREY, "-------------- %s's licenses ------------------", GetName(playerid));
    
    for(new i = 0; i < sizeof licensesStructure; ++i) {
        gString[0] = EOS;

        if(!playerInfo[playerid][licensesStructure[i][licenseIdx]]) 
            format(gString, sizeof gString, "%s License: Expired", licensesStructure[i][licenseName]);

        else if(playerInfo[playerid][licensesStructure[i][licenseIdx]] > 0)
            format(gString, sizeof gString, "%s License: Available (%d hours)", licensesStructure[i][licenseName], playerInfo[playerid][licensesStructure[i][licenseIdx]]);

        else if(playerInfo[playerid][licensesStructure[i][licenseIdx]] < 0) 
            format(gString, sizeof gString, "%s License: Suspended (%d hours)", licensesStructure[i][licenseName], playerInfo[playerid][licensesStructure[i][licenseIdx]] * -1);

        SCM(userID, COLOR_WHITE, gString); 
    }
    
    SCM(userID, COLOR_GREY, "----------------------------------------");
    return 1;
}

function initConnection(const playerid) {
    stop playerInfo[playerid][pLoginTimer];

    anticheatInfo[playerid][ac_lastvehicle] = anticheatInfo[playerid][ac_entervehtime] = reportInfo[playerid][rReportConversation] = -1;

    playerInfo[playerid] = playerInfo[MAX_PLAYERS]; 
    playerVars[playerid] = playerVars[MAX_PLAYERS];
    memset(playerTextdraws[playerid], -1);

    GetPlayerName(playerid, playerInfo[playerid][pName], MAX_PLAYER_NAME);
    GetPlayerIp(playerid, playerInfo[playerid][pIPAddress]);
    playerInfo[playerid][pIntIP] = IPToInt(playerInfo[playerid][pIPAddress]);

    loadPlayerAnimations(playerid);
    return 1;
}

function resetVarsOnDisconnect(const playerid) {
    stop playerInfo[playerid][pLoginTimer]; 
    stop playerVars[playerid][var_spectatetimer];
    stop playerVars[playerid][var_ad_timer];
    stop playerVars[playerid][var_healtharmourhudtimer];
    stop playerVars[playerid][var_speedometertimer];

    Iter_Remove(serverPlayers, playerid);

    MAP_remove_str(playersNames, GetName(playerid));
    MAP_remove_val(playersSQLID, playerInfo[playerid][pSQLID]);

    RemovePlayerAttachedObject(playerid, INDEX_HELMET); 
    RemovePlayerAttachedObject(playerid, INDEX_PHONE);

    if(playerInfo[playerid][pSQLLoginCache] != Cache: 0) 
        cache_delete(playerInfo[playerid][pSQLLoginCache]);

    if(playerVars[playerid][var_working])
        stopWork(playerid);

    if(getPlayerLastVehicle(playerid) != -1) {
        if(vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio])
            --radioListeners[vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio]-1];

        Iter_Remove(playersInVehicles, playerid);
    }

    new const front = Queue_GetFrontValue(loginQueue);

    if(Queue_RemoveValue(loginQueue, playerid)) {
        if(front == playerid) 
            pickNextPlayerFromLoginQueue(true);

        else 
            updateLoginQueueTextdraws(true);
    }

    if(playerVars[playerid][var_rentedcar] != -1) 
        destroyPlayerRentVehicle(playerid);

    if(playerInfo[playerid][pWalkieTalkie] && playerInfo[playerid][pFrequency] != 0)
        Iter_Remove(serverFrequency[playerInfo[playerid][pFrequency]], playerid);

    if(playerInfo[playerid][pPhoneNumber] != 0) 
        MAP_remove_val(phoneNumbers, playerInfo[playerid][pPhoneNumber]);

    if(playerVars[playerid][var_incall] != -1) {
        SetPlayerSpecialAction(playerVars[playerid][var_incall], SPECIAL_ACTION_STOPUSECELLPHONE); 
        RemovePlayerAttachedObject(playerVars[playerid][var_incall], INDEX_PHONE);

        SCM(playerVars[playerid][var_incall], -1, "The other person ended the call.");

        playerVars[playerVars[playerid][var_incall]][b_PHONE_SPEAKER] = false;
        playerVars[playerid][var_incall] = playerVars[playerVars[playerid][var_incall]][var_incall] = playerVars[playerVars[playerid][var_incall]][var_calls] = playerVars[playerid][var_calls] = playerVars[playerid][var_callfrom] = playerVars[playerVars[playerid][var_incall]][var_callfrom] = -1;
    }

    if(playerInfo[playerid][pHouse] != -1) 
        HouseInfo[playerInfo[playerid][pHouse]][hOwnerGameID] = -1;

    if(playerInfo[playerid][pBusiness] != -1) 
        bizzInfo[playerInfo[playerid][pBusiness]][bOwnerGameID] = -1;

    if(playerVars[playerid][var_SpectatePlayer] != -1)
        playerVars[playerVars[playerid][var_SpectatePlayer]][var_spectateMe] = -1;

    if(playerVars[playerid][var_spectateMe] != -1) {
        TogglePlayerSpectating(playerVars[playerid][var_spectateMe], false); 
        SetCameraBehindPlayer(playerVars[playerid][var_spectateMe]);

        playerVars[playerVars[playerid][var_spectateMe]][var_SpectatePlayer] = playerVars[playerVars[playerid][var_spectateMe]][var_spectateseconds] = -1; 
        
        playerTextDrawDestroy(playerVars[playerid][var_spectateMe], playerTextdraws[playerVars[playerid][var_spectateMe]][SpecTD]); 
        
        stop playerVars[playerVars[playerid][var_spectateMe]][var_spectatetimer];

        SCM(playerVars[playerid][var_spectateMe], COLOR_GREY, "* You are no longer spectator because currently player has disconnected.");
    }

    if(reportInfo[playerid][rReportedBy] != -1) {
        Iter_Remove(serverReports, reportInfo[playerid][rReportedBy]);

        reportInfo[reportInfo[playerid][rReportedBy]][rReportText][0] = EOS;
        reportInfo[reportInfo[playerid][rReportedBy]][rReportedPlayer] = reportInfo[reportInfo[playerid][rReportedBy]][rReportType] = REPORT_TYPE_DELETED;
    }

    reportInfo[playerid][rReportText] = reportInfo[playerid][rReportedPlayer] = reportInfo[playerid][rReportedBy] = reportInfo[playerid][rReportType] = REPORT_TYPE_DELETED; 
    reportInfo[playerid][rReported] = 0;

    if(reportInfo[playerid][rReportConversation] != -1) {
        SCM(reportInfo[playerid][rReportConversation], COLOR_YELLOW, "* Conversatia a fost terminata deoarece jucatorul respectiv s-a deconectat.");

        reportInfo[reportInfo[playerid][rReportConversation]][rReportConversation] = reportInfo[playerid][rReportConversation] = -1;
    }
    
    Iter_Remove(serverReports, playerid);
    Iter_Remove(serverQuestions, playerid); 

    if(playerVars[playerid][var_calls] != -1) 
        playerVars[playerVars[playerid][var_calls]][var_callfrom] = -1;

    DestroyDynamicObject(playerVars[playerid][var_objectweapon]);

    Iter_Remove(serverAdmins, playerid); 
    Iter_Remove(serverHelpers, playerid); 
    Iter_Remove(serverStaff, playerid); 

    Iter_Clear(playersStreamed[playerid]); 
    Iter_Clear(vehiclesStreamed[playerid]);
    return 1;
}

wrongPass(const playerid) {
    if(++playerInfo[playerid][pLoginTries] == 3) {
        defer delayedKick(playerid);

        SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {FFFFFF}%s has been kicked because he have 3/3 incorrect attempts to login.", GetName(playerid));
        return sendError(playerid, "Ai primit kick deoarece ai gresit parola de 3 ori.");
    }
    return Dialog_Show(playerid, LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "Your password was invalid!\nPlease enter your correct account password.", "Login", "Quit");
}

function OnLoginRegisterPassword(const playerid, const success) {
    if(!IsPlayerConnected(playerid))
        return 1;

    switch(success) {
        case 0: {
            wrongPass(playerid);
        }
        case 1: {
            onPlayerLogin(playerid);
        }
        case 2: {
            bcrypt_get_hash(playerInfo[playerid][pPassword], 65);

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_users` (Name, Password) VALUES ('%e', '%e')", GetName(playerid), playerInfo[playerid][pPassword]);
            mysql_tquery(SQL, gQuery, "onPlayerRegister", "dd", playerid, raceCheckThreads[playerid]);
        }
    }
    return 1;
}

function givePayday(const playerid) {
    if(playerInfo[playerid][pSeconds] / 60 >= 30) 
        updatePlayerQuestProgress(playerid, QUEST_TYPE_PLAYTIME);

    new 
        hour, minute;

    gettime(hour, minute);

    GameTextForPlayer(playerid, "~Y~payday    ~N~~W~arrived", 4000, 1);
    SCM(playerid, COLOR_GREEN, "-------------------- [PAYDAY] --------------------");
    SCMf(playerid, COLOR_WHITE, "Salariul tau a sosit. Ceasul este acum %02d:%02d.", hour, minute);
    SCMf(playerid, COLOR_WHITE, "Ai primit %.2f ore jucate. (%.0f minute)", (playerInfo[playerid][pSeconds] / 3600), (playerInfo[playerid][pSeconds] / 60));
    SCMf(playerid, COLOR_WHITE, "Salariu: $%s", formatNumber(playerInfo[playerid][pLevel] * 125));

    if(playerInfo[playerid][pRent] != -1) { 
        if(GetMoney(playerid) < HouseInfo[playerInfo[playerid][pRent]][hRentPrice] && GetMilliards(playerid) < 1) {
            removeHouseRenter(playerid);

            playerInfo[playerid][pSpawnType] = SPAWN_TYPE_NORMAL; 

            SCM(playerid, COLOR_BROWN, "Ai fost dat afara din chirie deoarece nu ai avut bani pentru a o platii.");

            va_mysql_tquery("UPDATE `server_users` SET `Rent` = -1, `SpawnType` = 1 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);
        }
        else {
            SCMf(playerid, COLOR_WHITE, "Rent: Ai platit $%s propietarului casei cu id %d.", formatNumber(HouseInfo[playerInfo[playerid][pRent]][hRentPrice]), HouseInfo[playerInfo[playerid][pRent]][hID]);
            
            substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, HouseInfo[playerInfo[playerid][pRent]][hRentPrice], false);
            HouseInfo[playerInfo[playerid][pRent]][hBalance] += HouseInfo[playerInfo[playerid][pRent]][hRentPrice];
            
            va_mysql_tquery("UPDATE `server_houses` SET `Balance` = %d WHERE `ID` = %d", HouseInfo[playerInfo[playerid][pRent]][hBalance], HouseInfo[playerInfo[playerid][pRent]][hID]);
        }
    }

    playerInfo[playerid][pHours] += (playerInfo[playerid][pSeconds] / 3600);
    playerInfo[playerid][pSeconds] = 0;

    playerInfo[playerid][pRespectPoints] ++;
    SCMf(playerid, COLOR_WHITE, "Ai primit un punct de respect. Mai ai nevoie de %d puncte de respect pentru a avansa in level.", ((playerInfo[playerid][pLevel] * 3)-playerInfo[playerid][pRespectPoints] <= -1) ? (0) : (playerInfo[playerid][pLevel] * 3)-playerInfo[playerid][pRespectPoints]);

    addBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], 0, (playerInfo[playerid][pLevel] * 125), false);
    
    if((playerInfo[playerid][pLevel] * 3) <= playerInfo[playerid][pRespectPoints])
        SCM(playerid, COLOR_BROWN, "Ai punctele de respect necesare pentru a avansa in nivel. Tasteaza [/buylevel].");

    if(playerInfo[playerid][pDrivingLicense] != 0) 
        playerInfo[playerid][pDrivingLicense] = playerInfo[playerid][pDrivingLicense] < 0 ? playerInfo[playerid][pDrivingLicense]+1 : playerInfo[playerid][pDrivingLicense]-1;

    if(playerInfo[playerid][pFlyLicense] != 0) 
        playerInfo[playerid][pFlyLicense] = playerInfo[playerid][pFlyLicense] < 0 ? playerInfo[playerid][pFlyLicense]+1 : playerInfo[playerid][pFlyLicense]-1;

    if(playerInfo[playerid][pWeaponLicense] != 0) 
        playerInfo[playerid][pWeaponLicense] = playerInfo[playerid][pWeaponLicense] < 0 ? playerInfo[playerid][pWeaponLicense]+1 : playerInfo[playerid][pWeaponLicense]-1;

    if(playerInfo[playerid][pBoatLicense] != 0) 
        playerInfo[playerid][pBoatLicense] = playerInfo[playerid][pBoatLicense] < 0 ? playerInfo[playerid][pBoatLicense]+1 : playerInfo[playerid][pBoatLicense]-1;

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `BankStore` = %d, `Bank` = %d, `Hours` = '%f', `Seconds` = 0, `RespectPoints` = %d WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], playerInfo[playerid][pHours], playerInfo[playerid][pRespectPoints], playerInfo[playerid][pSQLID]);
    
    SCM(playerid, COLOR_GREEN, "--------------------------------------------------");
    return 1;
}

function OnChangePass(playerid, bool:success) {
    if(GetPVarInt(playerid, "changePassPass") == 1) {
        if(!success)
            return sendError(playerid, "Parola introdusa nu corespunde cu cea a contului.");

        SetPVarInt(playerid, "changePassPass", 2);

        return Dialog_Show(playerid, CHANGEPASS, DIALOG_STYLE_PASSWORD, "SERVER: Change Pass", "Insert your new password in box below:", "Ok", "Exit");
    }

    bcrypt_get_hash(playerInfo[playerid][pPassword], 65);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `Password` = '%e' WHERE `ID` = %d", playerInfo[playerid][pPassword], playerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");

    SCM(playerid, COLOR_YELLOW, "* Your password was changed successfully.");

    playerVars[playerid][var_changepass_delay] = gettime() + 180;
    
    return DeletePVar(playerid, "changePassPass");
}

resetVehicleVars(const vehicleid) {
    vehicleVars[vehicleid][var_carEngine] = vehicleVars[vehicleid][var_carLights] = vehicleVars[vehicleid][var_carBoot] = vehicleVars[vehicleid][var_carBoonet] = vehicleVars[vehicleid][var_carLocked] = false; 
    vehicleVars[vehicleid][var_carRadio] = 0; 
    vehicleVars[vehicleid][var_carPersonal] = -1; 
    vehicleVars[vehicleid][var_carFuel] = 100.99;

    if(getVehicleModelType(GetVehicleModel(vehicleid)) == VEHICLE_MODEL_TYPE_BIKE) {
        SetVehicleParamsEx(vehicleid, 1, 0, 0, 0, 0, 0, 0);
        vehicleVars[vehicleid][var_carEngine] = true;
    }
    else SetVehicleParamsEx(vehicleid, 0, 0, 0, 0, 0, 0, 0);

    return 1;
}

updateLoginQueueTextdraws(bool:updatepos) {
    if(updatepos) {
        Queue_Foreach(new i : loginQueue) {
            gString[0] = EOS;
            format(gString, sizeof gString, "#%d", Queue_GetValuePos(loginQueue, i));
            PlayerTextDrawSetString(i, playerTextdraws[i][LoginQueuePositionTD], gString);
        }
    }

    gString[0] = EOS;
    format(gString, sizeof gString, "players in login queue: %d", Queue_Count(loginQueue)); 
    return TextDrawSetString(LoginQueueTD[2], gString); 
}

pickNextPlayerFromLoginQueue(bool:updatepos) {
    new const nextPlayer = Queue_GetFrontValue(loginQueue);

    if(nextPlayer == INVALID_QUEUE_VALUE)
        return 1;

    TextDrawHideForPlayer(nextPlayer, LoginQueueTD[0]); 
    TextDrawHideForPlayer(nextPlayer, LoginQueueTD[1]); 
    TextDrawHideForPlayer(nextPlayer, LoginQueueTD[2]);
    playerTextDrawDestroy(nextPlayer, playerTextdraws[nextPlayer][LoginQueuePositionTD]);

    updateLoginQueueTextdraws(updatepos);

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_bans` WHERE `Name` = '%e' AND `Active` = 1 LIMIT 1", GetName(nextPlayer)); 
    mysql_tquery(SQL, gQuery, "checkBanStatus", "d", nextPlayer);
    return 1;
}

initialisePlayerLoginQueue(const playerid) {
    Queue_InsertValue(loginQueue, playerid);

    gString[0] = EOS;
    format(gString, sizeof gString, "#%d", Queue_GetValuePos(loginQueue, playerid));

    playerTextdraws[playerid][LoginQueuePositionTD] = CreatePlayerTextDraw(playerid, 321.962158, 183.716720, gString);
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 0.777158, 3.431664);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][LoginQueuePositionTD], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 2);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 3);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][LoginQueuePositionTD], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][LoginQueuePositionTD]); 

    TextDrawShowForPlayer(playerid, LoginQueueTD[0]); 
    TextDrawShowForPlayer(playerid, LoginQueueTD[1]); 
    TextDrawShowForPlayer(playerid, LoginQueueTD[2]); 

    updateLoginQueueTextdraws(false);

    if(Queue_Count(loginQueue) == 1) 
        defer checkAccountPlayer(playerid);

    return 1;
}

showPlayerTruckerLocations(const playerid) {
    playerVars[playerid][b_ACTIVE_TIMER] = true;

    return Dialog_Show(playerid, TRUCKER, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Select Location", 
        "Location Name\tDistance\tNeeded Skill\nFlint Intersection ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nRed County ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nWillowfield ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nOcean Docks ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nMontgomery ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nEsplanade North ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nAngel Pine ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nGanton ({1C8A15}Legal{FFFFFF})\t%0.2fkm\t1\nFlint Intersection ({990000}Illegal{FFFFFF})\t%0.2fkm\t2\nRed County ({990000}Illegal{FFFFFF})\t%0.2fkm\t2\nWillowfield ({990000}Illegal{FFFFFF})\t%0.2fkm\t2\nOcean Docks ({990000}Illegal{FFFFFF})\t%0.2fkm\t2\nMontgomery ({990000}Illegal{FFFFFF})\t%0.2fkm\t3\nEsplanade North ({990000}Illegal{FFFFFF})\t%0.2fkm\t3\nAngel Pine ({990000}Illegal{FFFFFF})\t%0.2fkm\t3\nGanton ({990000}Illegal{FFFFFF})\t%0.2fkm\t3",
    "Select", "Cancel", GetPlayerDistanceFromPoint(playerid, truckerLocations[0][tr_X], truckerLocations[0][tr_Y], truckerLocations[0][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[1][tr_X], truckerLocations[1][tr_Y], truckerLocations[1][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[2][tr_X], truckerLocations[2][tr_Y], truckerLocations[2][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[3][tr_X], truckerLocations[3][tr_Y], truckerLocations[3][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[4][tr_X], truckerLocations[4][tr_Y], truckerLocations[4][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[5][tr_X], truckerLocations[5][tr_Y], truckerLocations[5][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[6][tr_X], truckerLocations[6][tr_Y], truckerLocations[6][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[7][tr_X], truckerLocations[7][tr_Y], truckerLocations[7][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[0][tr_X], truckerLocations[0][tr_Y], truckerLocations[0][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[1][tr_X], truckerLocations[1][tr_Y], truckerLocations[1][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[2][tr_X], truckerLocations[2][tr_Y], truckerLocations[2][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[3][tr_X], truckerLocations[3][tr_Y], truckerLocations[3][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[4][tr_X], truckerLocations[4][tr_Y], truckerLocations[4][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[5][tr_X], truckerLocations[5][tr_Y], truckerLocations[5][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[6][tr_X], truckerLocations[6][tr_Y], truckerLocations[6][tr_Z])/1000, GetPlayerDistanceFromPoint(playerid, truckerLocations[7][tr_X], truckerLocations[7][tr_Y], truckerLocations[7][tr_Z])/1000);
}

loadSkins(const playerid) {
    new 
        load_skins[5];
    
    gString[0] = EOS;
    cache_get_field_content(0, "Skins", gString, SQL, 64);
    sscanf(gString, "p<|>ddddd", load_skins[0], load_skins[1], load_skins[2], load_skins[3], load_skins[4]);

    Iter_Clear(playerSkins[playerid]);

    for(new i = 0; i < MAX_SKINS; ++i) {
        if(load_skins[i] != -1)
            Iter_Add(playerSkins[playerid], load_skins[i]);
    }
    return 1;
}

saveSkins(const playerid) {
    new 
        save_arr[5] = {-1, ...}, 
        x;

    foreach(new i : playerSkins[playerid]) 
        save_arr[x++] = i;

    return va_mysql_tquery("UPDATE `server_users` SET `Skins` = '%d|%d|%d|%d|%d' WHERE `ID` = %d", save_arr[0], save_arr[1], save_arr[2], save_arr[3], save_arr[4], playerInfo[playerid][pSQLID]);
}

createVehicle(const vehicletype, Float:x, Float:y, Float:z, Float:rotation, const color1, const color2, const respawn_delay, const addsiren = 0, const Float:fuel = 100.99) {
    new const vehicleid = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);

    resetVehicleVars(vehicleid);
    vehicleVars[vehicleid][var_carFuel] = fuel;
    return vehicleid;
}

TogglePlayerControllableEx(const playerid, bool:toggle) {
    playerVars[playerid][var_freezed] = !toggle;
    return TogglePlayerControllable(playerid, toggle);
}

IsPlayerLogged(const playerid) {
    if(!IsPlayerConnected(playerid)) 
        return 0;

    return playerInfo[playerid][pSQLID] > 0;
}

isPlayerDead(const playerid)
    return playerVars[playerid][var_death];

GetCheaters() {
    new result;

    foreach(new i : serverReports) {
        if(reportInfo[i][rReportType] == REPORT_TYPE_DM) ++result;
    }
    
    return result;
}

TogglePlayerSpeedometer(const playerid, bool:toggle) {
    if(toggle) {
        playerTextdraws[playerid][SpeedTD] = CreatePlayerTextDraw(playerid, 540.601440, 316.077758, "...");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][SpeedTD], 0.400000, 1.600000);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][SpeedTD], 3);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][SpeedTD], -1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][SpeedTD], 0);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][SpeedTD], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][SpeedTD], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][SpeedTD], 3);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][SpeedTD], 1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][SpeedTD], 0);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][SpeedTD]);

        playerTextdraws[playerid][kmTD] = CreatePlayerTextDraw(playerid, 542.243225, 319.866668, playerInfo[playerid][pHUDSpeedometer] ? "mp/h" : "km/h");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][kmTD], 0.249999, 1.176887);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][kmTD], 1);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][kmTD], -1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][kmTD], 0);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][kmTD], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][kmTD], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][kmTD], 1);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][kmTD], 1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][kmTD], 0);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][kmTD]);

        playerTextdraws[playerid][SpeedometerTD] = CreatePlayerTextDraw(playerid, 514.667968, 330.877929, "...");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][SpeedometerTD], 0.200499, 0.991554);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][SpeedometerTD], 1);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][SpeedometerTD], -1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][SpeedometerTD], 0);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][SpeedometerTD], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][SpeedometerTD], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][SpeedometerTD], 2);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][SpeedometerTD], 1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][SpeedometerTD], 0);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][SpeedometerTD]);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
            playerVars[playerid][var_speedometertimer] = repeat updateDriverSpeedometer(playerid); 
        }
        else {
            playerVars[playerid][var_speedometertimer] = repeat updatePassengerSpeedometer(playerid);
        }
        return 1;
    }
    playerTextDrawDestroy(playerid, playerTextdraws[playerid][SpeedTD]); 
    playerTextDrawDestroy(playerid, playerTextdraws[playerid][kmTD]);
    playerTextDrawDestroy(playerid, playerTextdraws[playerid][SpeedometerTD]);

    stop playerVars[playerid][var_speedometertimer];
    return 0;
}

givePlayerWarn(playerid, adminid, const reason[]) {
    new adminName[MAX_PLAYER_NAME] = "AdmBot";

    if(adminid != INVALID_PLAYER_ID) {
        GetPlayerName(adminid, adminName, MAX_PLAYER_NAME); 
        playerVars[adminid][var_warn_delay] = gettime() + 60;
    }

    playerInfo[playerid][pWarn] ++;

    if(playerInfo[playerid][pWarn] == 3) {
        playerInfo[playerid][pWarn] = 0; 
        givePlayerBan(playerid, INVALID_PLAYER_ID, 3, "3/3 warns");
    }

    va_mysql_tquery("UPDATE `server_users` SET `Warn` = %d WHERE `ID` = %d", playerInfo[playerid][pWarn], playerInfo[playerid][pSQLID]);

    sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been warned by %s, reason: %s", GetName(playerid), adminName, reason);
    SCMf(playerid, COLOR_GREY, "* You are warned by %s, reason: %s", adminName, reason);

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_warn_logs` (AdminSQLID, PlayerSQLID, Reason) VALUES (%d, %d, '%e')", adminid != INVALID_PLAYER_ID ? playerInfo[adminid][pSQLID] : -1, playerInfo[playerid][pSQLID], reason);
    mysql_tquery(SQL, gQuery, "", "");

    insertEmail(playerid, GetName(playerid), "AdmBot", "Admin %s warned you, reason: %s", adminName, reason);
    return 1;
}

givePlayerMute(playerid, adminid, minutes, const reason[]) {
    new adminName[MAX_PLAYER_NAME] = "AdmBot";

    if(adminid != INVALID_PLAYER_ID) {
        GetPlayerName(adminid, adminName, MAX_PLAYER_NAME); 
        playerVars[adminid][var_mute_delay] = gettime() + 60;
    }

    playerInfo[playerid][pMute] = gettime() + minutes * 60;
    va_mysql_tquery("UPDATE `server_users` SET `Mute` = %d WHERE `ID` = %d", minutes * 60, playerInfo[playerid][pSQLID]);
    
    sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been muted for %d minutes by %s, reason: %s", GetName(playerid), minutes, adminName, reason);
    SCMf(playerid, COLOR_GREY, "* You are muted now for %d minutes by %s.", minutes, adminName);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_mute_logs` (AdminSQLID, PlayerSQLID, Minutes, Reason) VALUES (%d, %d, %d, '%e')", adminid != INVALID_PLAYER_ID ? playerInfo[adminid][pSQLID] : -1, playerInfo[playerid][pSQLID], minutes, reason);
    mysql_tquery(SQL, gQuery, "", "");

    insertEmail(playerid, GetName(playerid), "AdmBot", "Admin %s muted you for %d minutes, reason: %s", adminName, minutes, reason);
    return 1;
}

givePlayerBan(playerid, adminid, days, const reason[]) {
    new adminName[MAX_PLAYER_NAME] = "AdmBot";

    if(adminid != INVALID_PLAYER_ID) { 
        GetPlayerName(adminid, adminName, MAX_PLAYER_NAME); 
        playerVars[adminid][var_ban_delay] = gettime() + 60;
    }

    if(!days) {
        sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been banned by %s permanently, reason: %s.", GetName(playerid), adminName, reason); 

        insertEmail(playerid, GetName(playerid), "AdmBot", "Admin %s banned you permanently, reason: %s", adminName, reason);
    }
    else {
        sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been banned by %s for %d days, reason: %s.", GetName(playerid), adminName, days, reason); 

        insertEmail(playerid, GetName(playerid), "AdmBot", "Admin %s banned you for %d days, reason: %s", adminName, days, reason);
    }

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_bans` (Name, PlayerSQLID, AdminName, AdminSQLID, Reason, Days, Permanent, Date, Active) VALUES ('%e', %d, '%e', %d, '%e', %d, %d, '%e', 1)", GetName(playerid), playerInfo[playerid][pSQLID], adminName, INVALID_PLAYER_ID == adminid ? 0 : playerInfo[adminid][pSQLID], reason, days == 0 ? 0 : gettime() + days * 86400, days == 0 ? 1 : 0, getDateTime());
    mysql_tquery(SQL, gQuery, "", "");

    clearChat(playerid);

    SCMf(playerid, COLOR_LIGHTRED, "(Ban System) You are %s banned by admin %s.", !days ? "permanently" : "temporary", adminName);
    SCMf(playerid, COLOR_LIGHTRED, "(Ban System) Ban reason: %s", reason);

    if(days)
        SCMf(playerid, COLOR_LIGHTRED, "(Ban System) Ban expires in %d days.", days);

    SCM(playerid, COLOR_LIGHTRED, "(Ban System) If you think you have been unfairly banned, you can make a unban ticket on: panel.Lurk.ro.");

    GameTextForPlayer(playerid, "Banned", 6000, 2);

    defer delayedKick(playerid);
    return 1;
}

sendError(playerid, const text[], va_args<>) 
    return SCMf(playerid, COLOR_GREY, "Error: {FFFFFF}%s", va_return(text, va_start<2>));

sendUsage(playerid, const text[]) 
    return SCMf(playerid, COLOR_GREY, "Usage: {FFFFFF}%s", text);

sendDeathMessage(playerid, killerid, reason) {
    foreach(new i : serverAdmins) 
        SendDeathMessageToPlayer(i, killerid, playerid, reason);

    return 1;
}

SendAdmins(color, const text[], va_args<>) {
    new string[156];
    va_format(string, sizeof string, text, va_start<2>);

    foreach(new playerid : serverAdmins) 
        SCM(playerid, color, string);
    
    return 1;
}

stock SendHelpers(color, const text[], va_args<>) {
    new string[156];
    va_format(string, sizeof string, text, va_start<2>);

    foreach(new playerid : serverHelpers) 
        SCM(playerid, color, string);
    
    return 1;
}

SendStaff(color, const text[], va_args<>) {
    new string[156];
    va_format(string, sizeof string, text, va_start<2>);

    foreach(new playerid : serverStaff) 
        SCM(playerid, color, string);
    
    return 1;
}

DisablePlayerCheckpointEx(const playerid) {
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);

    playerVars[playerid][var_checkpoint] = -1; 
    
    return PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);  
}

AdmBot(playerid, const reason[], const bool:anticheat = false) {
    sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "%s: %s has been kicked by AdmBot, reason: %s.", anticheat ? "AC" : "AdmBot", GetName(playerid), reason);
    
    if(anticheat)
        return Kick(playerid);
    
    defer delayedKick(playerid);
    return 1;
}

initResettedVariables() {
    //playerInfo struct

    playerInfo[MAX_PLAYERS][pSQLLoginCache] = Cache: 0;

    playerInfo[MAX_PLAYERS][pGender] = playerInfo[MAX_PLAYERS][pLevel] = 1;
    playerInfo[MAX_PLAYERS][pMoney] = 2500;
    playerInfo[MAX_PLAYERS][pBank] = 5000;
    playerInfo[MAX_PLAYERS][pVehiclesSlots] = 2;
    playerInfo[MAX_PLAYERS][pSpawnType] = SPAWN_TYPE_NORMAL;

    playerInfo[MAX_PLAYERS][pReferral] = '-';

    playerInfo[MAX_PLAYERS][pRent] = playerInfo[MAX_PLAYERS][pHouse] = playerInfo[MAX_PLAYERS][pBusiness] = playerInfo[MAX_PLAYERS][pPin] = playerInfo[MAX_PLAYERS][pReferralSQLID] = playerInfo[MAX_PLAYERS][pQuestType][0] = playerInfo[MAX_PLAYERS][pQuestType][1] = playerInfo[MAX_PLAYERS][pQuestType][2] = -1;

    playerInfo[MAX_PLAYERS][pPassword][0] = playerInfo[MAX_PLAYERS][pEMail][0] = EOS;
    
    playerInfo[MAX_PLAYERS][pSQLID] = playerInfo[MAX_PLAYERS][pSkin] = playerInfo[MAX_PLAYERS][pReferralRespectPoints] = playerInfo[MAX_PLAYERS][pReferralCash] = playerInfo[MAX_PLAYERS][pAdmin] = playerInfo[MAX_PLAYERS][pHelper] = playerInfo[MAX_PLAYERS][pRespectPoints] = playerInfo[MAX_PLAYERS][pMoneyStore] = 
    playerInfo[MAX_PLAYERS][pBankStore] = playerInfo[MAX_PLAYERS][pDrivingLicense] = playerInfo[MAX_PLAYERS][pWeaponLicense] = playerInfo[MAX_PLAYERS][pFlyLicense] = playerInfo[MAX_PLAYERS][pBoatLicense] =
    playerInfo[MAX_PLAYERS][pMute] = playerInfo[MAX_PLAYERS][pWarn] = playerInfo[MAX_PLAYERS][pLoginTries] = playerInfo[MAX_PLAYERS][pAFKSeconds] = playerInfo[MAX_PLAYERS][pPlayersHelped] = 
    playerInfo[MAX_PLAYERS][pAge] = playerInfo[MAX_PLAYERS][pHelperWarns] = playerInfo[MAX_PLAYERS][pAdminWarns] = playerInfo[MAX_PLAYERS][pPhoneNumber] = playerInfo[MAX_PLAYERS][pPhoneCredit] = playerInfo[MAX_PLAYERS][pFrequency] = playerInfo[MAX_PLAYERS][pFightingStyle] = 
    playerInfo[MAX_PLAYERS][pJob] = playerInfo[MAX_PLAYERS][pFarmerSkill] = playerInfo[MAX_PLAYERS][pFishermanSkill] = playerInfo[MAX_PLAYERS][pFiremanSkill] = playerInfo[MAX_PLAYERS][pBusDriverSkill] = playerInfo[MAX_PLAYERS][pHunterSkill] = playerInfo[MAX_PLAYERS][pRepairKits] = 
    playerInfo[MAX_PLAYERS][pCourierSkill] = playerInfo[MAX_PLAYERS][pDrugs] = playerInfo[MAX_PLAYERS][pDrugsDealerSkill] = playerInfo[MAX_PLAYERS][pMaterials] = playerInfo[MAX_PLAYERS][pArmsDealerSkill] = playerInfo[MAX_PLAYERS][pTruckerSkill] = playerInfo[MAX_PLAYERS][pQuestProgress][0] = playerInfo[MAX_PLAYERS][pQuestProgress][1] = playerInfo[MAX_PLAYERS][pQuestProgress][2] = playerInfo[MAX_PLAYERS][pReportMute] = playerInfo[MAX_PLAYERS][pQuestionMute] = 
    playerInfo[MAX_PLAYERS][pPremiumPoints] = 0;
    
    playerInfo[MAX_PLAYERS][pTutorial] = playerInfo[MAX_PLAYERS][pWalkieTalkie] = playerInfo[MAX_PLAYERS][pPhoneBook] = playerInfo[MAX_PLAYERS][pHUDFps] = playerInfo[MAX_PLAYERS][pHUDDMG] = playerInfo[MAX_PLAYERS][pHUDDMG] = playerInfo[MAX_PLAYERS][pHUDSpeedometer] = playerInfo[MAX_PLAYERS][pHUDShowAHp] = playerInfo[MAX_PLAYERS][pHUDAdminStats] = playerInfo[MAX_PLAYERS][pTOGFind] = playerInfo[MAX_PLAYERS][pTOGSurf] = playerInfo[MAX_PLAYERS][pTOGPay] = false;
    
    playerInfo[MAX_PLAYERS][pHours] = playerInfo[MAX_PLAYERS][pSeconds] = playerInfo[MAX_PLAYERS][pLastPosX] = playerInfo[MAX_PLAYERS][pLastPosY] = playerInfo[MAX_PLAYERS][pLastPosZ] = 0.0;

    playerInfo[MAX_PLAYERS][pLoginTimer] = Timer: 0;  

    //playerVars struct

    playerVars[MAX_PLAYERS][var_chat_last][0] = playerVars[MAX_PLAYERS][var_QuestionText][0] = playerVars[MAX_PLAYERS][var_placed_ad][0] = EOS;
    
    playerVars[MAX_PLAYERS][var_insafezone] = playerVars[MAX_PLAYERS][var_delay] = playerVars[MAX_PLAYERS][var_death] = playerVars[MAX_PLAYERS][var_usingAnimation] = playerVars[MAX_PLAYERS][var_loopingAnimation] = playerVars[MAX_PLAYERS][var_freezed] = playerVars[MAX_PLAYERS][var_working] = playerVars[MAX_PLAYERS][var_have_seeds] = playerVars[MAX_PLAYERS][var_gascan] =
    playerVars[MAX_PLAYERS][b_FLY_MODE] = playerVars[MAX_PLAYERS][b_ADMIN_DUTY] = playerVars[MAX_PLAYERS][b_HELPER_DUTY] = playerVars[MAX_PLAYERS][b_HELMET_ON] = playerVars[MAX_PLAYERS][b_IS_SLEEPING] = playerVars[MAX_PLAYERS][b_CLOTHES_SHOW] = playerVars[MAX_PLAYERS][b_GUNSHOP_SHOW] = 
    playerVars[MAX_PLAYERS][b_SPEED_BOOST] = playerVars[MAX_PLAYERS][b_PHONE_SPEAKER] = playerVars[MAX_PLAYERS][b_FISHING] = playerVars[MAX_PLAYERS][b_ACTIVE_TIMER] = playerVars[MAX_PLAYERS][b_ARMS_DEALER_WORKING] = false;
    
    playerVars[MAX_PLAYERS][b_PHONE_TURN] = true;
    
    playerVars[MAX_PLAYERS][var_engine_delay] = playerVars[MAX_PLAYERS][var_kick_delay] = playerVars[MAX_PLAYERS][var_me_delay] = playerVars[MAX_PLAYERS][var_shout_delay] = playerVars[MAX_PLAYERS][var_time_delay] = playerVars[MAX_PLAYERS][var_changepass_delay] = playerVars[MAX_PLAYERS][var_ban_delay] = playerVars[MAX_PLAYERS][var_buy_delay] = playerVars[MAX_PLAYERS][var_wt_delay] = 
    playerVars[MAX_PLAYERS][var_house_delay] =  playerVars[MAX_PLAYERS][var_ph_delay] = playerVars[MAX_PLAYERS][var_sleep_delay] = playerVars[MAX_PLAYERS][var_pay_delay] = playerVars[MAX_PLAYERS][var_work_delay] = playerVars[MAX_PLAYERS][var_heal_delay] = playerVars[MAX_PLAYERS][var_radio_delay] = playerVars[MAX_PLAYERS][var_bank_delay] = 
    playerVars[MAX_PLAYERS][var_bizz_delay] = playerVars[MAX_PLAYERS][var_atm_delay] = playerVars[MAX_PLAYERS][var_gunshop_delay] = playerVars[MAX_PLAYERS][var_warn_delay] = playerVars[MAX_PLAYERS][var_unwarn_delay] = playerVars[MAX_PLAYERS][var_mute_delay] = playerVars[MAX_PLAYERS][var_report_delay] = playerVars[MAX_PLAYERS][var_nmute_delay] =
    playerVars[MAX_PLAYERS][var_hduty_delay] = playerVars[MAX_PLAYERS][var_rmute_delay] = playerVars[MAX_PLAYERS][var_aduty_delay] = playerVars[MAX_PLAYERS][var_call_delay] = playerVars[MAX_PLAYERS][var_sms_delay] = playerVars[MAX_PLAYERS][var_dice_delay] = playerVars[MAX_PLAYERS][var_pns_delay] = playerVars[MAX_PLAYERS][var_incall_delay] = playerVars[MAX_PLAYERS][var_addfriend_delay] = playerVars[MAX_PLAYERS][var_repair_delay] = playerVars[MAX_PLAYERS][var_gunshopopened_delay] =
    playerVars[MAX_PLAYERS][var_car_spawn_delay] = playerVars[MAX_PLAYERS][var_car_unstuck_delay] = -1;
    
    playerVars[MAX_PLAYERS][var_SpectatePlayer] = playerVars[MAX_PLAYERS][var_inhouse] = playerVars[MAX_PLAYERS][var_spectateMe] = playerVars[MAX_PLAYERS][var_warningtimer] = playerVars[MAX_PLAYERS][var_inbizz] = playerVars[MAX_PLAYERS][var_precedentweapon] = playerVars[MAX_PLAYERS][var_objectweapon] = 
    playerVars[MAX_PLAYERS][var_incall] = playerVars[MAX_PLAYERS][var_calls] = playerVars[MAX_PLAYERS][var_callfrom] = playerVars[MAX_PLAYERS][var_dice_invited] = playerVars[MAX_PLAYERS][var_dice_money] = playerVars[MAX_PLAYERS][var_checkpoint] = playerVars[MAX_PLAYERS][var_rentedcar] = playerVars[MAX_PLAYERS][var_rentedcarbusiness] = playerVars[MAX_PLAYERS][var_rentlistitem] = playerVars[MAX_PLAYERS][var_rentedcartime] = playerVars[MAX_PLAYERS][var_findon] =
    playerVars[MAX_PLAYERS][var_jobvehicle] = playerVars[MAX_PLAYERS][var_jobseconds] = playerVars[MAX_PLAYERS][var_jobtime] = playerVars[MAX_PLAYERS][var_jobexitvehicletime] = playerVars[MAX_PLAYERS][var_jobobject] = 
    playerVars[MAX_PLAYERS][var_planted_seeds_time] = playerVars[MAX_PLAYERS][var_sell_drugs] = playerVars[MAX_PLAYERS][var_sell_drugs_money] = playerVars[MAX_PLAYERS][var_sell_drugs_value] = playerVars[MAX_PLAYERS][var_arms_dealer_materials] = playerVars[MAX_PLAYERS][var_arms_dealer_money] = playerVars[MAX_PLAYERS][var_sell_mats] = playerVars[MAX_PLAYERS][var_sell_mats_money] =
    playerVars[MAX_PLAYERS][var_sell_mats_value] = playerVars[MAX_PLAYERS][var_cigarettes_delay] = playerVars[MAX_PLAYERS][var_trucker_trailer] = playerVars[MAX_PLAYERS][var_trucker_cash_bonus] = playerVars[MAX_PLAYERS][var_trucker_chat_delay] = playerVars[MAX_PLAYERS][var_spectateseconds] = playerVars[MAX_PLAYERS][var_repair_invited] = playerVars[MAX_PLAYERS][var_courierhouse] = -1;

    playerVars[MAX_PLAYERS][var_cigarettes] = playerVars[MAX_PLAYERS][var_fishkg] = playerVars[MAX_PLAYERS][var_drunklevel] = playerVars[MAX_PLAYERS][var_FPS] = playerVars[MAX_PLAYERS][var_precedentskin] = playerVars[MAX_PLAYERS][var_busdrivercheckpoint] = playerVars[MAX_PLAYERS][var_courierstuff] = playerVars[MAX_PLAYERS][var_repair_price] = 0;

    playerVars[MAX_PLAYERS][var_jobtimer] = playerVars[MAX_PLAYERS][var_ad_timer] = playerVars[MAX_PLAYERS][var_spectatetimer] = playerVars[MAX_PLAYERS][var_drugs_dealer_timer] = playerVars[MAX_PLAYERS][var_find_timer] = playerVars[MAX_PLAYERS][var_renttimer] = playerVars[MAX_PLAYERS][var_flytimer] = playerVars[MAX_PLAYERS][var_healtharmourhudtimer] = playerVars[MAX_PLAYERS][var_jobtimerchecks] = playerVars[MAX_PLAYERS][var_speedometertimer] = playerVars[MAX_PLAYERS][var_damageinformer_timer] = Timer: 0;

    playerVars[MAX_PLAYERS][var_chat_delay] = playerVars[MAX_PLAYERS][var_car_lock_delay] = GetTickCount();
}

initCommandAltNames() {
    Command_AddAltNamed("adminchat", "a"),
    Command_AddAltNamed("adminchat", "ac"),
    Command_AddAltNamed("helperchat", "hc"),
    Command_AddAltNamed("admingivelicense", "agl"),
    Command_AddAltNamed("adminsuspendlicense", "asl"),
    Command_AddAltNamed("adminsuspendlicense", "suspendlicense"),
    Command_AddAltNamed("clearchat", "cc"),
    Command_AddAltNamed("adminclearchat", "acc"),
    Command_AddAltNamed("respawn", "spawn"),
    Command_AddAltNamed("whisper", "w"),
    Command_AddAltNamed("shout", "s"),
    Command_AddAltNamed("anno", "o"),
    Command_AddAltNamed("anno2", "o2"),
    Command_AddAltNamed("spectate", "spec"),
    Command_AddAltNamed("sethealth", "sethp"),
    Command_AddAltNamed("closereport", "cr"),
    Command_AddAltNamed("acceptreport", "ar"),
    Command_AddAltNamed("banoffline", "bano"),
    Command_AddAltNamed("newbie", "n"),
    Command_AddAltNamed("fixveh", "fv"),
    Command_AddAltNamed("hmenu", "housemenu"),
    Command_AddAltNamed("examen", "exam"),
    Command_AddAltNamed("locations", "gps"),
    Command_AddAltNamed("puthelmet", "ph"),
    Command_AddAltNamed("gotom", "gotochilliad"),
    Command_AddAltNamed("para", "parachute"),
    Command_AddAltNamed("givehelperwarn", "givehw"),
    Command_AddAltNamed("givehelperwarn", "givehwarn"),
    Command_AddAltNamed("giveadminwarn", "giveaw"),
    Command_AddAltNamed("giveadminwarn", "giveawarn"),
    Command_AddAltNamed("setadminwarn", "setaw"),
    Command_AddAltNamed("setadminwarn", "setawarn"),
    Command_AddAltNamed("sethelperwarn", "sethw"),
    Command_AddAltNamed("sethelperwarn", "sethwarn"),
    Command_AddAltNamed("carwhisper", "cw"),
    Command_AddAltNamed("bmenu", "bizzmenu"),
    Command_AddAltNamed("hangup", "h"),
    Command_AddAltNamed("pickup", "p"),
    Command_AddAltNamed("setfreq", "setfrequency"),
    Command_AddAltNamed("getmats", "getmaterials"),
    Command_AddAltNamed("sellmaterials", "sellmats"),
    Command_AddAltNamed("lastchat", "lc"),
    Command_AddAltNamed("forcenamechange", "fnc");
    Command_AddAltNamed("vehicles", "v");
    Command_AddAltNamed("gotods", "gotodealership");
    Command_AddAltNamed("dealershipveh", "dsveh");
    Command_AddAltNamed("givepremiumpoints", "givepp");
}

// ------------------------------------- //
//              Load Pickups             //
// ------------------------------------- //

loadPickups() {  
    CreateDynamicPickup(1239, 23, 1219.2386,-1812.8556,16.5938);
    CreateDynamicPickup(371, 23, -2232.8813,-1735.5844,480.8433);
    CreateDynamicPickup(1318, 23, 301.8002,-76.7811,1001.5156);
    CreateDynamicPickup(1318, 23, 301.7888,-75.4750,1001.5156);
    CreateDynamicPickup(1279, 23, -1069.3879,-1205.5856,129.2188);
    CreateDynamicPickup(1279, 23, 2178.6499,-1660.4121,14.9628);
    return printf("[GAMEMODE LOADED] Pickups: %d", Streamer_CountItems(STREAMER_TYPE_PICKUP));
}

// ------------------------------------- //
//              Load Map Icons           //
// ------------------------------------- //

loadMapIcons() {
    CreateDynamicMapIcon(1219.2386,-1812.8556,16.5938, 55, 0);
    return printf("[GAMEMODE LOADED] Map Icons: %d", Streamer_CountItems(STREAMER_TYPE_MAP_ICON));
}

// ------------------------------------- //
//              Load Objects             //
// ------------------------------------- //

loadObjects() {
    // ------------------------------------- //
    //               LSPD Gates              //
    // ------------------------------------- //

    // LSPD
    CreateDynamicObject(2952, 1581.99524, -1637.93494, 12.36840, 0.00000, 0.00000, 90.00000);
    CreateDynamicObject(983, 1545.0706787109, -1635.6511230469, 13.237774848938, 0, 0, 0, -1, -1, -1,300.0);
    CreateDynamicObject(983, 1544.4979248047, -1620.7434082031, 13.238116264343, 0, 0, 0, -1, -1, -1,300.0);
    serverLSPDbar = CreateDynamicObject(968, 1544.7007, -1630.7527, 13.2983, 0.0000, 90.0200, 90.0000, -1,- 1, -1, 300.0);

    // ------------------------------------- //
    //              PNS Gates                //
    // ------------------------------------- //

    CreateDynamicObject(971, 489.20, -1735.32, 13.04, 0.00, 0.00, -9.50);
    CreateDynamicObject(971, 1025.65308, -1029.21753, 33.20733, 0.00, 0.00, 0.00);
    CreateDynamicObject(971, 2071.44434, -1830.65222, 14.00510, 0.00, 0.00, 90.00);

    // ------------------------------------- //
    //              CNN                      //
    // ------------------------------------- //

    CreateDynamicObject(970, 1113.81, -1415.96, 13.00,   0.00, 0.00, 0.65);
    CreateDynamicObject(970, 1186.08, -1495.66, 12.96,   0.00, 0.00, -90.06);
    CreateDynamicObject(970, 1186.08, -1490.92, 12.96,   0.00, 0.00, -90.06);
    CreateDynamicObject(970, 1186.08, -1486.26, 12.96,   0.00, 0.00, -90.06);
    CreateDynamicObject(970, 1186.08, -1481.49, 12.96,   0.00, 0.00, -90.06);
    CreateDynamicObject(970, 1124.01, -1562.16, 12.96,   0.00, 0.00, -0.48);
    CreateDynamicObject(970, 1133.22, -1562.23, 12.96,   0.00, 0.00, -0.30);
    CreateDynamicObject(970, 1128.58, -1562.20, 12.96,   0.00, 0.00, -0.48);
    CreateDynamicObject(970, 1061.49, -1492.59, 12.97,   0.00, 0.00, -105.30);
    CreateDynamicObject(970, 1059.10, -1501.51, 12.97,   0.00, 0.00, -104.90);
    CreateDynamicObject(970, 1060.29, -1497.05, 12.97,   0.00, 0.00, -104.85);
    CreateDynamicObject(970, 266.38, 82.12, 1000.48,   0.00, 0.00, 90.00);
    CreateDynamicObject(970, 266.38, 82.12, 1001.26,   0.00, 0.00, 90.00);
    CreateDynamicObject(970, 266.38, 82.12, 1002.02,   0.00, 0.00, 90.00);
    CreateDynamicObject(970, 266.38, 82.12, 1002.84,   0.00, 0.00, 90.00);
    CreateDynamicObject(970, 266.37, 77.60, 1000.48,   0.00, 0.00, 89.94);
    CreateDynamicObject(970, 266.37, 77.60, 1001.26,   0.00, 0.00, 89.94);
    CreateDynamicObject(970, 266.37, 77.60, 1002.04,   0.00, 0.00, 89.94);
    CreateDynamicObject(970, 266.37, 77.60, 1002.82,   0.00, 0.00, 89.94);
    CreateDynamicObject(970, 266.37, 86.61, 1000.48,   0.00, 0.00, 90.30);
    CreateDynamicObject(970, 266.37, 86.61, 1001.28,   0.00, 0.00, 90.30);
    CreateDynamicObject(970, 266.37, 86.61, 1002.08,   0.00, 0.00, 90.30);
    CreateDynamicObject(970, 266.37, 86.61, 1002.86,   0.00, 0.00, 90.30);
    CreateDynamicObject(970, 1119.35, -1415.94, 13.00,   0.00, 0.00, 0.00);
    CreateDynamicObject(970, 1124.63, -1415.94, 13.00,   0.00, 0.00, 0.00);
    CreateDynamicObject(970, 1130.06, -1415.94, 13.00,   0.00, 0.00, 0.00);
    CreateDynamicObject(970, 1135.56, -1415.94, 13.00,   0.00, 0.00, 0.00);
    CreateDynamicObject(970, 1140.76, -1415.94, 13.00,   0.00, 0.00, 0.00);
    CreateDynamicObject(970, 1146.03, -1415.94, 13.00,   0.00, 0.00, 0.00);

    // ------------------------------------- //
    //              Gas Stations             //
    // ------------------------------------- //

    CreateDynamicObject(1676, 998.38, -937.65, 42.83,   0.00, 0.00, 7.98);
    CreateDynamicObject(1676, 1002.46, -937.00, 42.83,   0.00, 0.00, 7.98);
    CreateDynamicObject(1676, 1005.33, -936.57, 42.83,   0.00, 0.00, 7.98);
    CreateDynamicObject(1676, 1009.41, -935.97, 42.83,   0.00, 0.00, 7.98);

    // ------------------------------------- //
    //              Spawn                    //
    // ------------------------------------- //

    CreateDynamicObject(970, 493.86, -1561.23, 16.70,   0.00, 0.00, 36.48);
    CreateDynamicObject(970, 497.88, -1558.26, 16.57,   0.00, 0.00, 36.48);
    CreateDynamicObject(970, 505.87, -1552.35, 16.71,   0.00, 0.00, 36.48);
    CreateDynamicObject(970, 501.99, -1555.22, 16.57,   0.00, 0.00, 36.48);
    CreateDynamicObject(970, 493.90, -1458.25, 16.96,   0.00, 0.00, -30.00);
    CreateDynamicObject(970, 489.30, -1455.57, 17.09,   0.00, 0.00, -30.00);
    CreateDynamicObject(970, 498.69, -1460.99, 16.96,   0.00, 0.00, -30.00);
    CreateDynamicObject(970, 503.08, -1463.51, 17.09,   0.00, 0.00, -30.00);

    // ------------------------------------- //
    //              24/7 Bomb                //
    // ------------------------------------- //

    CreateDynamicObject(971, 1843.30, -1855.48, 11.97,   0.00, 0.00, 90.00);

    return printf("[GAMEMODE LOADED] Objects: %d", Streamer_CountItems(STREAMER_TYPE_OBJECT));
}

// ------------------------------------- //
//              Labels                   //
// ------------------------------------- //

loadLabels() {  
    CreateDynamic3DTextLabel("DMV Location{FFFFFF}\nType {1C8A15}[/examen]{FFFFFF} to do DMV examen.", COLOR_GREEN, 1219.2386,-1812.8556,16.5938, 3.0);
    CreateDynamic3DTextLabel("Buy Parachute{FFFFFF}\nType {1C8A15}[/para]{FFFFFF} to buy a parachute.\nCost: {1C8A15}$5000", COLOR_GREEN, -2232.8813,-1735.5844,480.8433, 6.0);
    CreateDynamic3DTextLabel("Gun Shop{FFFFFF}\nPress {1C8A15}'Y'{FFFFFF} to buy a weapon.", COLOR_GREEN, 295.5730,-80.4439,1001.5156, 5.0);
    CreateDynamic3DTextLabel("Training Arena{FFFFFF}\nPress {1C8A15}'F'{FFFFFF} to enter in arena.", COLOR_GREEN, 301.8002,-76.7811,1001.5156, 5.0);
    CreateDynamic3DTextLabel("Training Arena{FFFFFF}\nPress {1C8A15}'F'{FFFFFF} to exit from arena.", COLOR_GREEN, 301.7888,-75.4750,1001.5156, 5.0);
    CreateDynamic3DTextLabel("Fishing Zone{FFFFFF}\nWrite {1C8A15}[/fish]{FFFFFF} if you want to fishing.", COLOR_GREEN, 383.7535,-2084.1587,7.8359, 15.0);
    CreateDynamic3DTextLabel("Fireman{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, 797.7266,-611.7032,16.3432, 20.0);
    CreateDynamic3DTextLabel("Bus Driver{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, 1664.2177,-2269.4932,-1.2628, 15.0);
    CreateDynamic3DTextLabel("Farmer{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, -377.6356,-1410.4612,25.7266, 15.0);
    CreateDynamic3DTextLabel("Drugs Dealer{FFFFFF}\nWrite {1C8A15}[/getseeds]{FFFFFF} to get seeds.", COLOR_GREEN, -1069.3879,-1205.5856,129.2188, 15.0);
    CreateDynamic3DTextLabel("Arms Dealer{FFFFFF}\nWrite {1C8A15}[/getmaterials]{FFFFFF} if you want to work.", COLOR_GREEN, 2178.6499,-1660.4121,14.9628, 15.0);
    CreateDynamic3DTextLabel("Trucker{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, 1034.7891,2132.8279,10.8203, 15.0);
    CreateDynamic3DTextLabel("Hunter{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, 1553.57,37.894,24.2427, 15.0);
    CreateDynamic3DTextLabel("Courier{FFFFFF}\nWrite {1C8A15}[/work]{FFFFFF} if you want to work.", COLOR_GREEN, 2742.41,-2466.15,13.6484, 15.0);
    return printf("[GAMEMODE LOADED] Text Labels: %d", Streamer_CountItems(STREAMER_TYPE_3D_TEXT_LABEL));
}

destroyPlayerLabels(const playerid) {
    DestroyDynamic3DTextLabel(playerLabels[playerid][l_death]); 
    DestroyDynamic3DTextLabel(playerLabels[playerid][l_drugs_dealer]);
    return 1;
}

// ------------------------------------- //
//             Load Actors               //
// ------------------------------------- //

loadActors() {
    ApplyDynamicActorAnimation(CreateDynamicActorEx(7, 295.5938,-83.0727,1001.5156,2.3366, .worlds = {5, 6}), "DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
    CreateDynamicActorEx(211, 207.5916,-98.3781,1005.2578,182.2609, .worlds = {3, 4});
    CreateDynamicActorEx(172, -28.9956,-186.8191,1003.5469,356.8609, .worlds = {7, 8, 10, 23});
    CreateDynamicActorEx(205, 377.3455,-65.5390,1001.5078,179.7920, .worlds = {9, 11});
    CreateDynamicActorEx(171, 501.9233,-20.2183,1000.6797,89.5859, .worlds = {13});
    CreateDynamicActorEx(169, -103.8213,-24.3650,1000.7188,358.7646, .worlds = {12});
    return printf("[GAMEMODE LOADED] Actors: %d", Streamer_CountItems(STREAMER_TYPE_ACTOR));
}