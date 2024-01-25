// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_COLLISION_AREAS 3

// ------------------------------------- //
//              Enum                     //
// ------------------------------------- //

static enum e_cInfo {
    Float:minX, 
    Float:minY,
    Float:maxX, 
    Float:maxY,
    area_id
}

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static const collisionArea[MAX_COLLISION_AREAS][e_cInfo] = {
    {426.2109375, -1739.46875, 559.2109375, -1700.46875, -1},
    {968.72265625, -1054.46875, 1071.72265625, -1023.46875, -1},
    {2056.20703125, -1881.21875, 2095.20703125, -1807.21875, -1}
};

// ------------------------------------- //
//      Init Collision Areas             //
// ------------------------------------- //

hook OnGameModeInit() {
    for(new i = 0; i < MAX_COLLISION_AREAS; ++i) {
        collisionArea[i][area_id] = CreateDynamicRectangle(collisionArea[i][minX], collisionArea[i][minY], collisionArea[i][maxX], collisionArea[i][maxY]);
        Streamer_SetIntData(STREAMER_TYPE_AREA, collisionArea[i][area_id], E_STREAMER_EXTRA_ID, i);
    }
    return 1;
}

// ------------------------------------- //
//      Enter/Leave collision area       //
// ------------------------------------- //

hook OP_EnterDynamicArea(playerid, areaid) {
    new const id = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(id < MAX_COLLISION_AREAS && areaid == collisionArea[id][area_id]) 
         DisableRemoteVehicleCollisions(playerid, true);

    return 1;
}

hook OP_LeaveDynamicArea(playerid, areaid) {
    new const id = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(id < MAX_COLLISION_AREAS && areaid == collisionArea[id][area_id]) 
         DisableRemoteVehicleCollisions(playerid, false);

    return 1;
}