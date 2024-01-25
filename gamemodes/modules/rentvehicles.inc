// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_RENT_LOCATIONS 1
#define RENT_VEHICLES_STOCK 15
#define RENT_VEHICLES_COUNT 15

// ------------------------------------- //
//              Enum                     //
// ------------------------------------- //

enum e_rentInfo {
    Float:rent_X, Float:rent_Y, Float:rent_Z, Float:rent_carSpawnAngle, rent_business, rent_carStock[RENT_VEHICLES_COUNT]
}

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static rentInfo[MAX_RENT_LOCATIONS][e_rentInfo] = {
    {561.4120, -1279.6511, 17.2482, 11.5699, 20 - 1}
};

static const rentVehicle[][] = {
    {1000, 481},
    {1500, 510},
    {2500, 402},
    {1750, 401},
    {1750, 410},
    {2000, 507},
    {2000, 400},
    {3500, 522},
    {4000, 411}, 
    {3000, 415},
    {1750, 436},
    {1750, 439},
    {1500, 462},
    {3000, 521},
    {2000, 412}
};

// ------------------------------------- //
//              Load Function            //
// ------------------------------------- //

function loadRentLocations() {
    for(new i = 0; i < MAX_RENT_LOCATIONS; ++i) {
        pickupInfo[CreateDynamicPickup(19134, 23, rentInfo[i][rent_X], rentInfo[i][rent_Y], rentInfo[i][rent_Z], 0, 0)][pk_Rent] = i;
        CreateDynamic3DTextLabel("Vehicle Rent\n\n{FFFFFF}Vehicles available: {1C8A15}15\n{FFFFFF}Type {1C8A15}[/rentveh]{FFFFFF} to rent a vehicle.", COLOR_GREEN, rentInfo[i][rent_X], rentInfo[i][rent_Y], rentInfo[i][rent_Z], 3.5);
    
        memset(rentInfo[i][rent_carStock], RENT_VEHICLES_STOCK);
    }
    return print("[GAMEMODE LOADED] Rent Locations: "#MAX_RENT_LOCATIONS"");
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

getNearbyRentCar(const playerid, const Float:range) {
    new 
        nearbyPickup[1] = -1,
        Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerid, X, Y, Z);
    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_PICKUP, nearbyPickup[0], _, range);

    if(nearbyPickup[0] == -1)
        return -1;
    
    return pickupInfo[nearbyPickup[0]][pk_Rent];
}

destroyPlayerRentVehicle(const playerid) {
    DestroyVehicle(playerVars[playerid][var_rentedcar]); 
    stop playerVars[playerid][var_renttimer];

    ++rentInfo[playerVars[playerid][var_rentedcarbusiness]][rent_carStock][playerVars[playerid][var_rentlistitem]];
    
    return playerVars[playerid][var_rentedcarbusiness] = playerVars[playerid][var_rentedcar] = playerVars[playerid][var_rentlistitem] = playerVars[playerid][var_rentedcartime] = -1;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:rentveh(playerid, params[], help) {
    if(playerInfo[playerid][pDrivingLicense] <= 0)
        return sendError(playerid, "Nu ai licenta de condus sau aceasta a fost suspendata.");

    if(playerVars[playerid][var_rentedcar] != -1)
        return sendError(playerid, "Ai inchiriat deja un vehicul. Foloseste [/unrentveh] pentru a distruge vehiculul inchiriat.");

    new const rentcar = getNearbyRentCar(playerid, 2.0);
    
    if(rentcar == -1) 
        return sendError(playerid, "Nu esti la locatia potrivita.");

    gDialog = "Model\tFee (per minute)\tStock\n";

    for(new i = 0; i < RENT_VEHICLES_COUNT; ++i) 
        format(gDialog, sizeof gDialog, "%s%s\t$%s\t%d\n", gDialog, aVehicleNames[rentVehicle[i][1] - 400], formatNumber(rentVehicle[i][0]), rentInfo[rentcar][rent_carStock][i]);

    return Dialog_Show(playerid, RENTVEHICLE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Vehicle Rent", gDialog, "Rent", "Exit");
}

YCMD:locaterentveh(playerid, params[], help) {
    if(playerVars[playerid][var_rentedcar] == -1)
        return sendError(playerid, "Nu ai inchiriat un vehicul.");

    CheckPlayerCheckpoint(playerid);

    new Float: vX, Float: vY, Float: vZ; 
    GetVehiclePos(playerVars[playerid][var_rentedcar], vX, vY, vZ);

    if(IsPlayerInRangeOfPoint(playerid, 5.0, vX, vY, vZ))
        return sendError(playerid, "Nu poti face asta deoarece esti foarte aproape de vehiculul inchiriat.");

    playerVars[playerid][var_checkpoint] = 1;
    SetPlayerCheckpoint(playerid, vX, vY, vZ, 5.0); 

    return SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}A checkpoint has been placed on your rented vehicle.");
}

YCMD:unrentveh(playerid, params[], help) {
    if(playerVars[playerid][var_rentedcar] == -1)
        return sendError(playerid, "Nu ai inchiriat un vehicul.");

    destroyPlayerRentVehicle(playerid);

    return SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}Your rented vehicle has been destroyed succesfully.");
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:RENTVEHICLE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu poti folosi aceasta comanda daca esti intr-un vehicul.");

    new const rentcar = getNearbyRentCar(playerid, 2.0);

    if(rentcar == -1)
        return 1;

    new const price = bizzInfo[rentInfo[rentcar][rent_business]][bFee] + rentVehicle[listitem][0];

    if(GetMoney(playerid) < price && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai suficienti bani. Ai nevoie de $%s (taxa afacerii inclusa).", formatNumber(price));

    if(!rentInfo[rentcar][rent_carStock][listitem])
        return sendError(playerid, "Nu este stock disponibil pentru acest vehicul.");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price, false); 
    va_GameTextForPlayer(playerid, "~R~-$%s", 3000, 1, formatNumber(price));

    playerVars[playerid][var_rentedcar] = createVehicle(rentVehicle[listitem][1], rentInfo[rentcar][rent_X], rentInfo[rentcar][rent_Y], rentInfo[rentcar][rent_Z], rentInfo[rentcar][rent_carSpawnAngle], 2, 2, -1);

    playerVars[playerid][var_rentlistitem] = listitem;
    playerVars[playerid][var_rentedcarbusiness] = rentcar; 
    playerVars[playerid][var_rentedcartime] = 10;
    playerVars[playerid][var_renttimer] = repeat rentVehicleTimer(playerid, price - bizzInfo[rentInfo[rentcar][rent_business]][bFee]);

    --rentInfo[rentcar][rent_carStock][listitem];
    bizzInfo[rentInfo[rentcar][rent_business]][bBalance] += bizzInfo[rentInfo[rentcar][rent_business]][bFee];

    gString[0] = EOS;
    format(gString, sizeof gString, "RENT - %d", playerid); 
    SetVehicleNumberPlate(playerVars[playerid][var_rentedcar], gString);

    PutPlayerInVehicle(playerid, playerVars[playerid][var_rentedcar], 0);

    va_mysql_tquery("UPDATE `server_business`, `server_users` SET server_business.Balance = %d, server_users.MoneyStore = %d, server_users.Money = %d WHERE server_business.ID = %d AND server_users.ID = %d", bizzInfo[rentInfo[rentcar][rent_business]][bBalance], GetMilliards(playerid), GetMoney(playerid), bizzInfo[rentInfo[rentcar][rent_business]][bID], playerInfo[playerid][pSQLID]); 
    
    SCMf(playerid, COLOR_GREEN, "(Rent Car): {ffffff}You succesfully rented a vehicle (model: %s) for $%s (business fee: $%s) money.", GetVehicleName(GetPlayerVehicleID(playerid)), formatNumber(price - bizzInfo[rentInfo[rentcar][rent_business]][bFee]), formatNumber(bizzInfo[rentInfo[rentcar][rent_business]][bFee]));
    SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}After 10 minutes the rented vehicle will be destroyed automatically.");
    SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}Available commands: /unrentveh, /locaterentveh."); 

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_RENTCAR);
}

// ------------------------------------- //
//              Timers                   //
// ------------------------------------- //

timer rentVehicleTimer[60000](const playerid, const tax) {
    if(GetMoney(playerid) < tax && GetMilliards(playerid) < 1) {
        destroyPlayerRentVehicle(playerid);

        return SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}Your rented vehicle has been destroyed because you don't have money to pay costs.");
    }
    
    if(--playerVars[playerid][var_rentedcartime] <= 0) {
        destroyPlayerRentVehicle(playerid);
        
        SCM(playerid, COLOR_GREEN, "(Rent Car): {ffffff}Your rented vehicle has been destroyed because time has passed.");
    }

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, tax); 
    va_GameTextForPlayer(playerid, "~R~-$%s", 2500, 1, formatNumber(tax));
    return 1;
}