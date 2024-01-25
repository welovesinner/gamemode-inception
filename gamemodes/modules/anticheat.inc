// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//        Anticheat debugging            //
// ------------------------------------- //

#define DEBUG_ANTICHEAT 1

// ------------------------------------- //
//        Variables                      //
// ------------------------------------- //

enum e_acInfo {
    ac_lastvehicle, ac_warningtime, ac_entervehtime
}

new anticheatInfo[MAX_PLAYERS][e_acInfo];

// ------------------------------------- //
//        Anti Cheat Timer               //
// ------------------------------------- //

ptask antiCheatsTimer[2000](playerid) {
    if(anticheatInfo[playerid][ac_warningtime] < gettime()) {
        new 
            anim = GetPlayerAnimationIndex(playerid), 
            playerstate = GetPlayerState(playerid),
            vehicleid = GetPlayerVehicleID(playerid),
            Float: X, Float: Y, Float: Z;

        GetPlayerPos(playerid, X,Y,Z);

        // ------------------------------------- //
        //           Admin Warnings              //
        // ------------------------------------- // 

        if(playerstate != PLAYER_STATE_SPECTATING && !CA_IsPlayerInWater(playerid) && !CA_IsPlayerOnSurface(playerid, 50.0) && getVehicleModelType(GetVehicleModel(vehicleid)) != VEHICLE_MODEL_TYPE_PLANE && anim != 1130 && GetPlayerWeapon(playerid) != 46 && serverVars[2][svar_Value] == 1) { 
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (fly-hack, status: %s).", playerInfo[playerid][pName], playerstate == PLAYER_STATE_ONFOOT ? "on foot" : vehicleid != INVALID_VEHICLE_ID ? "in vehicle" : "?"), anticheatInfo[playerid][ac_warningtime] = gettime() + 5;
        
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Fly-hack detected - playerid: %d, state: %s, speed: %d", playerid, playerstate == PLAYER_STATE_ONFOOT ? "on foot" : vehicleid != INVALID_VEHICLE_ID ? "in vehicle" : "?", GetPlayerSpeed(playerid));
            #endif
        }

        if(GetPlayerSpeed(playerid) > 300 && anim != 1130 && playerstate == PLAYER_STATE_ONFOOT && serverVars[1][svar_Value] == 1) {
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (speed-hack, status: on foot).", playerInfo[playerid][pName]), anticheatInfo[playerid][ac_warningtime] = gettime() + 5;
        
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Speed-hack onfoot detected - playerid: %d, speed: %d, allowed speed: <300", playerid, GetPlayerSpeed(playerid));
            #endif
        }

        if(playerstate == PLAYER_STATE_DRIVER && GetVehicleModel(vehicleid) != 0 && getVehicleModelType(GetVehicleModel(vehicleid)) != VEHICLE_MODEL_TYPE_PLANE && getVehicleSpeed(vehicleid) > aVehicleMaxSpeed[GetVehicleModel(vehicleid)-400]+50 && serverVars[1][svar_Value] == 1) {
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (speed-hack, vehicle: %s, speed: %d, allowed speed: %d).", GetName(playerid), GetVehicleName(vehicleid), getVehicleSpeed(vehicleid), aVehicleMaxSpeed[GetVehicleModel(vehicleid)-400]), anticheatInfo[playerid][ac_warningtime] = gettime() + 5;
        
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Speed-hack incar detected - playerid: %d, vehicleid: %d, speed: %d, max. speed: %d", playerid, GetPlayerVehicleID(playerid), getVehicleSpeed(vehicleid), aVehicleMaxSpeed[GetVehicleModel(vehicleid)-400]);
            #endif  
        }
    
        if((IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleID(playerid) != anticheatInfo[playerid][ac_lastvehicle] && anticheatInfo[playerid][ac_lastvehicle] != -1) && anticheatInfo[playerid][ac_entervehtime] > GetTickCount()) {
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (troll #1).", playerInfo[playerid][pName]), anticheatInfo[playerid][ac_warningtime] = gettime() + 5;
            
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Troll detected (#1 - fast enter) - playerid: %d, entered vehicleid: %d, enter time: %d, last vehicleid: %d", playerid, GetPlayerVehicleID(playerid), (anticheatInfo[playerid][ac_entervehtime] - GetTickCount()), getPlayerLastVehicle(playerid));
            #endif  
        }

        if(playerstate != PLAYER_STATE_SPECTATING && !isPlayerInDealership(playerid) && !IsPlayerInRangeOfPoint(playerid, 100.0, playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ]) && GetPlayerSpeed(playerid) < 70 && (X != 0.0 && Y != 0.0 && Z != 0.0)) {
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (teleport-hack).", playerInfo[playerid][pName]);
        
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Teleport-hack detected - playerid: %d, state: %s, speed: %d, time: eta 1s, last pos: %0.2f, %0.2f, %0.2f, new pos: %0.2f, %0.2f, %0.2f", playerid, playerstate == PLAYER_STATE_ONFOOT ? "on foot" : vehicleid != INVALID_VEHICLE_ID ? "in vehicle" : "?", GetPlayerSpeed(playerid), playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ], X, Y, Z);
            #endif
        }
    }
    return 1;
}

// ------------------------------------- //
//           Hooks                       //
// ------------------------------------- //

hook OP_StateChange(playerid, newstate, oldstate) {
    switch(newstate) {
        case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER: {
            anticheatInfo[playerid][ac_entervehtime] = GetTickCount() + 1350;
        
            #if DEBUG_ANTICHEAT == 1
                printf("[anticheat debug]: Entered in vehicle %d, tickcount setted: %d.", GetPlayerVehicleID(playerid), anticheatInfo[playerid][ac_entervehtime]);
            #endif  

            if(!isPlayerInDealership(playerid) && !IsPlayerInRangeOfPoint(playerid, 17.0, playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ])) {
                SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (teleport to vehicle).", playerInfo[playerid][pName]);

                #if DEBUG_ANTICHEAT == 1
                    new Float: X, Float: Y, Float: Z;
                    GetPlayerPos(playerid, X, Y, Z);
                    printf("[anticheat debug]: Teleport-hack detected (teleport to vehicle) - playerid: %d, entered vehicleid: %d, lastpos: %0.2f, %0.2f, %0.2f, newpos: %0.2f, %0.2f, %0.2f", playerid, GetPlayerVehicleID(playerid), playerInfo[playerid][pLastPosX], playerInfo[playerid][pLastPosY], playerInfo[playerid][pLastPosZ], X, Y, Z);
                #endif
            }   
        }
    }
    return 1;
}

hook OP_WeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    if(hitid != INVALID_PLAYER_ID && hittype == BULLET_HIT_TYPE_PLAYER && IsValidWeapon(weaponid)) {
        new 
            Float:startX, Float:startY, Float:startZ,
            Float:x, Float:y, Float:z;

        GetPlayerLastShotVectors(playerid, startX, startY, startZ, fX, fY, fZ);

        if(serverVars[9][svar_Value] == 1) {
            new const object_collided = CA_RayCastLine(startX, startY, startZ, fX, fY, fZ, x, y, z);

            if(object_collided && object_collided != WATER_OBJECT && (floatcmp(fX, 0.000000) && floatcmp(fY, 0.000000))) {
                SendAdmins(COLOR_DARKRED, "[adm-warning]: %s is shooting through objects in player %s. (weapon: %s, distance: %0.2fm, modelID: %d)", GetName(playerid), GetName(hitid), GunNames[weaponid], GetDistanceBetweenPlayers(playerid, hitid), object_collided);
                
                #if DEBUG_ANTICHEAT == 1
                    printf("[anticheat debug]: %s is shooting through objects in %s. (%f, %f, %f, %d)", GetName(playerid), GetName(hitid), x, y, z, object_collided);
                #endif

                return 0;
            }
        }
        
        if(serverVars[10][svar_Value] == 1 && !IsPlayerInRangeOfPoint(hitid, 3.0, fX, fY, fZ) && anticheatInfo[playerid][ac_warningtime] < gettime()) { 
            SendAdmins(COLOR_DARKRED, "[adm-warning]: %s may be cheating (aimbot).", GetName(playerid)); 
            anticheatInfo[playerid][ac_warningtime] = gettime() + 3;

            #if DEBUG_ANTICHEAT == 1
                GetPlayerPos(playerid, x, y, z), printf("[anticheat debug]: %s is using pro aimbot. (bullet %0.1f, %0.1f, %0.1f, player in range of bullet %0.1f, %0.1f, %0.1f)", GetName(playerid), fX, fY, fZ, x, y, z);
            #endif

            return 0;
        }
    }
    return 1;
}
