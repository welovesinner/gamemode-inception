/*
    TURFS
*/

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>

#define MAX_TURFS           (40)

enum E_TURFS
{
    turf_owner,
    
    turf_area,
    turf_zone
}

new turfsVariables[MAX_TURFS][E_TURFS],
    Iterator:server_turfs<MAX_TURFS>,
    TurfsOn[MAX_PLAYERS];

hook OnPlayerDisconnect(playerid, reason)
{
    TurfsOn[playerid] = 0;
}
query_function iniTurfs() {
    if(cache_num_rows() == 0) return 1;
    new id, Float:x, Float:y, Float:mx, Float:my;
    for(new i; i < cache_num_rows(); i++) {
        id = i + 1;

        id =                             cache_get_field_content_int(i, "id");
        turfsVariables[id][turf_owner] = cache_get_field_content_int(i, "gang");

        x = cache_get_field_content_float(i, "min_x");
        y = cache_get_field_content_float(i, "min_y");

        mx = cache_get_field_content_float(i, "max_x");
        my = cache_get_field_content_float(i, "max_y");

        turfsVariables[id][turf_zone] = GangZoneCreateEx(x, y, mx, my, id, 1.0);
        turfsVariables[id][turf_area] = CreateDynamicRectangle(x, y, mx, my, -1, 0, -1);

        Iter_Add(server_turfs, id);
    }
    printf("[script] %d turfs loaded", Iter_Count(server_turfs));
    return 1;
}


stock ShowPlayerTurfs(playerid)
{
    foreach(new turf : server_turfs)
    {
        switch(turfsVariables[turf][turf_owner])
        {
            case 6: GangZoneShowForPlayerEx(playerid, turfsVariables[turf][turf_zone], 0x33AA3399);
            case 7: GangZoneShowForPlayerEx(playerid, turfsVariables[turf][turf_zone], 0x66003399);
            case 8: GangZoneShowForPlayerEx(playerid, turfsVariables[turf][turf_zone], 0x1AFFFF99);
            case 9: GangZoneShowForPlayerEx(playerid, turfsVariables[turf][turf_zone], 0xB3B30099);
        }
    }
    
    TurfsOn[playerid] = 1;
    return 1;
}

stock HidePlayerTurfs(playerid)
{
    foreach(new turf : server_turfs)
    {
        GangZoneHideForPlayerEx(playerid, turfsVariables[turf][turf_zone]);
    }

    return 1;
}

stock GetGangTurfs(gang)
{
    new turfs;
    foreach(new turf : server_turfs) if(turfsVariables[turf][turf_owner] == gang) turfs++;
    return turfs;
}

CMD:turfs(playerid, params[])
{
    if(TurfsOn[playerid])
    {
        HidePlayerTurfs(playerid);
        TurfsOn[playerid] = 0;

        SCM(playerid, COLOR_WHITE, "Turfuri ascunse.");
    }

    else
    {
        ShowPlayerTurfs(playerid);

        SCM(playerid, COLOR_WHITE, "Turfuri afisate.");
    }

    return 1;
}

CMD:top(playerid, params[])
{
    SCM(playerid, COLOR_TEAL, "---- TOP GANGS ----");

    foreach(new g : server_groups)
    {
        if(groupVariables[g][gType] == 5) SCMf(playerid, COLOR_WHITE, "%s - %d turfs", groupVariables[g][gName], GetGangTurfs(g));
    }
    return 1;
}