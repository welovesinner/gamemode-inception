YCMD:ah(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul necesar pentru a folosi aceasta comanda.");

    SCM(playerid, COLOR_GREEN, "________________________________________________________");
    SCM(playerid, COLOR_GREEN, "Admin Level 1: {FFFFFF}/mute /unmute /a /freeze /unfreeze /cc /fly /spawncar /despawncars /respawn /check /slap /unstuck /slapcar");
    SCM(playerid, COLOR_GREEN, "Admin Level 1: {FFFFFF}/anno(/o) /anno2(/o2) /getcar /pm /gotocar /goto /gotols /gotolv /gotosf /gethere /aaa2 /aaa3 /kick");
    SCM(playerid, COLOR_GREEN, "Admin Level 1: {FFFFFF}/givegun /aduty /closereport /acceptreport /reports /rmute /gsearch /vsearch /ban /respawnhere /re /nmute /nos");
    SCM(playerid, COLOR_GREEN, "Admin Level 1: {FFFFFF}/fv /flip /gotom /speed /deletead /gotobizz /gotohouse /gotojob /toggleeventteleport /fnc(/forcenamechange)");
    SCM(playerid, COLOR_GREEN, "Admin Level 1: {FFFFFF}/spec /specoff /disarm /gotodealership(/gotods) /dealershipveh(/dsveh)");
    if(playerInfo[playerid][pAdmin] >= 2) SCM(playerid, COLOR_GREEN, "Admin Level 2: {FFFFFF}/vre /rac /closestcar /sethealth /setarmour /area /bano(offline) /mark /gotomark /ip /putplayerinvehicle /lc(/lastchat)");
    if(playerInfo[playerid][pAdmin] >= 3) SCM(playerid, COLOR_GREEN, "Admin Level 3: {FFFFFF}/unwarn /skick /gotoxyz /acc");
    if(playerInfo[playerid][pAdmin] >= 4) SCM(playerid, COLOR_GREEN, "Admin Level 4: {FFFFFF}/suspend /agl /givemoney /unban /givepremiumpoints /giveallmoney /givealllevel /giveallrp");
    if(playerInfo[playerid][pAdmin] >= 5) SCM(playerid, COLOR_GREEN, "Admin Level 5: {FFFFFF}/sstats /setworldtime /setworldweather /set");
    if(playerInfo[playerid][pAdmin] >= 6) {
        SCM(playerid, COLOR_GREEN, "Admin Level 6: {FFFFFF}/setadmin /sethelper /setadminoff /sethelperoff /staff /givehwarn /giveawarn /setawarn /sethwarn /remotecommand");
        SCM(playerid, COLOR_GREEN, "Admin Level 6: {FFFFFF}/checkv /vowner");
    }
    if(playerInfo[playerid][pAdmin] >= 7) SCM(playerid, COLOR_GREEN, "Owner: {FFFFFF}/serverpass /createbizz /editbizz /serverrestart /cancelrestart /addservervehicle /checkdbaccount");
    if(playerInfo[playerid][pAdmin] >= 8) SCM(playerid, COLOR_GREEN, "Scripter: {FFFFFF}/svars /addsvar /addsafezone");
    SCM(playerid, COLOR_GREEN, "________________________________________________________");
    return 1;
}

YCMD:givepremiumpoints(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, value; if(sscanf(params, "ud", userID, value)) 
        return sendUsage(playerid, "/givepremiumpoints <playerid/name> <points>"); 

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(value < 1 || value > 1000)
        return sendError(playerid, "Suma de puncte trebuie sa fie cuprinsa intre 1 si 1000.");

    playerInfo[userID][pPremiumPoints] += value;

    va_mysql_tquery("UPDATE `server_users` SET `PremiumPoints` = %d WHERE `ID` = %d", playerInfo[userID][pPremiumPoints], playerInfo[userID][pSQLID]);

    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s gived %d premium points to player %s.", GetName(playerid), value, GetName(userID));
    return 1;
}

YCMD:checkdbaccount(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    gString[0] = EOS; if(sscanf(params, "s[144]", gString))
        return sendUsage(playerid, "/checkdbaccount <name>");

    if(strlen(gString) > MAX_PLAYER_NAME)
        return sendError(playerid, "Numele trebuie sa aiba maxim "#MAX_PLAYER_NAME" caractere.");

    if(MAP_contains_str(playersNames, gString)) 
        return sendError(playerid, "Acel player este online.");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_users` WHERE `Name` = BINARY '%e' LIMIT 1", gString);
    mysql_tquery(SQL, gQuery, "checkDatabaseAccount", "ds", playerid, gString);
    return 1;
}

YCMD:forcenamechange(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS; if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/forcenamechange <playerid/name> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat pe server.");

    new const length = strlen(gString);

    if(length < 3 || length > 64) 
        return sendError(playerid, "Motiv-ul trebuie sa cuprinda intre 3 si 64 caractere.");

    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}Admin %s forced player %s (%d) to change his nickname. Reason: %s", GetName(playerid), GetName(userID), userID, gString);
    SCMf(userID, COLOR_GREY, "* Admin %s forced you to change your nickname. Reason: %s", GetName(playerid), gString);

    TogglePlayerControllableEx(userID, false);

    return Dialog_Show(userID, FORCENAMECHANGE, DIALOG_STYLE_INPUT, "SERVER: Force Name Change", "Enter a new nickname in the box below:", "Ok", "Kick");
}

YCMD:lastchat(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/lastchat <playerid/name>");

    if(!IsPlayerLogged(userID)) 
        return sendError(playerid, "Acel player nu este logat pe server.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda pe acel player.");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_chat_logs` WHERE `PlayerSQLID` = %d ORDER BY `server_chat_logs`.`ID` DESC LIMIT 10", playerInfo[userID][pSQLID]);
    mysql_tquery(SQL, gQuery, "loadChatLogsForPlayer", "dd", playerid, userID);
    return 1;   
}

YCMD:set(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 5) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, value; gString[0] = EOS; if(sscanf(params, "us[32]d", userID, gString, value))
        return sendUsage(playerid, "/set <playerid/name> <option> <value>"), SCM(playerid, COLOR_GREY, "Options Available: {FFFFFF}skin, virtualworld, interior, level, respect, money, job, hours, drugs, materials, group, grouprank premiumpoints.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    switch(YHash(gString)) {
        case _H<skin>: {
            if(value < 0 || value > 311)
                return sendError(playerid, "Skin Invalid! (0 - 311)");
        
            if(playerInfo[userID][pSkin] == value)
                return sendError(playerid, "Acel player are deja skin-ul cu ID %d.", value);

            playerInfo[userID][pSkin] = value;

            SetPlayerSkin(userID, value);

            va_mysql_tquery("UPDATE `server_users` SET `Skin` = %d WHERE `ID` = %d", playerInfo[userID][pSkin], playerInfo[userID][pSQLID]);
        }
        case _H<virtualworld>: {
            SetPlayerVirtualWorld(userID, value);
        }
        case _H<interior>: {
            SetPlayerInterior(userID, value);
        }
        case _H<level>: {
            playerInfo[userID][pLevel] = value;

            SetPlayerScore(userID, value);

            va_mysql_tquery("UPDATE `server_users` SET `Level` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
        }
        case _H<respect>: {
            playerInfo[userID][pRespectPoints] = value;

            va_mysql_tquery("UPDATE `server_users` SET `RespectPoints` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
        }
        case _H<money>: {
            if(value < 0 || value >= 999999999)
                return sendError(playerid, "Invalid Money! ($1 - $999.999.999)");

            playerInfo[userID][pMoney] = value;
            playerInfo[userID][pMoneyStore] = 0;

            ResetPlayerMoney(userID);
            GivePlayerMoney(userID, value);

            va_mysql_tquery("UPDATE `server_users` SET `Money` = %d, `MoneyStore` = 0 WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
        }
        case _H<job>: {
            if(value > serverStuff[jobs] || value < 1)
                return sendError(playerid, "Acel job este invalid.");

            va_mysql_tquery("UPDATE `server_users` SET `Job` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pJob] = value;
        }
        case _H<hours>: {
            va_mysql_tquery("UPDATE `server_users` SET `Hours` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pHours] = value;
        }
        case _H<materials>: {
            va_mysql_tquery("UPDATE `server_users` SET `Materials` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pMaterials] = value;
        }
        case _H<drugs>: {
            va_mysql_tquery("UPDATE `server_users` SET `Drugs` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pDrugs] = value;
        }
        case _H<premiumpoints>: {
            va_mysql_tquery("UPDATE `server_users` SET `PremiumPoints` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pPremiumPoints] = value;
        }
        case _H<group>: {
            va_mysql_tquery("UPDATE `server_users` SET `playerGroup` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pGroup] = value; 
        }
        case _H<grouprank>: {
            va_mysql_tquery("UPDATE `server_users` SET `playerGroupRank` = %d WHERE `ID` = %d", value, playerInfo[userID][pSQLID]);
            playerInfo[userID][pGroupRank] = value; 
        }
        default: {
            sendUsage(playerid, "/set <playerid/name> <option> <value>");
            return SCM(playerid, COLOR_GREY, "Options Available: {FFFFFF}skin, virtualworld, interior, level, respect, money, job, hours, drugs, materials, group, grouprank, premiumpoints.");
        }
    }

    return SendStaff(COLOR_LIGHTRED, "(Staff Info): {FFFFFF}Admin %s setted %s's '%s' to %d.", GetName(playerid), GetName(userID), gString, value);
}

YCMD:teleportevent(playerid, params[], help) {
    if(!serverTeleportEvent || IsPlayerInRangeOfPoint(playerid, 7.5, serverTeleportEventLocation[0], serverTeleportEventLocation[1], serverTeleportEventLocation[2]))
        return 1;

    SetPlayerPosFindZ(playerid, serverTeleportEventLocation[0], serverTeleportEventLocation[1], serverTeleportEventLocation[2]);
    return SCM(playerid, COLOR_GREY, "* You've been teleported succesfully to event.");
}

YCMD:toggleeventteleport(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    serverTeleportEvent = !serverTeleportEvent;

    if(serverTeleportEvent) {
        GetPlayerPos(playerid, serverTeleportEventLocation[0], serverTeleportEventLocation[1], serverTeleportEventLocation[2]);

        SCMTAf(COLOR_PINK, "* Administratorul %s a activat teleportarile pentru event.", GetName(playerid));
        SCMTA(COLOR_PINK, "* Foloseste comanda [/teleportevent] pentru a te teleporta catre event.");
        return 1;
    }
    return SCMTAf(COLOR_PINK, "* Administratorul %s a dezactivat teleportarile pentru event.", GetName(playerid));
}

YCMD:remotecommand(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    gString[0] = EOS; new userID; if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/remotecommand <playerid/name> <cmdtext>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(gString[0] == '/')
        Command_ReProcess(userID, gString, false);

    else OnPlayerText(userID, gString);

    return SCMf(playerid, COLOR_GREY, "Command executed succesfully. (player: %s, command: '%s')", GetName(userID), gString);
}

YCMD:serverrestart(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(serverRestartTime != -1)
        return sendError(playerid, "Este deja programat un restart, pentru a-l anula tasteaza comanda [/cancelrestart].");

    gString[0] = EOS; new minutes; if(sscanf(params, "ds[144]", minutes, gString) || minutes < 1 || minutes > 60)
        return sendUsage(playerid, "/serverrestart <minutes> <reason>");

    serverRestartTime = minutes*60;
    serverRestartTimerVar = repeat serverRestartTimer();

    return SCMTAf(COLOR_CLIENT, "SERVER: A restart countdown was started. Reason: %s.", gString);
}

YCMD:cancelrestart(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(serverRestartTime == -1)
        return sendError(playerid, "Nu a fost programat vreun restart.");

    gString[0] = EOS; if(sscanf(params, "s[144]", gString))
        return sendUsage(playerid, "/cancelrestart <reason>");

    stop serverRestartTimerVar; 
    serverRestartTime = -1; 

    return SCMTAf(COLOR_CLIENT, "SERVER: The server restart countdown was canceled. Reason: %s.", gString);
}

YCMD:putplayerinvehicle(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, vehicleid, seat; if(sscanf(params, "udd", userID, vehicleid, seat) || seat < 0 || seat > 4) 
        return sendUsage(playerid, "/putplayerinvehicle <playerid/name> <vehicleid> <seat (0 - 4)>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!IsValidVehicle(vehicleid)) 
        return sendError(playerid, "Acel vehicul este invalid.");

    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {FFFFFF}Admin %s putted player %s in vehicle %d (seat: %d) via [/putplayerinvehicle].", GetName(playerid), GetName(userID), vehicleid, seat);

    return PutPlayerInVehicle(userID, vehicleid, seat);
} 

YCMD:setworldtime(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 5)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params) || strval(params) > 23)
        return sendUsage(playerid, "/setworldtime <time (0 - 23)>");

    SetWorldTime(strval(params));

    return SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s setted the world time on %02d:00.", GetName(playerid), strval(params));
}

YCMD:setworldweather(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 5)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params)) 
        return sendUsage(playerid, "/setworldweather <value>");

    SetWeather(strval(params));

    return SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s setted the world weather to %d.", GetName(playerid), strval(params));
}

YCMD:speed(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    playerVars[playerid][b_SPEED_BOOST] = !playerVars[playerid][b_SPEED_BOOST];

    return SCM(playerid, -1, playerVars[playerid][b_SPEED_BOOST] ? "You enabled the speed boost." : "You disabled the speed boost.");
}

YCMD:serverpass(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/serverpass <password (0 = none)>");

    if(params[0] == '0') 
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s removed the password from server.", GetName(playerid));

    else SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s setted password '%s' on server.", GetName(playerid), params);

    gString[0] = EOS; 
    format(gString, sizeof gString, "password %s", params);
    SendRconCommand(gString);
    return 1;
}

YCMD:sethelperwarn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, warn; if(sscanf(params, "ud", userID, warn))
        return sendUsage(playerid, "/sethelperwarn <playerid/name> <value>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(warn < 0 || warn > 2)
        return sendError(playerid, "Valoarea trebuie sa fie cuprinsa intre 0 si 2.");

    if(warn == playerInfo[userID][pHelperWarns])
        return sendError(playerid, "Acel player are deja %d warn-uri.", warn);

    if(!playerInfo[userID][pHelper])
        return sendError(playerid, "Acel player nu este helper.");

    playerInfo[userID][pHelperWarns] = warn;
    
    va_mysql_tquery("UPDATE `server_users` SET `HelperWarns` = %d WHERE `ID` = %d", warn, playerInfo[userID][pSQLID]);

    return SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's helper warns to %d.", GetName(playerid), GetName(userID), warn);
}

YCMD:setadminwarn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, warn; if(sscanf(params, "ud", userID, warn))
        return sendUsage(playerid, "/setadminwarn <playerid/name> <value>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(warn < 0 || warn > 2)
        return sendError(playerid, "Valoarea trebuie sa fie cuprinsa intre 0 si 2.");

    if(warn == playerInfo[userID][pAdminWarns])
        return sendError(playerid, "Acel player are deja %d warn-uri.", warn);

    if(!playerInfo[userID][pAdmin])
        return sendError(playerid, "Acel player nu este admin.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti face asta pe acel player.");

    playerInfo[userID][pAdminWarns] = warn;
    
    va_mysql_tquery("UPDATE `server_users` SET `AdminWarns` = %d WHERE `ID` = %d", warn, playerInfo[userID][pSQLID]);

    return SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's admin warns to %d.", GetName(playerid), GetName(userID), warn);
}

YCMD:giveadminwarn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/giveadminwarn <playerid/name> <reason>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!playerInfo[userID][pAdmin])
        return sendError(playerid, "Acel player nu este admin.");

    if(strlen(gString) < 1 || strlen(gString) >= 64)
        return sendError(playerid, "Motiv-ul trebuie sa fie cuprins intre 1 si 64 caractere.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti face asta pe acel player.");

    playerInfo[userID][pAdminWarns] ++;

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s gived an admin warn to %s (%d/3). Reason: %s.", GetName(playerid), GetName(userID), playerInfo[userID][pAdminWarns], gString);
    
    if(playerInfo[userID][pAdminWarns] >= 3) {
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s was demoted from admin because he has accumulated 3/3 admin warns.", GetName(userID));

        Iter_Remove(serverStaff, userID);
        Iter_Remove(serverAdmins, userID);

        playerInfo[userID][pAdmin] = playerInfo[userID][pPlayersHelped] = playerInfo[userID][pAdminWarns] = 0;
    }
    return va_mysql_tquery("UPDATE `server_users` SET `AdminWarns` = %d, `Admin` = %d, `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[userID][pAdminWarns], playerInfo[userID][pAdmin], playerInfo[userID][pPlayersHelped], playerInfo[userID][pSQLID]);
}

YCMD:givehelperwarn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/givehelperwarn <playerid/name> <reason>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!playerInfo[userID][pHelper])
        return sendError(playerid, "Acel player nu este helper.");

    if(strlen(gString) < 1 || strlen(gString) >= 64)
        return sendError(playerid, "Motiv-ul trebuie sa fie cuprins intre 1 si 64 caractere.");

    playerInfo[userID][pHelperWarns] ++;

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s gived an helper warn to %s (%d/3). Reason: %s.", GetName(playerid), GetName(userID), playerInfo[userID][pHelperWarns], gString);
    
    if(playerInfo[userID][pHelperWarns] >= 3) {
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s was demoted from helper because he has accumulated 3/3 helper warns.", GetName(userID));

        Iter_Remove(serverStaff, userID);
        Iter_Remove(serverHelpers, userID);

        playerInfo[userID][pHelper] = playerInfo[userID][pPlayersHelped] = playerInfo[userID][pHelperWarns] = 0;
    }
    return va_mysql_tquery("UPDATE `server_users` SET `HelperWarns` = %d, `Helper` = %d, `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[userID][pHelperWarns], playerInfo[userID][pHelper], playerInfo[userID][pPlayersHelped], playerInfo[userID][pSQLID]);
}

YCMD:staff(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    return Dialog_Show(playerid, STAFF, DIALOG_STYLE_LIST, "SERVER: Staff Category", "Admins (%d online)\nHelpers (%d online)", "Select", "Exit", Iter_Count(serverAdmins), Iter_Count(serverHelpers));
}

YCMD:givealllevel(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new const level = strval(params);

    if(!isnumeric(params) || level <= 0 || level >= 100) 
        return sendUsage(playerid, "/givealllevel <level>");

    foreach(new i : serverPlayers) {
        playerInfo[i][pLevel] += level;
        SetPlayerScore(i, playerInfo[i][pLevel]);
    }
    
    va_mysql_tquery("UPDATE `server_users` SET `Level` = `Level` + %d WHERE `Status` = 1", level);

    return SCMTAf(COLOR_YELLOW, "* Administrator %s gived to all online players +%d level up.", GetName(playerid), level);
}

YCMD:giveallrp(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new const rp = strval(params);

    if(!isnumeric(params) || rp <= 0 || rp >= 1000)
        return sendUsage(playerid, "/giveallrespectpoints <points>");

    foreach(new i : serverPlayers) {
        playerInfo[i][pRespectPoints] += rp;
    }

    va_mysql_tquery("UPDATE `server_users` SET `RespectPoints` = `RespectPoints` + %d WHERE `Status` = 1", rp);

    return SCMTAf(COLOR_YELLOW, "* Administrator %s gived to all online players %d respect points.", GetName(playerid), rp);
}

YCMD:giveallmoney(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params)) 
        return sendUsage(playerid, "/giveallmoney <money>");

    new const money = strval(params);

    if(money <= 0 || money >= 20000000)
        return sendError(playerid, "Suma de bani trebuie sa fie cuprinsa intre $0 si $20.000.000.");

    foreach(new i : serverPlayers) {
        addMoney(i, playerInfo[i][pMoneyStore], playerInfo[i][pMoney], 0, money);
    }
    return SCMTAf(COLOR_YELLOW, "* Administrator %s gived to all online players $%s money.", GetName(playerid), formatNumber(money));
}

YCMD:givemoney(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "us[32]", userID, gString) || !isnumeric(gString) || strlen(gString) > 10)
        return sendUsage(playerid, "/givemoney <playerid/name> <money>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    new milliards, millions;
    
    delimiteMoneyFromString(milliards, millions, gString);

    if((milliards >= 5 && millions) || (milliards > 5 && !millions) || (milliards <= 0 && millions <= 0))
        return sendError(playerid, "Suma de bani trebuie sa fie cuprinsa intre $0 si $5.000.000.000.");

    addMoney(userID, playerInfo[userID][pMoneyStore], playerInfo[userID][pMoney], milliards, millions);

    return SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s gived $%s money to player %s.", GetName(playerid), formatMoney(milliards, millions), GetName(userID));
}

YCMD:ip(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "u", userID)) 
        return sendUsage(playerid, "/ip <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin]) 
        return sendError(playerid, "Nu poti folosi aceasta comanda pe acel admin.");
    
    SCMf(playerid, COLOR_GREY, "Searching other accounts with %s's IP (%s)...", GetName(userID), GetPlayerIP(userID));

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT `ID`, `Name` FROM `server_users` WHERE `IP` = '%s' AND `ID` != %d", GetPlayerIP(userID), playerInfo[userID][pSQLID]);
    mysql_tquery(SQL, gQuery, "checkPlayerIP", "d", playerid);
    return 1;
}

YCMD:setadminoff(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new level; gString[0] = EOS; if(sscanf(params, "s[32]d", gString, level) || level < 0 || level > 6 || strlen(gString) > 32)  
        return sendUsage(playerid, "/setadminoff <name> <admin level (0-6)>");

    if(MAP_contains_str(playersNames, gString))
        return sendError(playerid, "Acel player este online.");

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_users` WHERE `Name` = '%e' LIMIT 1", gString);
    mysql_tquery(SQL, gQuery, "setAdminOffline", "dsd", playerid, gString, level);
    return 1;
}

YCMD:sethelperoff(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new level; gString[0] = EOS; if(sscanf(params, "s[32]d", gString, level) || level < 0 || level > 3 || strlen(gString) > 32)  
        return sendUsage(playerid, "/sethelperoff <name> <helper level (0-3)>");

    if(MAP_contains_str(playersNames, gString))
        return sendError(playerid, "Acel player este online.");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_users` WHERE `Name` = '%e' LIMIT 1", gString);
    mysql_tquery(SQL, gQuery, "setHelperOffline", "dsd", playerid, gString, level);
    return 1;
}

YCMD:mark(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new Float: X, Float: Y, Float: Z; GetPlayerPos(playerid, X,Y,Z),

    SetPVarInt(playerid, "Marked", 1);
    SetPVarFloat(playerid, "X", X);
    SetPVarFloat(playerid, "Y", Y);
    SetPVarFloat(playerid, "Z", Z);

    return SCM(playerid, COLOR_GREY, "* Your positions has been saved, if you want to teleport to saved positions, write [/gotomark].");
}

YCMD:gotomark(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(GetPVarInt(playerid, "Marked") != 1) 
        return sendError(playerid, "Nu ai salvat nicio pozitie.");

    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerInterior(playerid, 0);
    SetPlayerPos(playerid, GetPVarFloat(playerid, "X"), GetPVarFloat(playerid, "Y"), GetPVarFloat(playerid, "Z"));

    return SCM(playerid, COLOR_GREY, "* You are teleported to the saved positions.");
}

YCMD:flip(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu esti intr-un vehicul.");

    new Float:angle;

    GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
    SetVehicleZAngle(GetPlayerVehicleID(playerid), angle);

    return SCM(playerid, -1, "Your vehicle was succesfully fliped over.");
}

YCMD:fixveh(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu esti intr-un vehicul.");

    RepairVehicle(GetPlayerVehicleID(playerid));

    return SCM(playerid, -1, "Your vehicle was succesfully repaired.");
}

YCMD:nos(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu esti intr-un vehicul.");

    AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);

    return SCM(playerid, -1, "NOS was added succesfully on your vehicle.");
}

YCMD:gotoxyz(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 3)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new Float: X, Float: Y, Float: Z, interiorid;

    if(sscanf(params, "fffd", X, Y, Z, interiorid)) 
        return sendUsage(playerid, "/gotoxyz <x> <y> <z> <interiorid>");

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
        SetVehiclePos(GetPlayerVehicleID(playerid), X, Y, Z);
        LinkVehicleToInterior(GetPlayerVehicleID(playerid), interiorid);
    }
    else
        SetPlayerPos(playerid, X,Y,Z);
    
    SetPlayerInterior(playerid, interiorid);

    return SCM(playerid, COLOR_GREY, "* You have successfully teleported to those coordinates.");
}

YCMD:respawnhere(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, Float: X, Float: Y, Float: Z; if(sscanf(params, "u", userID))   
        return sendUsage(playerid, "/respawnhere <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    GetPlayerPos(userID, X, Y, Z);

    SpawnPlayer(userID);

    defer delayedSetPlayerPos(userID, X, Y, Z);
    
    SCMf(playerid, COLOR_GREY, "* You respawned %s using command [/respawnhere].", GetName(userID));
    SCMf(userID, COLOR_GREY, "* %s respawned you and teleported you to last location.", GetName(playerid));
    return 1;
}

YCMD:unban(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID[MAX_PLAYER_NAME];
    
    gString[0] = EOS; if(sscanf(params, "s[25]s[64]", userID, gString))
        return sendUsage(playerid, "/unban <full name> <reason>");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_bans` WHERE `Name` = '%e' AND `Active` = 1 LIMIT 1", userID);
    mysql_tquery(SQL, gQuery, "checkBannedPlayer", "dss", playerid, userID, gString);
    return 1;
}

YCMD:banoffline(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_ban_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_ban_delay] - gettime());

    new userID[MAX_PLAYER_NAME], days, reason[64];

    if(sscanf(params, "s[24]ds[64]", userID, days, reason))
        return sendUsage(playerid, "/banoffline <exact name> <days (0 = permanent)> <reason>");

    if(MAP_contains_str(playersNames, userID))
        return sendError(playerid, "Acel player este online.");

    if(days < 0 || days > 360)
        return sendError(playerid, "Invalid Days! (0-360)");

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_users` WHERE `Name` = BINARY '%e' LIMIT 1", userID);
    mysql_tquery(SQL, gQuery, "banOfflineAccount", "ddss", playerid, days, reason, userID);
    return 1;
}

YCMD:ban(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, days; gString[0] = EOS;

    if(playerVars[playerid][var_ban_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_ban_delay] - gettime());

    if(sscanf(params, "uds[64]", userID, days, gString))
        return sendUsage(playerid, "/ban <playerid/name> <days (0 = permanent)> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(playerInfo[userID][pAdmin] || playerInfo[userID][pHelper])
        return sendError(playerid, "Acel player face parte din staff.");

    if(userID == playerid)
        return sendError(playerid, "Nu iti poti da ban singur.");

    if(days < 0 || days > 360)
        return sendError(playerid, "Invalid Days! (0-360)");

    if(strlen(gString) < 4 || strlen(gString) > 64)
        return sendError(playerid, "Invalid reason length! (min. 4 - max. 64)");

    playerVars[playerid][var_ban_delay] = gettime() + 60;

    return givePlayerBan(userID, playerid, days, gString);
}

YCMD:gsearch(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/gsearch <name>");

    new results;

    SCM(playerid, COLOR_GREEN, "___________________________________");

    for(new g = 1; g < sizeof GunNames; g++) {
        if(strfind(GunNames[g], params, true) != -1 || g == strval(params)) {
            SCMf(playerid, -1, "%d. %s [id: %d]", results, GunNames[g], g); 
            results++;
        }
    }

    SCMf(playerid, COLOR_WHITE, "There are %d found results for '%s'.", results, params);
    SCM(playerid, COLOR_GREEN, "___________________________________");
    return 1;
}

YCMD:vsearch(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/vsearch <name>");

    new results;

    SCM(playerid, COLOR_GREEN, "___________________________________");

    for(new v = 0; v < sizeof aVehicleNames; v++) {
        if(strfind(aVehicleNames[v], params, true) != -1 || v == strval(params)-400) {
            SCMf(playerid, -1, "%d. Model: %s [id: %d]", results, aVehicleNames[v], v+400); 
            results++;
        }
    }

    SCMf(playerid, COLOR_WHITE, "There are %d found results for '%s'.", results, params);
    SCM(playerid, COLOR_GREEN, "___________________________________");
    return 1;
}

YCMD:reports(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!Iter_Count(serverReports))
        return sendError(playerid, "Nu sunt report-uri active.");

    SCM(playerid, COLOR_GREY, "* Active reports:");

    foreach(new i : serverReports) {
        switch(reportInfo[i][rReportType]) {
            case REPORT_TYPE_MESSAGE: SCMf(playerid, -1, "Report sent by %s (%d): %s", GetName(i), i, reportInfo[i][rReportText]);
            case REPORT_TYPE_STUCK: SCMf(playerid, -1, "%s (%d) is stuck.", GetName(i), i);
            case REPORT_TYPE_DM: SCMf(playerid, -1, "%s reported %s (%d) for DM/Cheats.", GetName(i), GetName(reportInfo[i][rReportedPlayer]), reportInfo[i][rReportedPlayer]);
        }
    }

    return SCMf(playerid, COLOR_GREY, "* There are %d active reports found.", Iter_Count(serverReports));
}

YCMD:closereport(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(reportInfo[playerid][rReportConversation] != -1) {
        new playeridd = reportInfo[playerid][rReportConversation];

        SCM(playeridd, COLOR_YELLOW, "* Conversatia a fost terminata.");
        SCM(playerid, COLOR_YELLOW, "* Conversatia a fost terminata.");

        reportInfo[playeridd][rReportConversation] = reportInfo[playerid][rReportConversation] = -1;
        return 1;
    }

    if(!playerVars[playerid][b_ADMIN_DUTY])
        return sendError(playerid, "Nu esti on-duty ca administrator. (/aduty)");

    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/closereport <playerid/name> <reason>");

    if(strlen(gString) < 4 || strlen(gString) >= 64)
        return sendError(playerid, "Motiv-ul trebuie sa cuprinda intre 4 si 64 caractere.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverReports, userID))
        return sendError(playerid, "Acel player nu are vreun report activ.");

    if(reportInfo[userID][rReportType] == REPORT_TYPE_DM)
        return sendError(playerid, "Nu poti inchide acest tip de report, foloseste (/spec) pe player-ul raportat.");

    reportInfo[userID][rReportType] = REPORT_TYPE_DELETED;
    reportInfo[userID][rReportText][0] = EOS;

    Iter_Remove(serverReports, userID);

    SCMf(playerid, COLOR_YELLOW, "* You closed %s's report, reason: %s", GetName(userID), gString);
    SCMf(userID, COLOR_YELLOW, "* %s closed your report, reason: %s", GetName(playerid), gString);
    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s closed %s's report, reason: %s", GetName(playerid), GetName(userID), gString);

    playerInfo[playerid][pPlayersHelped] ++;
    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:acceptreport(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!playerVars[playerid][b_ADMIN_DUTY])
        return sendError(playerid, "Nu esti on-duty ca administrator. (/aduty)");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/acceptreport <playerid/name>");

    if(!IsPlayerLogged(userID)) 
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverReports, userID))
        return sendError(playerid, "Acel player nu are vreun report activ.");

    if(reportInfo[userID][rReportType] == REPORT_TYPE_DM)
        return sendError(playerid, "Nu poti accepta acest tip de report, foloseste (/spec) pe player-ul raportat.");

    reportInfo[userID][rReportType] = REPORT_TYPE_DELETED;
    reportInfo[userID][rReportText][0] = EOS;
    reportInfo[userID][rReportConversation] = playerid;
    reportInfo[playerid][rReportConversation] = userID;
        
    Iter_Remove(serverReports, userID);

    SCMf(playerid, COLOR_YELLOW, "* You accepted %s's report. [/x]", GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s accepted your report. [/x]", GetName(playerid));
    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}%s accepted %s's report.", GetName(playerid), GetName(userID));

    playerInfo[playerid][pPlayersHelped] ++;
    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:rmute(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_rmute_delay] > gettime())
        return sendError(playerid, "Poti folosi iar aceasta comanda peste %d secunde.", playerVars[playerid][var_rmute_delay] - gettime());

    new userID, minutes; gString[0] = EOS; if(sscanf(params, "uds[64]", userID, minutes, gString))
        return sendUsage(playerid, "/rmute <playerid/name> <minutes> <reason>");

    if(playerInfo[userID][pAdmin] || playerInfo[userID][pHelper])
        return sendError(playerid, "Acel player face parte din staff.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(strlen(gString) > 32 || strlen(gString) < 5)
        return sendError(playerid, "Motiv-ul tau trebuie sa contina minim 5 caractere si maxim 32.");

    if(minutes > 60 || minutes < 1)
        return sendError(playerid, "Invalid Minutes! (1 - 60)");

    playerInfo[userID][pReportMute] = gettime() + minutes*60;
    playerVars[playerid][var_rmute_delay] = gettime() + 15;

    va_mysql_tquery("UPDATE `server_users` SET `ReportMute` = %d WHERE `ID` = %d", playerInfo[userID][pReportMute] - gettime(), playerInfo[userID][pSQLID]);

    return sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmBot: %s has been muted on [/report] by admin %s for %d minutes. Reason: %s", GetName(userID), GetName(playerid), minutes, gString);
}

YCMD:aduty(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_aduty_delay] > gettime())
        return sendError(playerid, "Poti folosi iar aceasta comanda dupa %d secunde.", playerVars[playerid][var_aduty_delay] - gettime());

    playerVars[playerid][b_ADMIN_DUTY] = !playerVars[playerid][b_ADMIN_DUTY];
    playerVars[playerid][var_aduty_delay] = gettime() + 10;

    if(playerVars[playerid][b_ADMIN_DUTY]) {
        SCM(playerid, COLOR_GREY, "* Now you are on-duty as a admin.");
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s is now on-duty as a admin.", GetName(playerid));
    }
    else {
        SCM(playerid, COLOR_GREY, "* Now you are off-duty as a admin.");
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s is now off-duty as a admin.", GetName(playerid));
    }
    return 1;
}

YCMD:givegun(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, int, int2; if(sscanf(params, "udd", userID, int, int2))
        return sendUsage(playerid, "/givegun <playerid/name> <weaponid> <ammo>");

    if(!IsPlayerLogged(userID)) 
        return sendError(playerid, "Acel player nu este logat.");

    if(int2 < 1 || int2 > 999999)
        return sendError(playerid, "Invalid Ammo! (1-999999)");

    if(!IsValidWeapon(int))
        return sendError(playerid, "Arma invalida!");

    GivePlayerWeapon(userID, int, int2);

    SCMf(playerid, COLOR_GREY, "* I-ai dat arma %s lui %s.", GunNames[int], GetName(userID));
    SCMf(userID, COLOR_GREY, "* %s ti-a dat arma %s.", GetName(playerid), GunNames[int]); 
    return 1;
}

YCMD:area(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new range, Float:X, Float:Y, Float:Z; gString[0] = EOS; if(sscanf(params, "ds[64]", range, gString)) 
        return sendUsage(playerid, "/area <range> <name>"), SCM(playerid, COLOR_GREY, "Name Options: heal, freeze, unfreeze, disarm, armour, fixveh, respawnveh."); 

    GetPlayerPos(playerid, X,Y,Z);

    if(range > 300 || range < 1)
        return sendError(playerid, "Invalid Range! (1m - 300m)");

    switch(YHash(gString)) {
        case _H<heal>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    SetPlayerHealth(i, 100.0);
                    SCMf(i, COLOR_GREY, "* %s healed you.", GetName(playerid));
                }
            }
        }
        case _H<freeze>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    TogglePlayerControllableEx(i, false);
                    SCMf(i, COLOR_GREY, "* %s freezed you.", GetName(playerid));
                }
            }
        }
        case _H<unfreeze>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    TogglePlayerControllableEx(i, true); 
                    SCMf(i, COLOR_GREY, "* %s unfreezed you.", GetName(playerid));
                }
            }
        }
        case _H<disarm>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    ResetPlayerWeapons(i);
                    SCMf(i, COLOR_GREY, "* %s disarmed you.", GetName(playerid));
                }
            }
        }
        case _H<armour>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    SetPlayerArmour(i, 100);
                    SCMf(i, COLOR_GREY, "* %s gived you armour.", GetName(playerid));
                }
            }
        }
        case _H<fixveh>: {
            foreach(new i : playersStreamed[playerid]) {
                if(IsPlayerInRangeOfPoint(i, range, X,Y,Z)) {
                    if(GetPlayerVehicleID(i)) {
                        RepairVehicle(GetPlayerVehicleID(i)); 
                        SCMf(i, COLOR_GREY, "* %s repaired your vehicle.", GetName(playerid));
                    }
                }
            }
        }
        case _H<respawnveh>: {
            new count, current_veh; 

            foreach(new veh : vehiclesStreamed[playerid]) {
                if(GetVehicleDistanceFromPoint(veh, X, Y, Z) <= range && !getVehicleOccupantsCount(veh)) {
                    ++count; 

                    current_veh = veh;

                    Iter_SafeRemove(vehiclesStreamed[playerid], current_veh, veh); 

                    SetVehicleToRespawn(current_veh);
                }
            }
            return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s respawned %d unused vehicles which are in his range (%dm distance).", GetName(playerid), count, range);
        }
        default: {
            sendError(playerid, "Invalid Name Option!");
            return SCM(playerid, COLOR_GREY, "Name Options: heal, freeze, unfreeze, disarm, armour, fixveh, respawnveh."); 
        }
    }

    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s gived '%s' to players which are in his range (%dm distance).", GetName(playerid), gString, range);
}

YCMD:disarm(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/disarm <playerid>");

    new id = strval(params);

    if(!IsPlayerLogged(id))
        return sendError(playerid, "Acel player nu este logat.");

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s disarmed %s.", GetName(playerid), GetName(id));
    SCMf(playerid, COLOR_GREY, "* You disarmed %s.", GetName(id));
    SCMf(id, COLOR_GREY, "* %s disarmed you.", GetName(playerid));
    return ResetPlayerWeapons(id);
}
YCMD:unjail(playerid, params[], help) {
	if(playerInfo[playerid][pAdmin] < 1) return sendError(playerid, "Error:{ffffff} Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");
	new target, reason[64];
	if(sscanf(params, "us[64]", target, reason)) return SCM(playerid, COLOR_GREY, "Usage: {ffffff}/unjail [player id/name] [reason]");
	if(!IsPlayerConnected(target)) return sendError(playerid, "Error: {ffffff}Player not connected.");
	if(playerInfo[target][pJailTime] == 0) return sendError(playerid, "Error: {ffffff}Player not jailed.");

	playerInfo[target][pJailTime] = 1;

	va_SendClientMessageToAll(COLOR_LIGHTRED, "Jail: %s has been released from jail by %s, reason: %s.", GetName(target), GetName(playerid), reason);
	SCMf(target, COLOR_LIGHTRED, "* You have been unjailed by admin %s.", GetName(playerid));

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerJailTime` = '%d' where `ID` = '%d'", 0, playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	return true;
}
YCMD:sstats(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 5)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new 
        housesowned, businessesowned, workers, playersafk, playersonsleep, personalvehicles,
        seconds = gettime() - serverStartTime, hours = seconds / 3600, minutes = (seconds % 3600) / 60;

    for(new i = 0; i < serverStuff[houses]; ++i) {
        if(HouseInfo[i][hOwnerID] != -1)
            ++housesowned;
    }

    for(new i = 0; i < serverStuff[business]; ++i) {
        if(bizzInfo[i][bOwnerSQLID] != -1)
            ++businessesowned;
    }

    foreach(new i : serverPlayers) {
        if(playerVars[i][var_working])
            ++workers;

        if(playerInfo[i][pAFKSeconds] > 9) 
            ++playersafk;

        if(playerVars[i][b_IS_SLEEPING])
            ++playersonsleep;
    }

    foreach(new i : Vehicle) {
        if(vehicleVars[i][var_carPersonal] != -1) 
            ++personalvehicles;
    }

    SCM(playerid, COLOR_GREY, "---------------- Server Stats -----------------");
    SCMf(playerid, -1, "Server Version: "SERVER_VERSION" | Server Uptime: %d days, %d hours, %d minutes", seconds / 86400, hours, minutes);
    SCMf(playerid, -1, "Server TickRate: %d | Unprocessed Queries: %d (on handle: %d) | Players Online: %d/%d (%d in login queue)", GetServerTickRate(), mysql_unprocessed_queries(), SQL, Iter_Count(Player), GetMaxPlayers(), Queue_Count(loginQueue));
    SCMf(playerid, -1, "Players AFK: %d (%d on /sleep) | Personal Vehicles (loaded on server): %d | Dealership vehicles: %d", playersafk, playersonsleep, Iter_Count(personalVehiclesIDs), serverStuff[dealershipVehiclesModels]);
    SCMf(playerid, -1, "Objects: %d | Text Labels: %d | Map Icons: %d | Pickups: %d | Vehicles: %d (%d personal vehicles) | Areas: %d | Actors: %d", Streamer_CountItems(STREAMER_TYPE_OBJECT), Streamer_CountItems(STREAMER_TYPE_3D_TEXT_LABEL), Streamer_CountItems(STREAMER_TYPE_MAP_ICON), Streamer_CountItems(STREAMER_TYPE_PICKUP), Iter_Count(Vehicle), personalvehicles, Streamer_CountItems(STREAMER_TYPE_AREA), Streamer_CountItems(STREAMER_TYPE_ACTOR));
    SCMf(playerid, -1, "Houses: %d (%d owned) | Businesses: %d (%d owned) | Jobs: %d (%d players working) | Safe-zones: %d", serverStuff[houses], housesowned, serverStuff[business], businessesowned, serverStuff[jobs], workers, serverStuff[safeZones]);
    SCM(playerid, COLOR_GREY, "-----------------------------------------------");
    return 1;
}

YCMD:setarmour(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, armura; if(sscanf(params, "ud", userID, armura))
        return sendUsage(playerid, "/setarmour <playerid/name> <value>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    SetPlayerArmour(userID, armura);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s setted %s's armour to %d.", GetName(playerid), GetName(userID), armura);
    SCMf(playerid, COLOR_GREY, "* You setted %s's armour to %d.", GetName(userID), armura);
    SCMf(userID, COLOR_GREY, "* %s setted your armour to %d.", GetName(playerid), armura);
    return 1;
}

YCMD:sethealth(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, viata; if(sscanf(params, "ud", userID, viata))
        return sendUsage(playerid, "/sethealth <playerid/name> <value>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    SetPlayerHealth(userID, viata);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s setted %s's heal to %d.", GetName(playerid), GetName(userID), viata);
    SCMf(playerid, COLOR_GREY, "* You setted %s's heal to %d.", GetName(userID), viata);
    SCMf(userID, COLOR_GREY, "* %s setted your heal to %d.", GetName(playerid), viata);
    return 1;
}

YCMD:spectate(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_SpectatePlayer] != -1)
        return sendError(playerid, "Foloseste comanda /specoff prima data.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/spec <playerid/name>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda pe player-ul respectiv.");

    if(playerVars[userID][var_spectateMe] != -1) 
        return sendError(playerid, "Este deja cineva spectator pe acest player.");

    return spectatePlayer(playerid, userID);
}

YCMD:specoff(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_SpectatePlayer] == -1)
        return sendError(playerid, "Nu esti spectator pe cineva.");

    stop playerVars[playerid][var_spectatetimer]; 

    TogglePlayerSpectating(playerid, false);

    playerTextDrawDestroy(playerid, playerTextdraws[playerid][SpecTD]); 

    playerVars[playerVars[playerid][var_SpectatePlayer]][var_spectateMe] = playerVars[playerid][var_SpectatePlayer] = playerVars[playerid][var_spectateseconds] = -1;

    return SCM(playerid, COLOR_GREY, "* You are no longer spectator.");
}

YCMD:skick(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 3 && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_kick_delay] > gettime())
        return sendError(playerid, "Mai ai de asteptat %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_kick_delay] - gettime());

    new userID; gString[0] = EOS; if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/skick <playerid/name> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra unui admin mai mare ca tine.");

    Kick(userID);

    playerVars[playerid][var_kick_delay] = gettime() + 30;

    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {FFFFFF}%s silent kicked %s (%d). Reason: %s", GetName(playerid), GetName(userID), userID, gString);
}

YCMD:kick(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1 && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_kick_delay] > gettime())
        return sendError(playerid, "Mai ai de asteptat %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_kick_delay] - gettime());

    new userid; gString[0] = EOS; if(sscanf(params, "us[64]", userid, gString))
        return sendUsage(playerid, "/kick <playerid/name> <reason>");

    if(strlen(gString) > 64)
        return sendError(playerid, "Motiv-ul trebuie sa aiba maxim 64 caractere.");

    if(!IsPlayerLogged(userid))
        return sendError(playerid, "Acel player nu este conectat.");

    if(userid == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerInfo[userid][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra unui admin mai mare ca tine.");

    playerVars[playerid][var_kick_delay] = gettime() + 30;

    sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been kicked by %s, reason: %s.", GetName(userid), GetName(playerid), gString);
    SCMf(userid, COLOR_CLIENT, "SERVER: {FFFFFF}You are kicked from the server, reason: %s.", gString);

    defer delayedKick(userid);

    insertEmail(userid, GetName(userid), "AdmBot", "Admin %s kicked you, reason: %s", GetName(playerid), gString);
    return 1;
}

YCMD:aaa2(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/aaa2 <virtual world (0-100)>");

    new vw = strval(params);

    if(vw < 0 || vw > 100)
        return sendError(playerid, "Invalid Virtual World! (0-100).");

    SetPlayerPos(playerid, 1477.0710, 1801.7677, 10.8125);
    SetPlayerVirtualWorld(playerid, vw);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat cu succes! (vw: %d)", vw);
}

YCMD:aaa3(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/aaa3 <virtual world (0-100)>");

    new vw = strval(params);

    if(vw < 0 || vw > 100)
        return sendError(playerid, "Invalid Virtual World! (0-100).");

    SetPlayerPos(playerid, 2021.6870, -2543.2671, 13.5469);
    SetPlayerVirtualWorld(playerid, vw);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat cu succes! (vw: %d)", vw);
}

YCMD:gotols(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda."); 

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(playerid), 1520.8737, -1668.5193, 13.5469);
        
    else SetPlayerPos(playerid, 1520.8737, -1668.5193, 13.5469);

    SetPlayerVirtualWorld(playerid, 0);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat in Los Santos.");
}

YCMD:gotolv(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda."); 

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(playerid), 1693.6194, 1442.2306, 10.7640);
        
    else SetPlayerPos(playerid, 1693.6194, 1442.2306, 10.7640);

    SetPlayerVirtualWorld(playerid, 0);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat in Las Venturas.");
}

YCMD:gotosf(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda."); 

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(playerid), -2705.7444, 375.9870, 4.9684);
        
    else SetPlayerPos(playerid, -2705.7444, 375.9870, 4.9684);

    SetPlayerVirtualWorld(playerid, 0);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat in San Fierro.");
}

YCMD:gotom(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda."); 

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(playerid), -2310.8276, -1652.6489, 483.6979);
        
    else SetPlayerPos(playerid, -2310.8276, -1652.6489, 483.6979);

    SetPlayerVirtualWorld(playerid, 0);

    return SCMf(playerid, COLOR_GREY, "* Ai fost teleportat pe muntele Chilliad.");
}

YCMD:gethere(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, Float:X, Float:Y, Float:Z; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/gethere <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti folosi aceasta comanda pe player-ul respectiv.");

    GetPlayerPos(playerid, X,Y,Z);

    if(GetPlayerState(userID) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(userID), X,Y+1.5,Z);
    
    else SetPlayerPos(userID, X,Y+1.5,Z);

    SetPlayerVirtualWorld(userID, GetPlayerVirtualWorld(playerid));
    SetPlayerInterior(userID, GetPlayerInterior(playerid));

    playerVars[userID][var_inhouse] = playerVars[playerid][var_inhouse];
    playerVars[userID][var_inbizz] = playerVars[playerid][var_inbizz];

    SCMf(playerid, COLOR_GREY, "* L-ai teleportat pe %s la tine.", GetName(userID)); 
    SCMf(userID, COLOR_GREY, "* %s te-a teleportat la el.", GetName(playerid));
    return 1;
}

YCMD:goto(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, Float: X, Float: Y, Float: Z; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/goto <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    GetPlayerPos(userID, X, Y, Z);
    
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
        SetVehiclePos(GetPlayerVehicleID(playerid), X,Y+1.5,Z);

    else SetPlayerPos(playerid, X,Y+1.5,Z);

    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(userID));
    SetPlayerInterior(playerid, GetPlayerInterior(userID));
    LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(userID));

    playerVars[playerid][var_inhouse] = playerVars[userID][var_inhouse];
    playerVars[playerid][var_inbizz] = playerVars[userID][var_inbizz];

    SCMf(playerid, COLOR_GREY, "* Te-ai teleportat la player-ul %s.", GetName(userID));
    SCMf(userID, COLOR_GREY, "* %s s-a teleportat la tine.", GetName(playerid));
    return 1;
}

YCMD:gotocar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/gotocar <carid>");

    new const carID = strval(params);

    if(!IsValidVehicle(carID))
        return sendError(playerid, "Vehiculul cu ID %d nu exista pe server.", carID);

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return sendError(playerid, "Nu trebuie sa fii intr-un vehicul pentru a folosi aceasta comanda.");

    if(GetVehicleDriver(carID) != INVALID_PLAYER_ID)
        return sendError(playerid, "Acel vehicul are un sofer.");

    SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(carID));

    PutPlayerInVehicle(playerid, carID, 0);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {FFFFFF}%s has teleported to vehicle with id %d.", GetName(playerid), carID);
    SCMf(playerid, COLOR_GREY, "* Ai fost teleportat la masina cu ID-ul %d.", carID);
    return 1;
}

YCMD:pm(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new id; gString[0] = EOS; if(sscanf(params, "us[144]", id, gString))
        return sendUsage(playerid, "/pm <playerid/name> <message>");

    if(!IsPlayerLogged(id))
        return sendError(playerid, "Acel player nu este logat.");

    if(id == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    SCMf(playerid, COLOR_YELLOW, "(( PM sent to %s: %s ))", GetName(id), gString);
    SCMf(id, COLOR_YELLOW, "(( PM from %s: %s ))", GetName(playerid), gString);
    return 1;
}

YCMD:closestcar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return sendError(playerid, "Nu poti folosi aceasta comanda deoarece esti deja intr-un vehicul.");

    new const closestcar = GetClosestVehicle(playerid, 15.0);

    if(closestcar == -1 || GetVehicleVirtualWorld(closestcar) != GetPlayerVirtualWorld(playerid) || GetVehicleDriver(closestcar) != INVALID_PLAYER_ID)
        return sendError(playerid, "Nu s-a gasit niciun vehicul gol in apropierea ta.");

    PutPlayerInVehicle(playerid, closestcar, 0);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s has teleported to vehicle %s (carid: %d) using command [/closestcar].", GetName(playerid), aVehicleNames[GetVehicleModel(closestcar)-400], closestcar);
    SCMf(playerid, COLOR_GREY, "* Ai fost teleportat in masina cu ID-ul %d (model: %s).", closestcar, aVehicleNames[GetVehicleModel(closestcar)-400]);
    return 1;
}

YCMD:slapcar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new carid = strval(params), Float: X, Float: Y, Float: Z; if(!isnumeric(params))
        return sendUsage(playerid, "/slapcar <carid>");

    if(!IsValidVehicle(carid))
        return sendError(playerid, "Vehiculul cu ID-ul %d nu exista pe server.", carid);

    GetVehicleVelocity(carid, X, Y, Z);
    SetVehicleVelocity(carid, X, Y, Z+0.3);

    SCMf(playerid, COLOR_GREY, "* Comanda a fost efectuata cu succes pe masina cu ID-ul %d.", carid); 
    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s used command [/slapcar] on vehicle with ID %d.", GetName(playerid), carid);
    return 1;
}

YCMD:getcar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new carid = strval(params), Float: X, Float: Y, Float: Z; if(!isnumeric(params))
        return sendUsage(playerid, "/getcar <carid>");

    if(!IsValidVehicle(carid))
        return sendError(playerid, "Masina cu ID-ul %d nu exista pe server.", carid);

    GetPlayerPos(playerid, X, Y, Z);
    SetVehiclePos(carid, X, Y+2, Z);
    SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
    LinkVehicleToInterior(carid, GetPlayerVirtualWorld(playerid));

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s has teleported vehicle with id %d at his location.", GetName(playerid), carid);
    SCMf(playerid, COLOR_GREY, "* Masina cu ID-ul %d a fost teleportata cu succes la locatia ta.", carid);
    return 1;
}

YCMD:anno(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/anno <message>");

    return sendSplittedMessageToAll(COLOR_CLIENT, COLOR_CLIENT, "(( Admin %s: %s ))", GetName(playerid), params);
}

YCMD:anno2(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/anno2 <message>");

    return sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "(( Admin %s: %s ))", GetName(playerid), params);
}

YCMD:slap(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/slap <playerid>");

    new const userID = strval(params);

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    SCMf(playerid, COLOR_YELLOW, "* Ai folosit /slap pe player-ul %s.", GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s a folosit /slap pe tine.", GetName(playerid));

    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s slapped player %s.", GetName(playerid), GetName(userID)), slapPlayer(userID);
}

YCMD:unstuck(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/unstuck <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    TogglePlayerControllableEx(userID, true);

    ClearAnimations(userID);

    slapPlayer(userID);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s unstucked player %s using command [/unstuck].", GetName(playerid), GetName(userID));
    SCMf(playerid, COLOR_YELLOW, "* Ai folosit comanda /unstuck pe player-ul %s.", GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s a folosit comanda /unstuck pe tine.", GetName(playerid));
    return 1;
}

YCMD:rac(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(racTimerActive)
        return sendError(playerid, "Nu poti face asta acum.");

    defer racTimer();

    SCMTA(COLOR_LIGHTRED, "AdmBot: All unused cars from the server will be respawned after 10 seconds, reason: [/rac].");

    return racTimerActive = true;
}

YCMD:vre(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new vehicleid = GetPlayerVehicleID(playerid);

    if(!vehicleid && sscanf(params, "d", vehicleid)) 
        return sendUsage(playerid, "/vre <vehicleid>");

    if(Iter_Remove(spawnedCars, vehicleid) != INVALID_ITERATOR_SLOT) 
        DestroyVehicle(vehicleid);

    else 
        SetVehicleToRespawn(vehicleid);

    return SCMf(playerid, COLOR_GREY, "* You respawned the vehicle with id %d.", vehicleid);
}

YCMD:respawn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/respawn <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    SpawnPlayer(userID);

    SCMf(userID, COLOR_YELLOW, "* Ai primit respawn de la admin-ul %s.", GetName(playerid));
    SCMf(playerid, COLOR_YELLOW, "* I-ai dat respawn jucatorului %s.", GetName(userID));
    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s respawned player %s.", GetName(playerid), GetName(userID));
    return 1;
}

YCMD:spawncar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(Iter_Count(spawnedCars) >= 198)
        return sendError(playerid, "Sunt foarte multe masini spawnate in momentul de fata.");

    new model, userID, Float: posX, Float: posY, Float: posZ; if(sscanf(params, va_return("dU(%d)", playerid), model, userID))
        return sendUsage(playerid, "/spawncar <modelid> <targetid>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(model < 400 || model > 611)
        return sendError(playerid, "Invalid car ID!");

    if(IsPlayerInAnyVehicle(userID))
        return sendError(playerid, "Nu poti folosi aceasta comanda pe acel player deoarece este intr-un vehicul.");

    GetPlayerPos(userID, posX, posY, posZ);

    new const carspawned = createVehicle(model, posX, posY, posZ, 90.0, random(211), random(211), -1);
    
    LinkVehicleToInterior(carspawned, GetPlayerInterior(userID));
    SetVehicleVirtualWorld(carspawned, GetPlayerVirtualWorld(userID));

    PutPlayerInVehicle(userID, carspawned, 0);
    Iter_Add(spawnedCars, carspawned);

    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s spawned a vehicle for %s. Vehicles spawned in total: %d", GetName(playerid), GetName(userID), Iter_Count(spawnedCars));
}

YCMD:despawncars(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!Iter_Count(spawnedCars))
        return sendError(playerid, "Nu sunt masini spawnate.");

    SCMf(playerid, COLOR_GREY, "* Total masini despawnate: %d", Iter_Count(spawnedCars));
    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s despawned all vehicles. Vehicles despawned in total: %d", GetName(playerid), Iter_Count(spawnedCars));

    foreach(new i : spawnedCars)
        DestroyVehicle(i);

    Iter_Clear(spawnedCars);
    return 1;
}

YCMD:fly(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(IsPlayerInAnyVehicle(playerid)) {
        new 
            Float: X, Float: Y, Float: Z, 
            vehicleid = GetPlayerVehicleID(playerid);

        GetVehicleVelocity(vehicleid, X, Y, Z);
        return SetVehicleVelocity(vehicleid, X, Y, Z+0.3);  
    }
    ToggleFlyMode(playerid, !playerVars[playerid][b_FLY_MODE]);

    if(playerVars[playerid][b_FLY_MODE]) {
        SetPlayerHealth(playerid, 9999999);
        SetPlayerArmour(playerid, 9999999);
    } 
    else {
        SetPlayerHealth(playerid, 100);
        SetPlayerArmour(playerid, 0);
    }
    return 1;
}

YCMD:freeze(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1 && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!isnumeric(params))
        return sendUsage(playerid, "/freeze <playerid>");

    new const userid = strval(params);

    if(!IsPlayerLogged(userid))
        return sendError(playerid, "Invalid ID!");

    TogglePlayerControllableEx(userid, false);

    SCMf(playerid, COLOR_GREY, "* You freezed player %s.", GetName(userid));
    SCMf(userid, COLOR_GREY, "* %s freezed you.", GetName(playerid));
    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s freezed player %s.", GetName(playerid), GetName(userid));   
}

YCMD:unfreeze(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1 && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda."); 

    if(!isnumeric(params))
        return sendUsage(playerid, "/unfreeze <playerid>");

    new const userid = strval(params);

    if(!IsPlayerLogged(userid))
        return sendError(playerid, "Invalid ID!");

    TogglePlayerControllableEx(userid, true);

    SCMf(playerid, COLOR_GREY, "* You unfreezed player %s.", GetName(userid));
    SCMf(userid, COLOR_GREY, "* %s unfreezed you.", GetName(playerid));
    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s unfreezed player %s.", GetName(playerid), GetName(userid));
}

YCMD:clearchat(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    foreach(new i : serverPlayers) {
        if(!playerInfo[i][pAdmin] && !playerInfo[i][pHelper]) {
            for(new c = 0; c < 100; ++c) SCM(i, -1, "");
        }
    }

    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s cleared chat for all online players.", GetName(playerid));
}

YCMD:adminclearchat(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 3) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    for(new i = 0; i < 100; ++i) SendStaff(-1, "");
    return SendStaff(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s cleared chat for admins/helpers.", GetName(playerid));
}

YCMD:suspend(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, hours; gString[0] = EOS;

    if(sscanf(params, "us[32]d", userID, gString, hours) || hours < 1) {
        sendUsage(playerid, "/suspend <playerid> <license> <hours>"); 
        return SCM(playerid, COLOR_GREY, "Licenses: driving, fly, boat, weapon.");
    }

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Jucatorul nu este conectat.");

    new e_pInfo:license;

    if(!strcmp(gString, "driving")) 
        license = pDrivingLicense;
    
    else if(!strcmp(gString, "fly")) 
        license = pFlyLicense;
    
    else if(!strcmp(gString, "boat")) 
        license = pBoatLicense;
    
    else if(!strcmp(gString, "weapon")) 
        license = pWeaponLicense;
    
    else {
        sendError(playerid, "Licenta invalida.");
        return SCM(playerid, COLOR_GREY, "Licenses: driving, fly, boat, weapon.");
    }

    if(playerInfo[userID][license] == -hours)
        return sendError(playerid, "Jucatorul are deja licenta de %s suspendata pentru %d ore.", gString, hours);

    playerInfo[userID][license] = -hours;

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}Admin %s suspended %s's %s license for %d hours.", GetName(playerid), GetName(userID), gString, hours);
    SCMf(userID, COLOR_GREY, "* Admin %s suspended your %s license for %d hours.", GetName(playerid), gString, hours);
    return 1;
}

YCMD:agl(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 4)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, hours; gString[0] = EOS;

    if(sscanf(params, "us[32]d", userID, gString, hours) || hours < 1) {
        sendUsage(playerid, "/agl <playerid> <license> <hours>"); 
        return SCM(playerid, COLOR_GREY, "Licenses: driving, boat, weapon, fly, all.");
    }
    
    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(!strcmp(gString, "driving")) 
        playerInfo[playerid][pDrivingLicense] = hours;
    
    else if(!strcmp(gString, "fly")) 
        playerInfo[playerid][pFlyLicense] = hours;
    
    else if(!strcmp(gString, "boat")) 
        playerInfo[playerid][pBoatLicense] = hours;
    
    else if(!strcmp(gString, "weapon")) 
        playerInfo[playerid][pWeaponLicense] = hours;

    else if(!strcmp(gString, "all")) {
        playerInfo[userID][pDrivingLicense] = playerInfo[userID][pFlyLicense] = playerInfo[userID][pBoatLicense] = playerInfo[userID][pWeaponLicense] = hours;
    
        SCMf(userID, COLOR_GREY, "* Admin %s setted your all licenses for %d hours.", GetName(playerid), hours);
        return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}Admin %s setted %s's all licenses for %d hours.", GetName(playerid), GetName(userID), hours);
    }
    
    else {
        sendError(playerid, "Licenta invalida.");
        return SCM(playerid, COLOR_GREY, "Licenses: driving, boat, weapon, fly, all.");
    }
    
    SCMf(userID, COLOR_GREY, "* Admin %s setted your %s license for %d hours.", GetName(playerid), gString, hours);
    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}Admin %s setted %s's %s license for %d hours.", GetName(playerid), GetName(userID), gString, hours);
    return 1;
}

YCMD:check(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin]) 
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/check <playerid/name>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    return showPlayerStatsToPlayer(playerid, userID);
}

YCMD:warn(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_warn_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti aceasta comanda.", (playerVars[playerid][var_warn_delay] - gettime())); 

    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/warn <playerid> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(playerInfo[playerid][pAdmin] < playerInfo[userID][pAdmin])
        return sendError(playerid, "Nu poti sa-i dai warn acelui player.");

    return givePlayerWarn(userID, playerid, gString);
}

YCMD:unwarn(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 3)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_unwarn_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti aceasta comanda.", (playerVars[playerid][var_unwarn_delay] - gettime()));

    new userID; gString[0] = EOS;

    if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/unwarn <playerid> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(playerInfo[userID][pWarn] == 0)
        return sendError(playerid, "Acel player nu are niciun warn.");

    playerInfo[userID][pWarn] --;
    playerVars[playerid][var_unwarn_delay] = gettime() + 60;

    va_mysql_tquery("UPDATE `server_users` SET `Warn` = %d WHERE `ID` = %d", playerInfo[userID][pWarn], playerInfo[userID][pSQLID]);

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s received one clear warn from Admin %s, reason: %s", GetName(userID), GetName(playerid), gString),
    SCMf(userID, COLOR_GREY, "* You received one clear warn, reason: %s", gString);
    return 1;
}

YCMD:mute(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin] && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_mute_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti aceasta comanda.", (playerVars[playerid][var_mute_delay] - gettime()));

    new userID, minutes; gString[0] = EOS; if(sscanf(params, "uds[64]", userID, minutes, gString))
        return sendUsage(playerid, "/mute <playerid/name> <minutes> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(minutes < 1 || minutes > 120)
        return sendError(playerid, "Invalid minutes! (1 - 120).");

    if(playerInfo[userID][pMute] > gettime() && playerInfo[playerid][pAdmin] < 2)
        return sendError(playerid, "Jucatorul are deja mute.");

    if(playerInfo[userID][pAdmin] >= playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti sa-i dai mute acelui jucator.");

    return givePlayerMute(userID, playerid, minutes, gString);
}

YCMD:unmute(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin] && playerInfo[playerid][pHelper] < 2)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS; if(sscanf(params, "us[32]", userID, gString))
        return sendUsage(playerid, "/unmute <playerid/name> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Jucatorul nu este conectat.");

    if(playerInfo[userID][pMute] < gettime())
        return sendError(playerid, "Jucatorul nu are mute.");

    playerInfo[userID][pMute] = 0;

    va_mysql_tquery("UPDATE `server_users` SET `Mute` = 0 WHERE `ID` = %d", playerInfo[userID][pSQLID]);

    SCMf(userID, COLOR_GREY, "* You are unmuted by admin %s, reason: %s.", GetName(playerid), gString);
    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}Admin %s unmuted %s, reason: %s.", GetName(playerid), GetName(userID), gString);
    return 1;
}

YCMD:adminchat(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/ac <text>");

    return SendAdmins(COLOR_ADMINCHAT, "(%d) %s %s: %s", playerInfo[playerid][pAdmin], playerInfo[playerid][pAdmin] == 7 ? "Owner" : playerInfo[playerid][pAdmin] == 8 ? "Scripter" : "Admin", GetName(playerid), params);
}

YCMD:setadmin(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, admin; if(sscanf(params, "ud", userID, admin) || admin < 0 || admin > 6) 
        return sendUsage(playerid, "/setadmin <playerid/name> <admin level (0-6)>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Jucatorul nu este conectat.");

    if(playerInfo[userID][pAdmin] == admin)
        return sendError(playerid, "Jucatorul are deja acest nivel de admin.");

    if(playerInfo[userID][pAdmin] > playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu poti seta nivelul de admin unui admin mai mare ca tine.");

    if(admin) {
        if(!playerInfo[userID][pAdmin]) { 
            Iter_Add(serverAdmins, userID);
            Iter_Add(serverStaff, userID); 
        }   
    }
    else {
        Iter_Remove(serverAdmins, userID);
        Iter_Remove(serverStaff, userID);

        TextDrawHideForPlayer(userID, AStatsTD);
        TextDrawHideForPlayer(userID, ReportsTD);

        playerInfo[userID][pHUDAdminStats] = false;  
    }
    
    playerInfo[userID][pAdmin] = admin;
    playerInfo[userID][pPlayersHelped] = 0;

    va_mysql_tquery("UPDATE `server_users` SET `Admin` = %d, `PlayersHelped` = 0, `HUDAdminStats` = %d WHERE `ID` = %d", admin, playerInfo[userID][pHUDAdminStats], playerInfo[userID][pSQLID]);

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's admin level to %d.", GetName(playerid), GetName(userID), admin);
    SCMf(userID, COLOR_YELLOW, "* Admin %s setted your admin level to %d.", GetName(playerid), admin);

    insertEmail(userID, GetName(userID), "AdmBot", "%s setted your admin level to %d.", GetName(playerid), admin);
    return 1;
}

YCMD:sethelper(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 6)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID, helper; if(sscanf(params, "ud", userID, helper) || helper < 0 || helper > 3)
        return sendUsage(playerid, "/sethelper <playerid/name> <helper level (0-3)>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Jucatorul nu este conectat.");

    if(playerInfo[userID][pHelper] == helper)
        return sendError(playerid, "Jucatorul are deja acest nivel de helper.");

    if(helper) {
        if(!playerInfo[userID][pHelper]) {
            Iter_Add(serverStaff, userID);
            Iter_Add(serverHelpers, userID);
        }
    }
    else {
        Iter_Remove(serverStaff, userID);
        Iter_Remove(serverHelpers, userID);
    }

    playerInfo[userID][pHelper] = helper;
    playerInfo[userID][pPlayersHelped] = 0;

    va_mysql_tquery("UPDATE `server_users` SET `Helper` = %d, `PlayersHelped` = 0 WHERE `ID` = %d", helper, playerInfo[userID][pSQLID]);

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}Admin %s setted %s's helper level to %d.", GetName(playerid), GetName(userID), helper);
    SCMf(userID, COLOR_YELLOW, "* Admin %s setted your helper level to %d.", GetName(playerid), helper);

    insertEmail(userID, GetName(userID), "AdmBot", "%s setted your helper level to %d.", GetName(playerid), helper);
    return 1;
}