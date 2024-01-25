// ------------------------------------- //
//              Defines                  //
// ------------------------------------- //

#define MAX_DOORS 5

new Iterator:server_doors<MAX_DOORS>;

// ------------------------------------- //
//                Enums                  //
// ------------------------------------- //

enum doorInfo {
	dID,
	dLocked,
	dPickup,
	dLabelText[256],

	Float:dPosX,
	Float:dPosY,
	Float:dPosZ,
	Float:dIntX,
	Float:dIntY,
	Float:dIntZ,
	dInt,

	dPickupID,
	Text3D:dLabel
}

new doorsVariables[MAX_DOORS][doorInfo];

// ------------------------------------- //
//            Query Functions            //
// ------------------------------------- //

query_function load_doors() {
	if(cache_num_rows() == 0) return 1;

	new id;
	for(new i; i < cache_num_rows(); i++) {
		id = i + 1;

		doorsVariables[id][dID] = cache_get_field_content_int(i, "doorID");
		doorsVariables[id][dLocked] = cache_get_field_content_int(i, "doorLocked");
		doorsVariables[id][dPickup] = cache_get_field_content_int(i, "doorPickup");

		cache_get_field_content(i, "doorLabelText", doorsVariables[id][dLabelText], SQL, 256);

		doorsVariables[id][dPosX] = cache_get_field_content_float(i, "doorPosX");
		doorsVariables[id][dPosY] = cache_get_field_content_float(i, "doorPosY");
		doorsVariables[id][dPosZ] = cache_get_field_content_float(i, "doorPosZ");

		doorsVariables[id][dIntX] = cache_get_field_content_float(i, "doorIntX");
		doorsVariables[id][dIntY] = cache_get_field_content_float(i, "doorIntY");
		doorsVariables[id][dIntZ] = cache_get_field_content_float(i, "doorIntZ");

		doorsVariables[id][dInt] = cache_get_field_content_int(i, "doorInfo");

		Iter_Add(server_doors, id);

		doorsVariables[id][dPickupID] = CreateDynamicPickup(doorsVariables[id][dPickup], 23, doorsVariables[id][dPosX], doorsVariables[id][dPosY], doorsVariables[id][dPosZ], 0, 0, -1, 20.0);
		doorsVariables[id][dLabel] = CreateDynamic3DTextLabel(doorsVariables[id][dLabelText], COLOR_WHITE, doorsVariables[id][dPosX], doorsVariables[id][dPosY], doorsVariables[id][dPosZ], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
	}
	printf("[MYSQL LOADED] Doors loaded: %d", Iter_Count(server_doors));
	return 1;
}

// ------------------------------------- //
//            	 Hooks            		 //
// ------------------------------------- //

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 1555.5052,-1675.5836,16.1953))
		{
			if(playerInfo[playerid][pGroup] != 1 && groupVariables[1][gHQStatus] == 1) return SCM(playerid, COLOR_GREY, "Error:{ffffff} You are not a member of this faction.");
			SetPlayerPos(playerid, 288.841, 167.781, 1007.17);
			SetPlayerVirtualWorld(playerid, 2000 + 1);
			SetPlayerInterior(playerid, 3);
			SetPVarInt(playerid, "in_hq", 1);
		}
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 288.841, 167.781, 1007.17))
		{
			if(playerInfo[playerid][pGroup] != 1 && groupVariables[1][gHQStatus] == 1) return SCM(playerid, COLOR_GREY, "Error:{ffffff} You are not a member of this faction.");
			SetPlayerPos(playerid, 1555.5052,-1675.5836,16.1953);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			SetPVarInt(playerid, "in_hq", 0);
		}
		foreach(new g : server_groups) 
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, groupVariables[g][gExteriorX], groupVariables[g][gExteriorY], groupVariables[g][gExteriorZ])) 
			{
				if(playerInfo[playerid][pGroup] != g && groupVariables[g][gHQStatus] == 1) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not the member of this faction.");

				SetPlayerPos(playerid, groupVariables[g][gInteriorX], groupVariables[g][gInteriorY], groupVariables[g][gInteriorZ]);
				SetPlayerInterior(playerid, groupVariables[g][gInterior]);
				SetPlayerVirtualWorld(playerid, g + 20000);
				SetPVarInt(playerid, "in_hq", 1);
				return 1;
			}
			if(IsPlayerInRangeOfPoint(playerid, 2.0, groupVariables[g][gInteriorX], groupVariables[g][gInteriorY], groupVariables[g][gInteriorZ]))
			{
				if(playerInfo[playerid][pGroup] == 1)
				{
					SetPlayerPos(playerid, 1555.5052,-1675.5836,16.1953);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
					SetPVarInt(playerid, "in_hq", 0);
				}
				else
				{
					SetPlayerPos(playerid, groupVariables[g][gExteriorX], groupVariables[g][gExteriorY], groupVariables[g][gExteriorZ]);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
					SetPVarInt(playerid, "in_hq", 0);
				}
			}
		}
	}
	return 1;
}