// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_JOBS 10

// ------------------------------------- //
//             Variables                 //
// ------------------------------------- //

enum e_jInfo {
    j_ID, j_Name[32], j_Level, j_Pickup, j_Vehicle, j_vColorOne, j_vColorTwo,
    Float: j_X, Float: j_Y, Float: j_Z, Float: j_wX, Float: j_wY, Float: j_wZ, Float:j_vX, Float: j_vY, Float: j_vZ, Float: j_vAngle
}

new jobInfo[MAX_JOBS][e_jInfo];

// ------------------------------------- //
//         Load Query Function           //
// ------------------------------------- //

query_function load_jobs() {
    serverStuff[jobs] = cache_num_rows();

    if(!serverStuff[jobs])
        return print("[MYSQL INFO] No jobs were found in the database.");

    for(new j = 0; j < serverStuff[jobs]; j++) {
        jobInfo[j][j_ID] = j + 1;

        jobInfo[j][j_Level] = cache_get_field_content_int(j, "Level");
        jobInfo[j][j_Vehicle] = cache_get_field_content_int(j, "Vehicle");
        jobInfo[j][j_vColorOne] = cache_get_field_content_int(j, "vColorOne");
        jobInfo[j][j_vColorTwo] = cache_get_field_content_int(j, "vColorTwo");
        
        jobInfo[j][j_X] = cache_get_field_content_float(j, "X");
        jobInfo[j][j_Y] = cache_get_field_content_float(j, "Y");
        jobInfo[j][j_Z] = cache_get_field_content_float(j, "Z");
        jobInfo[j][j_wX] = cache_get_field_content_float(j, "wX");
        jobInfo[j][j_wY] = cache_get_field_content_float(j, "wY");
        jobInfo[j][j_wZ] = cache_get_field_content_float(j, "wZ");
        jobInfo[j][j_vX] = cache_get_field_content_float(j, "vSpawnX");
        jobInfo[j][j_vY] = cache_get_field_content_float(j, "vSpawnY");
        jobInfo[j][j_vZ] = cache_get_field_content_float(j, "vSpawnZ");
        jobInfo[j][j_vAngle] = cache_get_field_content_float(j, "vSpawnAngle");

        cache_get_field_content(j, "Name", jobInfo[j][j_Name], SQL, 32);
    
        gString[0] = EOS;
        format(gString, sizeof gString, "Job {1C8A15}#%d\n{FFFFFF}Job Name: {1C8A15}%s\n{FFFFFF}Needed Level: {1C8A15}%d\n{FFFFFF}Type {1C8A15}[/getjob]{FFFFFF} to get this job.", j + 1, jobInfo[j][j_Name], jobInfo[j][j_Level]);
        CreateDynamic3DTextLabel(gString, -1, jobInfo[j][j_X], jobInfo[j][j_Y], jobInfo[j][j_Z], 3.5);

        jobInfo[j][j_Pickup] = CreateDynamicPickup(1275, 23, jobInfo[j][j_X], jobInfo[j][j_Y], jobInfo[j][j_Z], 0, 0);
        pickupInfo[jobInfo[j][j_Pickup]][pk_Job] = j;
    }
    return printf("[MYSQL LOADED] Jobs loaded: %d", serverStuff[jobs]);
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:jobs(playerid, params[], help) {
    gDialog[0] = EOS;

    gDialog = "Job\tDistance\n";

    for(new i = 0; i < serverStuff[jobs]; ++i)
        format(gDialog, sizeof gDialog, "%s%s\t%0.2fkm\n", gDialog, jobInfo[i][j_Name], GetPlayerDistanceFromPoint(playerid, jobInfo[i][j_X], jobInfo[i][j_Y], jobInfo[i][j_Z])/1000);

    return Dialog_Show(playerid, JOBS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Jobs", gDialog, "Select", "Exit");
}

YCMD:getjob(playerid, params[], help) {
    if(playerInfo[playerid][pJob])
        return sendError(playerid, "Ai deja un job. Demisioneaza folosind [/quitjob].");

    new 
        nearbyPickup[1] = -1, Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerid, X, Y, Z); 
    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, 2.0);

    if(nearbyPickup[0] == -1 || pickupInfo[nearbyPickup[0]][pk_Job] == -1)
        return 1;

    if(playerInfo[playerid][pLevel] < jobInfo[pickupInfo[nearbyPickup[0]][pk_Job]][j_Level])
        return sendError(playerid, "Nu ai level-ul necesar. Ai nevoie de minim level %d.", jobInfo[pickupInfo[nearbyPickup[0]][pk_Job]][j_Level]);

    playerInfo[playerid][pJob] = pickupInfo[nearbyPickup[0]][pk_Job] + 1;
    va_mysql_tquery("UPDATE `server_users` SET `Job` = %d WHERE `ID` = %d", playerInfo[playerid][pJob], playerInfo[playerid][pSQLID]);

    SCMf(playerid, COLOR_GREEN, "(Job Info): {FFFFFF}Congratulations, you have now the %s (id: %d) job. Use the command [/help] ...", jobInfo[pickupInfo[nearbyPickup[0]][pk_Job]][j_Name], playerInfo[playerid][pJob]);
    SCM(playerid, -1, "... and select the section named 'Jobs' to see the available commands for this job.");
    return 1;
} 

YCMD:quitjob(playerid, params[], help) {
    if(!playerInfo[playerid][pJob])
        return sendError(playerid, "Nu ai un job in momentul de fata.");

    if(playerVars[playerid][var_working])
        return sendError(playerid, "Nu poti face asta deoarece muncesti. Tasteaza [/stopwork].");

    if(playerVars[playerid][b_FISHING] || playerVars[playerid][b_ARMS_DEALER_WORKING] || (playerInfo[playerid][pJob] == 8 && IsValidDynamic3DTextLabel(playerLabels[playerid][l_drugs_dealer])))
        return sendError(playerid, "Nu poti face asta in momentul de fata.");

    playerInfo[playerid][pJob] = 0;
    va_mysql_tquery("UPDATE `server_users` SET `Job` = 0 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);

    return SCM(playerid, COLOR_GREEN, "(Job Info): {FFFFFF}You resigned from your job succesfully.");
}

YCMD:work(playerid, params[], help) {
    if(playerVars[playerid][var_work_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a folosi din nou aceasta comanda.", playerVars[playerid][var_work_delay] - gettime());

    if(playerVars[playerid][var_working])
        return sendError(playerid, "Nu poti face asta deoarece muncesti deja.");

    if(!playerInfo[playerid][pJob])
        return sendError(playerid, "Nu ai un job.");

    if(GetPlayerVehicleID(playerid))
        return sendError(playerid, "Nu poti folosi aceasta comanda daca esti intr-un vehicul.");

    CheckPlayerCheckpoint(playerid);

    new const job = playerInfo[playerid][pJob] - 1;

    if(jobInfo[job][j_wX] == 0.0) 
        return 1;

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, jobInfo[job][j_wX], jobInfo[job][j_wY], jobInfo[job][j_wZ])) { 
        SetPlayerCheckpoint(playerid, jobInfo[job][j_wX], jobInfo[job][j_wY], jobInfo[job][j_wZ], 4.0); 
        playerVars[playerid][var_checkpoint] = 1;
        return sendError(playerid, "Nu esti la locatia corecta pentru a incepe munca. Ti-a fost plasat un checkpoint unde poti tasta [/work].");
    }

    if(playerInfo[playerid][pDrivingLicense] <= 0)
        return sendError(playerid, "Ai nevoie de licenta de condus pentru a muncii la acest job.");

    playerVars[playerid][var_jobvehicle] = createVehicle(jobInfo[job][j_Vehicle], jobInfo[job][j_vX], jobInfo[job][j_vY], jobInfo[job][j_vZ], jobInfo[job][j_vAngle], jobInfo[job][j_vColorOne], jobInfo[job][j_vColorTwo], -1);
    PutPlayerInVehicle(playerid, playerVars[playerid][var_jobvehicle], 0); 
    SetVehicleParamsEx(playerVars[playerid][var_jobvehicle], 1, 0, 0, 1, 0, 0, 0);
    SetVehicleParamsForPlayer(playerVars[playerid][var_jobvehicle], playerid, 0, 0);

    switch(playerInfo[playerid][pJob]) {
        case 3: {
            playerTextdraws[playerid][JobTD] = CreatePlayerTextDraw(playerid, 552.005493, 198.711120, "~R~You must be in the work area.");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][JobTD], 0.145500, 0.977777);
            PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][JobTD], 0.000000, 174.000000);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][JobTD], -1);
            PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][JobTD], 210);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][JobTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][JobTD], 0);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][JobTD]); 

            playerVars[playerid][var_jobseconds] = 60;

            playerVars[playerid][var_jobtimer] = repeat farmerTimer(playerid);
        }
        case 4: {
            new const randcp = random(sizeof firePositions);
            SetPlayerCheckpoint(playerid, firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2], 2.5);
            playerVars[playerid][var_checkpoint] = 4;

            playerVars[playerid][var_jobobject] = CreateDynamicObject(18688, firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2]-2, 0.0, 0.0, 0.0, _, _, playerid);

            GivePlayerWeapon(playerid, 42, 99999);
            SetPlayerSkin(playerid, 279);
            
            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and extinguish the fire. Distance: %0.2fm.", GetPlayerDistanceFromPoint(playerid, firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2]));
        }
        case 5: {
            playerTextdraws[playerid][JobTD] = CreatePlayerTextDraw(playerid, 552.005493, 198.711120, "~W~Go in the red dots marked on map.~N~~N~Checkpoint: 0/53");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][JobTD], 0.145500, 0.977777);
            PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][JobTD], 0.000000, 174.000000);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][JobTD], -1);
            PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][JobTD], 210);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][JobTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][JobTD], 0);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][JobTD]);

            SetPlayerRaceCheckpoint(playerid, 0, 1736.0258,-2256.4021,-2.7565,1795.6776,-2282.5588,9.3188, 3.0);

            playerVars[playerid][var_busdrivercheckpoint] = 0; 
            playerVars[playerid][var_checkpoint] = 5;
        }
        case 6: {
            new const randcp = random(sizeof deerPositions); 
            SetPlayerMapIcon(playerid, 0, deerPositions[randcp][0], deerPositions[randcp][1], deerPositions[randcp][2], 56, -1, MAPICON_GLOBAL);
            playerVars[playerid][var_jobobject] = CreateDynamicObject(19315, deerPositions[randcp][0], deerPositions[randcp][1], deerPositions[randcp][2], deerPositions[randcp][3], deerPositions[randcp][4], deerPositions[randcp][5], _, _, playerid);

            SetPVarInt(playerid, "deerNumber", randcp);
            
            GivePlayerWeapon(playerid, 33, 99999);

            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and kill the deer marked on map. Distance: %0.2fm.", GetPlayerDistanceFromPoint(playerid, deerPositions[randcp][0], deerPositions[randcp][1], deerPositions[randcp][2]));
        }
        case 7: {
            new const randcp = random(sizeof courierLoadingLocations);
            
            playerTextdraws[playerid][JobTD] = CreatePlayerTextDraw(playerid, 552.005493, 198.711120, "~W~Go and load stuff in your truck.");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][JobTD], 0.145500, 0.977777);
            PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][JobTD], 0.000000, 174.000000);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][JobTD], -1);
            PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][JobTD], 210);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][JobTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][JobTD], 2);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][JobTD], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][JobTD], 0);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][JobTD]); 
            
            playerVars[playerid][var_checkpoint] = 7;
            SetPlayerCheckpoint(playerid, courierLoadingLocations[randcp][0], courierLoadingLocations[randcp][1], courierLoadingLocations[randcp][2], 3.5);
        }
        case 10: {
            showPlayerTruckerLocations(playerid); 
            TogglePlayerControllableEx(playerid, false);
        }
    }
    DisableRemoteVehicleCollisions(playerid, true); 

    playerVars[playerid][var_jobtimerchecks] = repeat jobTimerChecks(playerid);

    playerVars[playerid][var_work_delay] = gettime() + 15;
    playerVars[playerid][var_jobtime] = gettime(); 
    playerVars[playerid][var_working] = vehicleVars[playerVars[playerid][var_jobvehicle]][var_carLocked] = vehicleVars[playerVars[playerid][var_jobvehicle]][var_carEngine] = true;
    return 1;
}

YCMD:stopwork(playerid, params[], help) {
    if(playerVars[playerid][b_ARMS_DEALER_WORKING]) {
        playerVars[playerid][var_arms_dealer_materials] = playerVars[playerid][var_arms_dealer_money] = -1;
        playerVars[playerid][b_ARMS_DEALER_WORKING] = false;

        DisablePlayerCheckpointEx(playerid);

        return SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}You stopped work.");
    }

    if(!playerVars[playerid][var_working])
        return sendError(playerid, "Nu poti face asta deoarece nu muncesti.");

    if(playerVars[playerid][b_ACTIVE_TIMER])
        return sendError(playerid, "Nu poti face asta acum.");

    stopWork(playerid);

    return SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}You stopped work.");
}

YCMD:gotojob(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai acces la aceasta comanda.");

    gDialog = "Job\tDistance\n";

    for(new i = 0; i < serverStuff[jobs]; ++i)
        format(gDialog, sizeof gDialog, "%s%s\t%0.2fkm\n", gDialog, jobInfo[i][j_Name], GetPlayerDistanceFromPoint(playerid, jobInfo[i][j_X], jobInfo[i][j_Y], jobInfo[i][j_Z])/1000);

    return Dialog_Show(playerid, GOTOJOB, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Goto Job", gDialog, "Select", "Cancel");
}

YCMD:skills(playerid, params[], help) {
    static enum s_l_e_jobsSkillsStructure {
        jobName[32],
        e_pInfo:jobSkillIdx
    }

    static const jobsSkillsStructure[][s_l_e_jobsSkillsStructure] = {
        {"Farmer", pFarmerSkill}, 
        {"Fisherman", pFishermanSkill}, 
        {"Fireman", pFiremanSkill}, 
        {"Bus Driver", pBusDriverSkill}, 
        {"Hunter", pHunterSkill}, 
        {"Courier", pCourierSkill}, 
        {"Drugs Dealer", pDrugsDealerSkill}, 
        {"Arms Dealer", pArmsDealerSkill}, 
        {"Trucker", pTruckerSkill}
    };

    SCM(playerid, -1, "--- Your job skills:");

    for(new i = 0; i < sizeof jobsSkillsStructure; ++i) {
       SCMf(playerid, -1, playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] > 60 ? "-- %s: skill %d (%d shifts), max. skill." : "-- %s: skill %d (%d shifts), %d for next skill.", jobsSkillsStructure[i][jobName], playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] <= 30 ? 1 : playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] <= 60 ? 2 : 3, playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]], playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] <= 30 ? 31 - playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] : playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] <= 60 ? 61 - playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]] : 91 - playerInfo[playerid][jobsSkillsStructure[i][jobSkillIdx]]); 
    }

    return 1;
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:GOTOJOB(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    SetPlayerPos(playerid, jobInfo[listitem][j_X], jobInfo[listitem][j_Y], jobInfo[listitem][j_Z]); 
    
    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s has teleported to job %s (id: %d).", GetName(playerid), jobInfo[listitem][j_Name], jobInfo[listitem][j_ID]);
}

Dialog:JOBS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    CheckPlayerCheckpoint(playerid);

    playerVars[playerid][var_checkpoint] = 1;
    SetPlayerCheckpoint(playerid, jobInfo[listitem][j_X], jobInfo[listitem][j_Y], jobInfo[listitem][j_Z], 2.0); 

    return SCMf(playerid, COLOR_GREEN, "(Jobs): {FFFFFF}A checkpoint has been placed to job %s. Distance: %0.2fkm.", jobInfo[listitem][j_Name], GetPlayerDistanceFromPoint(playerid, jobInfo[listitem][j_X], jobInfo[listitem][j_Y], jobInfo[listitem][j_Z])/1000);
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

stopWork(const playerid) {
    playerTextDrawDestroy(playerid, playerTextdraws[playerid][JobTD]);

    DestroyVehicle(playerVars[playerid][var_jobvehicle]); 
    DestroyVehicle(playerVars[playerid][var_trucker_trailer]); 

    DestroyDynamicObject(playerVars[playerid][var_jobobject]); 

    if(GetPlayerSkin(playerid) != playerInfo[playerid][pSkin])
        SetPlayerSkin(playerid, playerInfo[playerid][pSkin]);

    Iter_Remove(truckersChat, playerid);

    stop playerVars[playerid][var_jobtimer];
    stop playerVars[playerid][var_drugs_dealer_timer];
    stop playerVars[playerid][var_jobtimerchecks];

    ResetPlayerWeapons(playerid);
    TogglePlayerControllableEx(playerid, true); 
    DisableRemoteVehicleCollisions(playerid, false); 
    DisablePlayerCheckpointEx(playerid); 
    RemovePlayerMapIcon(playerid, 0);
    RemovePlayerAttachedObject(playerid, INDEX_JOB);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

    playerVars[playerid][var_working] = false; 
    playerVars[playerid][var_jobexitvehicletime] = playerVars[playerid][var_jobseconds] = playerVars[playerid][var_courierhouse] = playerVars[playerid][var_jobvehicle] = playerVars[playerid][var_trucker_trailer] = playerVars[playerid][var_jobobject] = -1; 
    DeletePVar(playerid, "deerNumber"); 
    return 1;
}

giveJobMoney(const playerid, &playerskill, const bonus = 0) {
    new money; 

    switch(playerskill) {
        case 0..30: money = 4000 + random(2999) + bonus;
        case 31..60: money = 6000 + random(2999) + bonus;
        default: money = 9000 + random(2999) + bonus;
    }

    if(playerskill < 90) 
        ++playerskill; 

    addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false);
    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `FishermanSkill` = %d, `FarmerSkill` = %d, `FiremanSkill` = %d, `BusDriverSkill` = %d, `HunterSkill` = %d, `CourierSkill` = %d, `TruckerSkill` = %d WHERE `ID` = %d", playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], playerInfo[playerid][pFishermanSkill], playerInfo[playerid][pFarmerSkill], playerInfo[playerid][pFiremanSkill], playerInfo[playerid][pBusDriverSkill], playerInfo[playerid][pHunterSkill], playerInfo[playerid][pCourierSkill], playerInfo[playerid][pTruckerSkill], playerInfo[playerid][pSQLID]);
    return money;
}

// ------------------------------------- //
//              Hooks                    //
// ------------------------------------- //

hook OP_StateChange(playerid, newstate, oldstate) {
    switch(newstate) {
        case PLAYER_STATE_ONFOOT: {
            if(playerVars[playerid][var_working]) { 
                switch(playerInfo[playerid][pJob]) {
                    case 3, 5: stopWork(playerid);
                    default: {
                        if(getPlayerLastVehicle(playerid) == playerVars[playerid][var_jobvehicle]) {
                            playerVars[playerid][var_jobexitvehicletime] = gettime() + 180; 
                            SCM(playerid, COLOR_GREEN, "(Job): {ffffff}You have 180 seconds to enter back in job vehicle.");
                        }
                    }
                } 
            }
        }
        case PLAYER_STATE_DRIVER: {
            if(playerVars[playerid][var_working] && GetPlayerVehicleID(playerid) == playerVars[playerid][var_jobvehicle]) 
                playerVars[playerid][var_jobexitvehicletime] = -1;
        }
    }
    return 1;
}

hook OP_ShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z) {
    if(playerInfo[playerid][pJob] == 6 && playerVars[playerid][var_working] && weaponid == 33 && objectid == playerVars[playerid][var_jobobject] && playerVars[playerid][var_checkpoint] != 6) {
        new const deerNumber = GetPVarInt(playerid, "deerNumber");

        if(GetPlayerDistanceFromPoint(playerid, deerPositions[deerNumber][0], deerPositions[deerNumber][1], deerPositions[deerNumber][2]) < 35.0) {
            new const rand = random(sizeof deerPositions); 

            SetPVarInt(playerid, "deerNumber", rand);

            SetDynamicObjectPos(playerVars[playerid][var_jobobject], deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2]);
            SetDynamicObjectRot(playerVars[playerid][var_jobobject], deerPositions[rand][3], deerPositions[rand][4], deerPositions[rand][5]);
            SetPlayerMapIcon(playerid, 0, deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2], 56, -1, MAPICON_GLOBAL);

            SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}Your distance from deer was too small and he run away."); 
            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and kill next deer marked on map. Distance: %0.2fm.", GetPlayerDistanceFromPoint(playerid, deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2]));
            return 1;
        }

        SetDynamicObjectPos(playerVars[playerid][var_jobobject], deerPositions[deerNumber][6], deerPositions[deerNumber][7], deerPositions[deerNumber][8]);
        SetDynamicObjectRot(playerVars[playerid][var_jobobject], deerPositions[deerNumber][9], deerPositions[deerNumber][10], deerPositions[deerNumber][11]);
        SetPlayerCheckpoint(playerid, deerPositions[deerNumber][6], deerPositions[deerNumber][7], deerPositions[deerNumber][8], 2.5); 
        playerVars[playerid][var_checkpoint] = 6;
        
        RemovePlayerMapIcon(playerid, 0);
        
        SCM(playerid, COLOR_GREEN, "(Job): {FFFFFF}You killed succesfully that deer. Go and skin it.");
    }
    return 1;
}

// ------------------------------------- //
//              Timer                    //
// ------------------------------------- //

timer jobTimer[5000](playerid, job) {
    if(!playerVars[playerid][var_working])
        return 1;

    if(Dialog_IsOpened(playerid))
        Dialog_Close(playerid);

    TogglePlayerControllableEx(playerid, true); 

    playerVars[playerid][b_ACTIVE_TIMER] = false;

    switch(job) {
        case 4: {
            new const randcp = random(sizeof firePositions);

            SetPlayerCheckpoint(playerid, firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2], 2.5);
            playerVars[playerid][var_checkpoint] = 4;

            SetDynamicObjectPos(playerVars[playerid][var_jobobject], firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2]-2);

            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}You extinguished this fire succesfully and you received $%s money. Time elapsed: %s.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pFiremanSkill])), CalculateTime(gettime() - playerVars[playerid][var_jobtime]));
            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and extinguish the next fire. Distance: %0.2fm.", GetPlayerDistanceFromPoint(playerid, firePositions[randcp][0], firePositions[randcp][1], firePositions[randcp][2]));

            playerVars[playerid][var_jobtime] = gettime();
        }
        case 5: {
            ++playerVars[playerid][var_busdrivercheckpoint];

            switch(playerVars[playerid][var_busdrivercheckpoint]) {
                case 53: {
                    TogglePlayerControllableEx(playerid, true);
                    playerVars[playerid][b_ACTIVE_TIMER] = false;

                    SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}You received $%s money for your work. Time elapsed: %s.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pBusDriverSkill], 150000)), CalculateTime(gettime() - playerVars[playerid][var_jobtime])); 

                    return stopWork(playerid);
                }
                case 52: {
                    SetPlayerRaceCheckpoint(playerid, 1, busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][0], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][1], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][2], 0.0, 0.0, 0.0, 3.0);
                }
                default: {
                    SetPlayerRaceCheckpoint(playerid, 0, busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][0], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][1], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint]][2], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint] + 1][0], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint] + 1][1], busDriverCheckpoints[playerVars[playerid][var_busdrivercheckpoint] + 1][2], 3.0);
                }
            }

            gString[0] = EOS; 
            format(gString, sizeof gString, "~W~Go in the red dots marked on map.~N~~N~Checkpoint: %d/53", playerVars[playerid][var_busdrivercheckpoint]);
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], gString);
        }
        case 6: {
            new const rand = random(sizeof deerPositions); 

            SetPVarInt(playerid, "deerNumber", rand);

            SetDynamicObjectPos(playerVars[playerid][var_jobobject], deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2]);
            SetDynamicObjectRot(playerVars[playerid][var_jobobject], deerPositions[rand][3], deerPositions[rand][4], deerPositions[rand][5]);
            SetPlayerMapIcon(playerid, 0, deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2], 56, -1, MAPICON_GLOBAL);

            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}You received $%s money for your work. Time elapsed: %s.", formatNumber(giveJobMoney(playerid, playerInfo[playerid][pHunterSkill])), CalculateTime(gettime() - playerVars[playerid][var_jobtime]));
            SCMf(playerid, COLOR_GREEN, "(Job): {FFFFFF}Go and kill next deer marked on map. Distance: %0.2fm.", GetPlayerDistanceFromPoint(playerid, deerPositions[rand][0], deerPositions[rand][1], deerPositions[rand][2]));

            playerVars[playerid][var_jobtime] = gettime();
        }
        case 7: {
            new const randcp = random(serverStuff[houses]); 

            playerVars[playerid][var_courierhouse] = randcp;

            SetPlayerCheckpoint(playerid, HouseInfo[randcp][hX], HouseInfo[randcp][hY], HouseInfo[randcp][hZ], 3.5); 
            playerVars[playerid][var_checkpoint] = 8;

            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][JobTD], "Go and transport all stuff loaded.~N~Stuff: 6/6");
        }
    }
    return 1;
}