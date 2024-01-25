#if defined INITIALISE_GAMEMODE_delay

timer loadServer[60000]() {
    SendRconCommand("hostname "SERVER_HOSTNAME""); 
    SendRconCommand("password "SERVER_PASSWORD""); 
    SetGameModeText("INC v0.3.7, "SERVER_VERSION"");
    return 1;
}

#endif

timer farmerTimer[1000](const playerid) {
    if(!(isPlayerInRectangleArea(playerid, -594, -342, -1408.5, -1258.5) || isPlayerInRectangleArea(playerid, -342, -160, -1560.5, -1306.5)))
        return PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "~R~You must be in the work area.");

    if(playerVars[playerid][var_jobseconds] <= 1) {
        stop playerVars[playerid][var_jobtimer];

        playerVars[playerid][var_jobobject] = CreateDynamicObject(1454, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        AttachDynamicObjectToVehicle(playerVars[playerid][var_jobobject], playerVars[playerid][var_jobvehicle], -0.014999, -2.800016, 0.000000, 0.000000, 7.035000, -89.444953);

        if(!random(2)) 
            SetPlayerCheckpoint(playerid, -567.8726, -1477.4612, 9.9931, 3.5); 

        else 
            SetPlayerCheckpoint(playerid, -368.1149, -1437.5499, 25.6928, 3.5); 
        
        playerVars[playerid][var_checkpoint] = 3;
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "~G~Go to the red marker and leave the bale.");
    }
    else if(getVehicleSpeed(playerVars[playerid][var_jobvehicle]) >= 25) {
        --playerVars[playerid][var_jobseconds];

        gString[0] = EOS;
        format(gString, sizeof gString, "~G~Another %d seconds until the work is done.", playerVars[playerid][var_jobseconds]);
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], gString);
    }
    else 
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "~R~You must have more than 25 KM/H speed.");
    
    return 1;
}

timer fillVehicle[5000](const playerid, const vehicleid, const bizzid, const Float:fuel, const fuelprice) {
    if(!IsPlayerConnected(playerid))
        return 1;

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, fuelprice, false);

    vehicleVars[vehicleid][var_carFuel] = 100.99; 
    bizzInfo[bizzid][bBalance] += bizzInfo[bizzid][bFee];

    va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[bizzid][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[bizzid][bID], playerInfo[playerid][pSQLID]);
    
    SCMf(playerid, COLOR_GREEN, "(Gas Station): {ffffff}You filled up your vehicle with %.0f litres of fuel for $%s money.", fuel, formatNumber(fuelprice)); 

    playerVars[playerid][b_ACTIVE_TIMER] = false; 
    TogglePlayerControllableEx(playerid, true); 

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_FUELVEHICLE);
}

timer checkAccountPlayer[2500](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    return pickNextPlayerFromLoginQueue(false);
}

timer attachTruckerTrailer[1500](const playerid) 
    return AttachTrailerToVehicle(playerVars[playerid][var_trucker_trailer], playerVars[playerid][var_jobvehicle]);

timer findPlayer[1000](const playerid) {
    if(playerVars[playerid][var_findon] != -1) {
        if(IsPlayerLogged(playerVars[playerid][var_findon])) {
            new Float: X, Float: Y, Float: Z; 

            if(playerVars[playerVars[playerid][var_findon]][var_inhouse] != -1) {
                X = HouseInfo[playerVars[playerVars[playerid][var_findon]][var_inhouse]][hX]; 
                Y = HouseInfo[playerVars[playerVars[playerid][var_findon]][var_inhouse]][hY]; 
                Z = HouseInfo[playerVars[playerVars[playerid][var_findon]][var_inhouse]][hZ];
            }
            else if(playerVars[playerVars[playerid][var_findon]][var_inbizz] != -1) {
                X = bizzInfo[playerVars[playerVars[playerid][var_findon]][var_inbizz]][bX]; 
                Y = bizzInfo[playerVars[playerVars[playerid][var_findon]][var_inbizz]][bY]; 
                Z = bizzInfo[playerVars[playerVars[playerid][var_findon]][var_inbizz]][bZ];
            }
            else 
                GetPlayerPos(playerVars[playerid][var_findon], X, Y, Z);

            gString[0] = EOS;
            format(gString, sizeof gString, "%s~N~~W~~H~STATUS: ~G~%s~N~~W~~H~DISTANCE: ~G~%0.2fkm", GetName(playerVars[playerid][var_findon]), GetPlayerState(playerVars[playerid][var_findon]) == PLAYER_STATE_DRIVER ? "IN VEHICLE (DRIVER)" : GetPlayerState(playerVars[playerid][var_findon]) == PLAYER_STATE_PASSENGER ? "IN VEHICLE (PASSENGER)" : "ON FOOT", GetPlayerDistanceFromPoint(playerid, X, Y, Z)/1000); 
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][FindTD][0], gString);
            
            SetPlayerCheckpoint(playerid, X, Y, Z, 2.0);
        }
        else {
            playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][0]); 
            playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][1]); 

            playerVars[playerid][var_findon] = -1;

            DisablePlayerCheckpointEx(playerid); 

            SCM(playerid, COLOR_GREEN, "(Info): {FFFFFF}Your red marker has gone because that player has disconnected."); 
            
            stop playerVars[playerid][var_find_timer]; 
        }
        return 1;
    }
    stop playerVars[playerid][var_find_timer];
    return 1;
}

timer drugsDealerTimer[1000](const playerid) {
    gString[0] = EOS;

    if(playerVars[playerid][var_planted_seeds_time] > gettime())
        format(gString, sizeof gString, "{1C8A15}%s{FFFFFF}'s drugs\nHarvest in {1C8A15}%s{FFFFFF} minutes.", GetName(playerid), CalculateTime(playerVars[playerid][var_planted_seeds_time] - gettime()));

    else { 
        format(gString, sizeof gString, "{1C8A15}%s{FFFFFF}'s drugs\nCollect them by typing command {1C8A15}[/getdrugs]{FFFFFF}.", GetName(playerid)); 
        SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}Your drugs are ready. Go and collect them.");

        playerVars[playerid][var_planted_seeds_time] = 0;
        
        stop playerVars[playerid][var_drugs_dealer_timer];
    }
    return UpdateDynamic3DTextLabelText(playerLabels[playerid][l_drugs_dealer], -1, gString);
}

timer spectateTimer[1000](const playerid) {
    new targetid = playerVars[playerid][var_SpectatePlayer], Float: viata;

    if(playerVars[playerid][var_spectateseconds] < gettime()) {
        stop playerVars[playerid][var_spectatetimer]; 
        
        TogglePlayerSpectating(playerid, false); 
        
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][SpecTD]);
        
        playerVars[playerVars[playerid][var_SpectatePlayer]][var_spectateMe] = playerVars[playerid][var_SpectatePlayer] = playerVars[playerid][var_spectateseconds] = -1;
        
        return SCM(playerid, COLOR_GREY, "* You are no longer spectator because 5 minutes of inactivity have passed.");
    }

    if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(targetid)) 
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

    if(GetPlayerInterior(playerid) != GetPlayerInterior(targetid))
        SetPlayerInterior(playerid, GetPlayerInterior(targetid));

    gString[0] = EOS;

    if(!IsPlayerInAnyVehicle(targetid)) {
        GetPlayerHealth(targetid, viata);   
        format(gString, sizeof gString, "~R~%s ~W~~H~(~R~%d~W~~H~) - L: ~R~%d~N~~W~~H~Health: ~R~%.2f~N~~W~~H~Ping: ~R~%d~N~~W~~H~FPS: ~R~%d~N~~W~~H~Packet Loss: ~R~%.2f%%~N~~W~~H~AFK Seconds: ~R~%d", GetName(targetid), targetid, playerInfo[targetid][pLevel], viata, GetPlayerPing(targetid), playerVars[targetid][var_FPS], NetStats_PacketLossPercent(targetid), playerInfo[targetid][pAFKSeconds]);
    }
    else {
        GetVehicleHealth(GetPlayerVehicleID(targetid), viata); 
        format(gString, sizeof gString, "~R~%s ~W~~H~(~R~%d~W~~H~) - L: ~R~%d~N~~W~~H~Car Speed: ~R~%d~N~~W~~H~Car Health: ~R~%.2f~N~~W~~H~Ping: ~R~%d~N~~W~~H~FPS: ~R~%d~N~~W~~H~Packet Loss: ~R~%.2f%%~N~~W~~H~AFK Seconds: ~R~%d", GetName(targetid), targetid, playerInfo[targetid][pLevel], getVehicleSpeed(GetPlayerVehicleID(targetid)), viata, GetPlayerPing(targetid), playerVars[targetid][var_FPS], NetStats_PacketLossPercent(targetid), playerInfo[targetid][pAFKSeconds]);
    }

    return PlayerTextDrawSetString(playerid, playerTextdraws[playerid][SpecTD], gString);
}

timer serverRestartTimer[1000]() {
    --serverRestartTime;

    va_GameTextForAll("~w~SERVER RESTART IN ~g~%d~w~ SECONDS...", 3500, 4, serverRestartTime);

    if(serverRestartTime == 10) {
        foreach(new i : Player) Kick(i);
        
        SendRconCommand("password inusdnuandsuNUUSDBU218818ssuaysd99287287sao");
        SendRconCommand("hostname rpg.Lurk.ro - server is restarting...");
    }
    else if(serverRestartTime <= 0) {
        stop serverRestartTimerVar;
        SendRconCommand("gmx");
    }
    return 1;
}

timer drugsDealerSetCameraBehind[7500](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    clearChat(playerid, 25); 

    SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and plant your seeds."); 
    
    return SetCameraBehindPlayer(playerid);
}

timer hideDamageInformer[2000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    playerVars[playerid][var_damageinformer_timer] = Timer: 0;
    return PlayerTextDrawHide(playerid, playerTextdraws[playerid][DMG]);
}

timer fishTimer[10000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    playerVars[playerid][b_FISHING] = false; 

    RemovePlayerAttachedObject(playerid, INDEX_JOB); 

    TogglePlayerControllableEx(playerid, true);
    ClearAnimations(playerid);

    if(random(6) >= 2) {
        playerVars[playerid][var_fishkg] = 1 + random(7);

        SCMf(playerid, COLOR_GREEN, "(Fish): {FFFFFF}You catched a fish with %d kilograms weight. You can sell the fish in a 24/7 business type.", playerVars[playerid][var_fishkg]); 
        return sendNearbyMessage(playerid, COLOR_YELLOW, 15.0, "* %s catched a fish with %d kilograms weight.", GetName(playerid), playerVars[playerid][var_fishkg]);
    }
    return SCM(playerid, COLOR_GREEN, "(Fish): {FFFFFF}Unlucky, you don't catched any fish.");
}

timer pnsTimer[4000](const playerid, const bid, Float: X, Float: Y, Float: Z, Float: AngleZ) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(playerInfo[playerid][pBusiness] != bid) {
        substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, bizzInfo[bid][bFee], false); 
        va_GameTextForPlayer(playerid, "~r~-$%d", 5000, 1, bizzInfo[bid][bFee]);

        bizzInfo[bid][bBalance] += bizzInfo[bid][bFee]; 
        
        va_mysql_tquery("UPDATE `server_business`, `server_users` SET `server_business`.`Balance` = %d, `server_users`.`MoneyStore` = %d, `server_users`.`Money` = %d WHERE `server_business`.`ID` = %d AND `server_users`.`ID` = %d", bizzInfo[bid][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[bid][bID], playerInfo[playerid][pSQLID]);
    }
    
    SetVehiclePos(GetPlayerVehicleID(playerid), X,Y,Z); 
    SetVehicleZAngle(GetPlayerVehicleID(playerid), AngleZ);

    playerVars[playerid][var_pns_delay] = gettime() + 4; 

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_REPAIRPNS);
}

timer advertTimer[30000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    sendSplittedMessageToAll(COLOR_GREEN, COLOR_GREEN, "Advert by %s (phone: {ffffff}%d{1C8A15}): %s", GetName(playerid), playerInfo[playerid][pPhoneNumber], playerVars[playerid][var_placed_ad]); 
    playerVars[playerid][var_placed_ad][0] = EOS;
    playerVars[playerid][var_ad_timer] = Timer: 0;
    return 1;
}

timer freezeTimer[5000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(playerVars[playerid][var_delay]) 
        playerVars[playerid][var_delay] = false;

    return TogglePlayerControllableEx(playerid, true);
}

timer delayedSetPlayerPos[500](const playerid, Float: X, Float: Y, Float: Z) {
    return SetPlayerPos(playerid, X, Y, Z);
}

timer racTimer[10000]() {
    foreach(new car : Vehicle) 
        if(!getVehicleOccupantsCount(car)) SetVehicleToRespawn(car);  
    
    return racTimerActive = false;
}

timer delayedKick[350](const playerid) return Kick(playerid);

timer kickAll[1000]() {
    foreach(new i : Player) Kick(i);
}

timer loginTimer[30000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    defer delayedKick(playerid); 
    playerInfo[playerid][pLoginTimer] = Timer: 0;
    return SCM(playerid, COLOR_RED, "* Ai primit kick deoarece nu te-ai logat/inregistrat in 30 secunde.");
}

timer healthArmourHUDUpdate[1000](const playerid) {
    new Float:health_armour; 

    GetPlayerHealth(playerid, health_armour);
    
    gString[0] = EOS;
    format(gString, sizeof gString, "%.0f", health_armour);
    PlayerTextDrawSetString(playerid, playerTextdraws[playerid][HealthTD], gString);

    GetPlayerArmour(playerid, health_armour);

    if(health_armour >= 2) {
        if(playerTextdraws[playerid][ArmourTD] == PlayerText: -1) {
            playerTextdraws[playerid][ArmourTD] = CreatePlayerTextDraw(playerid, 577.500000, 42.611305, "");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ArmourTD], 0.238500, 1.276444);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ArmourTD], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][ArmourTD], -1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ArmourTD], 0);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ArmourTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ArmourTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][ArmourTD], 2);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ArmourTD], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ArmourTD], 0);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][ArmourTD]);
        }

        gString[0] = EOS;
        format(gString, sizeof gString, "%.0f", health_armour);  
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ArmourTD], gString);
    }
    else 
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][ArmourTD]);

    return 1;
}

timer jobTimerChecks[1000](const playerid) {
    if(playerInfo[playerid][pAFKSeconds] >= 300) {
        stopWork(playerid);
        SCM(playerid, COLOR_GREEN, "(Job): {ffffff}Your work was stopped because you stayed afk more than 5 minutes.");
    }
    else if(playerVars[playerid][var_jobexitvehicletime] != -1 && playerVars[playerid][var_jobexitvehicletime] < gettime()) {
        stopWork(playerid);
    }
    return 1;
} 

timer updatePassengerSpeedometer[1000](const playerid) {
    new 
        vehicleid = GetPlayerVehicleID(playerid),
        e_vehicleModelTypes:vehicletype = getVehicleModelType(GetVehicleModel(vehicleid));

    gString[0] = EOS;
    format(gString, sizeof gString, "%d", getVehicleSpeed(vehicleid, playerInfo[playerid][pHUDSpeedometer]));
    PlayerTextDrawSetString(playerid, playerTextdraws[playerid][SpeedTD], gString);

    gString[0] = EOS;
    format(gString, sizeof gString, "Radio: ~G~%s", !vehicleVars[vehicleid][var_carRadio] ? "NONE" : radioSelected[vehicleVars[vehicleid][var_carRadio]-1][1]);

    if(vehicletype != VEHICLE_MODEL_TYPE_BIKE && vehicletype != VEHICLE_MODEL_TYPE_PLANE && vehicletype != VEHICLE_MODEL_TYPE_BOAT)
        format(gString, sizeof gString, "%s~N~~W~~H~Fuel: ~G~%.0fL", gString, vehicleVars[vehicleid][var_carFuel]);

    if(vehicleVars[vehicleid][var_carPersonal] != -1) 
        format(gString, sizeof gString, "%s~N~~W~~H~Odometer: ~G~%.0fKM~N~~G~%s", gString, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Odometer], vehicleVars[vehicleid][var_carLocked] ? "Locked" : "Unlocked");  

    return PlayerTextDrawSetString(playerid, playerTextdraws[playerid][SpeedometerTD], gString);
}

timer updateDriverSpeedometer[1000](const playerid) {
    new 
        vehicleid = GetPlayerVehicleID(playerid), 
        e_vehicleModelTypes:vehicletype = getVehicleModelType(GetVehicleModel(vehicleid)),
        speed = getVehicleSpeed(vehicleid);

    gString[0] = EOS;
    format(gString, sizeof gString, "%d", getVehicleSpeed(vehicleid, playerInfo[playerid][pHUDSpeedometer]));
    PlayerTextDrawSetString(playerid, playerTextdraws[playerid][SpeedTD], gString);

    gString[0] = EOS;
    format(gString, sizeof gString, "Radio: ~G~%s", !vehicleVars[vehicleid][var_carRadio] ? "NONE" : radioSelected[vehicleVars[vehicleid][var_carRadio]-1][1]);

    if(vehicletype != VEHICLE_MODEL_TYPE_BIKE && vehicletype != VEHICLE_MODEL_TYPE_PLANE && vehicletype != VEHICLE_MODEL_TYPE_BOAT) {
        if(vehicleVars[vehicleid][var_carEngine] && playerVars[playerid][var_jobvehicle] != vehicleid) {
            vehicleVars[vehicleid][var_carFuel] -= (speed * 0.060) / 100;
            
            if(vehicleVars[vehicleid][var_carFuel] <= 1) {
                vehicleVars[vehicleid][var_carEngine] = false;
                
                GameTextForPlayer(playerid, "~W~NO FUEL!", 5000, 4); 

                SetVehicleParamsEx(vehicleid, false, -1, -1, -1, -1, -1, false);
            }

            if(vehicleVars[vehicleid][var_carPersonal] != -1) 
                personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Fuel] = vehicleVars[vehicleid][var_carFuel];
        }
        format(gString, sizeof gString, "%s~N~~W~~H~Fuel: ~G~%.0fL", gString, vehicleVars[vehicleid][var_carFuel]);
    }

    if(vehicleVars[vehicleid][var_carPersonal] != -1) {
        personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Odometer] += (speed * 0.050) / 100;

        format(gString, sizeof gString, "%s~N~~W~~H~Odometer: ~G~%.0fKM~N~~G~%s", gString, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Odometer], vehicleVars[vehicleid][var_carLocked] ? "Locked" : "Unlocked");
    }

    else if(isPlayerInDMVExamen(playerid)) 
        format(gString, sizeof gString, "%s~N~~W~~H~Checkpoints: ~G~%d/25", gString, getPlayerDMVNextCheckpoint(playerid) - 1);      

    else if(isPlayerInDealershipTestDrive(playerid)) 
        format(gString, sizeof gString, "%s~N~~W~~H~Time Left: ~G~%s", gString, CalculateTime(getDealershipTestDriveTime(playerid) - gettime()));

    return PlayerTextDrawSetString(playerid, playerTextdraws[playerid][SpeedometerTD], gString);
}

ptask playerSecondTimer[1000](playerid) {
    if(IsPlayerInRangeOfPoint(playerid, 1.0, playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ]))
        ++playerInfo[playerid][pAFKSeconds];
    
    else playerInfo[playerid][pAFKSeconds] = 0;

    if(playerInfo[playerid][pAFKSeconds] < 10) 
        ++playerInfo[playerid][pSeconds]; 

    if(playerInfo[playerid][pJailTime] > 0) {
        playerInfo[playerid][pJailTime]--;

        gString[0] = EOS;
        format(gString, sizeof(gString), "jailed for ~y~%s minutes", ConvertToMinutes(playerInfo[playerid][pJailTime]));
        PlayerTextDrawSetString(playerid, ptd_wanted, gString);

        if(playerInfo[playerid][pJailTime] == 0) {
            SetPlayerPos(playerid, 1553.8391,-1675.5680,16.1953);
            SetPlayerFacingAngle(playerid, 0.0);
            SCM(playerid, COLOR_WHITE, "Your time is up! You have been released from jail.");
            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);

            format(playerInfo[playerid][pCrime1], 48, "no crime");
            format(playerInfo[playerid][pCrime2], 48, "no crime");
            format(playerInfo[playerid][pCrime3], 48, "no crime");

            PlayerTextDrawHide(playerid, ptd_wanted);

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerJailTime` = '0', `playerCrime1` = '%e', `playerCrime2` = '%e', `playerCrime3` = '%e' where `ID` = '%d'", playerInfo[playerid][pCrime1], playerInfo[playerid][pCrime2], playerInfo[playerid][pCrime3], playerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "", "");
        }
    }
    if(haveServiceActive[playerid] != 0) activeServiceTimer[playerid] ++;
    if(FreeExpire[playerid] > 0)
    {
        FreeExpire[playerid]--;
        if(FreeExpire[playerid] == 0)
        {
            FreeOffer[FreePlayer[playerid]] = -1;
            FreePrice[FreePlayer[playerid]] = 0;
            FreePlayer[playerid] = -1;
            SendClientMessage(playerid, COLOR_WHITE, "Free offer has expired, you can now offer free to somebody else.");
        }
    }
    if(playerInfo[playerid][pWantedExpire] > 0 && playerInfo[playerid][pWantedLevel] > 0) {
        playerInfo[playerid][pWantedExpire]--;

        gString[0] = EOS;
        format(gString, sizeof(gString), "wanted expires in ~g~%s minutes", ConvertToMinutes(playerInfo[playerid][pWantedExpire]));
        PlayerTextDrawSetString(playerid, ptd_wanted, gString);

        if(playerInfo[playerid][pWantedExpire] == 0 && playerInfo[playerid][pWantedLevel] > 0) {
            playerInfo[playerid][pWantedLevel]--;
            SetPlayerWantedLevel(playerid, playerInfo[playerid][pWantedLevel]);

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerWantedLevel` = '%d' where `ID` = '%d'", playerInfo[playerid][pWantedLevel], playerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "", "");

            if(playerInfo[playerid][pWantedLevel] > 0) {
                SCMf(playerid, COLOR_YELLOW, "You lost one wanted point. New wanted level: %d", playerInfo[playerid][pWantedLevel]);

                playerInfo[playerid][pWantedExpire] = 300;
            }

            else if(playerInfo[playerid][pWantedLevel] == 0) {
                SCM(playerid, COLOR_YELLOW, "You escaped the police.");

                PlayerTextDrawHide(playerid, ptd_wanted);
            }
        }
    }
    new const drunkLevel = GetPlayerDrunkLevel(playerid);
    if(drunkLevel < 100) 
        SetPlayerDrunkLevel(playerid, 2000);

    else if(playerVars[playerid][var_drunklevel] != drunkLevel) {
        if(playerVars[playerid][var_drunklevel] - drunkLevel > 0) {
            playerVars[playerid][var_FPS] = playerVars[playerid][var_drunklevel] - drunkLevel;

            if(playerInfo[playerid][pHUDFps]) {
                gString[0] = EOS; 
                format(gString, sizeof gString, "~Y~%d", playerVars[playerid][var_FPS]); 
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][FpsTD], gString);
            }
        }
        playerVars[playerid][var_drunklevel] = drunkLevel;
    }
    
    if(serverVars[8][svar_Value] == 1 && playerVars[playerid][var_warningtimer] < gettime()) {
        if(playerInfo[playerid][pAFKSeconds] >= 1800 && !playerVars[playerid][b_IS_SLEEPING]) {
            AdmBot(playerid, "AFK for 30 minutes without /sleep");
            playerVars[playerid][var_warningtimer] = gettime() + 3;
        }
        else if(playerInfo[playerid][pAFKSeconds] >= 7200 && playerVars[playerid][b_IS_SLEEPING]) {
            AdmBot(playerid, "AFK for 2 hours with /sleep");
            playerVars[playerid][var_warningtimer] = gettime() + 3;
        }
    }

    new const surfingVehicleDriver = GetVehicleDriver(GetPlayerSurfingVehicleID(playerid));

    if(surfingVehicleDriver != INVALID_PLAYER_ID && playerInfo[surfingVehicleDriver][pTOGSurf])
        slapPlayer(playerid);

    GetPlayerPos(playerid, playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ]);
    return 1;
}

task paydayCheckTimer[60000]() {
    new 
        hour, minute;

    gettime(hour, minute);

    if(serverPayday != hour && minute <= 3) {
        foreach(new i : serverPlayers)
            givePayday(i); 
        
        serverPayday = hour;

        FixWorldWeather(hour);
    }
    return 1;
}

task globalSecondTimer[1000]() {
    new 
        hour, minute, second, year, month, day;

    gettime(hour, minute, second); 
    getdate(year, month, day);

    gString[0] = EOS;
    format(gString, sizeof gString, "~W~~H~%02d.%02d.%d", day, month, year);
    TextDrawSetString(serverDateTD, gString);

    gString[0] = EOS;
    format(gString, sizeof gString, "~W~~H~%02d:%02d:%02d", hour, minute, second);
    TextDrawSetString(serverClockTD, gString);

    gString[0] = EOS;
    format(gString, sizeof gString, "ticks: ~r~%d ~W~~H~mysql: ~G~%d", GetServerTickRate(), mysql_unprocessed_queries());
    TextDrawSetString(AStatsTD, gString);

    gString[0] = EOS;
    format(gString, sizeof gString, "REPORTS: ~R~%d~W~~H~ / CHEATERS: ~B~%d", Iter_Count(serverReports), GetCheaters());
    TextDrawSetString(ReportsTD, gString);

    if(staffQuestionsInfoDelay < gettime()) {
        SendStaff(COLOR_YELLOW, "** There are %d pending questions right now and %d helpers online.", Iter_Count(serverQuestions), Iter_Count(serverHelpers)); 
        staffQuestionsInfoDelay = gettime() + 300;
    }
    return 1;
}

task randomServerMessages[60000 * 10]() {
    switch(random(10)) {
        case 0: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Daca esti incepator pe server si ai nevoie de anumite informatii despre acesta, nu ezita sa pui intrebari folosind comanda [/newbie].");
        case 1: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Pentru a afla mai multe comenzi ale server-ului, poti folosi comanda [/help].");
        case 2: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Pentru a vedea job-urile disponibile, foloseste comanda [/jobs].");
        case 3: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Panel-ul server-ului este: http://panel.Lurk.ro");
        case 4: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Forum-ul server-ului este: http://forum.Lurk.ro");
        case 5: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Afacerile ilegale cu bani reali sunt interzise, iar cine va fii prins va fii banat permanent.");
        case 6: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Daca ai vazut un jucator care foloseste moduri interzise si influenteaza negativ gameplay-ul, nu ezita sa-l raportezi administratorilor folosind comanda [/report].");
        case 7: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Pentru a plasa un anunt comercial, du-te la un business de tip CNN si foloseste comanda [/ad].");
        case 8: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Pentru a vedea locatiile disponibile, foloseste comanda [/gps].");
        case 9: sendSplittedMessageToAll(COLOR_DARKGREEN, COLOR_DARKGREEN, "Daca ai nevoie de bani urgent si nu te poti deplasa catre o banca, poti cauta un ATM in apropiere.");
    }
    return 1;
}