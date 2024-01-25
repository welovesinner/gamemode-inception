// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constant                 //
// ------------------------------------- //

#define MAX_SAFEZONES 3

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static safezoneAreas[MAX_SAFEZONES];

// ------------------------------------- //
//          Load Query Function          //
// ------------------------------------- //

query_function load_safezones() {
    serverStuff[safeZones] = cache_num_rows();

    if(!serverStuff[safeZones]) 
        return print("[MYSQL INFO] No safe-zones were found in the database.");

    for(new i = 0; i < serverStuff[safeZones]; i++) {
        safezoneAreas[i] = CreateDynamicRectangle(cache_get_field_content_float(i, "minX"), cache_get_field_content_float(i, "minY"), cache_get_field_content_float(i, "maxX"), cache_get_field_content_float(i, "maxY"));
        Streamer_SetIntData(STREAMER_TYPE_AREA, safezoneAreas[i], E_STREAMER_EXTRA_ID, i);
    }
    return printf("[MYSQL LOADED] Safe-zones loaded: %d", serverStuff[safeZones]);
}

// ------------------------------------- //
//      Enter/Leave safe-zone            //
// ------------------------------------- //

hook OP_EnterDynamicArea(playerid, areaid) { 
    new const id = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(id < MAX_SAFEZONES && safezoneAreas[id] == areaid) {
        playerVars[playerid][var_insafezone] = true; 
        TextDrawShowForPlayer(playerid, SafezoneTD);
    }
    return 1;
}

hook OP_LeaveDynamicArea(playerid, areaid) {
    new const id = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(id < MAX_SAFEZONES && safezoneAreas[id] == areaid && playerVars[playerid][var_insafezone]) {
        playerVars[playerid][var_insafezone] = false; 
        TextDrawHideForPlayer(playerid, SafezoneTD); 
    }
    return 1;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:addsafezone(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 8)
        return sendError(playerid, "Nu ai acces la aceasta comanda.");

    if(serverStuff[safeZones] >= MAX_SAFEZONES-1)
        return sendError(playerid, "Limita a fost atinsa! ("#MAX_SAFEZONES")");

    new 
        Float:minX, Float:minY, Float:maxX, Float:maxY;

    if(sscanf(params, "ffff", minX, minY, maxX, maxY))
        return sendUsage(playerid, "/addsafezone <minX> <minY> <maxX> <maxY>");

    ++serverStuff[safeZones];

    safezoneAreas[serverStuff[safeZones]] = CreateDynamicRectangle(minX, minY, maxX, maxY);
    Streamer_SetIntData(STREAMER_TYPE_AREA, safezoneAreas[serverStuff[safeZones]], E_STREAMER_EXTRA_ID, serverStuff[safeZones]);

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_safezones` (minX, minY, maxX, maxY) VALUES ('%f', '%f', '%f', '%f')", minX, minY, maxX, maxY);
    mysql_tquery(SQL, gQuery, "", "");

    SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s added a new safe-zone. (dbid: %d)", GetName(playerid), serverStuff[safeZones]); 
    SCMf(playerid, COLOR_GREY, "* You added succesfully a new safe-zone! (dbid: %d)", serverStuff[safeZones]);
    return 1;
}