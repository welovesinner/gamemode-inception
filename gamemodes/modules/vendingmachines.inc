// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//          Client Vending Machines      //
// ------------------------------------- //

static enum e_rmvVending {
    vending_modelid,

    Float:vending_X, Float:vending_Y, Float:vending_Z
}

static const removeVendingMachines[][e_rmvVending] = {
    {955, -862.82, 1536.60, 21.98},
    {956, 2271.72, -76.46, 25.96},
    {955, 1277.83, 372.51, 18.95},
    {956, 662.42, -552.16, 15.71},
    {955, 201.01, -107.61, 0.89},
    {955, -253.74, 2597.95, 62.24},
    {956, -253.74, 2599.75, 62.24},
    {956, -76.03, 1227.99, 19.12},
    {955, -14.70, 1175.35, 18.95},
    {1977, 316.87, -140.35, 998.58},
    {1775, 373.82, -178.14, 1000.73},
    {1776, 379.03, -178.88, 1000.73},
    {1775, 495.96, -24.32, 1000.73},
    {1776, 500.56, -1.36, 1000.73},
    {1775, 501.82, -1.42, 1000.73},
    {956, -1455.11, 2591.66, 55.23},
    {955, 2352.17, -1357.15, 23.77},
    {955, 2325.97, -1645.13, 14.21},
    {956, 2139.51, -1161.48, 23.35},
    {956, 2153.23, -1016.14, 62.23},
    {955, 1928.73, -1772.44, 12.94},
    {1776, 2222.36, 1602.64, 1000.06},
    {1775, 2222.20, 1606.77, 1000.05},
    {1775, 2155.90, 1606.77, 1000.05},
    {1775, 2209.90, 1607.19, 1000.05},
    {1776, 2155.84, 1607.87, 1000.06},
    {1776, 2202.45, 1617.00, 1000.06},
    {1776, 2209.24, 1621.21, 1000.06},
    {1776, 330.67, 178.50, 1020.07},
    {1776, 331.92, 178.50, 1020.07},
    {1776, 350.90, 206.08, 1008.47},
    {1776, 361.56, 158.61, 1008.47},
    {1776, 371.59, 178.45, 1020.07},
    {1776, 374.89, 188.97, 1008.47},
    {1775, 2576.70, -1284.43, 1061.09},
    {1775, 2225.20, -1153.42, 1025.90},
    {955, 1154.72, -1460.89, 15.15},
    {956, 2480.85, -1959.27, 12.96},
    {955, 2060.11, -1897.64, 12.92},
    {955, 1729.78, -1943.04, 12.94},
    {956, 1634.10, -2237.53, 12.89},
    {955, 1789.21, -1369.26, 15.16},
    {956, -2229.18, 286.41, 34.70},
    {955, -1980.78, 142.66, 27.07},
    {955, -2118.96, -423.64, 34.72},
    {955, -2118.61, -422.41, 34.72},
    {955, -2097.27, -398.33, 34.72},
    {955, -2092.08, -490.05, 34.72},
    {955, -2063.27, -490.05, 34.72},
    {955, -2005.64, -490.05, 34.72},
    {955, -2034.46, -490.05, 34.72},
    {955, -2068.56, -398.33, 34.72},
    {955, -2039.85, -398.33, 34.72},
    {955, -2011.14, -398.33, 34.72},
    {955, -1350.11, 492.28, 10.58},
    {956, -1350.11, 493.85, 10.58},
    {955, 2319.99, 2532.85, 10.21},
    {956, 2845.72, 1295.04, 10.78},
    {955, 2503.14, 1243.69, 10.21},
    {956, 2647.69, 1129.66, 10.21},
    {1209, -2420.21, 984.57, 44.29},
    {1302, -2420.17, 985.94, 44.29},
    {955, 2085.77, 2071.35, 10.45},
    {956, 1398.84, 2222.60, 10.42},
    {956, 1659.46, 1722.85, 10.21},
    {955, 1520.14, 1055.26, 10.00},
    {1775, -19.03, -57.83, 1003.63},
    {1775, -16.11, -91.64, 1003.63},
    {1775, -15.10, -140.22, 1003.63},
    {1775, -32.44, -186.69, 1003.63},
    {1775, -35.72, -140.22, 1003.63},
    {1776, -36.14, -57.87, 1003.63},
    {1776, -17.54, -91.71, 1003.63},
    {1776, -16.53, -140.29, 1003.63},
    {1776, -33.87, -186.76, 1003.63},
    {1775, -19.03, -57.83, 1003.63},
    {1776, -36.14, -57.87, 1003.63},
    {1775, -16.11, -91.64, 1003.63},
    {1776, -17.54, -91.71, 1003.63},
    {1776, -16.53, -140.29, 1003.63},
    {1775, -15.10, -140.22, 1003.63},
    {1776, -33.87, -186.76, 1003.63},
    {1775, -32.44, -186.69, 1003.63},
    {1775, -35.72, -140.22, 1003.63}
};

// ------------------------------------- //
//      Server Vending Machines          //
// ------------------------------------- //

enum e_vendingMachines {
    vending_objectid, vending_modelid, 

    Float:vending_X, Float:vending_Y, Float:vending_Z,
    Float:vending_rX, Float:vending_rY, Float:vending_rZ
}

new const vendingMachines[][e_vendingMachines] = {
    {-1, 955, -862.82, 1536.60, 21.98, 0.00, 0.00, 180.00},
    {-1, 956, 2271.72, -76.46, 25.96, 0.00, 0.00, 0.00},
    {-1, 955, 1277.83, 372.51, 18.95, 0.00, 0.00, 64.00},
    {-1, 956, 662.42, -552.16, 15.71, 0.00, 0.00, 180.00},
    {-1, 955, 201.01, -107.61, 0.89, 0.00, 0.00, 270.00},
    {-1, 955, -253.74, 2597.95, 62.24, 0.00, 0.00, 90.00},
    {-1, 956, -253.74, 2599.75, 62.24, 0.00, 0.00, 90.00},
    {-1, 956, -76.03, 1227.99, 19.12, 0.00, 0.00, 90.00},
    {-1, 955, -14.70, 1175.35, 18.95, 0.00, 0.00, 180.00},
    {-1, 956, -1455.11, 2591.66, 55.23, 0.00, 0.00, 180.00},
    {-1, 955, 2352.17, -1357.15, 23.77, 0.00, 0.00, 90.00},
    {-1, 955, 2325.97, -1645.13, 14.21, 0.00, 0.00, 0.00},
    {-1, 956, 2139.51, -1161.48, 23.35, 0.00, 0.00, 87.00},
    {-1, 956, 2153.23, -1016.14, 62.23, 0.00, 0.00, 127.00},
    {-1, 955, 1928.73, -1772.44, 12.94, 0.00, 0.00, 90.00},
    {-1, 955, 1154.72, -1460.89, 15.15, 0.00, 0.00, 270.00},
    {-1, 956, 2480.85, -1959.27, 12.96, 0.00, 0.00, 180.00},
    {-1, 955, 2060.11, -1897.64, 12.92, 0.00, 0.00, 0.00},
    {-1, 955, 1729.78, -1943.04, 12.94, 0.00, 0.00, 0.00},
    {-1, 956, 1634.10, -2237.53, 12.89, 0.00, 0.00, 0.00},
    {-1, 955, 1789.21, -1369.26, 15.16, 0.00, 0.00, 270.00},
    {-1, 956, -2229.18, 286.41, 34.70, 0.00, 0.00, 180.00},
    {-1, 955, 2319.99, 2532.85, 10.21, 0.00, 0.00, 0.00},
    {-1, 956, 2845.72, 1295.04, 10.78, 0.00, 0.00, 0.00},
    {-1, 955, 2503.14, 1243.69, 10.21, 0.00, 0.00, 180.00},
    {-1, 956, 2647.69, 1129.66, 10.21, 0.00, 0.00, 0.00},
    {-1, 955, 2085.77, 2071.35, 10.45, 0.00, 0.00, 90.00},
    {-1, 956, 1398.84, 2222.60, 10.42, 0.00, 0.00, 180.00},
    {-1, 956, 1659.46, 1722.85, 10.21, 0.00, 0.00, 0.00},
    {-1, 955, 1520.14, 1055.26, 10.00, 0.00, 0.00, 270.00}
};

// ------------------------------------- //
//            Load Function              //
// ------------------------------------- //

function loadVendingMachines() {
    for(new i = 0; i < sizeof vendingMachines; ++i) {
        vendingMachines[i][vending_objectid] = CreateDynamicObject(vendingMachines[i][vending_modelid], vendingMachines[i][vending_X], vendingMachines[i][vending_Y], vendingMachines[i][vending_Z], vendingMachines[i][vending_rX], vendingMachines[i][vending_rY], vendingMachines[i][vending_rZ]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, vendingMachines[i][vending_objectid], E_STREAMER_EXTRA_ID, i);
    }
    return printf("[GAMEMODE LOADED] Vending Machines: %d", sizeof vendingMachines);
}

// ------------------------------------- //
//            Functions                  //
// ------------------------------------- //

static GetNearbyVendingMachine(const playerid) {
    new  
        nearbyObject[1] = -1,
        Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerid, X, Y, Z);
    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_OBJECT, nearbyObject[0], _, 1.5);

    if(nearbyObject[0] == -1)
        return -1;

    switch(Streamer_GetIntData(STREAMER_TYPE_OBJECT, nearbyObject[0], E_STREAMER_MODEL_ID)) {
        case 955, 956: {
            return Streamer_GetIntData(STREAMER_TYPE_OBJECT, nearbyObject[0], E_STREAMER_EXTRA_ID);
        }
    }
    return -1;
}

function onPlayerUseVendingMachine(const playerid, const vendingid) {
    if(GetMoney(playerid) < 250 && GetMilliards(playerid) < 1) {
        sendError(playerid, "Ai nevoie de $250 pentru a folosii acest tonomat.");
        return ClearAnimations(playerid);
    }

    SetPlayerFacingAngle(playerid, vendingMachines[vendingid][vending_rZ]);

    ApplyAnimationEx(playerid, "VENDING", "VEND_USE", 10.0, 0, 0, 0, 0, 0, 1);
    PlayerPlaySound(playerid, 42600, 0.0, 0.0, 0.0);

    new Float:health;
    GetPlayerHealth(playerid, health);
    SetPlayerHealth(playerid, (health >= 85.0) ? 100.0 : health + 15.0);

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, 250);
    GameTextForPlayer(playerid, "~r~-$250", 5000, 1);

    sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s bought a drink from the vending machine.", GetName(playerid));

    return updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYVENDINGDRINK);
}

// ------------------------------------- //
//            Hooks                      //
// ------------------------------------- //

hook OnPlayerConnect(playerid) {
    for(new i = 0; i < sizeof removeVendingMachines; ++i) {
        RemoveBuildingForPlayer(playerid, removeVendingMachines[i][vending_modelid], removeVendingMachines[i][vending_X], removeVendingMachines[i][vending_Y], removeVendingMachines[i][vending_Z], 3.0);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SECONDARY_ATTACK) && GetPlayerAnimationIndex(playerid) != 1660) {
        new const vending = GetNearbyVendingMachine(playerid);

        if(vending != -1)
            return onPlayerUseVendingMachine(playerid, vending);
    }
    return 1;
}