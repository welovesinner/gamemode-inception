// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//             Variables                 //
// ------------------------------------- //

static const Float:examenCheckpoints[][] = {
    {1198.86, -1849.58, 13.1202}, {1144.54, -1849.59, 13.11}, {1073.96, -1849.72, 13.1185}, {1050.35, -1814.62, 13.3622}, {1039.92, -1777.39, 13.1369}, {1039.73, -1727.84, 13.1099},
    {1070.82, -1714.84, 13.1099}, {1135.1, -1714.77, 13.3528}, {1152.6, -1669.83, 13.5083}, {1152.8, -1586.11, 13.1071}, {1181.37, -1574.63, 13.0894}, {1250.28, -1574.52, 13.1099}, {1284.16, -1574.41, 13.1099},
    {1295.1, -1603.75, 13.1099}, {1295.23, -1662.64, 13.1099}, {1295.3, -1699.03, 13.1099}, {1243.37, -1709.67, 13.1099}, {1181.41, -1709.31, 13.2268},
    {1172.75, -1739.02, 13.1596}, {1172.93, -1795.3, 13.1255}, {1173.06, -1837.89, 13.1336}, {1195.17, -1854.74, 13.1238}, {1256.63, -1854.94, 13.1099}, {1270.23, -1839.2, 13.1167}, {1228.96, -1831.86, 13.1243}
};

static 	
	examenVehicle[MAX_PLAYERS],
	examenNextCheckpoint[MAX_PLAYERS],
	examenDelay[MAX_PLAYERS],
	examenSelectedHours[MAX_PLAYERS];

// ------------------------------------- //
//             Functions 	             //
// ------------------------------------- //

static resetPlayerDMVExamen(const playerid) {
    DestroyVehicle(examenVehicle[playerid]);
    DisablePlayerRaceCheckpoint(playerid);

    examenVehicle[playerid] = 0;

    playerVars[playerid][var_checkpoint] = -1; 
    return 1;
}

bool:isPlayerInDMVExamen(const playerid) 
	return examenVehicle[playerid] != 0;

getPlayerDMVNextCheckpoint(const playerid)
	return examenNextCheckpoint[playerid];

getPlayerDMVVehicle(const playerid)
	return examenVehicle[playerid];

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:examen(playerid, params[], help) {
    if(isPlayerInDMVExamen(playerid) || !IsPlayerInRangeOfPoint(playerid, 2.5, 1219.2386,-1812.8556,16.5938))
        return 1;

    if(playerInfo[playerid][pDrivingLicense] > 0)
        return sendError(playerid, "Ai deja licenta de condus.");

    if(playerInfo[playerid][pDrivingLicense] < 0)
        return sendError(playerid, "Licenta ta de condus este suspendata pentru inca %d ore.", playerInfo[playerid][pDrivingLicense] * -1);

    if(IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu trebuie sa fii intr-un vehicul.");

    if(examenDelay[playerid] > gettime())
        return sendError(playerid, "Trebuie sa astepti %s minute pentru a face asta din nou.", CalculateTime(examenDelay[playerid] - gettime()));

    return Dialog_Show(playerid, EXAMEN, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: DMV Examen", "Money\tLicense Hours\n5.000$\t15\n15.000$\t30\n50.000$\t50", "Select", "Exit");
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:EXAMEN(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    CheckPlayerCheckpoint(playerid);

    new money;

    switch(listitem) {
        case 0: {
            money = 5000;
            examenSelectedHours[playerid] = 15;
        }
        case 1: {
            money = 15000;
            examenSelectedHours[playerid] = 30;
        }
        case 2: {
            money = 50000;
            examenSelectedHours[playerid] = 50;
        }
    }

    if(GetMoney(playerid) < money && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai $%s.", formatNumber(money));

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, money);

    examenVehicle[playerid] = createVehicle(serverVars[3][svar_Value], 1213.6901,-1839.1895,13.1102,177.7767, 31, 31, 0);

    SetVehicleParamsEx(examenVehicle[playerid], 0, 0, 0, 1, 0, 0, 0); 
    SetVehicleNumberPlate(examenVehicle[playerid], "DMV"); 
    PutPlayerInVehicle(playerid, examenVehicle[playerid], 0);
    
    SetPlayerRaceCheckpoint(playerid, 0, examenCheckpoints[0][0], examenCheckpoints[0][1], examenCheckpoints[0][2], examenCheckpoints[1][0], examenCheckpoints[1][1], examenCheckpoints[1][2], 3.0);
    
    playerVars[playerid][var_checkpoint] = examenNextCheckpoint[playerid] = 1;
    examenDelay[playerid] = gettime() + 180; 

    SCM(playerid, COLOR_GREEN, "(DMV Info): {ffffff}You started the DMV examen! Press '2' or write [/engine] to start the vehicle's engine."); 
    SCM(playerid, COLOR_GREEN, "(DMV Info): {ffffff}Drive carefully, otherwise you will fail the examen!"); 
    SCM(playerid, COLOR_GREEN, "(DMV Info): {ffffff}Good luck!");
    return 1;
}

// ------------------------------------- //
//             Hooks                     //
// ------------------------------------- //

hook OP_EnterRaceCheckpoint(playerid) {
    if(playerVars[playerid][var_checkpoint] == 1) {
        switch(examenNextCheckpoint[playerid]) {
            case sizeof examenCheckpoints: {
                playerInfo[playerid][pDrivingLicense] = examenSelectedHours[playerid];
                
                resetPlayerDMVExamen(playerid);

                return SCMf(playerid, COLOR_GREEN, "(DMV Info): {ffffff}You finished the DMV examen succesfully! You received the driving license for %d hours.", playerInfo[playerid][pDrivingLicense]);
            }
            case sizeof examenCheckpoints - 1: {
                SetPlayerRaceCheckpoint(playerid, 1, examenCheckpoints[examenNextCheckpoint[playerid]][0], examenCheckpoints[examenNextCheckpoint[playerid]][1], examenCheckpoints[examenNextCheckpoint[playerid]][2], 0.0, 0.0, 0.0, 3.0); 
            }
            default: {
                SetPlayerRaceCheckpoint(playerid, 0, examenCheckpoints[examenNextCheckpoint[playerid]][0], examenCheckpoints[examenNextCheckpoint[playerid]][1], examenCheckpoints[examenNextCheckpoint[playerid]][2], examenCheckpoints[examenNextCheckpoint[playerid] + 1][0], examenCheckpoints[examenNextCheckpoint[playerid] + 1][1], examenCheckpoints[examenNextCheckpoint[playerid] + 1][2], 3.0); 
            }
        }
        
        ++examenNextCheckpoint[playerid];
    }
    return 1;
}

hook OP_StateChange(playerid, newstate, oldstate) {
	if(oldstate == PLAYER_STATE_DRIVER && isPlayerInDMVExamen(playerid)) {
        examenDelay[playerid] = gettime() + 180; 
        resetPlayerDMVExamen(playerid);

        SetPlayerPos(playerid, 1219.2386, -1812.8556, 16.5938);

        SCM(playerid, COLOR_GREEN, "(DMV Info): {ffffff}You failed the examen because you leaved the examen's vehicle.");
    }
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	if(isPlayerInDMVExamen(playerid)) 
        resetPlayerDMVExamen(playerid); 

    examenDelay[playerid] = -1;
    return 1;
}
