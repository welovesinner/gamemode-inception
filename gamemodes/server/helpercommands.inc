YCMD:hh(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1) 
        return sendError(playerid, "Nu ai gradul necesar pentru a folosi aceasta comanda.");

    SCM(playerid, COLOR_GREEN, "________________________________________________________");
    SCM(playerid, COLOR_GREEN, "Helper Level 1: {FFFFFF}/hc /hduty /nre /ndelete /nr /re /nreport /nmute /deletead /dealershipveh(/dsveh)");
    if(playerInfo[playerid][pHelper] >= 2) SCM(playerid, COLOR_GREEN, "Helper Level 2: {FFFFFF}/kick /freeze /unfreeze /skick /mute /unmute");
    SCM(playerid, COLOR_GREEN, "________________________________________________________");
    return 1;
}

YCMD:deletead(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1 && playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/deletead <playerid/name> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(playerVars[userID][var_placed_ad][0] == EOS)
        return sendError(playerid, "Acel player nu are un anunt plasat.");

    if(strlen(gString) < 1 && strlen(gString) > 64)
        return sendError(playerid, "Motiv-ul tau trebuie sa aiba minim 1 si maxim 64 caractere.");

    stop playerVars[userID][var_ad_timer];

    playerVars[userID][var_placed_ad][0] = EOS;

    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s deleted %s's advert, reason: %s", GetName(playerid), GetName(userID), gString);

    SCMf(playerid, COLOR_YELLOW, "* You deleted %s's advert, reason: %s", GetName(userID), gString);
    SCMf(userID, COLOR_YELLOW, "* %s deleted your advert, reason: %s", GetName(playerid), gString);

    playerInfo[playerid][pPlayersHelped] ++;

    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:nr(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!playerVars[playerid][b_HELPER_DUTY])
        return sendError(playerid, "Nu esti on-duty ca helper. (/hduty)");

    new userID; gString[0] = EOS; 

    if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/nr <playerid/name> <text>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverQuestions, userID))
        return sendError(playerid, "Acel player nu are vreo intrebare activa.");

    SCMf(playerid, COLOR_LGREEN, "* Newbie %s: %s", GetName(userID), playerVars[userID][var_QuestionText]);
    SCMf(playerid, COLOR_LGREEN, "(NR) * Helper %s: %s", GetName(playerid), gString);
    SCMf(userID, COLOR_LGREEN, "* Newbie %s: %s", GetName(userID), playerVars[userID][var_QuestionText]);
    SCMf(userID, COLOR_LGREEN, "(NR) * Helper %s: %s", GetName(playerid), gString);

    playerVars[userID][var_QuestionText][0] = EOS;

    Iter_Remove(serverQuestions, userID);

    playerInfo[playerid][pPlayersHelped] ++;

    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:ndelete(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!playerVars[playerid][b_HELPER_DUTY])
        return sendError(playerid, "Nu esti on-duty ca helper. (/hduty)");

    new userID; gString[0] = EOS;

    if(sscanf(params, "us[64]", userID, gString))
        return sendUsage(playerid, "/ndelete <playerid/name> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverQuestions, userID))
        return sendError(playerid, "Acel player nu are vreo intrebare activa.");

    if(strlen(gString) > 64)
        return sendError(playerid, "Motiv-ul trebuie sa aiba maxim 64 caractere.");

    Iter_Remove(serverQuestions, userID);

    playerVars[userID][var_QuestionText][0] = EOS;

    SCMf(playerid, COLOR_YELLOW, "* You deleted %s's question, reason: %s.", GetName(userID), gString);
    SCMf(userID, COLOR_YELLOW, "* %s deleted your question, reason: %s.", GetName(playerid), gString);
    SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s deleted %s's question, reason: %s.", GetName(playerid), GetName(userID), gString);

    playerInfo[playerid][pPlayersHelped] ++;

    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:nre(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!playerVars[playerid][b_HELPER_DUTY])
        return sendError(playerid, "Nu esti on-duty ca helper. (/hduty)");

    new userID; gString[0] = EOS; 

    if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/nre <playerid/name> <text>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverQuestions, userID))
        return sendError(playerid, "Acel player nu are vreo intrebare activa.");

    sendSplittedMessageToAll(COLOR_LGREEN, COLOR_LGREEN, "* Newbie %s: %s", GetName(userID), playerVars[userID][var_QuestionText]);
    sendSplittedMessageToAll(COLOR_LGREEN, COLOR_LGREEN, "* Helper %s: %s", GetName(playerid), gString);
    sendSplittedMessageToPlayer(userID, COLOR_YELLOW, COLOR_YELLOW, "* Helper %s: %s", GetName(playerid), gString);

    playerVars[userID][var_QuestionText][0] = EOS;

    Iter_Remove(serverQuestions, userID); 

    ++playerInfo[playerid][pPlayersHelped];

    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:questions(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1 && playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!Iter_Count(serverQuestions))
        return sendError(playerid, "Nu sunt intrebari active.");

    SCM(playerid, COLOR_GREY, "* Active Questions:");
    
    foreach(new i : serverQuestions) 
        sendSplittedMessageToPlayer(playerid, -1, -1, "Question from %s (%d): %s", GetName(i), i, playerVars[i][var_QuestionText]);
    
    SCMf(playerid, COLOR_GREY, "* There are %d active questions found.", Iter_Count(serverQuestions));
    return 1;
}

YCMD:nmute(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_nmute_delay] > gettime())
        return sendError(playerid, "Poti folosi iar aceasta comanda peste %d secunde.", playerVars[playerid][var_nmute_delay] - gettime());

    new userID, minutes; gString[0] = EOS;

    if(sscanf(params, "uds[64]", userID, minutes, gString))
        return sendUsage(playerid, "/nmute <playerid/name> <minutes> <reason>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(strlen(gString) > 64)
        return sendError(playerid, "Motiv-ul trebuie sa aiba maxim 64 caractere.");

    if(minutes > 60 || minutes < 1)
        return sendError(playerid, "Invalid Minutes! (1 - 60)");

    playerInfo[userID][pQuestionMute] = gettime() + minutes*60;
    playerVars[playerid][var_nmute_delay] = gettime() + 15;

    va_mysql_tquery("UPDATE `server_users` SET `QuestionMute` = %d WHERE `ID` = %d", (playerInfo[userID][pQuestionMute] - gettime()), playerInfo[userID][pSQLID]);

    return sendSplittedMessageToAll(COLOR_LIGHTRED, COLOR_LIGHTRED, "AdmCmd: %s has been muted on [/n] for %d minutes from %s, reason: %s", GetName(userID), minutes, GetName(playerid), gString);
}

YCMD:nreport(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(!playerVars[playerid][b_HELPER_DUTY])
        return sendError(playerid, "Nu esti on-duty ca helper. (/hduty)");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/nreport <playerid/name>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!Iter_Contains(serverQuestions, userID))
        return sendError(playerid, "Acel player nu are vreo intrebare activa.");

    Iter_Add(serverReports, userID);

    strcpy(reportInfo[userID][rReportText], playerVars[userID][var_QuestionText], 128);

    reportInfo[userID][rReportType] = REPORT_TYPE_MESSAGE;
    playerVars[userID][var_QuestionText][0] = EOS;

    Iter_Remove(serverQuestions, userID);

    SCMf(userID, COLOR_LIGHTRED, "(!) %s marked your question as a report.", GetName(playerid));
    SendStaff(COLOR_DARKRED, "%s's (%d) question was marked as report: %s", GetName(userID), userID, reportInfo[userID][rReportText]);

    playerInfo[playerid][pPlayersHelped] ++;

    va_mysql_tquery("UPDATE `server_users` SET `PlayersHelped` = %d WHERE `ID` = %d", playerInfo[playerid][pPlayersHelped], playerInfo[playerid][pSQLID]);
    return 1;
}

YCMD:hduty(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_hduty_delay] > gettime())
        return sendError(playerid, "Poti folosi iar aceasta comanda dupa %d secunde.", playerVars[playerid][var_hduty_delay] - gettime());

    playerVars[playerid][b_HELPER_DUTY] = !playerVars[playerid][b_HELPER_DUTY];
    playerVars[playerid][var_hduty_delay] = gettime() + 10;

    if(playerVars[playerid][b_HELPER_DUTY]) {
        SCM(playerid, COLOR_GREY, "* Now you are on-duty as a helper.");
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s is now on-duty as a helper.", GetName(playerid));
    }
    else {
        SCM(playerid, COLOR_GREY, "* Now you are off-duty as a helper.");
        SendStaff(COLOR_LIGHTRED, "(Staff Info): {ffffff}%s is now off-duty as a helper.", GetName(playerid));
    }
    return 1;
}

YCMD:re(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1 && playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    new userID; gString[0] = EOS;

    if(sscanf(params, "us[144]", userID, gString))
        return sendUsage(playerid, "/re <playerid/name> <message>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda pe tine.");

    SCMf(playerid, COLOR_YELLOW, "(/re) sended to %s: %s", GetName(userID), gString);
    SCMf(userID, COLOR_YELLOW, "(/re) from %s: %s", GetName(playerid), gString);

    SendStaff(COLOR_YELLOW, "(/re) %s to %s: %s", GetName(playerid), GetName(userID), gString);
    return 1;
}

YCMD:helperchat(playerid, params[], help) {
    if(playerInfo[playerid][pHelper] < 1 && playerInfo[playerid][pAdmin] < 1)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(isnull(params)) 
        return sendUsage(playerid, "/hc <text>");

    return SendStaff(COLOR_HELPERCHAT, "(%d) %s %s: %s", playerInfo[playerid][pAdmin] ? playerInfo[playerid][pAdmin] : playerInfo[playerid][pHelper], playerInfo[playerid][pAdmin] < 7 ? "Admin" : playerInfo[playerid][pAdmin] == 7 ? "Owner" : playerInfo[playerid][pAdmin] == 8 ? "Scripter" : "Helper", GetName(playerid), params);
}