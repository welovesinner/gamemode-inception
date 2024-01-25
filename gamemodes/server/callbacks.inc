public OnRuntimeError(code, &bool:suppress) {
    SendAdmins(COLOR_DARKRED, "(!) Warning: An runtime error occurred while executing a script. (errorid: %d)", code);
    return 1;
}

public Streamer_OnPluginError(const error[]) {
    SendAdmins(COLOR_DARKRED, "(!) Warning: An streamer error occurred.");
    return PrintAmxBacktrace();
}

public OnQueryError(errorid, error[], callback[], query[], connectionHandle) { 
    if(errorid == 2003) {
        for(new i; i < 20; ++i) SCMTA(-1, "");
        SCMTA(COLOR_CLIENT, "SERVER: A fatal database error occurred. The server will enter in maintenance."); 
        SCMTA(COLOR_CLIENT, "SERVER: We will be back as soon as possible.");
        SCMTA(-1, "");
        SCMTA(COLOR_CLIENT, "SERVER: A aparut o eroare fatala la baza de date. Server-ul va intra in mentenanta.");
        SCMTA(COLOR_CLIENT, "SERVER: Vom revenii cat de curand posibil.");
        SCMTA(-1, "");

        SendRconCommand("hostname rpg.Lurk.ro - maintenance"); 
        SendRconCommand("password dbsuadbaubd17271dbsuadbua"); 

        defer kickAll();
    }

    else SendAdmins(COLOR_DARKRED, "(!) Warning: An mysql error occurred while processing a query. (errorid: %d)", errorid);

    print("=========================================");
    printf("Handle: %d", connectionHandle);
    print("=========================================");
    printf("Error ID: %d", errorid);
    printf("Error: %s", error);
    printf("Callback: %s", callback);
    printf("Query Unprocessed: %s", query);
    print("========================================="); 
    return 1;
}

public OnGameModeInit() {
    print(" \n_________________________________________________");
    print(" rpg.Lurk.ro se incarca...                  ");
    print(" versiune: "SERVER_VERSION"                      ");
    print("_________________________________________________");
    print(" \n ");

    mysql_log(LOG_ERROR | LOG_WARNING, LOG_TYPE_TEXT);
    SQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_DATABASE, MYSQL_PASSWORD);

    if(mysql_errno()) 
        return printf("[MYSQL ERROR] The database have an error [id: %d]. (gamemode initialisation stopped)", mysql_errno());

    print("[MYSQL SUCCES] The database was connected succesfully.");

    ManualVehicleEngineAndLights();
    DisableInteriorEnterExits();
    SetNameTagDrawDistance(30.0);
    EnableStuntBonusForAll(false);
    AllowInteriorWeapons(true);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    UsePlayerPedAnims();

    Command_SetDeniedReturn(true);

    Streamer_ToggleErrorCallback(true);

    new hour; 
    gettime(hour); 
    FixWorldWeather(hour);

    staffQuestionsInfoDelay = gettime() + 300;

    for(new i = 0; i < sizeof pickupInfo; ++i) {
        memset(pickupInfo[i], -1);
    }

    mysql_tquery(SQL, "UPDATE `server_users` SET `Status` = 0 WHERE `Status` = 1");
    mysql_tquery(SQL, "UPDATE `server_users` SET `PlayerID` = -1");

    mysql_tquery(SQL, "SELECT * FROM `server_svars`", "load_server_vars", "");
    mysql_tquery(SQL, "SELECT * FROM `server_houses`", "load_houses", "");
    mysql_tquery(SQL, "SELECT * FROM `server_safezones`", "load_safezones", "");
    mysql_tquery(SQL, "SELECT * FROM `server_business`", "load_business", "");
    mysql_tquery(SQL, "SELECT * FROM `server_jobs`", "load_jobs", "");
    mysql_tquery(SQL, "SELECT * FROM `server_doors`", "load_doors", "");
    mysql_tquery(SQL, "SELECT * FROM `server_groups`", "load_groups", "");
    mysql_tquery(SQL, "SELECT * FROM `server_group_vehicles`", "LoadGroupVehicles", "");
    mysql_tquery(SQL, "SELECT * FROM `server_turfs`", "iniTurfs", "");
    mysql_tquery(SQL, "SELECT * FROM `server_vehicles`", "load_server_vehicles", "");
    mysql_tquery(SQL, "SELECT * FROM `server_dealership_vehicles` ORDER BY `server_dealership_vehicles`.`Price` ASC", "load_dealership_vehicles", "");
    CA_Init();
    initResettedVariables();
    initCommandAltNames();
    
    loadServerTextdraws();

    loadLabels();
    loadPickups();
    loadMapIcons();
    loadObjects();
    loadActors();
    loadRentLocations();
    loadVendingMachines();
    SendRconCommand("weburl "SERVER_WEBURL"");
    SendRconCommand("language "SERVER_LANGUAGE"");

    #if defined INITIALISE_GAMEMODE_DELAY
        SetGameModeText("loading...");
        SendRconCommand("hostname "SERVER_HOSTNAME" initialising...");
        SendRconCommand("password nidsandiasidbsoadhw821838SAgsyagsySBuiuSYYYSioiii@!3");
        defer loadServer();
    #else
        SendRconCommand("hostname "SERVER_HOSTNAME"");
        SendRconCommand("password "SERVER_PASSWORD""); 
        SetGameModeText(SERVER_VERSION);
    #endif

    serverStartTime = gettime();
    return 1;
}

public OnGameModeExit() {
    destroyServerTextdraws(); 
    mysql_close(SQL); 
    return 1;
}

public OnPlayerConnect(playerid) {    
    initConnection(playerid); 

    SetPlayerScore(playerid, 0);
    SetPlayerPos(playerid, 0.0, 0.0, 0.0);
    SetPlayerVirtualWorld(playerid, playerid + 1);
    SetPlayerColor(playerid, COLOR_GREY);
    SetPlayerWorldBounds(playerid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);

    sendDeathMessage(playerid, INVALID_PLAYER_ID, 200);

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `IP` = '%e' WHERE `Name` = '%e'", GetPlayerIP(playerid), GetName(playerid)); 
    mysql_tquery(SQL, gQuery, "", "");

    if(serverVars[7][svar_Value] != 0 && 1 + SortArray_CountOccurences(playersIPs, playerInfo[playerid][pIntIP]) >= serverVars[7][svar_Value]) 
        return Kick(playerid);
        
    SortArray_Insert(playersIPs, playerInfo[playerid][pIntIP]);

    if(findAdvert(GetName(playerid))) {
        SCMf(playerid, COLOR_DARKRED, "You are kicked because your name contains an advert. (%s)", GetName(playerid));
        SendAdmins(COLOR_DARKRED, "%s has been kicked because his name contains an advert.", GetName(playerid));
    
        defer delayedKick(playerid); 
        return 1;
    }

    if(!strcmp(GetName(playerid), "AdmBot")) {
        SCMf(playerid, COLOR_DARKRED, "You can't have this name.");

        defer delayedKick(playerid); 
        return 1;
    }

    TogglePlayerSpectating(playerid, true); 
    
    InterpolateCameraPos(playerid, 370.658172, -1398.887207, 101.570533, 530.287475, -1413.706054, 87.225357, 15000);
    InterpolateCameraLookAt(playerid, 374.464080, -1400.969604, 99.084770, 528.010192, -1416.861450, 84.085639, 15000);

    TextDrawShowForPlayer(playerid, serverDateTD); 
    TextDrawShowForPlayer(playerid, serverClockTD); 
    TextDrawShowForPlayer(playerid, LogoTD[0]);
    TextDrawShowForPlayer(playerid, LogoTD[1]);
    TextDrawShowForPlayer(playerid, LogoTD[2]);

    PlayAudioStreamForPlayer(playerid, "http://sndup.net/bs7x/d");

    raceCheckThreads[playerid] ++;

    if(serverVars[11][svar_Value])
        initialisePlayerLoginQueue(playerid);

    else {
        gQuery[0] = EOS; 
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT * FROM `server_bans` WHERE `Name` = '%e' AND `Active` = 1 LIMIT 1", GetName(playerid)); 
        mysql_tquery(SQL, gQuery, "checkBanStatus", "d", playerid);
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason) { 
    raceCheckThreads[playerid] ++;

    new reasonStr[14];

    switch(reason) {
        case 0: reasonStr = "crash";
        case 1: reasonStr = "quit"; 
        default: reasonStr = "kicked/banned";
    }

    sendNearbyMessage(playerid, COLOR_CLIENT, 25.0, "%s has disconnected from server. (%s)", GetName(playerid), reasonStr);

    if(playerInfo[playerid][pAdmin]) 
        SendStaff(COLOR_HELPERCHAT, "(QuitBot): Admin %s has leaved. (%s)", GetName(playerid), reasonStr);
    
    else if(playerInfo[playerid][pHelper]) 
        SendStaff(COLOR_HELPERCHAT, "(QuitBot): Helper %s has leaved. (%s)", GetName(playerid), reasonStr);

    resetVarsOnDisconnect(playerid);

    va_mysql_tquery("UPDATE `server_users` SET `Seconds` = %f, `Mute` = %d, `QuestionMute` = %d, `ReportMute` = %d, `Status` = 0, `PlayerID` = -1, `DrivingLicense` = %d, `FlyLicense` = %d, `BoatLicense` = %d, `WeaponLicense` = %d WHERE `ID` = %d",
    playerInfo[playerid][pSeconds], (playerInfo[playerid][pMute] > gettime()) ? (playerInfo[playerid][pMute] - gettime()) : (0), (playerInfo[playerid][pQuestionMute] > gettime()) ? (playerInfo[playerid][pQuestionMute] - gettime()) : (0), (playerInfo[playerid][pReportMute] > gettime()) ? (playerInfo[playerid][pReportMute] - gettime()) : (0), 
    playerInfo[playerid][pDrivingLicense], playerInfo[playerid][pFlyLicense], playerInfo[playerid][pBoatLicense], playerInfo[playerid][pWeaponLicense], playerInfo[playerid][pSQLID]);

    SortArray_Remove(playersIPs, playerInfo[playerid][pIntIP]);

    destroyPlayerLabels(playerid);

    playerInfo[playerid][pSQLID] = 0;

    sendDeathMessage(playerid, INVALID_PLAYER_ID, 201);
    return 1;
}

public OnPlayerSpawn(playerid) {
    SetPlayerSkin(playerid, playerInfo[playerid][pSkin]);
    if(playerInfo[playerid][pGroup] == 0)
    {
        SetPlayerColor(playerid, COLOR_WHITE);
        SetPlayerFacingAngle(playerid, 270.0000);
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
    }
    SetPlayerColor(playerid, COLOR_WHITE);
    SetPlayerHealth(playerid, 100.0);
    SetPlayerArmour(playerid, 0.0);
    SetPlayerTeam(playerid, 1);
    StopAudioStreamForPlayer(playerid);

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetMoney(playerid) <= 999999998 && GetMilliards(playerid) < 1 ? GetMoney(playerid) : 999999999);

    playerVars[playerid][var_inbizz] = playerVars[playerid][var_inhouse] = -1;

    if(playerInfo[playerid][pSpawnType] == SPAWN_TYPE_HOUSE) 
        playerEnterHouse(playerid, playerInfo[playerid][pHouse] != -1 ? playerInfo[playerid][pHouse] : playerInfo[playerid][pRent]);

    if(playerVars[playerid][var_spectateMe] != -1) {
        TogglePlayerSpectating(playerVars[playerid][var_spectateMe], true); 
        SetPlayerInterior(playerVars[playerid][var_spectateMe], GetPlayerInterior(playerid)); 
        SetPlayerVirtualWorld(playerVars[playerid][var_spectateMe], GetPlayerVirtualWorld(playerid));
        
        PlayerSpectatePlayer(playerVars[playerid][var_spectateMe], playerid);
    }

    if(IsValidDynamic3DTextLabel(playerLabels[playerid][l_death])) {
        DestroyDynamic3DTextLabel(playerLabels[playerid][l_death]); 
        playerLabels[playerid][l_death] = Text3D:-1;
    }

    playerVars[playerid][var_death] = false;
    return 1;
}
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
    if(playerVars[playerid][var_insafezone] && !playerVars[playerid][var_delay]) {
        SetPlayerArmedWeapon(playerid, 0); 
        TogglePlayerControllableEx(playerid, false); 
        playerVars[playerid][var_delay] = true;
        defer freezeTimer[3000](playerid);

        SCM(playerid, COLOR_GREY, "Nu ai voie sa faci DM (DeathMatch) in safe-zone! Ai primit freeze timp de 3 secunde.");
    }
    return 1;
}
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {   
    if(!isPlayerDead(playerid) && !playerVars[playerid][b_FLY_MODE]) {
        playerDeathKillerID = issuerid;
        playerDeathReason = weaponid;

        if(issuerid != INVALID_PLAYER_ID) {
            if(playerVars[playerid][var_insafezone])
                return 1;

            if(weaponid == 34) { 
                SetPlayerHealth(playerid, 0.0); 
                SetPlayerArmour(playerid, 0.0);
                return 1;   
            }

            new bodystr[16];

            switch(bodypart) {
                case BODY_PART_HEAD: bodystr = "head";
                case BODY_PART_TORSO: bodystr = "torso";
                case BODY_PART_GROIN: bodystr = "groin";
                case BODY_PART_LEFT_ARM: bodystr = "left arm";
                case BODY_PART_RIGHT_ARM: bodystr = "right arm";
                case BODY_PART_LEFT_LEG: bodystr = "left leg";
                case BODY_PART_RIGHT_LEG: bodystr = "right leg";
            }

            if(playerVars[issuerid][var_spectateMe] != -1) 
                SCMf(playerVars[issuerid][var_spectateMe], COLOR_PINK, "[DMG]: %s damaged %s (weaponid: %d, bodypart: %s, amount: %0.2f).", GetName(issuerid), GetName(playerid), weaponid, bodystr, amount);

            new 
                weaponname[32] = "Fist";

            if(GetPlayerWeapon(issuerid) != 0)
                GetWeaponName(weaponid, weaponname, 32);

            if(playerInfo[playerid][pHUDDMG]) {
                gString[0] = EOS; 
                format(gString, sizeof gString, "~R~%s [%s, -%0.2f HP - %s]", GetName(issuerid), weaponname, amount, bodystr);
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][DMG], gString);
                
                PlayerTextDrawShow(playerid, playerTextdraws[playerid][DMG]);

                stop playerVars[playerid][var_damageinformer_timer];
                playerVars[playerid][var_damageinformer_timer] = defer hideDamageInformer(playerid);
            }
            if(playerInfo[issuerid][pHUDDMG]) {
                gString[0] = EOS; 
                format(gString, sizeof gString, "~G~%s [-%0.2f HP - %s]", weaponname, amount, bodystr);
                PlayerTextDrawSetString(issuerid, playerTextdraws[issuerid][DMG], gString);
                
                PlayerTextDrawShow(issuerid, playerTextdraws[issuerid][DMG]);
                
                PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);

                stop playerVars[issuerid][var_damageinformer_timer];
                playerVars[issuerid][var_damageinformer_timer] = defer hideDamageInformer(issuerid);
            }
        }

        new Float:HP, Float:AP;
        GetPlayerHealth(playerid, HP); 
        GetPlayerArmour(playerid, AP);

        if(AP >= amount) {
            SetPlayerArmour(playerid, AP - amount); 
        }
        else if(AP < 0.0) {
            HP -= amount; 
        }
        else {
            HP += AP - amount;
            SetPlayerArmour(playerid, 0.0);
        }

        SetPlayerHealth(playerid, HP);
    }
    return 1;
}
    
public OnPlayerDeath(playerid, killerid, reason) {
    killerid = playerDeathKillerID;
    reason = playerDeathReason;

    sendDeathMessage(playerid, killerid, reason);

    playerVars[playerid][var_death] = true;

    playerLabels[playerid][l_death] = CreateDynamic3DTextLabel("* dead *", COLOR_LIGHTRED, 0.0, 0.0, 0.0, 8.5, playerid);

    if(playerVars[playerid][var_working]) 
        stopWork(playerid);
    if(killerid != INVALID_PLAYER_ID) if(playerInfo[playerid][pHeadValue] > 0 && playerInfo[killerid][pGroup] == 5 && contract_get[killerid] == playerid) {
        if(Undercover[killerid] == 0) SendGroupMessage(5, COLOR_BLUE, "%s failed to complete the contract on %s, reason: not undercover.", GetName(killerid), GetName(playerid));
        else if(playerVars[killerid][b_PHONE_TURN] == true) SendGroupMessage(5, COLOR_BLUE, "%s failed to complete the contract on %s, reason: phone turned on.", GetName(killerid), GetName(playerid));
        else if(GetDistanceBetweenPlayers(playerid, killerid) < 100 && reason != WEAPON_KNIFE) SendGroupMessage(5, COLOR_BLUE, "%s failed to complete the contract on %s, reason: distance.", GetName(killerid), GetName(playerid)); 
        else {
            addMoney(killerid, GetMilliards(killerid), GetMoney(killerid), 0, playerInfo[playerid][pHeadValue]);
            SendGroupMessage(5, COLOR_BLUE, "%s has succesfully completed the contract on %s for %s$, distance: %0.2fm.", GetName(killerid), GetName(playerid), formatNumber(playerInfo[playerid][pHeadValue]), GetDistanceBetweenPlayers(playerid, killerid));
            giveRaportPoint(killerid, 1);
        }
        contract_get[killerid] = -1;
        playerInfo[playerid][pHeadValue] = 0; pUpdateInt(playerid, "HeadValue", 0); 
    } 
    if(killerid != INVALID_PLAYER_ID)
    {
        new memberPlayer = playerInfo[playerid][pGroup], memberKiller = playerInfo[killerid][pGroup];

        foreach(new t : active_wars) 
        {
            if(IsPlayerInTurf(playerid, t) && IsPlayerInTurf(killerid, t) && in_war[playerInfo[killerid][pGroup]] && in_war[playerInfo[playerid][pGroup]] == 1) 
            {
                SCMf(killerid, COLOR_TEAL, "War: {FFFFFF}L-ai ucis pe %s.", GetName(playerid));
                SCMf(playerid, COLOR_TEAL, "War: {FFFFFF}Ai fost ucis de %s.", GetName(killerid));

                warScore[playerid][1]++;
                warScore[killerid][0]++;
                if(warVariables[t][wDefender] == memberPlayer && warVariables[t][wAttacker] == memberKiller) warVariables[t][wAttackerScore]++;
                if(warVariables[t][wDefender] == memberKiller && warVariables[t][wAttacker] == memberPlayer) warVariables[t][wDefenderScore]++;

                foreach(new i : Player) 
                {
                    if(in_war[playerInfo[i][pGroup]] == 1) 
                    {
                        if(warVariables[t][wDefender] == playerInfo[i][pGroup] || warVariables[t][wAttacker] == playerInfo[i][pGroup]) 
                        {
                            SendDeathMessageToPlayer(i, killerid, playerid, reason);
                        }
                    }
                }

                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid, x, y, z);
                CreateDeathLoot(t, x, y + 2, z);
            }
        } 
    }
    return 1;
}

public OnVehicleSpawn(vehicleid) {
    if(vehicleVars[vehicleid][var_carRadio] && IsVehicleOccupied(vehicleid))
        StopAudioStreamForPlayers(vehicleid);

    vehicleVars[vehicleid][var_carEngine] = vehicleVars[vehicleid][var_carLights] = vehicleVars[vehicleid][var_carBoot] = vehicleVars[vehicleid][var_carBoonet] = false;
    vehicleVars[vehicleid][var_carRadio] = 0;
    
    if(getVehicleModelType(GetVehicleModel(vehicleid)) == VEHICLE_MODEL_TYPE_BIKE) {
        SetVehicleParamsEx(vehicleid, 1, 0, 0, vehicleVars[vehicleid][var_carLocked], 0, 0, 0);
        vehicleVars[vehicleid][var_carEngine] = true;
    }
    else SetVehicleParamsEx(vehicleid, 0, 0, 0, vehicleVars[vehicleid][var_carLocked], 0, 0, 0);

    return 1;
}

public OnVehicleDeath(vehicleid, killerid) {
    if(killerid != INVALID_PLAYER_ID) {
        if(vehicleid == playerVars[killerid][var_rentedcar]) {
            destroyPlayerRentVehicle(killerid);

            SCM(killerid, COLOR_GREEN, "(Rent Car): {ffffff}Your rented vehicle has been destroyed."); 
        }

        else if(playerVars[killerid][var_working] && vehicleid == playerVars[killerid][var_jobvehicle])
            stopWork(killerid);
    }

    if(vehicleVars[vehicleid][var_carRadio] && IsVehicleOccupied(vehicleid))
        StopAudioStreamForPlayers(vehicleid);

    return 1;
}

public OnPlayerText(playerid, text[]) {
    if(IsPlayerLogged(playerid)) {
        if(getPlayerPinInsertType(playerid) != PIN_INVALID_TYPE || isPlayerInDealership(playerid))
            return false;

        if(playerVars[playerid][var_chat_delay] > GetTickCount() && !strcmp(playerVars[playerid][var_chat_last], text))
            return false;

        if(sscanf(text, "s[144]", text))
            return false;

        if(playerVars[playerid][b_IS_SLEEPING]) {
            sendError(playerid, "Nu poti scrie in chat deoarece esti pe /sleep.");
            return false;
        }

        if(playerInfo[playerid][pMute] > gettime()) {
            sendError(playerid, "Nu poti scrie in chat deoarece ai mute pentru inca %d %s.", ((playerInfo[playerid][pMute] - gettime()) > 60) ? ((playerInfo[playerid][pMute] - gettime()) / 60) : (playerInfo[playerid][pMute] - gettime()), ((playerInfo[playerid][pMute] - gettime()) > 60) ? "minute" : "secunde");
            return false;
        }

        if(serverVars[4][svar_Value] == 1 && findAdvert(text)) {
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be advertising and has been muted for 1 minute (text: %s).", GetName(playerid), text); 
            playerInfo[playerid][pMute] = gettime() + 60;
            return false;
        }
        
        if(playerVars[playerid][var_incall] != -1) {
            if(playerVars[playerid][var_incall_delay] > gettime())
                return false;

            gString[0] = EOS;
            format(gString, sizeof gString, "(cellphone) %s", text);
            SetPlayerChatBubble(playerid, gString, COLOR_WHITE, 25.0, 5000);

            gString[0] = EOS;
            format(gString, sizeof gString, "(cellphone) %s (%d) says: %s", GetName(playerid), playerid, text);
            SCM(playerVars[playerid][var_incall], COLOR_YELLOW, gString); 
            SCM(playerid, COLOR_YELLOW, gString);

            if(playerVars[playerVars[playerid][var_incall]][b_PHONE_SPEAKER])
                sendNearbyMessage(playerVars[playerid][var_incall], 0xA0A0A0FF, 15.0, "(cellphone speaker) %s (%d) says to %s (%d): %s", GetName(playerid), playerid, GetName(playerVars[playerid][var_incall]), playerVars[playerid][var_incall], text);

            playerVars[playerid][var_incall_delay] = gettime() + 3;
            return false;
        }

        sendNearbyMessage(playerid, COLOR_WHITE, 25.0, "{%s}%s: {FFFFFF}%s", playerInfo[playerid][pAdmin] ? "BA0404" : "AFAFAF", GetName(playerid), text);
        SetPlayerChatBubble(playerid, text, COLOR_WHITE, 25.0, 5000);

        playerVars[playerid][var_chat_delay] = GetTickCount() + serverVars[5][svar_Value] * 1000;
        strcpy(playerVars[playerid][var_chat_last], text, 144);

        if(playerVars[playerid][var_spectateMe] != -1) 
            SCMf(playerVars[playerid][var_spectateMe], COLOR_PINK, "[CHAT]: %s: %s", GetName(playerid), text);

/*        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_chat_logs` (PlayerSQLID, Text) VALUES (%d, '%e')", playerInfo[playerid][pSQLID], text);
        mysql_tquery(SQL, gQuery, "", "");*/
    }
    return false;
} 

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) {
    if(!IsPlayerLogged(playerid) || getPlayerPinInsertType(playerid) != PIN_INVALID_TYPE || isPlayerInDealership(playerid))
        return COMMAND_DENIED;

    if(isPlayerInTrade(playerid)) {
        sendError(playerid, "Nu poti folosi comenzi in timp ce esti intr-o negociere.");
        return COMMAND_DENIED;
    }

    if(playerInfo[playerid][pMute] > gettime()) {
        sendError(playerid, "Nu poti folosi comenzi deoarece ai mute pentru inca %d %s.", ((playerInfo[playerid][pMute] - gettime()) > 60) ? ((playerInfo[playerid][pMute] - gettime()) / 60) : (playerInfo[playerid][pMute] - gettime()), ((playerInfo[playerid][pMute] - gettime()) > 60) ? "minute" : "secunde");
        return COMMAND_DENIED;
    }

    if(playerVars[playerid][b_IS_SLEEPING] && strcmp(cmdtext, "/sleep") != 0) {
        sendError(playerid, "Nu poti folosi comenzi in timp ce esti pe /sleep.");
        return COMMAND_DENIED;
    }

    if(playerVars[playerid][var_spectateMe] != -1) 
        SCMf(playerVars[playerid][var_spectateMe], COLOR_PINK, "%s used command %s.", GetName(playerid), cmdtext);

    if(success != COMMAND_OK) { 
        SCM(playerid, -1, "SERVER: This command does not exist."); 
        return COMMAND_OK; 
    }
    return COMMAND_OK;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
    if(!ispassenger) {
        switch(getVehicleModelType(GetVehicleModel(vehicleid))) {
            case VEHICLE_MODEL_TYPE_PLANE: {
                if(playerInfo[playerid][pFlyLicense] <= 0) {
                    sendError(playerid, "Nu ai licenta de pilot.");
                    return slapPlayer(playerid);
                }
            }
            case VEHICLE_MODEL_TYPE_BOAT: {
                if(playerInfo[playerid][pBoatLicense] <= 0) {
                    sendError(playerid, "Nu ai licenta de navigatie.");
                    return slapPlayer(playerid);
                }
            }
            case VEHICLE_MODEL_TYPE_CAR: {
                if(playerInfo[playerid][pDrivingLicense] <= 0) {
                    sendError(playerid, "Nu ai licenta de condus.");
                    return slapPlayer(playerid);
                }
            }
        }
    }
    return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate) {
    new const vehicleid = GetPlayerVehicleID(playerid);

    switch(newstate) {
        case PLAYER_STATE_DRIVER: {
            switch(getVehicleModelType(GetVehicleModel(vehicleid))) {
                case VEHICLE_MODEL_TYPE_PLANE: {
                    if(playerInfo[playerid][pFlyLicense] <= 0) {
                        sendError(playerid, "Nu ai licenta de pilot.");
                        return slapPlayer(playerid);
                    }
                }
                case VEHICLE_MODEL_TYPE_BOAT: {
                    if(playerInfo[playerid][pBoatLicense] <= 0) {
                        sendError(playerid, "Nu ai licenta de navigatie.");
                        return slapPlayer(playerid);
                    }
                }
                case VEHICLE_MODEL_TYPE_CAR: {
                    if(playerInfo[playerid][pDrivingLicense] <= 0 && getPlayerDMVVehicle(playerid) != vehicleid) {
                        sendError(playerid, "Nu ai licenta de condus.");
                        return slapPlayer(playerid);
                    }
                }
            }

            anticheatInfo[playerid][ac_lastvehicle] = vehicleid;

            TogglePlayerSpeedometer(playerid, true);

            Iter_Add(playersInVehicles, playerid);

            checkVehicleRadio(vehicleid, playerid);

            if(playerVars[playerid][var_spectateMe] != -1) 
                PlayerSpectateVehicle(playerVars[playerid][var_spectateMe], vehicleid);

            if(vehicleVars[vehicleid][var_carFuel] <= 1) 
                GameTextForPlayer(playerid, "~W~NO FUEL!", 5000, 4);

            if(vehicleVars[vehicleid][var_carPersonal] != -1) 
                OnPlayerEnterPersonalVehicle(playerid, vehicleid, false);
        }
        case PLAYER_STATE_PASSENGER: {
            anticheatInfo[playerid][ac_lastvehicle] = vehicleid;

            Iter_Add(playersInVehicles, playerid);

            TogglePlayerSpeedometer(playerid, true);

            checkVehicleRadio(vehicleid, playerid);

            if(playerVars[playerid][var_spectateMe] != -1) 
                PlayerSpectateVehicle(playerVars[playerid][var_spectateMe], vehicleid);

            if(vehicleVars[vehicleid][var_carPersonal] != -1) 
                OnPlayerEnterPersonalVehicle(playerid, vehicleid, true);
        }
    }

    switch(oldstate) {
        case PLAYER_STATE_DRIVER: {
            if(getPlayerLastVehicle(playerid) != -1) {
                TogglePlayerSpeedometer(playerid, false);

                Iter_Remove(playersInVehicles, playerid);

                if(vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio]) {
                    -- radioListeners[vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio]-1];
                    StopAudioStreamForPlayer(playerid);
                }

                if(playerVars[playerid][b_HELMET_ON]) {
                    RemovePlayerAttachedObject(playerid, INDEX_HELMET); 
                    playerVars[playerid][b_HELMET_ON] = false; 

                    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s unputted the helmet from head.", GetName(playerid));
                }

                if(vehicleVars[getPlayerLastVehicle(playerid)][var_carPersonal] != -1) 
                    OnPlayerExitPersonalVehicle(playerid, getPlayerLastVehicle(playerid), false);
            }

            if(playerVars[playerid][var_spectateMe] != -1) 
                PlayerSpectatePlayer(playerVars[playerid][var_spectateMe], playerid);
        }
        case PLAYER_STATE_PASSENGER: {
            if(getPlayerLastVehicle(playerid) != -1) {
                TogglePlayerSpeedometer(playerid, false);

                Iter_Remove(playersInVehicles, playerid);

                if(vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio]) {
                    -- radioListeners[vehicleVars[getPlayerLastVehicle(playerid)][var_carRadio]-1];
                    StopAudioStreamForPlayer(playerid);
                }

                if(playerVars[playerid][b_HELMET_ON]) {
                    RemovePlayerAttachedObject(playerid, INDEX_HELMET); 
                    playerVars[playerid][b_HELMET_ON] = false; 

                    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s unputted the helmet from head.", GetName(playerid));
                }

                if(vehicleVars[getPlayerLastVehicle(playerid)][var_carPersonal] != -1) 
                    OnPlayerExitPersonalVehicle(playerid, getPlayerLastVehicle(playerid), true);
            }

            if(playerVars[playerid][var_spectateMe] != -1) 
                PlayerSpectatePlayer(playerVars[playerid][var_spectateMe], playerid);
        }
    }
    return 1;
}

public OnPlayerEnterCheckpoint(playerid) {
    switch(playerVars[playerid][var_checkpoint]) {
        case 1: { 
            SCM(playerid, -1, "You reached your destination.");

            if(playerVars[playerid][var_findon] != -1) {
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][0]); 
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][1]);

                playerVars[playerid][var_findon] = -1; 

                stop playerVars[playerid][var_find_timer]; 
            }
        }
        case 3: {
            SCMf(playerid, COLOR_GREEN, "(Job): {ffffff}You received $%s money for your work.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pFarmerSkill])));
            
            DestroyDynamicObject(playerVars[playerid][var_jobobject]); 

            playerVars[playerid][var_jobobject] = -1; 
            playerVars[playerid][var_jobseconds] = 60;

            playerVars[playerid][var_jobtimer] = repeat farmerTimer(playerid);
        }
        case 4: {
            if(IsPlayerInAnyVehicle(playerid))
                return 1;

            GameTextForPlayer(playerid, "~W~EXTINGUISHING THE FIRE...", 5000, 3);
            TogglePlayerControllableEx(playerid, false);
            
            ApplyAnimationEx(playerid, "ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1); 
            SetPlayerArmedWeapon(playerid, 42),

            defer jobTimer(playerid, 4); 
            playerVars[playerid][b_ACTIVE_TIMER] = true;
        }
        case 6: {
            if(IsPlayerInAnyVehicle(playerid))
                return 1;

            GameTextForPlayer(playerid, "~W~SKINNING THE DEER...", 5000, 3);
            TogglePlayerControllableEx(playerid, false);
            ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 1, 0, 0, 0, 0);

            defer jobTimer(playerid, 6); 
            playerVars[playerid][b_ACTIVE_TIMER] = true;
        }
        case 7: {
            if(!IsPlayerInVehicle(playerid, playerVars[playerid][var_jobvehicle]))
                return 1;

            defer jobTimer(playerid, 7); 
            playerVars[playerid][b_ACTIVE_TIMER] = true; 
            TogglePlayerControllableEx(playerid, false); 

            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "~W~Loading stuff..."); 

            playerVars[playerid][var_courierstuff] = 6; 
            playerVars[playerid][var_jobtime] = gettime() - 5; 
        }
        case 8: {
            if(!IsPlayerAttachedObjectSlotUsed(playerid, INDEX_JOB))
                return sendError(playerid, "Nu ai un colet in mana. Du-te langa vehiculul de curierat si apasa tasta 'Y'.");

            new randcp;

            RemovePlayerAttachedObject(playerid, INDEX_JOB);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ApplyAnimationEx(playerid, "CARRY", "PUTDWN", 4.0, 0, 0, 0, 0, 0);

            if(playerVars[playerid][var_courierstuff] <= 1) {
                SCMf(playerid, COLOR_GREEN, "(Job): {ffffff}You received $%s for your work. Time elapsed: %s.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pCourierSkill], 2500)), CalculateTime(gettime() - playerVars[playerid][var_jobtime]));

                randcp = random(3); 
     
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "~W~Go and reload stuff in your truck.");

                playerVars[playerid][var_checkpoint] = 7;
                playerVars[playerid][var_courierhouse] = -1;

                SetPlayerCheckpoint(playerid, courierLoadingLocations[randcp][0], courierLoadingLocations[randcp][1], courierLoadingLocations[randcp][2], 3.5); 
                return 1;
            }

            randcp = random(serverStuff[houses]); 

            playerVars[playerid][var_courierhouse] = randcp;
            playerVars[playerid][var_checkpoint] = 8;

            SetPlayerCheckpoint(playerid, HouseInfo[randcp][hX], HouseInfo[randcp][hY], HouseInfo[randcp][hZ], 3.5);

            --playerVars[playerid][var_courierstuff];

            gString[0] = EOS;
            format(gString, sizeof gString, "Go and transport all stuff loaded.~N~Stuff: %d/6", playerVars[playerid][var_courierstuff]); 
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], gString);
            return 1;
        }
        case 9: {
            Dialog_Show(playerid, COLLECTARMSDEALER, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Arms Dealer", "Option\tValue\nMaterials\t%d\nMoney\t$%s", "Select", "", playerVars[playerid][var_arms_dealer_materials], formatNumber(playerVars[playerid][var_arms_dealer_money]));
        }
        case 10: {
            if(GetPlayerVehicleID(playerid) != playerVars[playerid][var_jobvehicle])
                return 1;

            if(!IsTrailerAttachedToVehicle(playerVars[playerid][var_jobvehicle]))
                return sendError(playerid, "Trebuie sa ai remorca cu marfa atasata de vehicul.");

            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}You received $%s money for your work. Time elapsed: %s.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pTruckerSkill], playerVars[playerid][var_trucker_cash_bonus])), CalculateTime(gettime() - playerVars[playerid][var_jobtime]));
            SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go at the marked red dot to load another trailer.");

            DestroyVehicle(playerVars[playerid][var_trucker_trailer]); 

            playerVars[playerid][var_checkpoint] = 11;
            SetPlayerCheckpoint(playerid, jobInfo[9][j_wX], jobInfo[9][j_wY], jobInfo[9][j_wZ], 4.0);
            return 1;
        }
        case 11: {
            if(GetPlayerVehicleID(playerid) != playerVars[playerid][var_jobvehicle])
                return 1;

            TogglePlayerControllableEx(playerid, false); 
            showPlayerTruckerLocations(playerid);
        }
    }
    DisablePlayerCheckpointEx(playerid);
    return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid) {
    switch(playerVars[playerid][var_checkpoint]) {
        case 5: {
            GameTextForPlayer(playerid, "~W~~N~~N~~N~~N~~N~PLEASE WAIT...", 5000, 3); 

            TogglePlayerControllableEx(playerid, false); 
            defer jobTimer(playerid, 5); 
            playerVars[playerid][b_ACTIVE_TIMER] = true;
        }
    }
    return 1;
}

public OnPlayerRequestSpawn(playerid) {
    if(IsPlayerLogged(playerid))
        return SpawnPlayer(playerid);

    return 0;
}

public OnEnterExitModShop(playerid, enterexit, interiorid) {
    if(enterexit) {
        new const nearbybusiness = getNearbyBusiness(playerid, 15.0, 14);

        if(nearbybusiness == -1 || GetMoney(playerid) < bizzInfo[nearbybusiness][bFee] && GetMilliards(playerid) < 1)
            return 1;

        if(bizzInfo[nearbybusiness][bFee]) {
            substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, bizzInfo[nearbybusiness][bFee], false);
            va_GameTextForPlayer(playerid, "~r~-$%d", 2500, 1, bizzInfo[nearbybusiness][bFee]);

            bizzInfo[nearbybusiness][bBalance] += bizzInfo[nearbybusiness][bFee];

            va_mysql_tquery("UPDATE `server_users`, `server_business` SET `server_business`.`Balance` = %d, `server_users`.`Money` = %d, `server_users`.`MoneyStore` = %d WHERE `server_business`.`ID` = %d AND `server_users`.`ID` = %d", bizzInfo[nearbybusiness][bBalance], GetMoney(playerid), GetMilliards(playerid), bizzInfo[nearbybusiness][bID], playerInfo[playerid][pSQLID]);
        }
    } 
    return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
    if(playerVars[playerid][var_spectateMe] != -1) {
        new const userID = playerVars[playerid][var_spectateMe];
        
        SetPlayerInterior(userID, newinteriorid);
        SetPlayerVirtualWorld(userID, GetPlayerVirtualWorld(playerid));
        
        if(IsPlayerInAnyVehicle(playerid)) 
            PlayerSpectateVehicle(userID, GetPlayerVehicleID(playerid));
        
        else PlayerSpectatePlayer(userID, playerid);    
    }
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    new 
        w = GetPlayerWeapon(playerid), 
        vehicleid = GetPlayerVehicleID(playerid), 
        e_vehicleModelTypes:vehicletype = getVehicleModelType(GetVehicleModel(vehicleid)),
        playerState = GetPlayerState(playerid); 

    if(serverVars[6][svar_Value] == 1 && !playerVars[playerid][var_delay] && (oldkeys & KEY_FIRE && newkeys & KEY_CROUCH) && (w == 24 || w == 25 || w == 27 || w == 34)) { 
        playerVars[playerid][var_delay] = true; 
        TogglePlayerControllableEx(playerid, false); 
        defer freezeTimer[2000](playerid);

        SCM(playerid, COLOR_GREY, "Nu ai voie sa faci C-BUG! Ai primit freeze timp de 2 secunde.");
    }

    if(PRESSED(newkeys)) {
        switch(newkeys) {
            case KEY_SECONDARY_ATTACK: {
                if(playerVars[playerid][b_FLY_MODE]) {
                    ToggleFlyMode(playerid); 

                    SetPlayerHealth(playerid, 100.0); 
                    SetPlayerArmour(playerid, 0.0);
                    return 1;
                }

                if(IsPlayerInRangeOfPoint(playerid, 1.0, 301.8002,-76.7811,1001.5156)) 
                    return SetPlayerPos(playerid, 301.7888,-75.4750,1001.5156);
                
                if(IsPlayerInRangeOfPoint(playerid, 1.0, 301.7888,-75.4750,1001.5156)) 
                    return SetPlayerPos(playerid, 301.8002,-76.7811,1001.5156);

                if(playerVars[playerid][var_inhouse] != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, HouseInfo[playerVars[playerid][var_inhouse]][hExitX], HouseInfo[playerVars[playerid][var_inhouse]][hExitY], HouseInfo[playerVars[playerid][var_inhouse]][hExitZ])) {
                    if(playerVars[playerid][var_house_delay] > gettime())
                        return sendError(playerid, "Trebuie sa astepti %d secunde pana cand sa iesi.", playerVars[playerid][var_house_delay] - gettime());

                    return playerLeaveHouse(playerid, playerVars[playerid][var_inhouse]);
                }

                if(playerVars[playerid][var_inbizz] != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, bizzInfo[playerVars[playerid][var_inbizz]][bExitX], bizzInfo[playerVars[playerid][var_inbizz]][bExitY], bizzInfo[playerVars[playerid][var_inbizz]][bExitZ])) {
                    if(playerVars[playerid][var_bizz_delay] > gettime())
                        return sendError(playerid, "Trebuie sa astepti %d secunde pana cand sa iesi.", playerVars[playerid][var_bizz_delay] - gettime());

                    return playerLeaveBusiness(playerid, playerVars[playerid][var_inbizz]);
                }

                new 
                    nearbyPickup[1] = -1, 
                    Float:X, Float:Y, Float:Z; 

                GetPlayerPos(playerid, X, Y, Z); 
                Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, 2.0);

                if(nearbyPickup[0] == -1 || (pickupInfo[nearbyPickup[0]][pk_House] == -1 && pickupInfo[nearbyPickup[0]][pk_Bizz] == -1))
                    return 1;

                if(!IsPlayerInAnyVehicle(playerid) && pickupInfo[nearbyPickup[0]][pk_House] != -1) {
                    if(HouseInfo[pickupInfo[nearbyPickup[0]][pk_House]][hLocked] && (playerInfo[playerid][pRent] != pickupInfo[nearbyPickup[0]][pk_House] && playerInfo[playerid][pHouse] != pickupInfo[nearbyPickup[0]][pk_House]))
                        return GameTextForPlayer(playerid, "~R~locked", 2500, 1);

                    return playerEnterHouse(playerid, pickupInfo[nearbyPickup[0]][pk_House]);
                }

                new const bizzid = pickupInfo[nearbyPickup[0]][pk_Bizz];

                if(bizzid != -1 && bizzInfo[bizzid][bExitX] != 0 && !IsPlayerInAnyVehicle(playerid)) {
                    if(GetMoney(playerid) < bizzInfo[bizzid][bFee] && GetMilliards(playerid) < 1 && bizzInfo[bizzid][bFee] != 0 && playerInfo[playerid][pBusiness] != bizzid)
                        return sendError(playerid, "Nu ai destui bani pentru a intra in acest business.");

                    if(bizzInfo[bizzid][bLocked] && playerInfo[playerid][pBusiness] != bizzid)
                        return GameTextForPlayer(playerid, "~R~locked", 2500, 1);

                    if(bizzInfo[bizzid][bType] == 4 && playerVars[playerid][var_fishkg] > 0) {
                        SCMf(playerid, COLOR_GREEN, "(Job): {ffffff}You selled your fish and you received $%s money.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pFishermanSkill], playerVars[playerid][var_fishkg] * 100))); 
                        playerVars[playerid][var_fishkg] = 0;
                    }
                    return playerEnterBusiness(playerid, bizzid);
                }
            }
            case KEY_YES: {
                if(IsPlayerInRangeOfPoint(playerid, 2.5, 295.5730,-80.4439,1001.5156) && playerVars[playerid][var_inbizz] != -1 && bizzInfo[playerVars[playerid][var_inbizz]][bType] == 3 && !playerVars[playerid][b_GUNSHOP_SHOW]) {
                    if(playerInfo[playerid][pWeaponLicense] <= 0)
                        return sendError(playerid, "Nu ai licenta pentru arme sau aceasta a fost suspendata.");

                    if(playerVars[playerid][var_gunshopopened_delay] > gettime())
                        return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a face asta.", playerVars[playerid][var_gunshopopened_delay] - gettime());

                    playerTextdraws[playerid][GunShopTD][0] = CreatePlayerTextDraw(playerid, 205.299774, 327.688659, "box");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][0], 0.000000, 12.000000);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][0], 442.299774, 0.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][0], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][0], -1);
                    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][GunShopTD][0], 1);
                    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][GunShopTD][0], 225);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][0], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][0], 0);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][0], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][0], 1);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][0], 1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][0], 0);

                    playerTextdraws[playerid][GunShopTD][1] = CreatePlayerTextDraw(playerid, 286.799774, 313.822357, "Gun Shop");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][1], 0.520000, 1.848885);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][1], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][1], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][1], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][1], 1);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][1], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][1], 0);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][1], 1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][1], 0);

                    playerTextdraws[playerid][GunShopTD][2] = CreatePlayerTextDraw(playerid, 267.899688, 324.633636, "");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][2], 0.000000, 0.000000);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][2], 123.000000, 113.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][2], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][2], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][2], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][2], 0);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][2], 0);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][2], 5);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][2], 0);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][2], 0);
                    PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][GunShopTD][2], 348);
                    PlayerTextDrawSetPreviewRot(playerid, playerTextdraws[playerid][GunShopTD][2], 0.000000, -30.000000, 0.000000, 2.299999);

                    playerTextdraws[playerid][GunShopTD][3] = CreatePlayerTextDraw(playerid, 245.699920, 361.344787, "LD_BEAT:left");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][3], 0.000000, 0.000000);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][3], 28.000000, 29.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][3], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][3], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][3], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][3], 0);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][3], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][3], 4);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][3], 0);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][3], 0);
                    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][GunShopTD][3], true);

                    playerTextdraws[playerid][GunShopTD][4] = CreatePlayerTextDraw(playerid, 370.007507, 361.744812, "LD_BEAT:right");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][4], 0.000000, 0.000000);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][4], 28.000000, 29.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][4], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][4], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][4], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][4], 0);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][4], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][4], 4);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][4], 0);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][4], 0);
                    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][GunShopTD][4], true);

                    playerTextdraws[playerid][GunShopTD][5] = CreatePlayerTextDraw(playerid, 434.599822, 314.911193, "LD_BEAT:cross");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][5], 0.000000, 0.000000);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][5], 19.000000, 22.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][5], 1);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][5], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][5], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][5], 0);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][5], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][5], 4);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][5], 0);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][5], 0);
                    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][GunShopTD][5], true);

                    playerTextdraws[playerid][GunShopTD][6] = CreatePlayerTextDraw(playerid, 318.899749, 399.355255, "WEAPON: ~p~DEAGLE~n~~w~~h~PRICE: ~g~$5.000");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][6], 0.168499, 1.027555);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][6], 2);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][6], -1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][6], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][6], 1);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][6], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][6], 2);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][6], 1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][6], 0);

                    playerTextdraws[playerid][GunShopTD][7] = CreatePlayerTextDraw(playerid, 320.999786, 425.200256, "buy");
                    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][GunShopTD][7], 0.208499, 1.008888);
                    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][GunShopTD][7], 10.000000, 17.000000);
                    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][GunShopTD][7], 2);
                    PlayerTextDrawColor(playerid, playerTextdraws[playerid][GunShopTD][7], -1);
                    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][GunShopTD][7], 1);
                    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][GunShopTD][7], 8388863);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][7], 0);
                    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][GunShopTD][7], 1);
                    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][GunShopTD][7], 255);
                    PlayerTextDrawFont(playerid, playerTextdraws[playerid][GunShopTD][7], 2);
                    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][GunShopTD][7], 1);
                    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][GunShopTD][7], 0);
                    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][GunShopTD][7], true);

                    playerVars[playerid][b_GUNSHOP_SHOW] = true; 
                    playerVars[playerid][var_precedentweapon] = 0;

                    playerVars[playerid][var_objectweapon] = CreateDynamicObject(348, 295.45, -81.47, 1001.60, 78.74, -27.04, 7.98, _, _, playerid);

                    SetPlayerCameraPos(playerid, 295.573760, -80.385215, 1002.470336); 
                    SetPlayerCameraLookAt(playerid, 295.627593, -84.481964, 999.604370); 
                    SetPlayerVirtualWorld(playerid, 1 + bizzInfo[playerVars[playerid][var_inbizz]][bID] + playerid);
                    SetPlayerPos(playerid, 295.5258,-79.0073,1001.5156);

                    SelectTextDraw(playerid, -1);

                    for(new i = 0; i < 8; ++i) PlayerTextDrawShow(playerid, playerTextdraws[playerid][GunShopTD][i]);
                }

                if(playerVars[playerid][var_working] && playerInfo[playerid][pJob] == 7 && !IsPlayerAttachedObjectSlotUsed(playerid, INDEX_JOB) && !IsPlayerInAnyVehicle(playerid) && playerVars[playerid][var_courierhouse] != -1 && IsPlayerInRangeOfPoint(playerid, 75.0, HouseInfo[playerVars[playerid][var_courierhouse]][hX], HouseInfo[playerVars[playerid][var_courierhouse]][hY], HouseInfo[playerVars[playerid][var_courierhouse]][hZ])) {
                    new Float: X, Float: Y, Float: Z; 
                    GetVehiclePos(playerVars[playerid][var_jobvehicle], X, Y, Z);

                    if(IsPlayerInRangeOfPoint(playerid, 3.5, X, Y, Z)) {
                        SetPlayerAttachedObject(playerid, INDEX_JOB, 1221, 6, -0.004000, 0.169000, -0.216000, -112.000030, -15.200000, -11.599995, 0.362000, 0.341000, 0.386000); 
                        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
                    }
                }
            }
            case KEY_ACTION, KEY_ANALOG_DOWN, KEY_ANALOG_UP, KEY_LOOK_BEHIND: {
                if(playerState == PLAYER_STATE_DRIVER && vehicletype != VEHICLE_MODEL_TYPE_BIKE) {
                    if(PRESSED(KEY_LOOK_BEHIND)) {
                        if(vehicleVars[vehicleid][var_carFuel] <= 1) 
                            return sendError(playerid, "Acest vehicul nu are combustibil suficient pentru a-l putea pornii.");

                        if(playerVars[playerid][var_engine_delay] > gettime())
                            return sendError(playerid, "Mai ai de asteptat %d secunde pentru a face asta.", playerVars[playerid][var_engine_delay] - gettime());
                    }

                    new const e_vVars:var = PRESSED(KEY_ACTION) ? var_carLights : PRESSED(KEY_ANALOG_DOWN) ? var_carBoot : PRESSED(KEY_ANALOG_UP) ? var_carBoonet : var_carEngine;

                    vehicleVars[vehicleid][var] = !vehicleVars[vehicleid][var];

                    SetVehicleParamsEx(vehicleid, vehicleVars[vehicleid][var_carEngine], vehicleVars[vehicleid][var_carLights], 0, vehicleVars[vehicleid][var_carLocked], vehicleVars[vehicleid][var_carBoonet], vehicleVars[vehicleid][var_carBoot], 0);

                    if(playerVars[playerid][var_jobvehicle] == vehicleid || getPersonalVehicleOwner(vehicleid) == playerid) 
                        SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);

                    if(PRESSED(KEY_LOOK_BEHIND)) {
                        sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "* %s %s the engine of his vehicle %s.", GetName(playerid), !vehicleVars[vehicleid][var_carEngine] ? "stops" : "starts", GetVehicleName(vehicleid)); 
                        playerVars[playerid][var_engine_delay] = gettime() + 5;
                    }
                }
            }
            case KEY_CTRL_BACK: {
                if(playerState == PLAYER_STATE_DRIVER) {
                    if(playerVars[playerid][var_radio_delay] > gettime())
                        return sendError(playerid, "Trebuie sa astepti inca %d secunde pana sa folosesti iar radio-ul.", playerVars[playerid][var_radio_delay] - gettime());

                    Dialog_Show(playerid, RADIO, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Vehicle Radio", "Radio Name\tListeners\n{990000}Stop Radio\nPro FM\t%d\nRadio Taraf\t%d\nRadio Bandit\t%d\nFM Radio Manele\t%d\nRadio Popular\t%d\nRadio Coxet\t%d\nRadio Vocea Strazii\t%d\nRadio HIT\t%d\nKiss FM\t%d", "Select", "Exit", radioListeners[0], radioListeners[1], radioListeners[2], radioListeners[3], radioListeners[4], radioListeners[5], radioListeners[6], radioListeners[7], radioListeners[8]);
                }
            }
            case KEY_FIRE: {
                if(playerInfo[playerid][pJob] == 10 && playerVars[playerid][var_working] && IsValidVehicle(playerVars[playerid][var_trucker_trailer]) && !IsTrailerAttachedToVehicle(playerVars[playerid][var_jobvehicle]) && GetPlayerVehicleID(playerid) == playerVars[playerid][var_jobvehicle]) {
                    new Float: X, Float: Y, Float: Z;

                    GetVehiclePos(playerVars[playerid][var_trucker_trailer], X, Y, Z);

                    if(IsPlayerInRangeOfPoint(playerid, 15.0, X, Y, Z))
                        AttachTrailerToVehicle(playerVars[playerid][var_trucker_trailer], playerVars[playerid][var_jobvehicle]);
                }
                else if(playerVars[playerid][b_SPEED_BOOST] && playerState == PLAYER_STATE_DRIVER) {
                    new 
                        Float: v_x, Float: v_y, Float: v_z;

                    GetVehicleVelocity(vehicleid, v_x, v_y, v_z); 
                    SetVehicleVelocity(vehicleid, v_x * 1.5, v_y * 1.5, v_z * 1.5);
                }
            }
            case KEY_CROUCH: {
                new bid = getNearbyBusiness(playerid, 5.0, 11);

                if(bid != -1 && playerState == PLAYER_STATE_DRIVER && vehicletype != VEHICLE_MODEL_TYPE_BIKE && vehicletype != VEHICLE_MODEL_TYPE_PLANE && playerVars[playerid][var_pns_delay] < gettime()) {
                    new Float:carhp;
                    GetVehicleHealth(vehicleid, carhp);

                    if(carhp > 950.0) 
                        return 1;

                    bid -= 16;

                    SetVehiclePos(vehicleid, pnsEnterLocations[bid][0], pnsEnterLocations[bid][1], pnsEnterLocations[bid][2]);
                    SetVehicleZAngle(vehicleid, pnsEnterLocations[bid][3]);
                    
                    defer pnsTimer(playerid, bid + 16, pnsEnterLocations[bid][4], pnsEnterLocations[bid][5], pnsEnterLocations[bid][6], pnsEnterLocations[bid][7]);
                }
            }
            case KEY_SPRINT: {
                if(playerVars[playerid][var_SpectatePlayer] != -1 && Iter_Count(serverPlayers) > 2) {
                    new 
                        randomplayer = Iter_Random(serverPlayers), x;

                    while(randomplayer == playerid || randomplayer == playerVars[playerid][var_SpectatePlayer] || (playerInfo[randomplayer][pAdmin] > playerInfo[playerid][pAdmin]) || playerVars[randomplayer][var_spectateMe] != -1) {
                        randomplayer = Iter_Random(serverPlayers);

                        if(++x > 20) 
                            return SCM(playerid, COLOR_PINK, "No players found.");
                    }

                    playerTextDrawDestroy(playerid, playerTextdraws[playerid][SpecTD]); 

                    playerVars[playerVars[playerid][var_SpectatePlayer]][var_spectateMe] = playerVars[playerid][var_SpectatePlayer] = playerVars[playerid][var_spectateseconds] = -1;
                    
                    stop playerVars[playerid][var_spectatetimer]; 

                    spectatePlayer(playerid, randomplayer);
                }
            }
            case KEY_NO: {
                if(playerVars[playerid][var_car_lock_delay] < GetTickCount()) {
                    lockPersonalVehicle(playerid);

                    playerVars[playerid][var_car_lock_delay] = GetTickCount() + 500;
                }
            }
        }
    }
    return 1; 
}

public OnRconLoginAttempt(ip[], password[], success) {
    if(!success) 
        BlockIpAddress(ip, 60000 * 3);
    
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid) {
    Iter_Add(playersStreamed[forplayerid], playerid);
    return 1;
}

public OnPlayerStreamOut(playerid, forplayerid) {
    Iter_Remove(playersStreamed[forplayerid], playerid);
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {
    if(IsPlayerLogged(playerid))
        return SpawnPlayer(playerid);

    return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid) {
    if(playerVars[forplayerid][var_jobvehicle] == vehicleid || getPersonalVehicleOwner(vehicleid) == forplayerid) 
        SetVehicleParamsForPlayer(vehicleid, forplayerid, 0, 0);
    
    Iter_Add(vehiclesStreamed[forplayerid], vehicleid);
    return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid) {
    Iter_Remove(vehiclesStreamed[forplayerid], vehicleid);
    return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
    if(playerInfo[playerid][pAdmin]) {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
            SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);

        else 
            SetPlayerPos(playerid, fX, fY, fZ);
    }
    return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source) { 
    if(source == CLICK_SOURCE_SCOREBOARD && IsPlayerLogged(playerid)) {
        if(IsPlayerLogged(clickedplayerid)) {
            if(playerInfo[clickedplayerid][pAFKSeconds] > 9) 
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | FPS: %d | Ping: %d | Status: AFK (for %d seconds)", GetName(clickedplayerid), clickedplayerid, playerInfo[clickedplayerid][pLevel], playerVars[clickedplayerid][var_FPS], GetPlayerPing(clickedplayerid), playerInfo[clickedplayerid][pAFKSeconds]);

            else 
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | FPS: %d | Ping: %d | Status: online", GetName(clickedplayerid), clickedplayerid, playerInfo[clickedplayerid][pLevel], playerVars[clickedplayerid][var_FPS], GetPlayerPing(clickedplayerid));
        }
    }
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    if(playerVars[playerid][b_CLOTHES_SHOW]) {
        if(playertextid == playerTextdraws[playerid][ClothesTD][6]) {
            playerVars[playerid][b_CLOTHES_SHOW] = false; 

            if(Dialog_IsOpened(playerid))
                Dialog_Close(playerid);
            
            CancelSelectTextDraw(playerid);

            SetPlayerVirtualWorld(playerid, bizzInfo[playerVars[playerid][var_inbizz]][bID]); 
            SetCameraBehindPlayer(playerid); 
            SetPlayerSkin(playerid, playerInfo[playerid][pSkin]);

            for(new i = 0; i < 8; ++i) playerTextDrawDestroy(playerid, playerTextdraws[playerid][ClothesTD][i]);
        }
        else if(playertextid == playerTextdraws[playerid][ClothesTD][2]) {
            new Float:angle; 
            GetPlayerFacingAngle(playerid, angle); 
            SetPlayerFacingAngle(playerid, angle+12);

            PlayerTextDrawSetPreviewRot(playerid, playerTextdraws[playerid][ClothesTD][2], 0.000000, 0.000000, angle-96, 1.000000);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][2]);
        }
        else if(playertextid == playerTextdraws[playerid][ClothesTD][3] || playertextid == playerTextdraws[playerid][ClothesTD][4]) {
            if(playertextid == playerTextdraws[playerid][ClothesTD][3]) 
                playerVars[playerid][var_precedentskin] = (playerVars[playerid][var_precedentskin] + 1) % sizeof clothesSkins;
            
            else 
                playerVars[playerid][var_precedentskin] = (playerVars[playerid][var_precedentskin] - 1) % sizeof clothesSkins;

            PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][ClothesTD][2], clothesSkins[playerVars[playerid][var_precedentskin]]); 
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][2]); 

            SetPlayerSkin(playerid, clothesSkins[playerVars[playerid][var_precedentskin]]);

            gString[0] = EOS;

            if(!Iter_Contains(playerSkins[playerid], playerVars[playerid][var_precedentskin])) {
                format(gString, sizeof gString, "SKIN ID: ~P~%d~N~~W~~H~PRICE: ~G~$5.000", clothesSkins[playerVars[playerid][var_precedentskin]]);
                PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 8388863);
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][5], "BUY");
            }
            else {
                format(gString, sizeof gString, "SKIN ID: ~P~%d~N~~W~~H~OWNED", clothesSkins[playerVars[playerid][var_precedentskin]]);
                PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 932573439); 
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][5], "SET");
            }

            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][7], gString); 
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][5]);
        }
        else if(playertextid == playerTextdraws[playerid][ClothesTD][5]) {
            if(Iter_Contains(playerSkins[playerid], playerVars[playerid][var_precedentskin])) 
                return Dialog_Show(playerid, SKINS, DIALOG_STYLE_LIST, "SERVER: Skins", "Set Skin\n{990000}Remove Skin", "Select", "Exit");

            if(Iter_Count(playerSkins[playerid]) >= MAX_SKINS)
                return sendError(playerid, "Nu iti poti cumpara mai mult de 5 skin-uri.");

            if(GetMoney(playerid) < 5000 && GetMilliards(playerid) < 1)
                return sendError(playerid, "Nu ai destui bani pentru a cumpara acest skin.");

            Iter_Add(playerSkins[playerid], playerVars[playerid][var_precedentskin]);

            substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, 5000, false);

            va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pSQLID]);
            saveSkins(playerid);

            SCMf(playerid, COLOR_GREEN, "(Clothes Info): {ffffff}You bought the skin %d succesfully for $5.000 money. Owned skins: %d/5", GetPlayerSkin(playerid), Iter_Count(playerSkins[playerid]));

            updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYCLOTHES);
            
            gString[0] = EOS;
            format(gString, sizeof gString, "SKIN ID: ~P~%d~N~~W~~H~OWNED", GetPlayerSkin(playerid));
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][7], gString);

            PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 932573439); 
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][5], "SET");
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][5]);
        }
    }
    else if(playerVars[playerid][b_GUNSHOP_SHOW]) {
        if(playertextid == playerTextdraws[playerid][GunShopTD][5]) {
            playerVars[playerid][b_GUNSHOP_SHOW] = false; 

            SetCameraBehindPlayer(playerid);

            CancelSelectTextDraw(playerid); 

            SetPlayerVirtualWorld(playerid, bizzInfo[playerVars[playerid][var_inbizz]][bID]);

            DestroyDynamicObject(playerVars[playerid][var_objectweapon]); 
            playerVars[playerid][var_objectweapon] = -1; 

            playerVars[playerid][var_gunshopopened_delay] = gettime() + 10;

            for(new i = 0; i < 8; ++i) playerTextDrawDestroy(playerid, playerTextdraws[playerid][GunShopTD][i]);
        }
        else if(playertextid == playerTextdraws[playerid][GunShopTD][4] || playertextid == playerTextdraws[playerid][GunShopTD][3]) {
            if(playertextid == playerTextdraws[playerid][GunShopTD][4]) 
                playerVars[playerid][var_precedentweapon] = (playerVars[playerid][var_precedentweapon] + 1) % sizeof gunShopWeapons;
            
            else 
                playerVars[playerid][var_precedentweapon] = (playerVars[playerid][var_precedentweapon] - 1) % sizeof gunShopWeapons;

            Streamer_SetIntData(STREAMER_TYPE_OBJECT, playerVars[playerid][var_objectweapon], E_STREAMER_MODEL_ID, gunShopWeapons[playerVars[playerid][var_precedentweapon]][2]);

            PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][GunShopTD][2], gunShopWeapons[playerVars[playerid][var_precedentweapon]][2]);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][GunShopTD][2]);
            
            gString[0] = EOS;
            format(gString, sizeof gString, "WEAPON: ~p~%s~n~~w~~h~PRICE: ~g~$%s", gunShopWeapons[playerVars[playerid][var_precedentweapon]][3], formatNumber(gunShopWeapons[playerVars[playerid][var_precedentweapon]][1])); 
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][GunShopTD][6], gString);
        }
        else if(playertextid == playerTextdraws[playerid][GunShopTD][7]) {
            if(GetMoney(playerid) < gunShopWeapons[playerVars[playerid][var_precedentweapon]][1] && GetMilliards(playerid) < 1)
                return sendError(playerid, "Nu ai destui bani pentru a cumpara aceasta arma.");

            if(playerVars[playerid][var_gunshop_delay] > gettime())
                return sendError(playerid, "Trebuie sa astepti %d secunde pana sa faci asta din nou.", playerVars[playerid][var_gunshop_delay] - gettime());

            substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, gunShopWeapons[playerVars[playerid][var_precedentweapon]][1]);

            GivePlayerWeapon(playerid, gunShopWeapons[playerVars[playerid][var_precedentweapon]][0], !playerVars[playerid][var_precedentweapon] ? 50 : 100);

            SCMf(playerid, COLOR_GREEN, "(Gun Shop): {ffffff}You bought weapon %s (id: %d, ammo: %d) for $%s money.", gunShopWeapons[playerVars[playerid][var_precedentweapon]][3], gunShopWeapons[playerVars[playerid][var_precedentweapon]][0], !playerVars[playerid][var_precedentweapon] ? 50 : 100, formatNumber(gunShopWeapons[playerVars[playerid][var_precedentweapon]][1]));

            playerVars[playerid][var_gunshop_delay] = gettime() + 5;

            updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYWEAPON);
        }
    }
    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == INVALID_TEXT_DRAW && playerVars[playerid][b_CLOTHES_SHOW] || playerVars[playerid][b_GUNSHOP_SHOW]) 
        return SelectTextDraw(playerid, -1);
    
    return 1;
}
