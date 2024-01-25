// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_DEALERSHIP_VEHICLES 105

// ------------------------------------- //
//         Dealership Location           //
// ------------------------------------- //

const 
    Float:dealership_Location_X = 1450.2622,
    Float:dealership_Location_Y = -2287.1309,
    Float:dealership_Location_Z = 13.5469;

// ------------------------------------- //
//              Enums                    //
// ------------------------------------- //

static enum e_dsInfo {
    dsID, dsModelID, dsStock, dsPrice, e_dsVehicleTypes:dsType
}

enum e_dsVehicleTypes {
    VEHICLE_TYPE_PLANE,
    VEHICLE_TYPE_BOAT,
    VEHICLE_TYPE_CAR_BIKE
}

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static 
    dealerShipInfo[MAX_DEALERSHIP_VEHICLES][e_dsInfo],
    dealerShipIndex[MAX_PLAYERS],
    e_dsVehicleTypes:dealerShipVehType[MAX_PLAYERS],
    dealerShipVerifyCode[MAX_PLAYERS][7],
    dealerShipVehicle[MAX_PLAYERS],
    dealerShipTestDriveTime[MAX_PLAYERS],
    bool:dealerShipPlayerIn[MAX_PLAYERS],
    Timer:dealerShipPlayerTimer[MAX_PLAYERS],
    dealerShipDelay[MAX_PLAYERS],
    dealerShipSelectDelay[MAX_PLAYERS],
    dealerShipVehiclesIndex[603 - 400 + 1] = {-1, ...};

// ------------------------------------- //
//              Arrays                   //
// ------------------------------------- //

static const Float:dealerShipCameraPos[][] = {
    {1534.580200, -1361.818359, 339.118133, 1537.563964, -1359.175292, 336.099670},
    {2323.392822, 517.400512, 12.913125, 2323.322021, 521.030273, 9.475152},
    {2359.821044, 520.229919, 8.494188, 2359.796386, 524.305908, 5.598422}
};

static const Float:dealerShipVehiclesPos[][] = {
    {1544.4556, -1353.3407, 329.6127, 88.6047},
    {2325.5532, 533.4022, -0.1943, 140.2029},
    {2359.8184, 530.7588, 1.5332, 135.8322}
};

// ------------------------------------- //
//          Load Query Function          //
// ------------------------------------- //

query_function load_dealership_vehicles() {
    serverStuff[dealershipVehiclesModels] = cache_num_rows();

    if(!serverStuff[dealershipVehiclesModels]) 
        return print("[MYSQL INFO] Dealership vehicles were not found in the database.");

    CreateDynamicPickup(1239, 23, dealership_Location_X, dealership_Location_Y, dealership_Location_Z);
    CreateDynamic3DTextLabel("Dealership\n{FFFFFF}Type {1C8A15}[/buyvehicle]{FFFFFF} to buy a vehicle.", COLOR_GREEN, dealership_Location_X, dealership_Location_Y, dealership_Location_Z, 5.0);
    CreateDynamicMapIcon(dealership_Location_X, dealership_Location_Y, dealership_Location_Z, 55, 0);

    for(new i = 0; i < serverStuff[dealershipVehiclesModels]; ++i) {
        dealerShipInfo[i][dsID] = cache_get_field_content_int(i, "ID");
        dealerShipInfo[i][dsModelID] = cache_get_field_content_int(i, "ModelID");
        dealerShipInfo[i][dsStock] = cache_get_field_content_int(i, "Stock");
        dealerShipInfo[i][dsPrice] = cache_get_field_content_int(i, "Price");

        dealerShipVehiclesIndex[dealerShipInfo[i][dsModelID] - 400] = i;

        switch(getVehicleModelType(dealerShipInfo[i][dsModelID])) {
            case VEHICLE_MODEL_TYPE_BOAT: dealerShipInfo[i][dsType] = VEHICLE_TYPE_BOAT;
            case VEHICLE_MODEL_TYPE_PLANE: dealerShipInfo[i][dsType] = VEHICLE_TYPE_PLANE;
            default: dealerShipInfo[i][dsType] = VEHICLE_TYPE_CAR_BIKE;
        }
    }
    return printf("[MYSQL LOADED] Dealership vehicles: %d", serverStuff[dealershipVehiclesModels]); 
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

static playerEnterDealership(const playerid) {
    playerTextdraws[playerid][dealerShipTD][0] = CreatePlayerTextDraw(playerid, 524.729431, 127.583366, "dealership");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][0], 0.379853, 1.401666);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][0], 0.000000, 126.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][0], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][0], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][dealerShipTD][0], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][dealerShipTD][0], 478811647);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][0], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][0], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][0], 3);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][0], 1);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][0]);

    playerTextdraws[playerid][dealerShipTD][1] = CreatePlayerTextDraw(playerid, 461.853210, 145.000030, "box");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][1], 0.000000, 14.380589);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][1], 587.650634, 0.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][1], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][1], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][dealerShipTD][1], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][dealerShipTD][1], 150);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][1], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][1], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][1], 1);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][1], 1);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][1]);

    playerTextdraws[playerid][dealerShipTD][2] = CreatePlayerTextDraw(playerid, 477.625671, 121.166732, "");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][2], 102.000000, 101.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][2], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][2], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][2], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][2], 0);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][2], 5);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][dealerShipTD][2], dealerShipInfo[0][dsModelID]);
    PlayerTextDrawSetPreviewRot(playerid, playerTextdraws[playerid][dealerShipTD][2], 0.000000, 0.000000, -50.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, playerTextdraws[playerid][dealerShipTD][2], 1, 1);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][2]);

    playerTextdraws[playerid][dealerShipTD][3] = CreatePlayerTextDraw(playerid, 524.860656, 196.799591, "");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][3], 0.193381, 1.040001);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][3], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][3], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][3], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][3], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][3], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][3], 1);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][3]);

    playerTextdraws[playerid][dealerShipTD][4] = CreatePlayerTextDraw(playerid, 469.463897, 204.050064, "<");
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][4], 10.000000, 10.000000);
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][4], 0.291771, 1.675833);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][4], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][4], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][4], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][4], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][4], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][4], 1);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][dealerShipTD][4], true);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][4]);

    playerTextdraws[playerid][dealerShipTD][5] = CreatePlayerTextDraw(playerid, 580.948791, 204.050064, ">");
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][5], 10.000000, 10.000000);
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][5], 0.291771, 1.675833);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][5], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][5], -1);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][5], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][5], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][5], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][5], 1);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][dealerShipTD][5], true);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][5]);

    playerTextdraws[playerid][dealerShipTD][6] = CreatePlayerTextDraw(playerid, 473.801452, 261.950714, "BUY");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][6], 0.193381, 1.040001);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][6], 8.000000, 20.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][6], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][6], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][dealerShipTD][6], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][dealerShipTD][6], 478811647);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][6], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][6], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][6], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][6], 1);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][dealerShipTD][6], true);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][6]);

    playerTextdraws[playerid][dealerShipTD][7] = CreatePlayerTextDraw(playerid, 561.882995, 261.950714, "TEST DRIVE");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][7], 0.193381, 1.040001);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][7], 8.000000, 47.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][7], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][7], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][dealerShipTD][7], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][dealerShipTD][7], 869072810);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][7], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][7], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][7], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][7], 1);
    PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][dealerShipTD][7], true);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][7]);

    if(playerInfo[playerid][pAdmin] > 5) {
        playerTextdraws[playerid][dealerShipTD][8] = CreatePlayerTextDraw(playerid, 524.996582, 242.317764, "EDIT VEHICLE (ADMIN)");
        PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][dealerShipTD][8], 8.000000, 75.000000);
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][dealerShipTD][8], 0.151683, 0.940834);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][dealerShipTD][8], 2);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][dealerShipTD][8], -1);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][dealerShipTD][8], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][dealerShipTD][8], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][dealerShipTD][8], 2);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][dealerShipTD][8], 1);
        PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][dealerShipTD][8], true);
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][8]);
    }

    SetPlayerVirtualWorld(playerid, playerid + 1);
    SetPlayerPos(playerid, 2310.7014, 566.2032, 7.7813);
    TogglePlayerControllableEx(playerid, false);

    dealerShipVehicle[playerid] = createVehicle(dealerShipInfo[0][dsModelID], dealerShipVehiclesPos[VEHICLE_TYPE_CAR_BIKE][0], dealerShipVehiclesPos[VEHICLE_TYPE_CAR_BIKE][1], dealerShipVehiclesPos[VEHICLE_TYPE_CAR_BIKE][2], dealerShipVehiclesPos[VEHICLE_TYPE_CAR_BIKE][3], 1, 1, -1);
    SetVehicleVirtualWorld(dealerShipVehicle[playerid], playerid + 1);
    SetVehicleNumberPlate(dealerShipVehicle[playerid], "Dealership");

    SetPlayerCameraPos(playerid, dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][0], dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][1], dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][2]);
    SetPlayerCameraLookAt(playerid, dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][3], dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][4], dealerShipCameraPos[VEHICLE_TYPE_CAR_BIKE][5]);
    
    SelectTextDraw(playerid, -1);

    dealerShipIndex[playerid] = 0;
    dealerShipVehType[playerid] = VEHICLE_TYPE_CAR_BIKE;

    updateDealershipTextdraw(playerid);

    return dealerShipPlayerIn[playerid] = true;    
}

static playerExitDealership(const playerid) {
    DestroyVehicle(dealerShipVehicle[playerid]);

    for(new i = 0; i < 9; ++i) 
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][dealerShipTD][i]);

    SetPlayerVirtualWorld(playerid, 0);
    TogglePlayerControllableEx(playerid, true);
    SetPlayerPos(playerid, dealership_Location_X, dealership_Location_Y, dealership_Location_Z);
    SetCameraBehindPlayer(playerid);

    return dealerShipPlayerIn[playerid] = false;   
} 

static updateDealershipTextdraw(const playerid) {
    gString[0] = EOS; 

    if(!aVehicleMaxSpeed[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400])
        format(gString, sizeof gString, "MODEL: ~g~%s~n~~w~~h~MAX. SPEED: ~g~UNKNOWN~n~~w~~h~STOCK: ~g~%d~n~~w~~h~PRICE: ~g~$%s", aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], dealerShipInfo[dealerShipIndex[playerid]][dsStock], formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]));
    
    else 
        format(gString, sizeof gString, "MODEL: ~g~%s~n~~w~~h~MAX. SPEED: ~g~%d~n~~w~~h~STOCK: ~g~%d~n~~w~~h~PRICE: ~g~$%s", aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], aVehicleMaxSpeed[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], dealerShipInfo[dealerShipIndex[playerid]][dsStock], formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]));

    return PlayerTextDrawSetString(playerid, playerTextdraws[playerid][dealerShipTD][3], gString);
}

static getDealershipVehicleIndex(const modelid) 
    return dealerShipVehiclesIndex[modelid];

getDealershipTestDriveTime(const playerid) 
    return dealerShipTestDriveTime[playerid];

getPersonalVehicleDsSellPrice(const vehicleid) {
    new const price = (dealerShipInfo[dealerShipVehiclesIndex[personalVehiclesInfo[vehicleid][pv_ModelID] - 400]][dsPrice] / 3) - (((gettime() - personalVehiclesInfo[vehicleid][pv_Days]) / 86400) + floatround(personalVehiclesInfo[vehicleid][pv_Odometer]));
    return price < 0 ? 0 : price;
}

isPlayerInDealershipTestDrive(const playerid)
    return dealerShipPlayerTimer[playerid] != Timer: 0;

isPlayerInDealership(const playerid) 
    return dealerShipPlayerIn[playerid];

setRandomDealershipParkPos(const e_dsVehicleTypes:vehicletype, &Float:x, &Float:y, &Float:z, &Float:a) {
    switch(vehicletype) {
        case VEHICLE_TYPE_CAR_BIKE: {
            static const Float:parkPosX[] = {
                1411.2725, 1407.9111, 1404.7783, 1401.5432, 1398.1716, 1394.9725, 1391.5664, 1388.1664, 1385.1289
            };

            x = parkPosX[random(sizeof parkPosX)]; 
            y = -2365.3032 + (random(4) * 17.0); 
            z = 13.2740; 
            a = 0.3763;
        }
        case VEHICLE_TYPE_BOAT: {
            x = 719.7054;
            y = -1701.9880 + (random(2) * 65.287);
            z = -0.1931;
            a = 178.9965;
        }
        case VEHICLE_TYPE_PLANE: {
            x = 1378.990 + (random(5) * 10.0);
            y = -2414.858;
            z = 13.732;
            a = 179.3598;
        }
    }
}

// ------------------------------------- //
//              Timers                   //
// ------------------------------------- //

timer dealerShipTestDriveTimer[60000](playerid) {
    DestroyVehicle(dealerShipVehicle[playerid]);

    SetPlayerVirtualWorld(playerid, 0);
    TogglePlayerControllableEx(playerid, true);
    SetPlayerPos(playerid, dealership_Location_X, dealership_Location_Y, dealership_Location_Z);
    
    dealerShipPlayerIn[playerid] = false;
    dealerShipPlayerTimer[playerid] = Timer: 0;
    return 1;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:buyvehicle(playerid, params[], help) {
    if(!IsPlayerInRangeOfPoint(playerid, 2.0, dealership_Location_X, dealership_Location_Y, dealership_Location_Z))
        return sendError(playerid, "Nu esti la locatia potrivita.");

    if(playerInfo[playerid][pLevel] < 3)
        return sendError(playerid, "Ai nevoie de minim level 3.");

    if(isPlayerInDealership(playerid))
        return 1;

    if(dealerShipDelay[playerid] > gettime())
        return sendError(playerid, "Mai ai de asteptat %d secunde inainte de a folosi aceasta comanda.", dealerShipDelay[playerid] - gettime());

    if(playerVars[playerid][var_working])
        return sendError(playerid, "Nu poti folosi aceasta comanda in timp ce muncesti.");
    
    clearChat(playerid, 5);

    SCM(playerid, COLOR_GREEN, "(Dealership): {ffffff}To navigate through vehicles press arrows textdraws showed on your display.");
    SCM(playerid, COLOR_GREEN, "(Dealership): {ffffff}To buy a vehicle press the button BUY, if you want to test it before press the button TEST DRIVE.");
    SCM(playerid, COLOR_GREEN, "(Dealership): {ffffff}To exit from dealership press ESC.");

    return playerEnterDealership(playerid);
}

YCMD:dealershipveh(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 1 && playerInfo[playerid][pHelper] < 1)
        return sendError(playerid, "Nu ai gradul necesar pentru a folosi aceasta comanda.");

    if(isnull(params))
        return sendUsage(playerid, "/dealershipveh <vehicle name>");

    new results, idx;

    SCM(playerid, COLOR_GREEN, "___________________________________");

    for(new i = 0; i < sizeof dealerShipVehiclesIndex; ++i) {
        idx = getDealershipVehicleIndex(i);

        if(idx != -1 && strfind(aVehicleNames[i], params, true) != -1 && dealerShipInfo[idx][dsModelID] == i + 400) {
            if(!aVehicleMaxSpeed[i]) {
                SCMf(playerid, -1, "%d. Model: %s [price: $%s, stock: %d, max speed: unknown]", results, aVehicleNames[i], formatNumber(dealerShipInfo[idx][dsPrice]), dealerShipInfo[idx][dsStock]);
            }
            else {
                SCMf(playerid, -1, "%d. Model: %s [price: $%s, stock: %d, max speed: %d]", results, aVehicleNames[i], formatNumber(dealerShipInfo[idx][dsPrice]), dealerShipInfo[idx][dsStock], aVehicleMaxSpeed[i]);
            }
            
            ++results;
        }
    }

    SCMf(playerid, COLOR_WHITE, "There are %d found results for '%s'.", results, params);
    SCM(playerid, COLOR_GREEN, "___________________________________");
    return 1;
}

YCMD:gotods(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
        new const vehicleid = GetPlayerVehicleID(playerid);

        SetVehiclePos(vehicleid, dealership_Location_X - 1.0, dealership_Location_Y, dealership_Location_Z);
        LinkVehicleToInterior(vehicleid, 0);
        SetVehicleVirtualWorld(vehicleid, 0);
    }
        
    else {
        SetPlayerPos(playerid, dealership_Location_X, dealership_Location_Y, dealership_Location_Z);
    }

    SetPlayerVirtualWorld(playerid, 0);

    return SCM(playerid, COLOR_GREY, "* Ai fost teleportat la Dealership.");
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:EDITVEHDS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!listitem) 
        return Dialog_Show(playerid, SETPRICEDS, DIALOG_STYLE_INPUT, "SERVER: Edit Price", "Type below the price you want to set for this vehicle:", "Set", "Cancel");
    
    return Dialog_Show(playerid, SETSTOCKDS, DIALOG_STYLE_INPUT, "SERVER: Edit Stock", "Type below the stock you want to set for this vehicle:", "Set", "Cancel");
}

Dialog:SETSTOCKDS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const value = strval(inputtext);

    if(!isnumeric(inputtext) || value < 0)
        return Dialog_Show(playerid, SETSTOCKDS, DIALOG_STYLE_INPUT, "SERVER: Edit Stock", "Type below the stock you want to set for this vehicle:", "Set", "Cancel");

    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {FFFFFF}Admin %s edited vehicle %s stock from %d to %d.", GetName(playerid), aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], dealerShipInfo[dealerShipIndex[playerid]][dsStock], value);

    dealerShipInfo[dealerShipIndex[playerid]][dsStock] = value;

    va_mysql_tquery("UPDATE `server_dealership_vehicles` SET `Stock` = %d WHERE `ID` = %d", value, dealerShipInfo[dealerShipIndex[playerid]][dsID]);

    return updateDealershipTextdraw(playerid);
}

Dialog:SETPRICEDS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const value = strval(inputtext);

    if(!isnumeric(inputtext) || value < 0)
        return Dialog_Show(playerid, SETPRICEDS, DIALOG_STYLE_INPUT, "SERVER: Edit Price", "Type below the price you want to set for this vehicle:", "Set", "Cancel");

    SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {FFFFFF}Admin %s edited vehicle %s price from $%s to $%s.", GetName(playerid), aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]), formatNumber(value));

    dealerShipInfo[dealerShipIndex[playerid]][dsPrice] = value;

    va_mysql_tquery("UPDATE `server_dealership_vehicles` SET `Price` = %d WHERE `ID` = %d", value, dealerShipInfo[dealerShipIndex[playerid]][dsID]);

    return updateDealershipTextdraw(playerid);
}

Dialog:TESTDRIVEDS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(GetMoney(playerid) < 50000 && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti.");

    switch(dealerShipVehType[playerid]) {
        case VEHICLE_TYPE_CAR_BIKE: {   
            new const e_vehicleModelTypes:modeltype = getVehicleModelType(dealerShipInfo[dealerShipIndex[playerid]][dsModelID]);

            if(playerInfo[playerid][pDrivingLicense] <= 0 && modeltype != VEHICLE_MODEL_TYPE_BIKE && modeltype != VEHICLE_MODEL_TYPE_MOTOR_BIKE) 
                return sendError(playerid, "Nu ai licenta de condus sau aceasta este expirata.");

            SetVehiclePos(dealerShipVehicle[playerid], 2287.4177, 612.6918, 10.5474);
            SetVehicleZAngle(dealerShipVehicle[playerid], 0.1664);
        }
        case VEHICLE_TYPE_PLANE: {
            if(playerInfo[playerid][pFlyLicense] <= 0) 
                return sendError(playerid, "Nu ai licenta de pilot sau aceasta este expirata.");
        }
        case VEHICLE_TYPE_BOAT: {
            if(playerInfo[playerid][pBoatLicense] <= 0) 
                return sendError(playerid, "Nu ai licenta de navigatie sau aceasta este expirata.");

            SetVehicleZAngle(dealerShipVehicle[playerid], 180.0);
        }
    }

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, 50000);

    for(new i = 0; i < 9; ++i) 
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][dealerShipTD][i]);

    dealerShipTestDriveTime[playerid] = gettime() + 60;
    dealerShipPlayerTimer[playerid] = defer dealerShipTestDriveTimer(playerid);

    TogglePlayerControllableEx(playerid, true);
    SetCameraBehindPlayer(playerid);
    CancelSelectTextDraw(playerid);
    PutPlayerInVehicle(playerid, dealerShipVehicle[playerid], 0);

    SCMf(playerid, COLOR_GREEN, "(Dealership): {ffffff}You paid $50.000 to do a test drive with vehicle %s for 1 minute.", aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400]);
    SCM(playerid, COLOR_GREEN, "(Dealership): {ffffff}You have been transferred on another virtual world. If you exit from vehicle or destroy it,");
    SCM(playerid, -1, "... your test drive will be canceled.");
    return 1;
}

Dialog:BUYVEHICLE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(strcmp(inputtext, dealerShipVerifyCode[playerid]) != 0)
        return sendError(playerid, "Codul introdus este incorect.");

    if(!dealerShipInfo[dealerShipIndex[playerid]][dsStock])
        return sendError(playerid, "Acest vehicul nu este in stock.");

    if(playerInfo[playerid][pVehiclesSlots] == VECTOR_size(personalVehicles[playerid]))
        return sendError(playerid, "Nu ai sloturi disponibile.");

    if(GetMoney(playerid) < dealerShipInfo[dealerShipIndex[playerid]][dsPrice] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti.");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, dealerShipInfo[dealerShipIndex[playerid]][dsPrice], false);

    dealerShipInfo[dealerShipIndex[playerid]][dsStock] --;

    new 
        timestamp = gettime(),
        id = Iter_Free(personalVehiclesIDs),
        Float:X, Float:Y, Float:Z, Float:A;

    setRandomDealershipParkPos(dealerShipInfo[dealerShipIndex[playerid]][dsType], X, Y, Z, A);
    
    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_personal_vehicles` (OwnerID, ModelID, Days, X, Y, Z, Angle) VALUES (%d, %d, %d, %f, %f, %f, %f)", playerInfo[playerid][pSQLID], dealerShipInfo[dealerShipIndex[playerid]][dsModelID], timestamp, X, Y, Z, A);
    mysql_tquery(SQL, gQuery, "insertPlayerPersonalVehicle", "dddddffff", playerid, playerInfo[playerid][pSQLID], id, dealerShipInfo[dealerShipIndex[playerid]][dsModelID], timestamp, X, Y, Z, A);

    va_mysql_tquery("UPDATE `server_dealership_vehicles`, `server_users` SET `server_dealership_vehicles`.`Stock` = %d, `server_users`.`Money` = %d, `server_users`.`MoneyStore` = %d WHERE `server_dealership_vehicles`.`ID` = %d AND `server_users`.`ID` = %d", dealerShipInfo[dealerShipIndex[playerid]][dsStock], GetMoney(playerid), GetMilliards(playerid), dealerShipInfo[dealerShipIndex[playerid]][dsID], playerInfo[playerid][pSQLID]);

    playerExitDealership(playerid);

    CancelSelectTextDraw(playerid);

    personalVehiclesInfo[id][pv_SpawnID] = createVehicle(dealerShipInfo[dealerShipIndex[playerid]][dsModelID], X, Y, Z, A, 1, 1, -1, 0, 100.9);
    SetVehicleNumberPlate(personalVehiclesInfo[id][pv_SpawnID], "New Car");

    if(getVehicleModelType(dealerShipInfo[dealerShipIndex[playerid]][dsModelID]) == VEHICLE_MODEL_TYPE_BIKE) {
        vehicleVars[personalVehiclesInfo[id][pv_SpawnID]][var_carEngine] = true;
        SetVehicleParamsEx(personalVehiclesInfo[id][pv_SpawnID], 1, 0, 0, 1, 0, 0, 0);
    }
    else 
        SetVehicleParamsEx(personalVehiclesInfo[id][pv_SpawnID], 0, 0, 0, 1, 0, 0, 0);

    vehicleVars[personalVehiclesInfo[id][pv_SpawnID]][var_carLocked] = true;
    vehicleVars[personalVehiclesInfo[id][pv_SpawnID]][var_carPersonal] = id;

    personalVehiclesInfo[id][pv_DespawnTime] = gettime() + (5 * 60);
    Iter_Add(pVehiclesDespawn, personalVehiclesInfo[id][pv_SpawnID]);

    personalVehiclesSpawned[playerid] ++;

    playerVars[playerid][var_checkpoint] = 1;
    SetPlayerCheckpoint(playerid, X, Y, Z, 3.5);

    SendAdmins(COLOR_LIGHTRED, "(Info): {FFFFFF}Player %s bought vehicle %s for $%s from dealership. Stock remaining: %d", GetName(playerid), aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]), dealerShipInfo[dealerShipIndex[playerid]][dsStock]);

    return SCMf(playerid, COLOR_GREEN, "(Dealership): {FFFFFF}You bought vehicle %s for $%s successfully. A checkpoint has been placed on your vehicle.", aVehicleNames[dealerShipInfo[dealerShipIndex[playerid]][dsModelID] - 400], formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]));
}

// ------------------------------------- //
//              Hooks                    //
// ------------------------------------- //

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    if(isPlayerInDealership(playerid)) {
        if(dealerShipSelectDelay[playerid] < GetTickCount() && (playertextid == playerTextdraws[playerid][dealerShipTD][4] || playertextid == playerTextdraws[playerid][dealerShipTD][5])) {
            if(playertextid == playerTextdraws[playerid][dealerShipTD][4]) 
                dealerShipIndex[playerid] = (dealerShipIndex[playerid] - 1) % serverStuff[dealershipVehiclesModels];
            
            else 
                dealerShipIndex[playerid] = (dealerShipIndex[playerid] + 1) % serverStuff[dealershipVehiclesModels];

            DestroyVehicle(dealerShipVehicle[playerid]);

            dealerShipVehicle[playerid] = createVehicle(dealerShipInfo[dealerShipIndex[playerid]][dsModelID], dealerShipVehiclesPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][0], dealerShipVehiclesPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][1], dealerShipVehiclesPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][2], dealerShipVehiclesPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][3], 1, 1, -1);
            SetVehicleVirtualWorld(dealerShipVehicle[playerid], playerid + 1);

            if(dealerShipInfo[dealerShipIndex[playerid]][dsType] == VEHICLE_TYPE_CAR_BIKE)
                SetVehicleNumberPlate(dealerShipVehicle[playerid], "Dealership");

            if(dealerShipVehType[playerid] != dealerShipInfo[dealerShipIndex[playerid]][dsType]) {
                SetPlayerCameraPos(playerid, dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][0], dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][1], dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][2]);
                SetPlayerCameraLookAt(playerid, dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][3], dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][4], dealerShipCameraPos[dealerShipInfo[dealerShipIndex[playerid]][dsType]][5]);
            
                if(dealerShipInfo[dealerShipIndex[playerid]][dsType] == VEHICLE_TYPE_PLANE) 
                    SetPlayerPos(playerid, 1547.2655, -1366.0780, 326.2109);

                else if(dealerShipVehType[playerid] == VEHICLE_TYPE_PLANE) 
                    SetPlayerPos(playerid, 2310.7014, 566.2032, 7.7813);

                dealerShipVehType[playerid] = dealerShipInfo[dealerShipIndex[playerid]][dsType];
            }

            updateDealershipTextdraw(playerid);

            PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][dealerShipTD][2], dealerShipInfo[dealerShipIndex[playerid]][dsModelID]);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][dealerShipTD][2]);

            dealerShipSelectDelay[playerid] = GetTickCount() + 750;
        }
        else if(playertextid == playerTextdraws[playerid][dealerShipTD][6]) {
            if(!dealerShipInfo[dealerShipIndex[playerid]][dsStock])
                return sendError(playerid, "Acest vehicul nu este in stock.");

            if(playerInfo[playerid][pVehiclesSlots] == VECTOR_size(personalVehicles[playerid]))
                return sendError(playerid, "Nu ai sloturi disponibile.");

            if(GetMoney(playerid) < dealerShipInfo[dealerShipIndex[playerid]][dsPrice] && GetMilliards(playerid) < 1)
                return sendError(playerid, "Nu ai bani suficienti.");

            generateRandomString(dealerShipVerifyCode[playerid], _, 3);

            Dialog_Show(playerid, BUYVEHICLE, DIALOG_STYLE_INPUT, "SERVER: Buy Vehicle", "Enter the verify code (%s) below:", "Ok", "Cancel", dealerShipVerifyCode[playerid]);
        }
        else if(playertextid == playerTextdraws[playerid][dealerShipTD][7]) {
            Dialog_Show(playerid, TESTDRIVEDS, DIALOG_STYLE_MSGBOX, "SERVER: Test Drive", "Do you want to test this vehicle? You will need to pay $50.000 to drive it for 1 minute.", "Ok", "Cancel");
        }
        else if(playertextid == playerTextdraws[playerid][dealerShipTD][8]) {
            Dialog_Show(playerid, EDITVEHDS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Edit Dealership Vehicle", "Type\tValue\nPrice\t$%s\nStock\t%d", "Select", "Exit", formatNumber(dealerShipInfo[dealerShipIndex[playerid]][dsPrice]), dealerShipInfo[dealerShipIndex[playerid]][dsStock]);
        }
    }
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == INVALID_TEXT_DRAW && isPlayerInDealership(playerid) && !isPlayerInDealershipTestDrive(playerid)) {
        if(Dialog_IsOpened(playerid))
            Dialog_Close(playerid);

        dealerShipDelay[playerid] = gettime() + 30;

        return playerExitDealership(playerid);
    }
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
    if(killerid != INVALID_PLAYER_ID && isPlayerInDealershipTestDrive(killerid)) {
        stop dealerShipPlayerTimer[killerid];
        dealerShipTestDriveTimer(killerid); 
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(oldstate == PLAYER_STATE_DRIVER && isPlayerInDealershipTestDrive(playerid)) {
        stop dealerShipPlayerTimer[playerid];
        dealerShipTestDriveTimer(playerid); 
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(isPlayerInDealership(playerid)) {
        DestroyVehicle(dealerShipVehicle[playerid]);
        stop dealerShipPlayerTimer[playerid];

        dealerShipPlayerIn[playerid] = false;
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
    dealerShipDelay[playerid] = -1;
    dealerShipSelectDelay[playerid] = GetTickCount();
    return 1;
}