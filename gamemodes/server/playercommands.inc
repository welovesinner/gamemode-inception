#if defined DEBUG

    YCMD:champagne(playerid, params[], help) {
        if(!IsPlayerAttachedObjectSlotUsed(playerid, 5) && !IsPlayerAttachedObjectSlotUsed(playerid, 6)) {
            ApplyAnimation(playerid, "ped", "IDLE_armed", 4.1, 1, 0, 0, 0, 0, 0);

            SetPlayerAttachedObject(playerid, 5, 19821, 6, 0.073999, 0.020000, 0.055999, -0.000000, 69.899986, 0.000000, 0.791000, 0.860000, 0.593999);
            SetPlayerAttachedObject(playerid, 6, 18717, 6, 0.414999, 0.020999, -1.485998, 0.000000, 0.000000, 0.000000);
        }
        else {
            RemovePlayerAttachedObject(playerid, 5);
            RemovePlayerAttachedObject(playerid, 6);

            ClearAnimations(playerid);
        }
        return 1;
    }

    YCMD:debughouse(playerid, params[], help) {
        new Float: X, Float: Y, Float: Z;
        GetPlayerPos(playerid, X,Y,Z);
        CreateDynamicPickup(1273, 23, X,Y,Z);
        CreateDynamicMapIcon(X,Y,Z, 55, 0);
        printf("%f, %f, %f", X,Y,Z);
        return 1;
    }

    YCMD:gimmeadmin(playerid, params[], help) return playerInfo[playerid][pAdmin] = 6, SCM(playerid, COLOR_LOGS, "Injected.");

    YCMD:debug2(playerid, params[], help) return playerInfo[playerid][pDrivingLicense] = 0, 1;

    YCMD:mystate(playerid, params[], help) {
        SCMf(playerid, -1, "%d", GetPlayerState(playerid));
        SCMf(playerid, -1, "%d | %d | %d | %d | %d | %d | %d", PLAYER_STATE_NONE, PLAYER_STATE_ONFOOT, PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER, PLAYER_STATE_WASTED, PLAYER_STATE_SPAWNED, PLAYER_STATE_SPECTATING); 
        return 1;
    }

    YCMD:pula(playerid, params[], help) return playerVars[playerid][var_jobseconds] = 5;

    YCMD:seteazamiskill(playerid, params[], help) {
        if(isnull(params) || !isnumeric(params))
            return sendUsage(playerid, "ce skill vrei stapine");

        playerInfo[playerid][pTruckerSkill] = strval(params);
        return SCMf(playerid, -1, "gata stapine ai skill %d", strval(params));
    }

    YCMD:teleport(playerid, params[], help) {
        SetVehiclePos(GetPlayerVehicleID(playerid), busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][0], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][1], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][2]);
    }

    YCMD:setcp(playerid, params[], help) {
        playerVars[playerid][var_busdrivercheckpoint] = strval(params);
        return SCMf(playerid, -1, "%d", playerVars[playerid][var_busdrivercheckpoint]), true;
    }

    YCMD:sulamea(playerid, params[], help) 
    {
        return playerVars[playerid][var_courierstuff] = strval(params);
    }

    YCMD:returneazapoolsize(playerid, params[], help) 
        return SCMf(playerid, -1, "%d", GetVehiclePoolSize());

    YCMD:unixtimestamp(playerid, params[], help) 
        return SCMf(playerid, -1, "%d | %d", gettime(_, _, _), gettime(_, _, _) + strval(params) * 86400);

    YCMD:damimateriale(playerid, params[], help) 
        return playerInfo[playerid][pMaterials] += strval(params);

    YCMD:getplayerid(playerid, params[], help) {
        new id;
        sscanf(params, "?<MATCH_NAME_PARTIAL=0>u", id);
        return SCMf(playerid, -1, "The ID of that player is: %d", id); 
    }

    YCMD:debugsmek(playerid, params[], help) {
        return SCMf(playerid, -1, "%d", Iter_Count(playerSkins[playerid]));
    }

    YCMD:vehiclesstreamed(playerid, params[], help) {
        return SCMf(playerid, -1, "%d", Iter_Count(vehiclesStreamed[playerid]));
    }

    YCMD:returneazavehicule(playerid, params[], help) {
        foreach(new veh : vehiclesStreamed[playerid]) SCMf(playerid, -1, "%d", veh);
        return 1;
    }

    YCMD:getnearbyitems(playerid, params[], help) {
        new 
            nearbyLabel[1], Float: X, Float: Y, Float: Z;

        GetPlayerPos(playerid, X, Y, Z);
        Streamer_GetNearbyItems(X,Y,Z, STREAMER_TYPE_3D_TEXT_LABEL, nearbyLabel, 1, 2.5);
        return SCMf(playerid, -1, "%d", 3 <= nearbyLabel[0] <= 5);
    }

    YCMD:eparolavalida(playerid, params[], help) {
        return SCMf(playerid, -1, "--- result: %d", IsValidPassword(params));
    }

    YCMD:loginqueue(playerid, params[], help) 
        return SCMf(playerid, -1, "%d", Queue_Contains(loginQueue, playerid));

    YCMD:whoisinlogin(playerid, params[], help)
        return SCMf(playerid, -1, "%d", Queue_GetFrontValue(loginQueue));

    YCMD:debugfuel(playerid, params[], help) 
        return vehicleVars[GetPlayerVehicleID(playerid)][var_carFuel] = 3.0, 1;

    YCMD:debugnearbypns(playerid, params[], help) 
        return SCMf(playerid, -1, "%d", getNearbyBusiness(playerid, 5.0, 11));

    YCMD:debugnearbygas(playerid, params[], help) 
        return SCMf(playerid, -1, "%d", getNearbyBusiness(playerid, 5.0, 13));

    YCMD:debugnearby(playerid, params[], help) {
        new 
            nearbyPickup[1] = -1, 
            Float:X, Float:Y, Float:Z; 

        GetPlayerPos(playerid, X, Y, Z), Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, 2.0);

        SCMf(playerid, -1, "ATM Nearby: %d", isNearATM(playerid));

        SCMf(playerid, -1, "House Nearby: %d", getNearbyHouse(playerid, 2.0));      
        SCMf(playerid, -1, "Business Nearby: %d", getNearbyBusiness(playerid, 2.0));
        SCMf(playerid, -1, "Job Nearby: %d", nearbyPickup[0] != -1 ? pickupInfo[nearbyPickup[0]][pk_Job] : -1);
        SCMf(playerid, -1, "Rentcar Nearby: %d", getNearbyRentCar(playerid, 2.0));
        return 1;
    }

    YCMD:ipencrypt(playerid, params[], help) 
        return SCMf(playerid, -1, "%s", encryptIPAddress(params));

    YCMD:debugvehiclemembers(playerid, params[], help) 
        return IsValidVehicle(strval(params)) ? SCMf(playerid, -1, "%d", getVehicleOccupantsCount(strval(params))) : sendError(playerid, "pula frate.. index out of bounds");

    YCMD:repairinvited(playerid, params[], help) 
        return SCMf(playerid, -1, "%d", playerVars[playerid][var_repair_invited]);

    YCMD:debugcrash(playerid, params[], help) {
        new val = -1;
        return playerVars[val][var_repair_price];
    }

    YCMD:debugquests(playerid, params[], help) {
        new questtypeone, questtypetwo, questtypethree; if(sscanf(params, "ddd", questtypeone, questtypetwo, questtypethree)) 
            return 1;

        playerInfo[playerid][pQuestType][0] = questtypeone;
        playerInfo[playerid][pQuestType][1] = questtypetwo;
        playerInfo[playerid][pQuestType][2] = questtypethree;

        playerInfo[playerid][pQuestProgress][0] = playerInfo[playerid][pQuestProgress][1] = playerInfo[playerid][pQuestProgress][2] = 0;

        return showPlayerQuests(playerid), va_mysql_tquery("UPDATE `server_users` SET `Quests` = '%d|%d|%d|%d|%d|%d' WHERE `ID` = %d", playerInfo[playerid][pQuestType][0], playerInfo[playerid][pQuestType][1], playerInfo[playerid][pQuestType][2], playerInfo[playerid][pQuestProgress][0], playerInfo[playerid][pQuestProgress][1], playerInfo[playerid][pQuestProgress][2], playerInfo[playerid][pSQLID]);
    }

    YCMD:debugjob(playerid, params[], help) {
        new money; switch(strval(params)) {
            case 0..30: money = 4000+random(2999);
            case 31..60: money = 6000+random(2999);
            default: money = 9000+random(2999);
        }
        return SCMf(playerid, -1, "%d", money); 
    }

    YCMD:debugfindplayersscanf(playerid, params[], help) {
        new cacat[20] = {INVALID_PLAYER_ID, ...}; if(sscanf(params, "?<MATCH_NAME_PARTIAL=1>u[20]", cacat))
            return 1;

        for(new i = 0; i < sizeof cacat; ++i) SCMf(playerid, -1, "%d", cacat[i]);
        return 1;
    }

    YCMD:streamvehforme(playerid, params[], help) {
        new vehicleid, type; if(sscanf(params, "dd", vehicleid, type) || type > 1 || type < 0)
            return sendUsage(playerid, "/streamvehicleforme <vehicleid> <type (0 = stream out, 1 = stream in)>");

        return CallRemoteFunction(type == 1 ? "OnVehicleStreamIn" : "OnVehicleStreamOut", "ii", vehicleid, playerid);
    }

    YCMD:payday(playerid, params[], help) {
        foreach(new i : serverPlayers) givePayday(i);
        return 1;
    }

    YCMD:timers(playerid, params[], help) {
        SCM(playerid, -1, "----------------- playerTimers -----------------");
        SCMf(playerid, -1, "pLoginTimer: %d", playerInfo[playerid][pLoginTimer]);
        SCMf(playerid, -1, "var_ad_timer: %d", playerVars[playerid][var_ad_timer]);
        SCMf(playerid, -1, "var_spectatetimer: %d", playerVars[playerid][var_spectatetimer]);
        SCMf(playerid, -1, "var_drugs_dealer_timer: %d", playerVars[playerid][var_drugs_dealer_timer]);
        SCMf(playerid, -1, "var_jobtimer: %d", playerVars[playerid][var_jobtimer]);
        SCMf(playerid, -1, "var_find_timer: %d", playerVars[playerid][var_find_timer]);
        SCMf(playerid, -1, "var_renttimer: %d", playerVars[playerid][var_renttimer]);
        SCMf(playerid, -1, "serverRestartTimerVar: %d", serverRestartTimerVar);
        SCM(playerid, -1, "---------------------------------------------");
        return 1;
    }

    YCMD:calculatepercent(playerid, params[], help) {
        new var, varx; if(sscanf(params, "dd", var, varx))
            return 1;

        return SCMf(playerid, -1, "Percentage (value: %d, max value: %d): %0.2f %%", var, varx, returnPercentage(var, varx));
    }

    YCMD:debuganim(playerid, params[], help) {
        new str[64], str1[64];

        if(sscanf(params, "s[64]s[64]", str, str1))
            return SCM(playerid, -1, "/debuganim <animlib> <animname>");

        return ApplyAnimationEx(playerid, str, str1, 4.0, 0, 0, 0, 0, 0);
    }

    YCMD:spawnsomecars(playerid, params[], help) {
        for(new i = 0; i <= 1940; ++i) {
            createVehicle(411, 0.0, 0.0, 0.0, 0.0, -1, -1, 0);
        }
        return SCM(playerid, -1, "spawned");
    }

    YCMD:debugseedstime(playerid, params[], help) 
        return SCMf(playerid, -1, "%i", playerVars[playerid][var_planted_seeds_time]);

    YCMD:executequery(playerid, params[], help) {
        if(playerInfo[playerid][pAdmin] != 8) 
            return 1;

        new query[456]; if(sscanf(params, "s[456]", query)) 
            return 1;

        mysql_tquery(SQL, query, "whenQueryIsFinished", "d", playerid);
        SCM(playerid, -1, "[MySQL] Sended query.");
        return 1;
    }
        
    function whenQueryIsFinished(playerid) {
        SCMf(playerid, -1, "[MySQL Response] Query finished succesfully. Time elapsed: %dms.", cache_get_query_exec_time()); 
    }
                            
    YCMD:test(playerid, params[], help) {
        new vehicle[32];
        sscanf("mave", "K<vehicle>(999)", vehicle);
        printf("%s", vehicle);
    }

    YCMD:deathmsg(playerid, params[], help) {
        SendDeathMessageToPlayer(playerid, INVALID_PLAYER_ID, playerid, 201);
        return 1;
    }

    YCMD:sendmessage(playerid, params[], help) {
        new str[400] = {'a', ...};

        sendSplittedMessageToAll(-1, -1, str);
        return 1;
    }

    YCMD:insertdealershipvehicles(playerid, params[], help) {
        new 
            vehicles[] = {481, 509, 510, 462, 400, 401, 402, 404, 405, 409, 410, 411, 412, 413, 414, 415, 418, 419, 421, 422, 424, 426, 429, 434, 436, 439, 440, 442, 445, 451, 458, 466, 467, 474, 475, 477, 478, 479, 480, 482, 483, 489, 491, 492, 494, 495, 496, 500, 502, 503, 505, 506, 507, 516, 517, 518, 
                526, 527, 529, 533, 534, 535, 536, 540, 541, 542, 543, 545, 546, 547, 549, 550, 551, 554, 555, 558, 559, 560, 561, 562, 565, 566, 567, 575, 576, 579, 580, 585, 587, 589, 600, 602, 603, 604, 605, 461, 463, 468, 471, 521, 522, 581, 586, 487
            };

        new tick = GetTickCount();
        for(new i = 0; i < sizeof vehicles; ++i) 
        {
            va_mysql_tquery("INSERT INTO `server_dealership_vehicles` (ModelID, Stock, Price) VALUES (%d, %d, %d)", vehicles[i], 0, 1);
        }
        return SCMf(playerid, -1, "INSERTED ALL VEHICLES MODELS IN DATABASE SUCCESSFULLY. EXECUTION TIME: %dms", tick - GetTickCount());
    }

    YCMD:debugregister(playerid, params[], help) {
        for(new e_pInfo:i = e_pInfo:0; i < e_pInfo; ++i) {
            SCMf(playerid, -1, "%d", playerInfo[playerid][i]);
        }
        return 1;
    }

    YCMD:debugvehicledriver(playerid, params[], help) {
        return IsValidVehicle(strval(params)) ? SCMf(playerid, -1, "%d, %d", GetVehicleDriver(strval(params)), GetVehicleLastDriver(strval(params))) : sendError(playerid, "invalid veh!");
    }

#endif

YCMD:repair(playerid, params[], help) {
    if(!playerInfo[playerid][pRepairKits])
        return sendError(playerid, "Nu ai niciun kit de reparare.");

    if(playerVars[playerid][var_repair_delay] > gettime())
        return sendError(playerid, "Poti folosi iar aceasta comanda peste %d secunde.", playerVars[playerid][var_repair_delay] - gettime());

    new userID, price; if(sscanf(params, "ud", userID, price)) 
        return sendUsage(playerid, "/repair <playerid/name> <price>");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat pe server.");

    if(userID == playerid) 
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(price < 1 || price > 10000)
        return sendError(playerid, "Pretul trebuie sa fie cuprins intre $1 si $10.000.");

    new const vehicleid = GetPlayerVehicleID(userID);

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 5.0) || (vehicleid == 0 || getVehicleModelType(GetVehicleModel(vehicleid)) == VEHICLE_MODEL_TYPE_BIKE))
        return sendError(playerid, "Nu esti in apropierea acelui player sau acel player nu este intr-un vehicul.");

    playerVars[userID][var_repair_invited] = playerid;
    playerVars[userID][var_repair_price] = price;

    SCMf(playerid, COLOR_GREEN, "(Repair): {ffffff}You sent a repair invite to player %s (%d) for $%s money. Wait until he accept the invite.", GetName(userID), userID, formatNumber(price));
    SCMf(userID, COLOR_GREEN, "(Repair): {ffffff}%s (%d) sent you a repair invite for $%s money. Use command [/accept %d repair] to accept his repair invite.", GetName(playerid), playerid, formatNumber(price), playerid);
    
    playerVars[playerid][var_repair_delay] = gettime() + 60;
    return 1;
}

YCMD:fillgascan(playerid, params[], help) {
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return 1;

    if(!playerVars[playerid][var_gascan])
        return sendError(playerid, "Nu ai o canistra cu combustibil.");

    new 
        vehicleid = GetPlayerVehicleID(playerid),
        modelid = GetVehicleModel(vehicleid),
        e_vehicleModelTypes:vehicletype = getVehicleModelType(modelid);

    if(vehicletype == VEHICLE_MODEL_TYPE_BIKE || vehicletype == VEHICLE_MODEL_TYPE_PLANE || vehicletype == VEHICLE_MODEL_TYPE_BOAT)
        return sendError(playerid, "Nu poti face asta in acest tip de vehicul.");

    if(vehicleVars[vehicleid][var_carFuel] > 80.00)
        return sendError(playerid, "Nu poti face plinul deoarece vehiculul are peste 80 litrii de combustibil.");

    if(vehicleVars[vehicleid][var_carEngine])
        return sendError(playerid, "Motorul vehiculului trebuie sa fie oprit inainte de a face plinul.");

    SCM(playerid, COLOR_GREEN, "(Gas Can): {ffffff}You filled your vehicle with 20 litres of fuel."); 

    playerVars[playerid][var_gascan] = false; 
    vehicleVars[vehicleid][var_carFuel] += 20.00; 
    return 1;
}

YCMD:fill(playerid, params[], help) {
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || playerVars[playerid][b_ACTIVE_TIMER])
        return 1;

    new const bizzid = getNearbyBusiness(playerid, 6.0, 13);

    if(bizzid == -1)
        return sendError(playerid, "Nu esti langa o benzinarie.");

    new
        vehicleid = GetPlayerVehicleID(playerid),
        modelid = GetVehicleModel(vehicleid),
        e_vehicleModelTypes:vehicletype = getVehicleModelType(modelid),
        Float:fuel = 100.99 - vehicleVars[vehicleid][var_carFuel],
        fuelprice = (floatround(fuel) * 180) + bizzInfo[bizzid][bFee];

    if(vehicletype == VEHICLE_MODEL_TYPE_BIKE || vehicletype == VEHICLE_MODEL_TYPE_PLANE || vehicletype == VEHICLE_MODEL_TYPE_BOAT)
        return sendError(playerid, "Nu poti face asta in acest tip de vehicul.");  

    if(vehicleVars[vehicleid][var_carFuel] > 95.99)
        return sendError(playerid, "Nu poti face plinul deoarece masina are peste 95 litrii de combustibil.");

    if(GetMilliards(playerid) < 1 && GetMoney(playerid) < fuelprice)
        return sendError(playerid, "Nu ai destui bani pentru a face plinul. Ai nevoie de $%s.", formatNumber(fuelprice));

    if(vehicleVars[vehicleid][var_carEngine])
        return sendError(playerid, "Motorul masinii trebuie sa fie oprit inainte de a face plinul.");

    TogglePlayerControllableEx(playerid, false);

    GameTextForPlayer(playerid, "~w~~n~~n~~n~~n~~n~~n~~n~~n~RE-FUELLING VEHICLE...", 5000, 3); 

    defer fillVehicle(playerid, vehicleid, bizzid, fuel, fuelprice); 
    playerVars[playerid][b_ACTIVE_TIMER] = true;
    return 1;
}

YCMD:refstats(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 5)
        return sendError(playerid, "Ai nevoie de minim level 5 pentru a folosi aceasta comanda.");

    return Dialog_Show(playerid, REFERRALCOLLECT, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Referral Rewards Collect", "Type\tAmount\nMoney\t$%s\nRespect Points\t%d", "Select", "Close", formatNumber(playerInfo[playerid][pReferralCash]), playerInfo[playerid][pReferralRespectPoints]);
}

YCMD:trc(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 10)
        return sendError(playerid, "Nu ai job-ul Trucker.");

    if(!playerVars[playerid][var_working])
        return sendError(playerid, "Nu poti folosi aceasta comanda deoarece nu muncesti.");

    if(playerInfo[playerid][pTruckerSkill] < 31)
        return sendError(playerid, "Ai nevoie de minim skill 2 pentru a folosi acest chat.");

    if(!Iter_Contains(truckersChat, playerid) || playerVars[playerid][var_trucker_chat_delay] > gettime())
        return 1;

    if(isnull(params))
        return sendUsage(playerid, "/trc <text>");

    gString[0] = EOS;
    format(gString, sizeof gString, "[truckers chat]: Trucker %s (%s): %s, over.", GetName(playerid), returnPlayerZoneName(playerid), params);

    foreach(new i : truckersChat) 
        sendSplittedMessageToPlayer(i, 0xf2cb5eff, 0xf2cb5eff, gString);

    playerVars[playerid][var_trucker_chat_delay] = gettime() + 2;
    return 1;
}

YCMD:smoke(playerid, params[], help) {
    if(!playerVars[playerid][var_cigarettes])
        return sendError(playerid, "Nu ai tigari.");

    if(playerVars[playerid][var_cigarettes_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_cigarettes_delay] - gettime());

    playerVars[playerid][var_cigarettes] --;

    playerVars[playerid][var_cigarettes_delay] = gettime() + 60; 

    return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
}

YCMD:creategun(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 9)
        return sendError(playerid, "Nu ai job-ul de Arms Dealer.");

    if(playerInfo[playerid][pWeaponLicense] <= 0)
        return sendError(playerid, "Nu ai licenta pentru arme.");

    new const weaponid = strval(params);

    if(!isnumeric(params) || (weaponid < 24 || (weaponid >= 26 && weaponid < 29) || weaponid == 32 || weaponid > 33))
        return sendUsage(playerid, "/creategun <weaponid>"), SCM(playerid, COLOR_GREY, "Weapons Available: {ffffff}Desert Eagle (24, 1500 materials), Shotgun (25, 2500 materials), Rifle (33, 2000 materials), ..."), SCM(playerid, -1, "... MP5 (29, 1700 materials), AK-47 (30, 3000 materials), M4 (31, 3250 materials).");

    new mats;

    switch(weaponid) {
        case 24: mats = 1500;
        case 25: mats = 2500;
        case 29: mats = 1700;
        case 30: mats = 3000;
        case 33: mats = 2000;
        case 31: mats = 3250;
    }

    if(playerInfo[playerid][pMaterials] < mats)
        return sendError(playerid, "Nu ai destule materiale asupra ta.");

    switch(weaponid) {
        case 24, 25, 33: GivePlayerWeapon(playerid, weaponid, 50);
        default: GivePlayerWeapon(playerid, weaponid, 120);
    }

    playerInfo[playerid][pMaterials] -= mats;

    va_mysql_tquery("UPDATE `server_users` SET `Materials` = %d WHERE `ID` = %d", playerInfo[playerid][pMaterials], playerInfo[playerid][pSQLID]); 

    return SCMf(playerid, COLOR_GREY, "* You created weapon %s (id: %d) for %d materials.", GunNames[weaponid], weaponid, mats);
}

YCMD:sellmaterials(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 9)
        return sendError(playerid, "Nu ai job-ul de Arms Dealer.");

    new userID, mats, money; if(sscanf(params, "udd", userID, mats, money) || mats < 1)
        return sendUsage(playerid, "/sellmaterials <playerid/name> <materials> <money>");

    if(playerInfo[playerid][pMaterials] < mats)
        return sendUsage(playerid, "Nu ai destule materiale asupra ta.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face asta asupra ta.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
        return sendError(playerid, "Nu esti in apropierea acelui player.");

    if(money < 1 || money > 500000)
        return sendError(playerid, "Invalid Money! ($1 - $500.000)");

    if(GetMoney(userID) < money && GetMilliards(userID) < 1)
        return sendError(playerid, "Acel player nu are bani suficienti.");

    if(playerVars[userID][var_sell_mats] == playerid)
        return sendError(playerid, "Asteapta ca acel player sa raspunda la aceasta propunere.");

    playerVars[userID][var_sell_mats] = playerid; 
    playerVars[userID][var_sell_mats_money] = money;
    playerVars[userID][var_sell_mats_value] = mats;
    
    SCMf(playerid, COLOR_GREEN, "(Sell Offer): {FFFFFF}You want to give %d materials to player %s for $%s money. Wait him to accept the sell offer.", mats, GetName(userID), formatNumber(money));
    SCMf(userID, COLOR_GREEN, "(Sell Offer): {FFFFFF}%s want to give you %d materials for $%s money. Accept the sell offer by typing command [/accept %d materials].", GetName(playerid), mats, formatNumber(money), playerid);
    return 1;
} 

YCMD:getmats(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 9)
        return sendError(playerid, "Nu ai job-ul de Arms Dealer.");

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, 2178.6499,-1660.4121,14.9628) || playerVars[playerid][b_ARMS_DEALER_WORKING])
        return 1;

    return Dialog_Show(playerid, SELECTMATSLOCATION, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Select Location", "Location Name\tDistance\nBeacon Hill\t%0.2fkm\nAngel Pine\t%0.2fkm\nFort Carson\t%0.2fkm\nEl Corona\t%0.2fkm\nEl Quebrados\t%0.2fkm\nHampton Barns\t%0.2fkm\nHilltop Farm\t%0.2fkm\nJuniper Hill\t%0.2fkm", "Select", "Exit", GetPlayerDistanceFromPoint(playerid, -365.6372,-1051.1757,59.3216)/1000, GetPlayerDistanceFromPoint(playerid, -2088.1455,-2526.7053,30.4219)/1000, GetPlayerDistanceFromPoint(playerid, 67.7654,1171.3551,18.6641)/1000, GetPlayerDistanceFromPoint(playerid, 1945.3020,-2085.6057,13.5501)/1000, GetPlayerDistanceFromPoint(playerid, -1525.3641,2638.2939,55.8359)/1000, GetPlayerDistanceFromPoint(playerid, 753.4481,342.3109,20.3653)/1000, GetPlayerDistanceFromPoint(playerid, 1025.3591,-339.4805,73.9922)/1000, GetPlayerDistanceFromPoint(playerid, -2467.2417,790.2145,35.1719)/1000);
}

YCMD:selldrugs(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 8)
        return sendError(playerid, "Nu ai job-ul de Drugs Dealer.");

    new userID, drugs, money; if(sscanf(params, "udd", userID, drugs, money) || drugs < 1)  
        return sendUsage(playerid, "/selldrugs <playerid/name> <drugs> <money>");

    if(playerInfo[playerid][pDrugs] < drugs)
        return sendError(playerid, "Nu ai destule droguri asupra ta.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face asta asupra ta.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
        return sendError(playerid, "Nu esti in apropierea acelui player.");

    if(money < 1 || money > 500000)
        return sendError(playerid, "Invalid Money! ($1 - $500.000)");

    if(GetMoney(userID) < money && GetMilliards(userID) < 1)
        return sendError(playerid, "Acel player nu are bani suficienti.");

    if(playerVars[userID][var_sell_drugs] == playerid)
        return sendError(playerid, "Asteapta ca acel player sa raspunda la aceasta propunere.");

    playerVars[userID][var_sell_drugs] = playerid;
    playerVars[userID][var_sell_drugs_money] = money;
    playerVars[userID][var_sell_drugs_value] = drugs;
    
    SCMf(playerid, COLOR_GREEN, "(Sell Offer): {FFFFFF}You want to give %dg of drugs to player %s for $%s money. Wait him to accept the sell offer.", drugs, GetName(userID), formatNumber(money));
    SCMf(userID, COLOR_GREEN, "(Sell Offer): {FFFFFF}%s want to give you %dg of drugs for $%s money. Accept the sell offer by typing command [/accept %d drugs].", GetName(playerid), drugs, formatNumber(money), playerid);
    return 1;
}

YCMD:usedrugs(playerid, params[], help) {
    if(!playerInfo[playerid][pDrugs])
        return sendError(playerid, "Nu ai droguri pentru a le putea folosi.");

    if(playerVars[playerid][var_delay])
        return 1;

    if(IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu poti folosi aceasta comanda daca te aflii intr-un vehicul.");

    TogglePlayerControllableEx(playerid, false);

    ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);

    va_mysql_tquery("UPDATE `server_users` SET `Drugs` = %d WHERE `ID` = %d", (--playerInfo[playerid][pDrugs], playerInfo[playerid][pDrugs]), playerInfo[playerid][pSQLID]);
    
    SetPlayerHealth(playerid, 100.0); 

    playerVars[playerid][var_delay] = true;
    defer freezeTimer[30000](playerid);

    sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "* %s used some drugs.", GetName(playerid));
    SCM(playerid, COLOR_GREY, "* You have to wait 30 seconds for the effect of the drugs to disappear.");
    return 1;
}

YCMD:getdrugs(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 8) 
        return sendError(playerid, "Nu ai job-ul de Drugs Dealer.");

    if(playerVars[playerid][var_planted_seeds_time] != 0)
        return 1;

    CheckPlayerCheckpoint(playerid);

    new Float: X, Float: Y, Float: Z; 
    GetDynamicObjectPos(playerVars[playerid][var_jobobject], X,Y,Z);

    if(!IsPlayerInRangeOfPoint(playerid, 2.5, X,Y,Z)) {
        SetPlayerCheckpoint(playerid, X,Y,Z, 2.5);
        playerVars[playerid][var_checkpoint] = 1;
        return sendError(playerid, "Nu esti in locatia corespunzatoare, ti-a fost plasat un checkpoint.");
    }

    new const drugs = ((playerInfo[playerid][pDrugsDealerSkill] <= 30 ? 1 : playerInfo[playerid][pDrugsDealerSkill] <= 60 ? 2 : 3)*2)+random(10);

    if(playerInfo[playerid][pDrugsDealerSkill] < 90) ++playerInfo[playerid][pDrugsDealerSkill];

    DestroyDynamic3DTextLabel(playerLabels[playerid][l_drugs_dealer]);
    DestroyDynamicObject(playerVars[playerid][var_jobobject]);

    playerInfo[playerid][pDrugs] += drugs;
    playerVars[playerid][var_planted_seeds_time] = playerVars[playerid][var_jobobject] = -1;

    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

    va_mysql_tquery("UPDATE `server_users` SET `Drugs` = %d, `DrugsDealerSkill` = %d WHERE `ID` = %d", playerInfo[playerid][pDrugs], playerInfo[playerid][pDrugsDealerSkill], playerInfo[playerid][pSQLID]);
    
    return SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}You collected your planted drugs and you received %dg of drugs.", drugs);
}

YCMD:plantseeds(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 8) 
        return sendError(playerid, "Nu ai job-ul de Drugs Dealer.");

    if(playerVars[playerid][var_planted_seeds_time] != -1)
        return 1;

    if(!playerVars[playerid][var_have_seeds])
        return sendError(playerid, "Nu ai semintele.");

    new Float: X, Float: Y, Float: Z; 

    GetPlayerPos(playerid, X, Y, Z);

    if(!isInRectangleArea(X, Y, -1196.265625, -1003.265625, -1062.484375, -909.484375))
        return sendError(playerid, "Nu esti in locatia corespunzatoare.");

    if(isPlayerFalling(playerid))
        return sendError(playerid, "Nu poti folosi aceasta comanda in timp ce esti in cadere.");

    playerVars[playerid][var_jobobject] = CreateDynamicObject(19473, X, Y, Z-2.5, 0.0, 0.0, 0.0);
    MoveDynamicObject(playerVars[playerid][var_jobobject], X, Y, Z-1.0, 0.013);

    playerLabels[playerid][l_drugs_dealer] = CreateDynamic3DTextLabel("Loading...", -1, X, Y, Z, 15.0);

    playerVars[playerid][var_drugs_dealer_timer] = repeat drugsDealerTimer(playerid);

    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

    playerVars[playerid][var_planted_seeds_time] = gettime() + 120;
    playerVars[playerid][var_have_seeds] = false;

    return SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}You've planted seeds succesfully.");
}

YCMD:getseeds(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 8) 
        return sendError(playerid, "Nu ai job-ul de Drugs Dealer.");

    if(!IsPlayerInRangeOfPoint(playerid, 2.5, -1069.3879,-1205.5856,129.2188) || playerVars[playerid][var_planted_seeds_time] != -1)
        return 1;

    if(playerVars[playerid][var_have_seeds])
        return sendError(playerid, "Ai deja semintele.");

    clearChat(playerid, 25);

    SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}You are needed to plant received seeds in this area using command [/plantseeds].");
    SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}After you planted the seeds, you need to wait 2:00 minutes for harvest.");
    SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}When 2:00 minutes are passed, you can get the drugs using command [/getdrugs].");
    
    InterpolateCameraPos(playerid, -1094.296020, -1204.233276, 141.128067, -1023.643066, -1070.246215, 182.082641, 5000);
    InterpolateCameraLookAt(playerid, -1089.792480, -1204.290039, 138.956741, -1026.636718, -1067.438232, 179.227264, 5000);
    defer drugsDealerSetCameraBehind(playerid);

    return playerVars[playerid][var_have_seeds] = true;
}

YCMD:fish(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 2)
        return sendError(playerid, "Nu ai job-ul de Fisherman.");

    if(!IsPlayerInRangeOfPoint(playerid, 10.0, 386.7305, -2084.8535, 7.8359))
        return sendError(playerid, "Nu esti la locatia corespunzatoare pentru a pescuii.");

    if(IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu poti pescuii daca esti intr-un vehicul.");

    if(playerVars[playerid][var_fishkg] > 0) 
        return sendError(playerid, "Ai prins deja un peste. Trebuie sa il vinzi la unul dintre afacerile de tip 24/7.");

    if(playerVars[playerid][b_FISHING])
        return 1;

    TogglePlayerControllableEx(playerid, false);
    defer fishTimer(playerid);

    playerVars[playerid][b_FISHING] = true;
    
    SetPlayerAttachedObject(playerid, INDEX_JOB, 18632, 6, 0.079376, 0.037070, 0.007706, 181.482910, 0.0, 0.0, 1.0, 1.0, 1.0);

    ApplyAnimationEx(playerid, "SAMP", "FishingIdle", 3.0, 1, 1, 0, 0, 0);
    
    return SCM(playerid, COLOR_GREEN, "(Fish): {FFFFFF}You are fishing now, wait...");
}

YCMD:find(playerid, params[], help) {
    if(playerInfo[playerid][pJob] != 1)
        return sendError(playerid, "Nu ai job-ul de Detective.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/find <playerid/name>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(playerVars[playerid][var_findon] == userID)
        return sendError(playerid, "Ai deja activat [/find] pe acel jucator.");

    if(playerInfo[userID][pTOGFind])
        return sendError(playerid, "Acel jucator nu poate fi localizat.");

    findFunction(playerid, userID);
    return updatePlayerQuestProgress(playerid, QUEST_TYPE_FINDPLAYER);
}

YCMD:help(playerid, params[], help) 
    return Dialog_Show(playerid, HELP, DIALOG_STYLE_LIST, "SERVER: Help", "Chat Commands\nJobs\nGeneral Commands\nBusiness\nHouse", "Select", "Exit");

YCMD:accept(playerid, params[], help) {
    new userID; gString[0] = EOS; if(sscanf(params, "us[64]", userID, gString) || strlen(gString) >= 63)
        return sendUsage(playerid, "/accept <playerid/name> <type>"), SCM(playerid, COLOR_GREY, "Types: dice, drugs, materials, repair, trade, live, free.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face asta asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!strcmp(gString, "dice")) {
        if(playerVars[playerid][var_dice_invited] != userID)
            return sendError(playerid, "Nu ai primit invitatie recenta de la acel player.");

        if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
            return sendError(playerid, "Nu esti in apropierea acelui player.");

        new 
            playerOne = 1 + random(6), playerTwo = 1 + random(6);

        if(playerOne == playerTwo) {
            sendNearbyMessage(playerid, COLOR_PURPLE, 10.0, "* %s and %s rolls. %d-%d. Equal.", GetName(playerid), GetName(userID), playerOne, playerTwo);
            SCM(playerid, COLOR_GREEN, "(Dice): {ffffff}It's equal. Nobody wins.");
            SCM(userID, COLOR_GREEN, "(Dice): {ffffff}It's equal. Nobody wins.");
        }
        else {
            new 
                winner, loser;

            if(playerOne > playerTwo) {
                winner = playerid;
                loser = userID;
            }
            else {
                winner = userID;
                loser = playerid;
            }

            sendNearbyMessage(playerid, COLOR_PURPLE, 10.0, "* %s and %s rolls. %d-%d. %s win $%s money.", GetName(playerid), GetName(userID), playerOne, playerTwo, GetName(winner), formatNumber(playerVars[playerid][var_dice_money]));
            SCMf(winner, COLOR_GREEN, "(Dice): {ffffff}You winned $%s money.", formatNumber(playerVars[playerid][var_dice_money]));
            SCMf(loser, COLOR_GREEN, "(Dice): {ffffff}You losed $%s money.", formatNumber(playerVars[playerid][var_dice_money]));
            
            addMoney(winner, GetMilliards(winner), GetMoney(winner), 0, playerVars[playerid][var_dice_money]); 
            substractMoney(loser, GetMilliards(loser), GetMoney(loser), 0, playerVars[playerid][var_dice_money]);
        
            updatePlayerQuestProgress(winner, QUEST_TYPE_DICE);
        }
        playerVars[playerid][var_dice_money] = playerVars[playerid][var_dice_invited] = -1;
    }
    else if(!strcmp(gString, "free"))
    {
        if(FreeOffer[playerid] > -1)
        {
            new string[100];
            if(FreeOffer[playerid] != userID) return SendClientMessage(playerid,-1, "This player has not offered you a free.");
            if(GetMoney(playerid) < FreePrice[playerid] && GetMilliards(playerid) < 1)
                return sendError(playerid, "Nu ai $%s.", formatNumber(FreePrice[playerid]));
            format(string, sizeof(string), "(+) %s a acceptat oferta de a fi eliberat iar tu ai primit $%s.", GetName(userID), formatNumber(FreePrice[playerid]));
            SendClientMessage(FreeOffer[playerid], COLOR_GREEN, string);
            format(string, sizeof(string), "Ai platit $%s pentru a fi eliberat din inchisoare.", formatNumber(FreePrice[playerid]));
            SendClientMessage(playerid, -1, string);
            playerInfo[userID][pJailTime] = 1;
            substractMoney(playerid, playerInfo[userID][pMoneyStore], playerInfo[userID][pMoney], 0, -FreePrice[playerid]);
            addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, FreePrice[playerid], false);
            playerInfo[userID][pJailTime] = 0;
            new str[356];
            mysql_format(SQL,str,sizeof(str),"update server_users set `playerJailTime` = '0' WHERE `Name` = '%s'",playerInfo[userID][pName]);
            mysql_tquery(SQL,str,"","");
            FreeOffer[playerid] = -1;
            FreePlayer[playerid] = -1;
            FreePrice[playerid] = 0;
            format(string, sizeof(string), "Dispatch: %s was released by %s from jail.", GetName(userID), GetName(playerid));
            SendGroupTypeMessage(1, COLOR_BLUE, string);
            SpawnPlayer(playerid);
            return 1;
        }
        else return SendClientMessage(playerid, -1, "Nobody offered you free.");
    }
    else if(!strcmp(gString, "drugs")) {
        if(playerVars[playerid][var_sell_drugs] != userID)
            return sendError(playerid, "Nu ai primit vreo oferta recenta de la acel player.");

        if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
            return sendError(playerid, "Nu esti in apropierea acelui player.");

        if(isPlayerInTrade(userID))
            return sendError(playerid, "Nu poti face asta deoarece acel player este in cursul unei negocieri.");

        if(playerInfo[userID][pDrugs] < playerVars[playerid][var_sell_drugs_value])
            return sendError(playerid, "Acel player nu are destule droguri.");

        addMoney(userID, GetMilliards(userID), GetMoney(userID), 0, playerVars[playerid][var_sell_drugs_money], false);
        substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, playerVars[playerid][var_sell_drugs_money], false);

        playerInfo[playerid][pDrugs] += playerVars[playerid][var_sell_drugs_value];
        playerInfo[userID][pDrugs] -= playerVars[playerid][var_sell_drugs_value];

        SCMf(playerid, COLOR_GREEN, "(Sell Offer): {FFFFFF}You received %dg of drugs from player %s for $%s money.", playerVars[playerid][var_sell_drugs_value], GetName(userID), formatNumber(playerVars[playerid][var_sell_drugs_money]));
        SCMf(userID, COLOR_GREEN, "(Sell Offer): {FFFFFF}%s accepted your offer and you received $%s money for %dg of drugs.", GetName(playerid), formatNumber(playerVars[playerid][var_sell_drugs_money]), playerVars[playerid][var_sell_drugs_value]);
    
        va_mysql_tquery("UPDATE `server_users` SET `Drugs` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[playerid][pDrugs], GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pSQLID]);
        va_mysql_tquery("UPDATE `server_users` SET `Drugs` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[userID][pDrugs], GetMilliards(userID), GetMoney(userID), playerInfo[userID][pSQLID]);

        playerVars[playerid][var_sell_drugs] = playerVars[playerid][var_sell_drugs_money] = playerVars[playerid][var_sell_drugs_value] = -1;
    }
    else if(!strcmp(gString, "materials")) {
        if(playerVars[playerid][var_sell_mats] != userID)
            return sendError(playerid, "Nu ai primit vreo oferta recenta de la acel player.");

        if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
            return sendError(playerid, "Nu esti in apropierea acelui player.");

        if(isPlayerInTrade(userID))
            return sendError(playerid, "Nu poti face asta deoarece acel player este in cursul unei negocieri.");

        if(playerInfo[userID][pMaterials] < playerVars[playerid][var_sell_mats_value])
            return sendError(playerid, "Acel player nu are destule materiale.");

        addMoney(userID, GetMilliards(userID), GetMoney(userID), 0, playerVars[playerid][var_sell_mats_money], false);
        substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, playerVars[playerid][var_sell_mats_money], false);

        playerInfo[playerid][pMaterials] += playerVars[playerid][var_sell_mats_value];
        playerInfo[userID][pMaterials] -= playerVars[playerid][var_sell_mats_value];

        SCMf(playerid, COLOR_GREEN, "(Sell Offer): {FFFFFF}You received %d materials from player %s for $%s money.", playerVars[playerid][var_sell_mats_value], GetName(userID), formatNumber(playerVars[playerid][var_sell_mats_money]));
        SCMf(userID, COLOR_GREEN, "(Sell Offer): {FFFFFF}%s accepted your offer and you received $%s money for %d materials.", GetName(playerid), formatNumber(playerVars[playerid][var_sell_mats_money]), playerVars[playerid][var_sell_mats_value]);
    
        va_mysql_tquery("UPDATE `server_users` SET `Materials` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[playerid][pMaterials], GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pSQLID]);
        va_mysql_tquery("UPDATE `server_users` SET `Materials` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[userID][pMaterials], GetMilliards(userID), GetMoney(userID), playerInfo[userID][pSQLID]);

        playerVars[playerid][var_sell_mats] = playerVars[playerid][var_sell_mats_money] = playerVars[playerid][var_sell_mats_value] = -1;
    }
    else if(!strcmp(gString, "repair")) {
        if(playerVars[playerid][var_repair_invited] != userID)
            return sendError(playerid, "Nu ai primit vreo invitatie recenta de la acel player.");

        if(!IsPlayerInRangeOfPlayer(playerid, userID, 3.0))
            return sendError(playerid, "Nu esti in apropierea acelui player.");

        if(playerInfo[playerVars[playerid][var_repair_invited]][pRepairKits] < 1)
            return sendError(playerid, "Acel player nu are kit-uri de reparare.");

        if(GetMoney(playerid) < playerVars[playerid][var_repair_price] && GetMilliards(playerid) < 1)
            return sendError(playerid, "Nu ai bani suficienti.");

        new const vehicleid = GetPlayerVehicleID(playerid);

        if(vehicleid == 0 || getVehicleModelType(GetVehicleModel(vehicleid)) == VEHICLE_MODEL_TYPE_BIKE)
            return sendError(playerid, "Nu esti intr-un vehicul.");

        --playerInfo[userID][pRepairKits];

        addMoney(userID, GetMilliards(userID), GetMoney(userID), 0, playerVars[playerid][var_repair_price], false);
        substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, playerVars[playerid][var_repair_price]);

        va_mysql_tquery("UPDATE `server_users` SET `RepairKits` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[userID][pRepairKits], GetMilliards(userID), GetMoney(userID), playerInfo[userID][pSQLID]), RepairVehicle(vehicleid);

        SCMf(playerid, COLOR_GREEN, "(Repair): {ffffff}You accepted %s's repair kit for $%s money and your vehicle is now repaired.", GetName(userID), formatNumber(playerVars[playerid][var_repair_price]));
        SCMf(userID, COLOR_GREEN, "(Repair): {ffffff}%s accepted your repair kit and you received $%s money.", GetName(playerid), formatNumber(playerVars[playerid][var_repair_price]));

        playerVars[playerid][var_repair_invited] = -1;
        playerVars[playerid][var_repair_price] = 0; 

        updatePlayerQuestProgress(userID, QUEST_TYPE_REPAIRKIT);
    }
    else if(!strcmp(gString, "live")) {
        OnPlayerAcceptsLiveInvite(playerid, userID);
    }
    else if(!strcmp(gString, "trade")) {
        if(getTradeInvite(playerid) != userID)
            return sendError(playerid, "Nu ai primit vreo invitatie recenta de la acel player.");

        if(!IsPlayerInRangeOfPlayer(playerid, userID, 3.0))
            return sendError(playerid, "Nu esti in apropierea acelui player.");

        if(isPlayerInTrade(playerid)) 
            return sendError(playerid, "Nu poti face asta deoarece esti deja intr-un trade.");

        if(isPlayerInTrade(userID))
            return sendError(playerid, "Acel player este deja intr-un trade.");

        if(IsPlayerInAnyVehicle(userID) || IsPlayerInAnyVehicle(playerid))
            return sendError(playerid, "Nu puteti negocia dintr-un vehicul.");

        startPlayersTrade(userID, playerid);

        SCMf(playerid, COLOR_GREEN, "(Trade): {ffffff}You accepted %s's trade invite.", GetName(userID));
        SCMf(userID, COLOR_GREEN, "(Trade): {ffffff}%s accepted your trade invite.", GetName(playerid));
    }
    else 
        return sendUsage(playerid, "/accept <playerid/name> <type>"), SCM(playerid, COLOR_GREY, "Types: dice, drugs, materials, repair, trade.");

    return 1;
}

YCMD:dice(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 10)
        return sendError(playerid, "Nu esti intr-un business de tip Casino.");

    if(playerVars[playerid][var_dice_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a face asta.", playerVars[playerid][var_dice_delay] - gettime());

    new userID, money; if(sscanf(params, "ud", userID, money))
        return sendUsage(playerid, "/dice <playerid/name> <money>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face asta asupra ta.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 2.5))
        return sendError(playerid, "Nu esti in apropierea acelui player.");

    if(money < 10000 || money > 5000000)
        return sendError(playerid, "Invalid Money! ($10.000 - $5.000.000)");

    if(GetMoney(playerid) < money && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti.");

    if(GetMoney(userID) < money && GetMilliards(userID) < 1)
        return sendError(playerid, "Acel player nu are bani suficienti.");

    if(playerVars[userID][var_dice_invited] == playerid)
        return sendError(playerid, "Asteapta ca acel player sa raspunda la invitatie.");

    playerVars[userID][var_dice_money] = money;
    playerVars[userID][var_dice_invited] = playerid;
    playerVars[playerid][var_dice_delay] = gettime() + 5;

    SCMf(playerid, COLOR_GREEN, "(Dice): {ffffff}You invited %s (%d) to dice for $%s money. Wait until he accept the invite.", GetName(userID), userID, formatNumber(money));
    SCMf(userID, COLOR_GREEN, "(Dice): {ffffff}%s (%d) invited you to dice for $%s money. Type [/accept %d dice] to accept his invite.", GetName(playerid), playerid, formatNumber(money), playerid);
    return 1;
}

YCMD:changestyle(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 9)
        return sendError(playerid, "Nu esti intr-un business de tip GYM.");

    return Dialog_Show(playerid, CHANGESTYLE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Change Fighting Style", "Type\tPrice\nNormal\t$500\nBoxing\t$500\nKung Fu\t$500\nKneehead\t$500\nGrabkick\t$500\nElbow\t$500", "Select", "Cancel");
}

YCMD:speaker(playerid, params[], help) {
    if(playerVars[playerid][var_incall] == -1)
        return sendError(playerid, "Nu esti intr-un apel.");

    playerVars[playerid][b_PHONE_SPEAKER] = !playerVars[playerid][b_PHONE_SPEAKER]; 
    return SCM(playerid, COLOR_GREY, playerVars[playerid][b_PHONE_SPEAKER] ? "* You turned on your speaker." : "* You turned off your speaker.");
}

YCMD:hud(playerid, params[], help) 
    return Dialog_Show(playerid, HUD, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Hud", "HUD\tStatus\nFPS\t%s\nHealth & Armour\t%s\nDamage Informer & Ding\t%s\nSpeedometer\t%s%s", "Select", "Exit", playerInfo[playerid][pHUDFps] ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pHUDShowAHp] ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pHUDDMG] ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pHUDSpeedometer] ? "{0AC917}mp/h" : "{0AC917}km/h", playerInfo[playerid][pAdmin] ? (playerInfo[playerid][pHUDAdminStats] ? "\nAdmin Stats\t{0AC917}enabled\n" : "\nAdmin Stats\t{990000}disabled\n") : "");

YCMD:tog(playerid, params[], help)  
    return Dialog_Show(playerid, TOG, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Tog", "Function Name\tStatus\nWalkie Talkie Chat\t%s\nVehicle Surf\t%s\nPay\t%s\nFind\t%s", "Select", "Exit", playerInfo[playerid][pFrequency] != 0 && Iter_Contains(serverFrequency[playerInfo[playerid][pFrequency]], playerid) ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pTOGSurf] ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pTOGPay] ? "{0AC917}enabled" : "{990000}disabled", playerInfo[playerid][pTOGFind] ? "{0AC917}enabled" : "{990000}disabled");

YCMD:freqmembers(playerid, params[], help) {
    if(!playerInfo[playerid][pWalkieTalkie] || playerInfo[playerid][pFrequency] == 0)
        return sendError(playerid, "Nu detii un Walkie Talkie sau nu esti pe niciuna dintre frecvente.");

    SCMf(playerid, COLOR_GREY, "* Frequency %d.0hz members:", playerInfo[playerid][pFrequency]);

    foreach(new i : serverFrequency[playerInfo[playerid][pFrequency]])
        SCMf(playerid, -1, i != Iter_Last(serverFrequency[playerInfo[playerid][pFrequency]]) ? "%s (%d)," : "%s (%d)", GetName(i), i);

    return SCMf(playerid, COLOR_GREY, "* Members found: %d", Iter_Count(serverFrequency[playerInfo[playerid][pFrequency]]));
}

YCMD:wt(playerid, params[], help) {
    if(!playerInfo[playerid][pWalkieTalkie] || playerInfo[playerid][pFrequency] == 0)
        return sendError(playerid, "Nu detii un Walkie Talkie sau nu esti pe niciuna dintre frecvente.");

    if(!Iter_Contains(serverFrequency[playerInfo[playerid][pFrequency]], playerid))
        return sendError(playerid, "Walkie Talkie-ul tau este dezactivat. [/tog]");

    if(playerVars[playerid][var_wt_delay] >= gettime())
        return 1;

    if(isnull(params))
        return sendUsage(playerid, "/wt <message>");

    gString[0] = EOS;
    format(gString, sizeof gString, "(frequency %d.0hz) %s: %s", playerInfo[playerid][pFrequency], GetName(playerid), params);

    foreach(new i : serverFrequency[playerInfo[playerid][pFrequency]]) 
        sendSplittedMessageToPlayer(i, COLOR_BROWN, COLOR_BROWN, gString);

    playerVars[playerid][var_wt_delay] = gettime() + 3;
    return 1;
}

YCMD:setfreq(playerid, params[], help) {
    if(!playerInfo[playerid][pWalkieTalkie])
        return sendError(playerid, "Nu detii un Walkie Talkie.");

    if(!isnumeric(params) || strval(params) < 0 || strval(params) > 200)
        return sendUsage(playerid, "/setfrequency <freq (0 - 200)>");

    new const freq = strval(params);

    if(freq == playerInfo[playerid][pFrequency])
        return sendError(playerid, "Esti deja pe frecventa aceasta.");

    if(playerInfo[playerid][pFrequency] != 0)
        Iter_Remove(serverFrequency[playerInfo[playerid][pFrequency]], playerid);

    playerInfo[playerid][pFrequency] = freq;
    
    va_mysql_tquery("UPDATE `server_users` SET `Frequency` = %d WHERE `ID` = %d", playerInfo[playerid][pFrequency], playerInfo[playerid][pSQLID]);

    if(freq != 0) {
        Iter_Add(serverFrequency[freq], playerid);

        return SCMf(playerid, COLOR_GREY, "* You changed your frequency to %d.0hz.", freq);
    }
    return SCM(playerid, COLOR_GREY, "* You turned off your walkie talkie.");
}

YCMD:myad(playerid, params[], help) {
    if(playerVars[playerid][var_placed_ad][0] == EOS)
        return sendError(playerid, "Nu ai plasat niciun anunt.");

    return sendSplittedMessageToPlayer(playerid, COLOR_YELLOW, COLOR_YELLOW, "Your current advert: %s", playerVars[playerid][var_placed_ad]);
}

YCMD:deletemyad(playerid, params[], help) {
    if(playerVars[playerid][var_placed_ad][0] == EOS)
        return sendError(playerid, "Nu ai plasat niciun anunt.");

    stop playerVars[playerid][var_ad_timer];

    playerVars[playerid][var_placed_ad][0] = EOS;

    return SCM(playerid, COLOR_YELLOW, "* You deleted your current advert succesfully.");
}

YCMD:ad(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 5)
        return sendError(playerid, "Nu ai nivel 5 pentru a plasa un anunt.");

    if(playerInfo[playerid][pPhoneNumber] == 0)
        return sendError(playerid, "Nu ai telefon pentru a plasa un anunt.");

    new const nearbybusiness = getNearbyBusiness(playerid, 2.0, 8);

    if(nearbybusiness == -1)
        return 1;

    if(GetMoney(playerid) < bizzInfo[nearbybusiness][bFee] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai suficienti bani. Ai nevoie de $%s pentru a plasa un anunt.", formatNumber(bizzInfo[nearbybusiness][bFee]));

    if(playerVars[playerid][var_placed_ad][0] != EOS)
        return sendError(playerid, "Ai plasat deja un anunt. Tasteaza /deletemyad pentru a sterge anuntul curent.");

    if(isnull(params))
        return sendUsage(playerid, "/ad <message>");

    new const length = strlen(params);

    if(length < 10)
        return sendError(playerid, "Anuntul tau trebuie sa aiba minim 10 caractere.");

    if(findAdvert(params) && serverVars[4][svar_Value] == 1) {
        playerInfo[playerid][pMute] = gettime() + 60;
        return SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be advertising and has been muted for 1 minute (text: %s).", GetName(playerid), params);
    }

    new const seconds = length + 15;

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, bizzInfo[nearbybusiness][bFee], false);
    va_GameTextForPlayer(playerid, "~R~-$%s", 2500, 1, formatNumber(bizzInfo[nearbybusiness][bFee]));

    strcpy(playerVars[playerid][var_placed_ad], params);

    playerVars[playerid][var_ad_timer] = defer advertTimer[seconds * 1000](playerid);

    SCMf(playerid, COLOR_GREEN, "(Info): {ffffff}You placed an advert with %d characters. This will be showed for everyone in %d seconds.", length, seconds);
    SCM(playerid, COLOR_GREEN, "(Info): {ffffff}If you want to remove your current advert write [/deletemyad], or if you want to see your advert write [/myad].");
    
    bizzInfo[nearbybusiness][bBalance] += bizzInfo[nearbybusiness][bFee];

    va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[nearbybusiness][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[nearbybusiness][bID], playerInfo[playerid][pSQLID]);

    gString[0] = EOS;
    format(gString, sizeof gString, "(Preview AD) by %s ({ffffff}%d{1C8A15}): %s", GetName(playerid), playerid, params);

    foreach(new i : serverStaff)
        sendSplittedMessageToPlayer(i, COLOR_GREEN, COLOR_GREEN, gString);

    updatePlayerQuestProgress(playerid, QUEST_TYPE_PLACEADCNN); 
    return 1;
}

YCMD:drink(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 7)
        return sendError(playerid, "Nu esti intr-un business de tip Bar.");

    return Dialog_Show(playerid, DRINK, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Buy Drink", "Type\tPrice\nWater\t$50\nBeer\t$100\nWine\t$150\nCoffee\t$50\nSoda\t$75", "Select", "Exit");
}

YCMD:eat(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 5)
        return sendError(playerid, "Nu esti intr-un business de tip Food Shop.");

    return Dialog_Show(playerid, FOOD, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Food Shop", "Type\tPrice\nPizza\t$500\nBurger\t$350\nChicken\t$450\nFries\t$300", "Select", "Exit");
}

YCMD:hangup(playerid, params[], help) {
    if(playerVars[playerid][var_incall] == -1)
        return sendError(playerid, "Nu esti intr-un apel.");

    new const userID = playerVars[playerid][var_incall];

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE); 
    SetPlayerSpecialAction(userID, SPECIAL_ACTION_STOPUSECELLPHONE);
    
    RemovePlayerAttachedObject(playerid, INDEX_PHONE); 
    RemovePlayerAttachedObject(userID, INDEX_PHONE);

    playerVars[playerid][b_PHONE_SPEAKER] = playerVars[userID][b_PHONE_SPEAKER] = false;
    playerVars[playerid][var_incall] = playerVars[userID][var_incall] = playerVars[userID][var_calls] = playerVars[playerid][var_calls] = playerVars[playerid][var_callfrom] = playerVars[userID][var_callfrom] = -1;
    
    SCM(userID, -1, "The other person ended the call.");
    SCM(playerid, -1, "You ended the call.");
    return 1;
}

YCMD:pickup(playerid, params[], help) {
    if(playerVars[playerid][var_callfrom] == -1)
        return sendError(playerid, "Nu ai primit niciun apel.");

    if(playerVars[playerid][var_incall] != -1)
        return sendError(playerid, "Esti deja intr-un apel.");

    if(playerVars[playerVars[playerid][var_callfrom]][var_incall] != -1)
        return sendError(playerid, "Acel player este intr-un apel.");

    new const userID = playerVars[playerid][var_callfrom];

    SetPlayerAttachedObject(playerid, INDEX_PHONE, 18874, 6, 0.086043, 0.027719, 0.003817, 95.232246, 178.651031, 1.691840, 1.002077, 1.000000, 1.000000);
    SetPlayerAttachedObject(userID, INDEX_PHONE, 18874, 6, 0.086043, 0.027719, 0.003817, 95.232246, 178.651031, 1.691840, 1.002077, 1.000000, 1.000000); 
    
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE); 
    SetPlayerSpecialAction(userID, SPECIAL_ACTION_USECELLPHONE);

    playerVars[playerid][var_incall] = userID;
    playerVars[userID][var_incall] = playerid; 
    playerVars[playerid][var_calls] = playerVars[playerid][var_callfrom] = playerVars[userID][var_callfrom] = playerVars[playerid][var_calls] = -1;

    SCMf(userID, COLOR_YELLOW, "* %s answered to your call.", GetName(playerid));
    SCMf(playerid, COLOR_YELLOW, "* You answered to %s call.", GetName(userID));
    return 1;
}

YCMD:call(playerid, params[], help) {
    if(playerInfo[playerid][pPhoneNumber] == 0)
        return sendError(playerid, "Nu ai un telefon.");

    if(!playerVars[playerid][b_PHONE_TURN])
        return sendError(playerid, "Nu ai telefonul pornit.");

    if(playerInfo[playerid][pPhoneCredit] < 5)
        return sendError(playerid, "Nu ai destul credit.");

    if(playerVars[playerid][var_call_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a face asta.", playerVars[playerid][var_call_delay] - gettime());

    if(playerVars[playerid][var_incall] != -1)
        return sendError(playerid, "Esti deja intr-un apel.");

    if(!isnumeric(params)) 
        return sendUsage(playerid, "/call <number>");

    new const userID = MAP_contains_val(phoneNumbers, strval(params)) ? MAP_get_val_val(phoneNumbers, strval(params)) : -1;

    if(strlen(params) > 6 || userID == -1)
        return sendError(playerid, "Acel numar de telefon este invalid.");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerVars[userID][var_incall] != -1)
        return sendError(playerid, "Acel player este intr-un apel.");

    if(!playerVars[userID][b_PHONE_TURN])
        return sendError(playerid, "Acel player are telefonul oprit.");

    playerVars[playerid][var_calls] = userID; 
    playerVars[userID][var_callfrom] = playerid;
    playerVars[playerid][var_call_delay] = gettime() + 15; 
    playerInfo[playerid][pPhoneCredit] -= 5;

    va_mysql_tquery("UPDATE `server_users` SET `PhoneCredit` = %d WHERE `ID` = %d", playerInfo[playerid][pPhoneCredit], playerInfo[playerid][pSQLID]);

    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s took the phone from pocket and dial a number.", GetName(playerid));
    sendNearbyMessage(userID, COLOR_PURPLE, 25.0, "* %s's phone is ringing...", GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s (%d) is calling you, write [/p] to answer.", GetName(playerid), playerid);
    
    PlayerPlaySound(userID, 3600, 0.0, 0.0, 0.0);
    return 1;
}

YCMD:turn(playerid, params[], help) {
    if(playerInfo[playerid][pPhoneNumber] == 0)
        return sendError(playerid, "Nu ai un telefon.");

    if(!strcmp(params, "on")) {
        if(playerVars[playerid][b_PHONE_TURN])
            return sendError(playerid, "Ai deja pornit telefonul.");

        playerVars[playerid][b_PHONE_TURN] = true;
        SCM(playerid, COLOR_GREY, "* You turned on your phone.");   
    }
    else if(!strcmp(params, "off")) {
        if(!playerVars[playerid][b_PHONE_TURN]) 
            return sendError(playerid, "Ai deja oprit telefonul.");

        playerVars[playerid][b_PHONE_TURN] = false;
        SCM(playerid, COLOR_GREY, "* You turned off your phone.");  
    }
    else 
        return sendUsage(playerid, "/turn <on/off>");

    return 1;   
}

YCMD:sms(playerid, params[], help) {
    if(playerVars[playerid][var_sms_delay] > gettime())
        return 1;

    if(playerInfo[playerid][pPhoneNumber] == 0)
        return sendError(playerid, "Nu ai un telefon.");

    if(!playerVars[playerid][b_PHONE_TURN])
        return sendError(playerid, "Nu ai telefonul pornit.");

    if(playerInfo[playerid][pPhoneCredit] < 1)
        return sendError(playerid, "Nu ai credit disponibil.");

    if(playerVars[playerid][var_incall] != -1)
        return sendError(playerid, "Nu poti face asta deoarece esti intr-un apel.");

    new number; gString[0] = EOS; if(sscanf(params, "ds[128]", number, gString))
        return sendUsage(playerid, "/sms <number> <message>");

    new const userID = MAP_contains_val(phoneNumbers, number) ? MAP_get_val_val(phoneNumbers, number) : -1;

    if((number > 999999 || number < 0) || userID == -1)
        return sendError(playerid, "Acel numar de telefon este invalid.");

    if(number == playerInfo[playerid][pPhoneNumber])
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerVars[userID][var_incall] != -1)
        return sendError(playerid, "Nu poti face asta deoarece acel player este intr-un apel.");

    if(!playerVars[userID][b_PHONE_TURN])
        return sendError(playerid, "Acel player nu are telefonul pornit.");

    playerInfo[playerid][pPhoneCredit] --;
    playerVars[playerid][var_sms_delay] = gettime() + 2;

    va_mysql_tquery("UPDATE `server_users` SET `PhoneCredit` = %d WHERE `ID` = %d", playerInfo[playerid][pPhoneCredit], playerInfo[playerid][pSQLID]);

    SCMf(userID, COLOR_YELLOW, "SMS from %s (%d): %s", GetName(playerid), playerInfo[playerid][pPhoneNumber], gString);
    SCMf(playerid, COLOR_YELLOW, "SMS sended to %s (%d): %s", GetName(userID), number, gString); 

    PlayerPlaySound(userID, 1138, 0.0, 0.0, 0.0);
    return 1;
}

YCMD:number(playerid, params[], help) {
    if(!playerInfo[playerid][pPhoneBook])
        return sendError(playerid, "Nu ai o carte de telefoane.");

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/number <playerid/name>");

    if(!IsPlayerLogged(userID)) 
        return sendError(playerid, "Acel player nu este logat.");

    if(playerInfo[userID][pPhoneNumber] != 0) 
        return SCMf(playerid, -1, "%s's phone number is: %d", GetName(userID), playerInfo[playerid][pPhoneNumber]);

    return SCMf(playerid, -1, "%s's phone number is: None", GetName(userID));
}

YCMD:buytoys(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 6)
        return 1;

    if(playerVars[playerid][var_buy_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa faci asta din nou.", playerVars[playerid][var_buy_delay] - gettime());

    return Dialog_Show(playerid, BUYTOYS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Sex Shop", "Item\tPrice\nPurple Dildo\t$500\nShort Vibrator\t$400\nLong Vibrator\t$450\nWhite Dildo\t$500\nFlowers\t$400", "Select", "Exit");
}

YCMD:buy(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 4)
        return 1;

    if(playerVars[playerid][var_buy_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa faci asta din nou.", playerVars[playerid][var_buy_delay] - gettime());

    return Dialog_Show(playerid, BUY, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: 24/7", "Item\tPrice\nPhone Book\t$500\nPhone Credit\t$1.000\nPhone\t$1.500\nWalkie Talkie\t$750\nCigarettes\t$250\nPhoto Camera\t$500\nGas Can\t$4.500\nRepair Kit\t$15.000", "Select", "Exit");
}

YCMD:clothes(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 2)
        return sendError(playerid, "Nu esti intr-un business de tip clothing store.");

    if(playerVars[playerid][b_CLOTHES_SHOW])
        return 1;

    SetPlayerPos(playerid, 218.1317,-98.5717,1005.2578);
    SetPlayerFacingAngle(playerid, 177.5475);
    SetPlayerArmedWeapon(playerid, 0);
    SetPlayerVirtualWorld(playerid, 1 + bizzInfo[playerVars[playerid][var_inbizz]][bID] + playerid);
    SetPlayerCameraPos(playerid, 213.670379, -101.292251, 1005.905700); 
    SetPlayerCameraLookAt(playerid, 217.904815, -98.668663, 1005.473937);
    SetPlayerSkin(playerid, 1);

    SelectTextDraw(playerid, -1);
    
    playerVars[playerid][var_precedentskin] = 0;

    playerTextdraws[playerid][ClothesTD][0] = CreatePlayerTextDraw(playerid, 399.000000, 97.288894, "box");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][0], 0.000000, 25.349988);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][0], 530.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][0], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][0], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][ClothesTD][0], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][0], 213);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][0], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][0], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][0], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][0], 1);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][0], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][0], 0);

    playerTextdraws[playerid][ClothesTD][1] = CreatePlayerTextDraw(playerid, 424.500000, 84.222213, "Clothes Store");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][1], 0.473000, 1.805333);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][1], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][1], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][1], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][1], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][1], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][1], 0);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][1], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][1], 0);

    playerTextdraws[playerid][ClothesTD][2] = CreatePlayerTextDraw(playerid, 394.899963, 132.944702, "");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][2], 0.000000, 0.000000);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][ClothesTD][2], true);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][2], 136.000000, 122.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][2], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][2], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][2], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][2], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][2], 0);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][2], 5);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][2], 0);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][ClothesTD][2], 1);
    PlayerTextDrawSetPreviewRot(playerid, playerTextdraws[playerid][ClothesTD][2], 0.000000, 0.000000, 87.4610-12, 1.000000);

    playerTextdraws[playerid][ClothesTD][3] = CreatePlayerTextDraw(playerid, 499.300292, 178.989196, "LD_BEAT:right");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][3], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][3], 26.000000, 27.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][3], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][3], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][3], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][3], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][3], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][3], 4);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][3], 0);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][3], 0);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][ClothesTD][3], true);

    playerTextdraws[playerid][ClothesTD][4] = CreatePlayerTextDraw(playerid, 404.394500, 178.989196, "LD_BEAT:left");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][4], 26.000000, 27.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][4], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][4], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][4], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][4], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][4], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][4], 4);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][4], 0);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][4], 0);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][ClothesTD][4], true);

    playerTextdraws[playerid][ClothesTD][5] = CreatePlayerTextDraw(playerid, 415.000000, 308.844512, "BUY");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][5], 0.320999, 1.481776);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][5], 10.000000, 27.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][5], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][5], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][ClothesTD][5], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 8388863);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][5], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][5], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][5], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][5], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][5], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][5], 0);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][ClothesTD][5], true);

    playerTextdraws[playerid][ClothesTD][6] = CreatePlayerTextDraw(playerid, 511.405883, 308.844512, "EXIT");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][6], 0.320999, 1.481776);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][ClothesTD][6], 10.000000, 31.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][6], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][6], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][ClothesTD][6], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][6], -16776961);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][6], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][6], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][6], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][6], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][6], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][6], 0);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][ClothesTD][6], true);

    playerTextdraws[playerid][ClothesTD][7] = CreatePlayerTextDraw(playerid, 463.000000, 265.911193, "SKIN ID: ~P~1~N~~W~~H~PRICE: ~G~$5.000");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][ClothesTD][7], 0.259999, 1.438222);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][ClothesTD][7], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][ClothesTD][7], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][7], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][ClothesTD][7], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][ClothesTD][7], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][ClothesTD][7], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][ClothesTD][7], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][ClothesTD][7], 0);

    if(Iter_Contains(playerSkins[playerid], 0)) {
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][7], "SKIN ID: ~P~1~N~~W~~H~OWNED");
        PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 932573439);
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][5], "SET");
    }

    for(new i = 0; i < 8; ++i) PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][i]);
    return playerVars[playerid][b_CLOTHES_SHOW] = true;
}

YCMD:transfer(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 1)
        return sendError(playerid, "Nu esti intr-un business de tip banca.");

    if(playerVars[playerid][var_bank_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti iar aceasta comanda.", playerVars[playerid][var_bank_delay] - gettime());

    if(playerInfo[playerid][pLevel] < 3)
        return sendError(playerid, "Nu ai level 3 pentru a folosi aceasta comanda.");

    new money, userID; if(sscanf(params, "ud", userID, money) || money < 1 || money >= 999999999)
        return sendUsage(playerid, "/transfer <playerid/name> <value>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(playerInfo[userID][pLevel] < 3)
        return sendError(playerid, "Acel player trebuie sa aiba minim level 3.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(playerInfo[playerid][pBank] < money && playerInfo[playerid][pBankStore] < 1)
        return sendError(playerid, "Nu ai banii necesari in banca.");

    SetPVarInt(playerid, "transferMoney", money);
    SetPVarInt(playerid, "transferPlayer", userID);

    playerVars[playerid][var_bank_delay] = gettime() + 10;

    return Dialog_Show(playerid, BANKTRANSFER, DIALOG_STYLE_MSGBOX, "SERVER: Bank Transfer", "Are you sure you want to transfer to player %s, $%s money?\nPress 'Send' to send the money, or 'Cancel' to cancel the transfer.", "Send", "Cancel", GetName(userID), formatNumber(money));
}

YCMD:withdraw(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 1)
        return sendError(playerid, "Nu esti intr-un business de tip banca.");

    if(playerVars[playerid][var_bank_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti iar aceasta comanda.", playerVars[playerid][var_bank_delay] - gettime());

    new money; if(sscanf(params, "d", money) || money < 1 || money >= 999999999)
        return sendUsage(playerid, "/withdraw <value>");

    if(playerInfo[playerid][pBank] < money && playerInfo[playerid][pBankStore] < 1)
        return sendError(playerid, "Nu ai banii necesari in banca.");
        
    addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false);
    substractBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], 0, money, false);

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `BankStore` = %d, `Bank` = %d WHERE `ID` = %d", playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], playerInfo[playerid][pSQLID]);

    playerVars[playerid][var_bank_delay] = gettime() + 10;

    return SCMf(playerid, COLOR_DARKGREEN, "* You withdrawed succesfully $%s money from your bank account. New balance: $%s.", formatNumber(money), formatMoney(playerInfo[playerid][pBankStore], playerInfo[playerid][pBank]));
}

YCMD:deposit(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 1)
        return sendError(playerid, "Nu esti intr-un business de tip banca.");

    if(playerVars[playerid][var_bank_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti iar aceasta comanda.", playerVars[playerid][var_bank_delay] - gettime());

    new money; if(sscanf(params, "d", money) || money < 1 || money >= 999999999)
        return sendUsage(playerid, "/deposit <value>");

    if(GetMoney(playerid) < money && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai banii necesari in mana.");

    if(money >= 50000)
        updatePlayerQuestProgress(playerid, QUEST_TYPE_BANKDEPOSIT);

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false);
    addBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], 0, money, false);

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `BankStore` = %d, `Bank` = %d WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], playerInfo[playerid][pSQLID]);

    playerVars[playerid][var_bank_delay] = gettime() + 10;

    return SCMf(playerid, COLOR_DARKGREEN, "* You deposited succesfully $%s money in your bank account. New balance: $%s.", formatNumber(money), formatMoney(playerInfo[playerid][pBankStore], playerInfo[playerid][pBank]));
}

YCMD:balance(playerid, params[], help) {
    if(playerVars[playerid][var_inbizz] == -1)
        return sendError(playerid, "Nu esti in interiorul unui business.");

    if(bizzInfo[playerVars[playerid][var_inbizz]][bType] != 1)
        return sendError(playerid, "Nu esti intr-un business de tip banca.");

    return SCMf(playerid, -1, "Your current balance in bank is: $%s.", formatMoney(playerInfo[playerid][pBankStore], playerInfo[playerid][pBank]));
}

YCMD:carwhisper(playerid, params[], help) {
    new const vehicleid = GetPlayerVehicleID(playerid);

    if(!vehicleid)
        return 1;

    if(isnull(params) || strlen(params) >= 128)
        return sendUsage(playerid, "/carwhisper <message>");

    new count, modelid = GetVehicleModel(vehicleid) - 400;

    gString[0] = EOS;
    format(gString, sizeof gString, "(Car Whisper) %s %s (%d): %s", GetPlayerState(playerid) == PLAYER_STATE_DRIVER ? "Driver" : "Passenger", GetName(playerid), playerid, params);

    foreach(new i : playersInVehicles) {
        if(GetPlayerVehicleID(i) != vehicleid) 
            continue;

        if(++count == aVehicleSeatsCount[modelid])
            break;

        SCM(i, COLOR_YELLOW, gString);
    }
    return 1;
}

YCMD:carradio(playerid, params[], help) {
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return sendError(playerid, "Nu esti soferul unui vehicul.");

    if(playerVars[playerid][var_radio_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti inca %d secunde pana sa folosesti iar radio-ul.", playerVars[playerid][var_radio_delay] - gettime());

    return Dialog_Show(playerid, RADIO, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Vehicle Radio", "Radio Name\tListeners\n{990000}Stop Radio\nPro FM\t%d\nRadio Taraf\t%d\nRadio Bandit\t%d\nFM Radio Manele\t%d\nRadio Popular\t%d\nRadio Coxet\t%d\nRadio Vocea Strazii\t%d\nRadio HIT\t%d\nKiss FM\t%d", "Select", "Exit", radioListeners[0], radioListeners[1], radioListeners[2], radioListeners[3], radioListeners[4], radioListeners[5], radioListeners[6], radioListeners[7], radioListeners[8]);
}

YCMD:heal(playerid, params[], help) {
    if(playerVars[playerid][var_heal_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_heal_delay] - gettime());

    if(playerVars[playerid][var_inhouse] == -1)
        return sendError(playerid, "Nu esti intr-o casa.");

    new Float:hp; 
    GetPlayerHealth(playerid, hp);

    if(hp >= 95.0) 
        return sendError(playerid, "Viata ta este deja plina.");

    SetPlayerHealth(playerid, 100.0);

    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

    playerVars[playerid][var_heal_delay] = gettime() + 15;
    return 1;
}

YCMD:pay(playerid, params[], help) {
    if(playerVars[playerid][var_pay_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_pay_delay] - gettime());

    new userID, money; if(sscanf(params, "ud", userID, money))
        return sendUsage(playerid, "/pay <playerid/name> <money>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda pe tine.");

    if(!IsPlayerLogged(userID)) 
        return sendError(playerid, "Acel player nu este conectat.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 4.5))
        return sendError(playerid, "Acel player nu este langa tine.");

    if(playerInfo[userID][pTOGPay])
        return sendError(playerid, "Acel player a dezactivat optiunea de a primii bani de la alti jucatori prin intermediul acestei comenzi.");

    if(money > 100000 || money <= 0)
        return sendError(playerid, "Invalid Money! ($0 - $100.000)");

    if(GetMoney(playerid) < money && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai suficienti bani.");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money);
    addMoney(userID, GetMilliards(userID), GetMoney(userID), 0, money);

    SCMf(playerid, COLOR_YELLOW, "* You sended $%s money to %s.", formatNumber(money), GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s sended $%s money to you.", GetName(playerid), formatNumber(money));

    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s takes out $%s in cash, and hands it to %s.", GetName(playerid), formatNumber(money), GetName(userID));

    playerVars[playerid][var_pay_delay] = gettime() + 10;

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_PAYPLAYER);
}

YCMD:sleep(playerid, params[], help) {
    if(playerVars[playerid][var_inhouse] == -1) 
        return sendError(playerid, "Nu esti intr-o casa.");

    if(playerVars[playerid][var_sleep_delay] > gettime()) 
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_sleep_delay] - gettime());

    if(playerInfo[playerid][pRent] != playerVars[playerid][var_inhouse] && playerInfo[playerid][pHouse] != playerVars[playerid][var_inhouse])
        return sendError(playerid, "Nu detii casa respectiva sau nu esti chiriasul acesteia.");

    if(IsPlayerInRangeOfPoint(playerid, 2.5, HouseInfo[playerVars[playerid][var_inhouse]][hExitX], HouseInfo[playerVars[playerid][var_inhouse]][hExitY], HouseInfo[playerVars[playerid][var_inhouse]][hExitZ]))
        return sendError(playerid, "Nu trebuie sa fii in apropierea iesirii de la casa.");

    playerVars[playerid][b_IS_SLEEPING] = !playerVars[playerid][b_IS_SLEEPING];

    TogglePlayerControllableEx(playerid, !playerVars[playerid][b_IS_SLEEPING]);
    
    if(playerVars[playerid][b_IS_SLEEPING]) {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
        SetPlayerColor(playerid, COLOR_GREY);

        SCM(playerid, COLOR_GREEN, "(Info): {ffffff}Now you are sleeping. You can't use commands, and you can't write in chat.");
    }
    else {
        SetPlayerColor(playerid, COLOR_WHITE);

        SCM(playerid, COLOR_GREEN, "(Info): {ffffff}Welcome back!");
    }

    playerVars[playerid][var_sleep_delay] = gettime() + 15;
    return 1;
}

YCMD:forum(playerid, params[], help) return SCM(playerid, COLOR_GREEN, "Forum: {ffffff}http://forum.Lurk.ro");
YCMD:panel(playerid, params[], help) return SCM(playerid, COLOR_GREEN, "Panel: {ffffff}http://panel.Lurk.ro");

YCMD:killcp(playerid, params[], help) {
    if(playerVars[playerid][var_checkpoint] == -1) 
        return sendError(playerid, "Nu ai vreun checkpoint activ.");

    if(playerVars[playerid][var_working] || playerVars[playerid][b_ARMS_DEALER_WORKING])
        return sendError(playerid, "Nu poti face asta deoarece muncesti.");

    if(isPlayerInDMVExamen(playerid))
        return sendError(playerid, "Nu poti face asta in acest moment.");

    DisablePlayerCheckpointEx(playerid);

    SCM(playerid, -1, "Your marker was deleted succesfully.");

    if(playerVars[playerid][var_findon] != -1) {
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][0]);
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][1]);

        playerVars[playerid][var_findon] = -1; 

        stop playerVars[playerid][var_find_timer]; 
    }
    return 1;
}

YCMD:para(playerid, params[], help) {
    if(!IsPlayerInRangeOfPoint(playerid, 2.5, -2232.8813,-1735.5844,480.8433))
        return 1;

    if(GetMoney(playerid) < 5000 && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti.");

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, 5000);

    GivePlayerWeapon(playerid, 46, 1); 

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYPARACHUTE);
}

YCMD:eject(playerid, params[], help) {
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return 1;

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/eject <playerid/name>");

    if(GetPlayerSurfingVehicleID(userID) != GetPlayerVehicleID(playerid) && GetPlayerVehicleID(userID) != GetPlayerVehicleID(playerid))
        return 1;

    if(userID == playerid)
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    slapPlayer(userID);

    SCMf(playerid, COLOR_YELLOW, "* You ejected %s from your vehicle.", GetName(userID));
    SCMf(userID, COLOR_YELLOW, "* %s ejected you from his vehicle.", GetName(playerid));

    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s has thrown %s out of their vehicle.", GetName(playerid), GetName(userID));
    return 1;
}

YCMD:puthelmet(playerid, params[], help) {
    if(playerVars[playerid][var_ph_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti aceasta comanda.", (playerVars[playerid][var_ph_delay] - gettime()));

    new const vehicleid = GetPlayerVehicleID(playerid);

    if(!vehicleid)
        return 1;

    new const e_vehicleModelTypes:vehicletype = getVehicleModelType(GetVehicleModel(vehicleid));

    if(vehicletype != VEHICLE_MODEL_TYPE_MOTOR_BIKE && vehicletype != VEHICLE_MODEL_TYPE_BIKE)
        return sendError(playerid, "Nu iti poti pune casca deoarece trebuie sa fii pe un motor/bicicleta.");

    playerVars[playerid][b_HELMET_ON] = !playerVars[playerid][b_HELMET_ON];

    if(playerVars[playerid][b_HELMET_ON]) { 
        SetPlayerAttachedObject(playerid, INDEX_HELMET, 18645, 2, 0.101, -0.0, 0.0, 5.50, 84.60, 83.7, 1, 1, 1);

        sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s putted the helmet on head.", GetName(playerid));
    }
    else {
        RemovePlayerAttachedObject(playerid, INDEX_HELMET);

        sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s removed the helmet from head.", GetName(playerid));
    }

    playerVars[playerid][var_ph_delay] = gettime() + 5; 
    return 1;
}

YCMD:locations(playerid, params[], help) {
    CheckPlayerCheckpoint(playerid);

    return Dialog_Show(playerid, LOCATIONS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Locations", "Type\tNumber of locations\nOther Locations\t2\nBusinesses\t%d\nServer ATMs\t16\nVending Machines\t%d\n", "Select", "Exit", serverStuff[business], sizeof vendingMachines);
}

YCMD:findhouse(playerid, params[], help) {
    CheckPlayerCheckpoint(playerid);

    if(!isnumeric(params))
        return sendUsage(playerid, "/findhouse <houseid>");

    new id = strval(params);

    if(serverStuff[houses] < id || id <= 0)
        return sendError(playerid, "Acea casa nu exista pe server.");

    id --;

    playerVars[playerid][var_checkpoint] = 1;
    SetPlayerCheckpoint(playerid, HouseInfo[id][hX], HouseInfo[id][hY], HouseInfo[id][hZ], 2.0);

    return SCMf(playerid, COLOR_YELLOW, "* Ti-a fost plasat un checkpoint pe harta catre casa cu id %d, distanta ramasa: %0.1fm.", HouseInfo[id][hID], GetPlayerDistanceFromPoint(playerid, HouseInfo[id][hX], HouseInfo[id][hY], HouseInfo[id][hZ]));
}

YCMD:spawnchange(playerid, params[], help) return Dialog_Show(playerid, SPAWNCHANGE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Spawn Change", "Type\nNormal Spawn\nHouse/Rent Spawn", "Select", "Cancel");

YCMD:newbie(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] || playerInfo[playerid][pHelper])
        return sendError(playerid, "Nu poti trimite o intrebare deoarece faci parte din staff.");

    if(!Iter_Count(serverHelpers))
        return sendError(playerid, "Nu poti trimite o intrebare deoarece nu sunt helperi conectati pe server in acest moment.");

    if(Iter_Contains(serverQuestions, playerid))
        return sendError(playerid, "Ai pus deja o intrebare, asteapta pana cand ti se va raspunde.");

    if(Iter_Count(serverQuestions) >= MAX_QUESTIONS - 1)
        return sendError(playerid, "Sunt prea multe intrebari active in momentul de fata, incearca mai tarziu.");

    if(playerInfo[playerid][pQuestionMute] > gettime())
        return sendError(playerid, "Poti folosi aceasta comanda peste %d secunde deoarece recent ai primit mute pe /n.", playerInfo[playerid][pQuestionMute] - gettime());

    if(isnull(params)) 
        return sendUsage(playerid, "/newbie <question>");

    if(strlen(params) < 4)
        return sendError(playerid, "Intrebarea ta trebuie sa fie de minim 4 caractere.");

    Iter_Add(serverQuestions, playerid);

    strcpy(playerVars[playerid][var_QuestionText], params);

    SCM(playerid, COLOR_LGREEN, "Your question has been sent. Wait until a helper will answer.");

    foreach(new i : serverStaff)
        sendSplittedMessageToPlayer(i, COLOR_LGREEN, COLOR_LGREEN, "New Question: %s (%d): %s", GetName(playerid), playerid, playerVars[playerid][var_QuestionText]);
    
    return 1;
}

YCMD:report(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] || playerInfo[playerid][pHelper])
        return sendError(playerid, "Nu poti trimite un report deoarece faci parte din staff.");

    if(!Iter_Count(serverAdmins))
        return sendError(playerid, "Nu poti trimite un report deoarece nu sunt admini conectati pe server in acest moment.");

    if(playerVars[playerid][var_report_delay] > gettime())
        return sendError(playerid, "Poti folosi aceasta comanda peste %d secunde.", playerVars[playerid][var_report_delay] - gettime());

    if(playerInfo[playerid][pReportMute] > gettime())
        return sendError(playerid, "Poti folosi aceasta comanda peste %d secunde deoarece recent ai primit mute pe /report.", playerInfo[playerid][pReportMute] - gettime());

    if(Iter_Count(serverReports) >= MAX_REPORTS - 1)
        return sendError(playerid, "Sunt prea multe report-uri active in momentul de fata, incearca mai tarziu.");

    if(Iter_Contains(serverReports, playerid))
        return sendError(playerid, "Ai deja un report activ.");

    return Dialog_Show(playerid, REPORT, DIALOG_STYLE_LIST, "SERVER: Report", "1. Sunt blocat\n2. Alta problema\n3. Raporteaza DM/Cheats", "Select", "Cancel");
}

YCMD:x(playerid, params[], help) {
    if(reportInfo[playerid][rReportConversation] != -1) {
        if(isnull(params))
            return sendUsage(playerid, "/x <text>");

        SCMf(playerid, COLOR_YELLOW, "(/x) %s: %s", GetName(playerid), params);
        SCMf(reportInfo[playerid][rReportConversation], COLOR_YELLOW, "(/x) %s: %s", GetName(playerid), params);
    }
    return 1;
}

YCMD:changepass(playerid, params[], help) {
    if(playerVars[playerid][var_changepass_delay] > gettime())
        return sendError(playerid, "Poti folosi aceasta comanda peste %d secunde.", playerVars[playerid][var_changepass_delay] - gettime());

    SetPVarInt(playerid, "changePassPass", 1);

    return Dialog_Show(playerid, CHANGEPASS, DIALOG_STYLE_PASSWORD, "SERVER: Change Pass", "Insert your current password in box below:", "Ok", "Exit");
} 

YCMD:id(playerid, params[], help) {
    new 
        userIDs[21] = {INVALID_PLAYER_ID, ...}, count;

    if(sscanf(params, "?<MATCH_NAME_PARTIAL=1>u[21]", userIDs)) 
        return sendUsage(playerid, "/id <playerid/name>");

    for(new i; userIDs[i] != INVALID_PLAYER_ID && userIDs[i] != cellmin; ++i) {
        if(!IsPlayerLogged(userIDs[i]))
            continue;

        if(playerInfo[userIDs[i]][pGroup] != 0)
        {
            if(playerInfo[userIDs[i]][pAFKSeconds] > 9)
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | Group: {%s}%s{ffffff} (rank %d) | FPS: %d | Ping: %d | Status: AFK (for %d seconds)", GetName(userIDs[i]), userIDs[i], playerInfo[userIDs[i]][pLevel], groupVariables[playerInfo[userIDs[i]][pGroup]][gColor], groupVariables[playerInfo[userIDs[i]][pGroup]][gName], playerInfo[userIDs[i]][pGroupRank], playerVars[userIDs[i]][var_FPS], GetPlayerPing(userIDs[i]), playerInfo[userIDs[i]][pAFKSeconds]);
            else 
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | Group: {%s}%s{ffffff} (rank %d) | FPS: %d | Ping: %d | Status: online", GetName(userIDs[i]), userIDs[i], playerInfo[userIDs[i]][pLevel], groupVariables[playerInfo[userIDs[i]][pGroup]][gColor], groupVariables[playerInfo[userIDs[i]][pGroup]][gName], playerInfo[userIDs[i]][pGroupRank], playerVars[userIDs[i]][var_FPS], GetPlayerPing(userIDs[i]));
        }
        else
        {
            if(playerInfo[userIDs[i]][pAFKSeconds] > 9)
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | FPS: %d | Ping: %d | Status: AFK (for %d seconds)", GetName(userIDs[i]), userIDs[i], playerInfo[userIDs[i]][pLevel], playerVars[userIDs[i]][var_FPS], GetPlayerPing(userIDs[i]), playerInfo[userIDs[i]][pAFKSeconds]);
            else 
                sendSplittedMessageToPlayer(playerid, -1, -1, "%s (%d) | Level %d | FPS: %d | Ping: %d | Status: online", GetName(userIDs[i]), userIDs[i], playerInfo[userIDs[i]][pLevel], playerVars[userIDs[i]][var_FPS], GetPlayerPing(userIDs[i]));
        }
        ++count;
    }
    return !count ? SCM(playerid, -1, "-- Nu au fost gasite rezultate.") : SCMf(playerid, -1, "-- Au fost gasite %d rezultate.", count);
}

YCMD:time(playerid, params[], help) {
    if(playerVars[playerid][var_time_delay] > gettime())
        return sendError(playerid, "Mai ai de asteptat %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_time_delay] - gettime());

    new hour, minute, second;
    gettime(hour, minute, second);

    SCMf(playerid, -1, "* Time is now %02d:%02d:%02d.", hour, minute, second);
    SCMf(playerid, -1, "* You are connected for %.0f minutes (%.0f seconds).", playerInfo[playerid][pSeconds] / 60, playerInfo[playerid][pSeconds]);
    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s raises his hand and looks down at his watch.", GetName(playerid));

    ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_watch", 4.1, 0, 0, 0, 0, 0);

    playerVars[playerid][var_time_delay] = gettime() + 15;
    return 1;
}

YCMD:shout(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 2)
        return sendError(playerid, "Iti trebuie minim level 2 pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_shout_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_shout_delay] - gettime()); 

    if(isnull(params))
        return sendUsage(playerid, "/s <message>");

    playerVars[playerid][var_shout_delay] = gettime() + 20; 

    return sendNearbyMessage(playerid, COLOR_WHITE, 45.0, "%s shouts: %s", GetName(playerid), params);
}

YCMD:me(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 2)
        return sendError(playerid, "Iti trebuie minim level 2 pentru a folosi aceasta comanda.");

    if(playerVars[playerid][var_me_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana sa folosesti iar aceasta comanda.", playerVars[playerid][var_me_delay] - gettime());

    if(isnull(params))
        return sendUsage(playerid, "/me <message>");

    playerVars[playerid][var_me_delay] = gettime() + 20;

    return sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "* %s %s.", GetName(playerid), params);
}

YCMD:whisper(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 3)
        return sendError(playerid, "Iti trebuie minim level 3 pentru a folosi aceasta comanda.");

    gString[0] = EOS; new userID;

    if(sscanf(params, "us[128]", userID, gString))
        return sendUsage(playerid, "/whisper <playerid/name> <message>");

    if(userID == playerid) 
        return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    if(!IsPlayerInRangeOfPlayer(playerid, userID, 5.0))
        return sendError(playerid, "Nu esti in apropierea acelui player.");

    SCMf(playerid, COLOR_LIGHTBLUE, "(Whisper) sent to %s (%d): %s", GetName(userID), userID, gString);
    SCMf(userID, COLOR_LIGHTBLUE, "(Whisper) from %s (%d): %s", GetName(playerid), playerid, gString);
    return 1;
}

YCMD:engine(playerid, params[], help) {
    new const vehicleid = GetPlayerVehicleID(playerid); 
    
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && getVehicleModelType(GetVehicleModel(vehicleid)) != VEHICLE_MODEL_TYPE_BIKE) {
        if(vehicleVars[vehicleid][var_carFuel] <= 1) 
            return sendError(playerid, "Acest vehicul nu are combustibil suficient pentru a-l putea pornii.");

        if(playerVars[playerid][var_engine_delay] > gettime())
            return sendError(playerid, "Mai ai de asteptat %d secunde pentru a face asta.", (playerVars[playerid][var_engine_delay] - gettime()));

        vehicleVars[vehicleid][var_carEngine] = !vehicleVars[vehicleid][var_carEngine];

        SetVehicleParamsEx(vehicleid, vehicleVars[vehicleid][var_carEngine], -1, -1, -1, -1, -1, -1);

        if(playerVars[playerid][var_jobvehicle] == vehicleid) 
            SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);

        sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "* %s %s the engine of his vehicle %s.", GetName(playerid), !vehicleVars[vehicleid][var_carEngine] ? "stops" : "starts", aVehicleNames[GetVehicleModel(vehicleid)-400]); 

        playerVars[playerid][var_engine_delay] = gettime() + 5;
    }
    return 1;
}

YCMD:lights(playerid, params[], help) {
    new const vehicleid = GetPlayerVehicleID(playerid); 
    
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && getVehicleModelType(GetVehicleModel(vehicleid)) != VEHICLE_MODEL_TYPE_BIKE) {
        vehicleVars[vehicleid][var_carLights] = !vehicleVars[vehicleid][var_carLights];

        SetVehicleParamsEx(vehicleid, -1, vehicleVars[vehicleid][var_carLights], -1, -1, -1, -1, -1);
    
        if(playerVars[playerid][var_jobvehicle] == vehicleid) 
            SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);
    }
    return 1;
}

YCMD:showlicenses(playerid, params[], help) {
    new id; if(sscanf(params, "u", id)) 
        return sendUsage(playerid, "/showlicenses <playerid/name>");

    if(!IsPlayerLogged(id))
        return sendError(playerid, "Invalid ID!");
    
    if(!IsPlayerInRangeOfPlayer(playerid, id, 5.0))
        return sendError(playerid, "Nu esti langa player-ul respectiv.");

    if(id == playerid)
        return sendError(playerid, "Nu iti poti arata singur licentele.");

    showLicenses(playerid, id);

    SCMf(playerid, COLOR_YELLOW, "* You showed your licenses to %s.", GetName(id));
    SCMf(id, COLOR_YELLOW, "* %s showed his licenses to you.", GetName(playerid));
    return 1;
}

YCMD:licenses(playerid, params[], help) return showLicenses(playerid, playerid);

YCMD:admins(playerid, params[], help) {
    SCM(playerid, COLOR_GREEN, "|________________| {ffffff}Admins{1C8A15} |____________|");

    foreach(new i : serverAdmins) {
        if(playerInfo[i][pAdmin] < 7) 
            SCMf(playerid, COLOR_WHITE, "%s (%d) - admin level %d%s", GetName(i), i, playerInfo[i][pAdmin], playerVars[i][b_ADMIN_DUTY] ? " - on-duty" : "");
    
        else SCMf(playerid, COLOR_WHITE, "%s (%d) - %s%s", GetName(i), i, playerInfo[i][pAdmin] == 7 ? "owner" : "scripter", playerVars[i][b_ADMIN_DUTY] ? " - on-duty" : "");
    }
    
    SCM(playerid, COLOR_GREEN, "_______________________________________________");
    SCMf(playerid, COLOR_WHITE, "There are %d admins online. If you have any problems, use /report.", Iter_Count(serverAdmins));
    return 1;
}

YCMD:helpers(playerid, params[], help) {
    SCM(playerid, COLOR_GREEN, "|________________| {ffffff}Helpers{1C8A15} |____________|");
    
    foreach(new i : serverHelpers) 
        SCMf(playerid, COLOR_WHITE, "%s (%d) - helper level %d%s", GetName(i), i, playerInfo[i][pHelper], playerVars[i][b_HELPER_DUTY] ? " - on-duty" : "");
    
    SCM(playerid, COLOR_GREEN, "_______________________________________________");
    SCMf(playerid, COLOR_WHITE, "There are %d helpers online. If you have any questions, use /newbie.", Iter_Count(serverHelpers));
    return 1;
}

YCMD:stats(playerid, params[], help) return showPlayerStatsToPlayer(playerid, playerid);

YCMD:buylevel(playerid, params[], help) {
    if(GetMoney(playerid) < (playerInfo[playerid][pLevel] * 250) && GetMilliards(playerid) < 1)
        return sendError(playerid, "Ai nevoie de $%s bani pentru a avansa in nivel.", formatNumber(playerInfo[playerid][pLevel] * 250));

    new 
        respect = (playerInfo[playerid][pLevel] * 3),
        money = (playerInfo[playerid][pLevel] * 250);

    if(playerInfo[playerid][pRespectPoints] < respect)
        return sendError(playerid, "Mai ai nevoie de %d puncte de respect pentru a avansa in nivel.", respect-playerInfo[playerid][pRespectPoints]);

    playerInfo[playerid][pRespectPoints] -= respect;
    playerInfo[playerid][pLevel] ++;

    SetPlayerScore(playerid, playerInfo[playerid][pLevel]);

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, money, false);

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `Level` = %d, `RespectPoints` = %d WHERE `ID` = %d", playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], playerInfo[playerid][pLevel], playerInfo[playerid][pRespectPoints], playerInfo[playerid][pSQLID]);
    
    SCMf(playerid, COLOR_YELLOW, "Congratulations! You have now level %d.", playerInfo[playerid][pLevel]);
    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s upgraded his level to %d.", GetName(playerid), playerInfo[playerid][pLevel]);

    updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYLEVEL);

    if(playerInfo[playerid][pReferralSQLID] != -1) {
        if(MAP_contains_val(playersSQLID, playerInfo[playerid][pReferralSQLID])) {
            giveReferralPlayerRewards(playerid, MAP_get_val_val(playersSQLID, playerInfo[playerid][pReferralSQLID]));
        }
        else {
            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "SELECT `ReferralRespectPoints`, `ReferralCash` FROM `server_users` WHERE `ID` = %d", playerInfo[playerid][pReferralSQLID]);
            mysql_tquery(SQL, gQuery, "giveReferralPlayerRewards", "dd", playerid, -1);
        }
    }

    if(playerInfo[playerid][pLevel] == 5) {
        givePlayerRandomQuests(playerid); 
        va_mysql_tquery("UPDATE `server_users` SET `DayQuest` = %d, `Quests` = '%d|%d|%d|%d|%d|%d' WHERE `ID` = %d", getdate(), playerInfo[playerid][pQuestType][0], playerInfo[playerid][pQuestType][1], playerInfo[playerid][pQuestType][2], playerInfo[playerid][pQuestProgress][0], playerInfo[playerid][pQuestProgress][1], playerInfo[playerid][pQuestProgress][2], playerInfo[playerid][pSQLID]);

        SCM(playerid, COLOR_YELLOW, "* Congratuations! You unlocked daily quests. Use [/quests] to see your quests for today.");
    }
    return 1;
}