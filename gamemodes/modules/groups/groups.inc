// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Defines                  //
// ------------------------------------- //

#define MAX_GROUPS 11

new
	Iterator:server_groups<MAX_GROUPS>,
	Iterator:DutyMember<MAX_PLAYERS>,
	Iterator:FactionMembers<MAX_GROUPS, MAX_PLAYERS>;

new
	selected_members[MAX_PLAYERS],
	dSelected[MAX_PLAYERS][101], 
	MemberSelect[MAX_PLAYERS],
	Selected[MAX_PLAYERS][101],
	selected_service[MAX_PLAYERS][100],
	selected_service_faction[MAX_PLAYERS],
	str2[256], str[256];

new haveServiceActive[MAX_PLAYERS],
	activeServiceTimer[MAX_PLAYERS],
	taxiServices,
	schoolServices,
	medicServices;


// ------------------------------------- //
//                Enums                  //
// ------------------------------------- //

enum groups {
	gID,
	gName[32],
	gMOTD[100],
	gMinLevel, 
	gMaxMembers,
	gHQStatus,
	gType,
	gAppStatus,

	Float:gExteriorX,
	Float:gExteriorY,
	Float:gExteriorZ,
	Float:gInteriorX,
	Float:gInteriorY,
	Float:gInteriorZ,
	gInterior,

	Float:gSafeX,
	Float:gSafeY,
	Float:gSafeZ,
	gSafeBalance[3],
	gRankName1[32],
	gRankName2[32],
	gRankName3[32],
	gRankName4[32],
	gRankName5[32],
	gRankName6[32],
	gRankName7[32],
	gSkins[9], // first 7 skins male, last 2 female
	gColor[8],
	
	Text3D:gLabel,
	gPickup
}

new groupVariables[MAX_GROUPS][groups];

// ------------------------------------- //
//            Query Functions            //
// ------------------------------------- //

query_function load_groups() {
	if(!cache_num_rows()) return 1;

	new id, result[256];
	for(new i; i < cache_num_rows(); i++) {
		id = i + 1;
		groupVariables[id][gID] = cache_get_field_content_int(i, "groupID");

		groupVariables[id][gMinLevel] = cache_get_field_content_int(i, "groupMinLevel");
		groupVariables[id][gMaxMembers] = cache_get_field_content_int(i, "groupMaxMembers");
		groupVariables[id][gHQStatus] = cache_get_field_content_int(i, "groupHQStatus");
		groupVariables[id][gType] = cache_get_field_content_int(i, "groupType");
		groupVariables[id][gAppStatus] = cache_get_field_content_int(i, "groupAppStatus");

		groupVariables[id][gExteriorX] = cache_get_field_content_float(i, "groupExteriorX");
		groupVariables[id][gExteriorY] = cache_get_field_content_float(i, "groupExteriorY");
		groupVariables[id][gExteriorZ] = cache_get_field_content_float(i, "groupExteriorZ");

		groupVariables[id][gInteriorX] = cache_get_field_content_float(i, "groupInteriorX");
		groupVariables[id][gInteriorY] = cache_get_field_content_float(i, "groupInteriorY");
		groupVariables[id][gInteriorZ] = cache_get_field_content_float(i, "groupInteriorZ");

		groupVariables[id][gInterior] = cache_get_field_content_int(i, "groupInterior");

		groupVariables[id][gSafeX] = cache_get_field_content_float(i, "groupSafeX");
		groupVariables[id][gSafeY] = cache_get_field_content_float(i, "groupSafeY");
		groupVariables[id][gSafeZ] = cache_get_field_content_float(i, "groupSafeZ");

		cache_get_field_content(i, "groupSafeBalance", result);
		sscanf(result, "p<|>iii", groupVariables[id][gSafeBalance][0], groupVariables[id][gSafeBalance][1], groupVariables[id][gSafeBalance][2]);

		cache_get_field_content(i, "groupRankNames", result);
		sscanf(result, "p<|>s[32]s[32]s[32]s[32]s[32]s[32]s[32]", groupVariables[id][gRankName1], groupVariables[id][gRankName2], groupVariables[id][gRankName3], groupVariables[id][gRankName4], groupVariables[id][gRankName5], groupVariables[id][gRankName6], groupVariables[id][gRankName7]);

		cache_get_field_content(i, "groupSkins", result);
		sscanf(result, "p<|>iiiiiiiii", groupVariables[id][gSkins][0], groupVariables[id][gSkins][1], groupVariables[id][gSkins][2], groupVariables[id][gSkins][3], groupVariables[id][gSkins][4], groupVariables[id][gSkins][5],
		groupVariables[id][gSkins][6], groupVariables[id][gSkins][7], groupVariables[id][gSkins][8]);

		cache_get_field_content(i, "groupColor", groupVariables[id][gColor]);

		cache_get_field_content(i, "groupMOTD", groupVariables[id][gMOTD]);
		cache_get_field_content(i, "groupName", groupVariables[id][gName], SQL, 32);

		CreateGroupLabel(id);
		Iter_Add(server_groups, id);
	}

	printf("[MYSQL LOADED] Groups loaded: %d", Iter_Count(server_groups));
	return 1;
}

query_function ShowFactionMembers(playerid)
{
    new
        memberName[MAX_PLAYER_NAME], memberRank, memberLastOnline[24], memberFactionWarns,
        memberFactionJoined, memberSQLId, rowId=0;

    gString = "Rank - Name\tLast Login\t\tFW\tDays\n";
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "Name", memberName);
        cache_get_field_content(i, "LastLogin", memberLastOnline);

        memberSQLId = cache_get_field_content_int(i, "ID");
        memberRank = cache_get_field_content_int(i, "playerGroupRank");
        memberFactionWarns = cache_get_field_content_int(i, "playerFactionWarns");
        memberFactionJoined = cache_get_field_content_int(i, "playerGroupJoin");

        dSelected[playerid][rowId] = memberSQLId;
        format(gString, sizeof gString, "%s%d - %s\t%s\t%d/3 fw\t%d days\n", gString, memberRank, memberName, (GetPlayerID(memberName) != INVALID_PLAYER_ID ? ("online right now") : (memberLastOnline)), memberFactionWarns, TSToDays(memberFactionJoined));

        rowId++;
    }
    if(playerInfo[playerid][pGroupRank] >= 6)
        Dialog_Show(playerid, DIALOG_MEMBERS, DIALOG_STYLE_TABLIST_HEADERS, "Faction members", gString, "Select", "Exit");
    else
        Dialog_Show(playerid, DIALOG_MEMBERS, DIALOG_STYLE_TABLIST_HEADERS, "Faction members", gString, "Exit", "");
    return 1;
}

giveRaportPoint(playerid, point) {
	switch(playerInfo[playerid][pGroup])
	{
		case 1: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Arrests and Kills: +1"); 
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}
				case 2: {
					if(playerInfo[playerid][pGroupRank] >= 2) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Fines: +1"); 
						playerInfo[playerid][pFactionRaport2]++;
					}	
				}
				case 3: {
					if(playerInfo[playerid][pGroupRank] >= 3) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Licenses: +1");
						playerInfo[playerid][pFactionRaport3]++;
					}	
				}	
			}
		}
		case 2: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Arrests and Kills: +1"); 
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}
				case 2: {
					if(playerInfo[playerid][pGroupRank] >= 2) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Fines: +1"); 
						playerInfo[playerid][pFactionRaport2]++;
					}	
				}
				case 3: {
					if(playerInfo[playerid][pGroupRank] >= 3) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Licenses: +1");
						playerInfo[playerid][pFactionRaport3]++;
					}	
				}	
			}
		}
		case 3: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Heals gived: +1"); 
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}	
			}
		}
		case 4: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | New's: +1"); 
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}
				case 2: {
					if(playerInfo[playerid][pGroupRank] >= 3) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Interviews: +1"); 
						playerInfo[playerid][pFactionRaport2]++;
					}
				}
			}
		}
		case 5: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Contracts: +1"); 
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}	
			}
		}
		/*case 10: {
			switch(point)
			{
				case 1: {
					if(playerInfo[playerid][pGroupRank] >= 1) {
						SCM(playerid, COLOR_YELLOW, "Raport+ | Orders: +1");
						playerInfo[playerid][pFactionRaport1]++;
					}	
				}	
			}
		}*/
	}
	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `FactionRaport1` = '%d', `FactionRaport2`= '%d', `FactionRaport3`= '%d' where `ID` = '%d'",
	playerInfo[playerid][pFactionRaport1], playerInfo[playerid][pFactionRaport2], playerInfo[playerid][pFactionRaport3], playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	return true;
} 

// ------------------------------------- //
//               Hooks                	 //
// ------------------------------------- //

hook OnPlayerConnect(playerid)
{
	playerInfo[playerid][pGroup] = 0;
	selected_members[playerid] = -1;
	selected_service_faction[playerid] = -1;
	if(haveServiceActive[playerid] == 1) taxiServices--;
	if(haveServiceActive[playerid] == 3) medicServices--;
	haveServiceActive[playerid] = 0;
	activeServiceTimer[playerid] = -1;
	return 1;
}

hook OnPlayerDisconnect(playerid)
{
	if(Iter_Contains(DutyMember, playerid))
		Iter_Remove(DutyMember, playerid);

	if(playerInfo[playerid][pGroup] != 0)
		Iter_Remove(FactionMembers<playerInfo[playerid][pGroup]>, playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	new group = playerInfo[playerid][pGroup];
	if(playerInfo[playerid][pGroup] > 0) 
	{
		if(playerInfo[playerid][pGroup] == 1)
		{
			SetPlayerPos(playerid, 288.841, 167.781, 1007.17);
			SetPlayerVirtualWorld(playerid, 2000 + 1);
			SetPlayerInterior(playerid, 3);
			SetPVarInt(playerid, "in_hq", 1);
		}
		if(playerInfo[playerid][pGroup] > 1)
		{
			SetPlayerPos(playerid, groupVariables[group][gInteriorX], groupVariables[group][gInteriorY], groupVariables[group][gInteriorZ]);
			SetPlayerInterior(playerid, groupVariables[group][gInterior]);
			SetPlayerVirtualWorld(playerid, 20000 + group);
			SetPVarInt(playerid, "in_hq", 1);
		}
		Iter_Add(FactionMembers<playerInfo[playerid][pGroup]>, playerid);
	}
	return 1;
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

CreateGroupLabel(g) {
	gString[0] = EOS;
	format(gString, sizeof(gString), "Group: {1C8A15}%s{ffffff} (ID: {1C8A15}%d{ffffff})\nDoor status: %s", groupVariables[g][gName], g, groupVariables[g][gHQStatus] == 1 ? "{d42619}locked" : "{a3ffac}unlocked");

	if(g == 1) {
		groupVariables[g][gLabel] = CreateDynamic3DTextLabel(gString, COLOR_WHITE, 242.3004,66.2824,1003.6406, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6);
		groupVariables[g][gPickup] = CreateDynamicPickup(1247, 23, 242.3004, 66.2824, 1003.6406, 0, 6, 0, 20.0);
	}
	else {
		groupVariables[g][gLabel] = CreateDynamic3DTextLabel(gString, COLOR_WHITE, groupVariables[g][gExteriorX], groupVariables[g][gExteriorY], groupVariables[g][gExteriorZ], 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
		
		new pickup;
		switch(groupVariables[g][gType]) {
			case 1: pickup = 1247;
			case 2,3,4: pickup = 1314;
			case 5: pickup = 1313;
		}	

		groupVariables[g][gPickup] = CreateDynamicPickup(pickup, COLOR_WHITE, groupVariables[g][gExteriorX], groupVariables[g][gExteriorY], groupVariables[g][gExteriorZ], 0, 0, 0, 20.0);
	}
	return 1;
}

GetFactionMembers(id) return Iter_Count(FactionMembers<id>);

TSToDays( iTimeStamp )
{
    if( iTimeStamp <= 0 ) return 1;
    new days = 0, actualTimeStamp = gettime ( ) - iTimeStamp;
    days = ( actualTimeStamp / 86400 );
    return ( days == 0 ) ? ( 0 ) : ( days );
}
SendGroupMessage(group, color, const message[], {Float, _}:...) {
	static out[256];
	va_format(out, sizeof(out), message, ___(3));

	foreach(new i : FactionMembers<group>) {
		SCMf(i, color, out);
	}

	return 1;
}
NumeFactiune(factionId)
{
    new
        factionName[32];

	format(factionName, sizeof factionName, groupVariables[factionId][gName]);
    return factionName;
}
SendFactionMessage(group, color, const text[]) 
{
    foreach(new i : Player) 
    {
    	if(playerInfo[i][pGroup] == group) SCMf(i, color, text);
    }
    return 1;
}

SetPlayerColorEx(playerid) {
	switch(playerInfo[playerid][pGroup]) {
		case 1: SetPlayerColor(playerid, 0x0066FFFF);
		case 2: SetPlayerColor(playerid, 0x0000CCFF);
		case 3: SetPlayerColor(playerid, 0xFF9966FF);
		case 4: SetPlayerColor(playerid, 0x996699FF);
		case 5: SetPlayerColor(playerid, 0x6e1818FF);
		case 6: SetPlayerColor(playerid, 0x40863CAA);
		case 7: SetPlayerColor(playerid, 0xBD1CDEC8);
		case 8: SetPlayerColor(playerid, 0x18EBD6C8);
		case 9: SetPlayerColor(playerid, 0xFFAE00C8);
		default: SetPlayerColor(playerid, COLOR_WHITE);
	}
	return 1;
}

function GetDays(time) {
	return ((gettime() - time) / 86400);
}
function getPlayerID(id) {
	foreach(new i : Player) if(playerInfo[i][pSQLID] == id) return i;
	return INVALID_PLAYER_ID;
}
function GetPlayerID(name[]) {
	foreach(new i : Player) if(strsame(playerInfo[i][pName], name, true)) return i;
	return INVALID_PLAYER_ID;
}

query_function showGroupMembers(playerid) {
	new status, string[100], lastonline[50], nume[MAX_PLAYER_NAME], rank, FW, playerID, count = 0;
	gString[0] = (EOS); format(gString, sizeof gString, "Nume\tFaction Warns\tRank\tOnline\n");
	if(!cache_num_rows()) return SCM(playerid, COLOR_GREY, "Error:{ffffff} There is a big problem.");
	for(new i = 0; i < cache_num_rows(); i++) {
		cache_get_field_content(i, "Name", string), format(nume, MAX_PLAYER_NAME, string);
		cache_get_field_content(i, "LastLogin", string), format(lastonline, 50, string);
		cache_get_field_content_int(i, "Status", status);
		cache_get_field_content_int(i, "playerGroupRank", rank);
		cache_get_field_content_int(i, "playerFactionWarns", FW);
		cache_get_field_content_int(i, "ID", playerID);
		
		if(status == 0) format(gString, sizeof gString, "%s%s\t%d/3\t%d\t%s\n", gString, nume, FW, rank, lastonline);
		else format(gString, sizeof gString, "%s%s\t%d/3\t%d\t%s\n", gString, nume, FW, rank, (status == 1) ? ("Online") : ("AFK"));
		format(Selected[count][playerid],MAX_PLAYER_NAME, nume);
		count ++;
	} 
	Dialog_Show(playerid, DIALOG_GMEMBERS, DIALOG_STYLE_TABLIST_HEADERS, "Members:", gString, "Ok", "Exit");
	return 1; 
}
ShowPlayerRaport(playerid, targetid)
{
	SCMf(playerid, -1, "------ Raport ------");
    SCMf(playerid, COLOR_GREEN, ">>{ffffff} Hours playing - %.2f/5:00", playerInfo[targetid][pRaportPlaying]);
	if(playerInfo[targetid][pGroup] == 1)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Fines - %d/3", playerInfo[targetid][pFactionRaport2]);
			case 3: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Fines - %d/3", playerInfo[targetid][pFactionRaport2]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Licenses - %d/3", playerInfo[targetid][pFactionRaport3]);
			case 4: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/10", playerInfo[targetid][pFactionRaport1]);
			case 5: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/5", playerInfo[targetid][pFactionRaport1]);
		}
		return 1;
	}
	if(playerInfo[targetid][pGroup] == 2)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Fines - %d/3", playerInfo[targetid][pFactionRaport2]);
			case 3: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/15", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Fines - %d/3", playerInfo[targetid][pFactionRaport2]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Licenses - %d/3", playerInfo[targetid][pFactionRaport3]);
			case 4: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/10", playerInfo[targetid][pFactionRaport1]);
			case 5: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Arrests and Kills - %d/5", playerInfo[targetid][pFactionRaport1]);
		}
		return 1;
	}
	else if(playerInfo[targetid][pGroup] == 3)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Heals gived - %d/25", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Heals gived - %d/35", playerInfo[targetid][pFactionRaport1]);
			case 3: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Heals gived - %d/15", playerInfo[targetid][pFactionRaport1]);
			case 4: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Heals gived - %d/10", playerInfo[targetid][pFactionRaport1]);
			case 5: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Heals gived - %d/10", playerInfo[targetid][pFactionRaport1]);
		}
		return 1;
	}
	else if(playerInfo[targetid][pGroup] == 4)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, ">>{ffffff} New's - %d/50", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, ">>{ffffff} New's - %d/55", playerInfo[targetid][pFactionRaport1]);
			case 3: SCMf(playerid, COLOR_GREEN, ">>{ffffff} New's - %d/45", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Interviews - %d/3", playerInfo[targetid][pFactionRaport2]);
			case 4: SCMf(playerid, COLOR_GREEN, ">>{ffffff} New's - %d/20", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Interviews - %d/5", playerInfo[targetid][pFactionRaport2]);
			case 5: SCMf(playerid, COLOR_GREEN, ">>{ffffff} New's - %d/15", playerInfo[targetid][pFactionRaport1]), SCMf(playerid, COLOR_GREEN, ">>{ffffff} Interviews - %d/10", playerInfo[targetid][pFactionRaport2]);
		}
		return 1;
	}

	else if(playerInfo[targetid][pGroup] == 5)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Contracts - %d/20", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Contracts - %d/15", playerInfo[targetid][pFactionRaport1]);
			case 3: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Contracts - %d/10", playerInfo[targetid][pFactionRaport1]);
			case 4: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Contracts - %d/5", playerInfo[targetid][pFactionRaport1]);
			case 5: SCMf(playerid, COLOR_GREEN, ">>{ffffff} Contracts - %d/5", playerInfo[targetid][pFactionRaport1]);
		}
		return 1;
	}
	/*else if(playerInfo[targetid][pGroup] == 10)
	{
		switch(playerInfo[targetid][pGroupRank]) {
			case 1: SCMf(playerid, COLOR_GREEN, "Orders - %d/35", playerInfo[targetid][pFactionRaport1]);
			case 2: SCMf(playerid, COLOR_GREEN, "Orders - %d/40", playerInfo[targetid][pFactionRaport1]);
			case 3: SCMf(playerid, COLOR_GREEN, "Orders - %d/25", playerInfo[targetid][pFactionRaport1]);
			case 4: SCMf(playerid, COLOR_GREEN, "Orders - %d/15", playerInfo[targetid][pFactionRaport1]);
			case 5: SCMf(playerid, COLOR_GREEN, "Orders - %d/10", playerInfo[targetid][pFactionRaport1]);
		}
		return 1;
	}*/
	SCMf(playerid, -1, "-------------------------------");
	return 1;
}

// ------------------------------------- //
//               Commands                //
// ------------------------------------- //

YCMD:factions(playerid, params[], help) {
    gDialog[0] = EOS;
    format(gDialog, sizeof(gDialog), "Faction\tMembers\tApps status\n");

    foreach(new g : server_groups) 
    {
        format(gDialog, sizeof(gDialog), "%s%s\t%d/%d members\t%s\n", gDialog, groupVariables[g][gName], GetFactionMembers(g), groupVariables[g][gMaxMembers], groupVariables[g][gAppStatus] == 0 ? "closed" : "open");
    }

    Dialog_Show(playerid, DIALOG_GROUPS, DIALOG_STYLE_TABLIST_HEADERS, "Server Factions", gDialog, "Select", "Exit");
    return 1;
}

YCMD:gotohq(playerid, params[], help) {
    if(!playerInfo[playerid][pAdmin])
        return SCM(playerid, COLOR_GREY, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

	if(isnull(params)) return SendClientMessage(playerid, COLOR_GREY, "Usage: {ffffff}/gotohq [hq id]");
	if(strval(params) < 1 || strval(params) > Iter_Count(server_groups)) return SendClientMessage(playerid, COLOR_GREY, "Invalid HQ.");
	new hq = strval(params);

	if(hq != 1) SetPlayerPos(playerid, groupVariables[hq][gExteriorX], groupVariables[hq][gExteriorY], groupVariables[hq][gExteriorZ]);
	else SetPlayerPos(playerid, 1554.1754,-1675.6774,16.1953);

	SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s used /gotohq %d.", GetName(playerid), hq);
	SCMf(playerid, COLOR_WHITE, "You have been teleported to %s", groupVariables[hq][gName]);

	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return true;
}

YCMD:setleader(playerid, params[], help) {
	if(playerInfo[playerid][pAdmin] < 3) return 1;

	new target, group;
	if(sscanf(params, "ud", target, group)) return SCM(playerid, COLOR_GREY, "Usage: {ffffff}/setleader [player id/name] [group]");
	if(group < 1 || group > 8) return SCM(playerid, COLOR_GREY, "Error: {ffffff}Invalid group.");

	if(!IsPlayerConnected(target)) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}Player not connected.");
	if(playerInfo[target][pGroup] > 0) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}That player is already in a faction.");

	if(group < 1 || group > Iter_Count(server_groups)) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}Invalid group id.");

	playerInfo[target][pGroup] = group;
	playerInfo[target][pGroupRank] = 7;
	playerInfo[target][pGroupJoin] = gettime();
	playerInfo[target][pFactionWarns] = 0;
	playerInfo[target][pFactionPunish] = 0;

	gString[0] = EOS;
	format(gString, sizeof(gString), "%s is now the leader of faction %s.", GetName(target), groupVariables[group][gName]);

	SetPlayerColorEx(target);

	SCMf(target, COLOR_LIGHTRED, "(AdmCmd):{ffffff} Administrator %s has set you to lead group %s.", GetName(playerid), groupVariables[group][gName]);
	SendAdmins(COLOR_LIGHTRED, gString);

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerGroup` = '%d', `playerGroupRank` = '7', `playerGroupJoin` = '%d', `playerFactionPunish` = '0', `playerFactionWarns` = '0' where `ID` = '%d'", group, gettime(), playerInfo[target][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	Iter_Add(FactionMembers<playerInfo[target][pGroup]>, target);
	return 1;
}

YCMD:fpk(playerid, params[], help) {
	if(playerInfo[playerid][pAdmin] < 3) return 1;

	new target, fp, reason[32];
	if(sscanf(params, "uds[32]", target, fp, reason)) return SCM(playerid, COLOR_GREY, "Usage: {ffffff}/auninvite [player id/name] [faction punish] [reason]");
	if(!IsPlayerConnected(target)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}Player not connected.");
	if(playerInfo[target][pGroup] == 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not in a group.");
	if(fp < 0 || fp > 60) return SCM(playerid, COLOR_GREY, "Error: {ffffff}Invalid FP (0-60).");

	gString[0] = EOS;
	format(gString, sizeof(gString), "%s has been uninvited by admin %s from %s (rank %i), without FP, after %d days, reason: %s.", GetName(target), GetName(playerid), groupVariables[playerInfo[target][pGroup]][gName], playerInfo[target][pGroupRank], (gettime()-playerInfo[target][pGroupJoin])/86400, reason);
	SendAdmins(COLOR_LIGHTRED, gString);
	SendGroupMessage(playerInfo[target][pGroup], COLOR_TEAL, gString);

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerGroup` = '0', `playerGroupRank` = '0', `playerGroupJoin` = '0', `playerFactionPunish` = '0', `playerFactionWarns` = '0' where `ID` = '%d'", playerInfo[target][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");

	playerInfo[target][pFactionRaport1] = 0;
	playerInfo[target][pFactionRaport2] = 0;
	playerInfo[target][pFactionRaport3] = 0;
	playerInfo[target][pRaportPlaying] = 0;

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `FactionRaport1` = '%d', `FactionRaport2`= '%d', `FactionRaport3`= '%d', `RaportPlaying`= '%f' where `ID` = '%d'",
    playerInfo[target][pFactionRaport1], playerInfo[target][pFactionRaport2], playerInfo[target][pFactionRaport3], playerInfo[target][pRaportPlaying], playerInfo[target][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");

	if(Iter_Contains(DutyMember, target)) Iter_Remove(DutyMember, target);
	Iter_Remove(FactionMembers<playerInfo[target][pGroup]>, target);
	DestroySpawnedVehicle(target);

	playerInfo[target][pGroup] = 0;
	playerInfo[target][pGroupRank] = 0;
	playerInfo[target][pGroupJoin] = 0;
	playerInfo[target][pFactionWarns] = 0;
	playerInfo[target][pFactionPunish] = 0;
	SetPlayerColorEx(target);
	SetPlayerSkin(target, playerInfo[target][pSkin]);
	SpawnPlayer(target);
	return 1;
}

YCMD:showmotd(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] == 0) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}You are not in a group.");
	SCMf(playerid, COLOR_TEAL, "Group MOTD: {FFFFFF}%s", groupVariables[playerInfo[playerid][pGroup]][gMOTD]);
	return true;
}

YCMD:gmotd(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] == 0) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}You are not in a group.");
	if(playerInfo[playerid][pGroupRank] < 6) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}You don't have rank 6+.");
	if(isnull(params)) return SCM(playerid, COLOR_GREY, "Usage: {FFFFFF}/gmotd [MOTD]");

	format(groupVariables[playerInfo[playerid][pGroup]][gMOTD], 96, params);
	SendGroupMessage(playerInfo[playerid][pGroup], COLOR_ANNOUNCE, "%s has changed the group MOTD to '%s'.", GetName(playerid), params);

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_groups` set `groupMOTD` = '%e' where `groupID` = '%d'", params, playerInfo[playerid][pGroup]);
	mysql_tquery(SQL, gQuery, "", "");
	return 1;
}

YCMD:r(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] == 0)
		return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte dintr-o factiune.");

	if(playerInfo[playerid][pGroup] == 4 || playerInfo[playerid][pGroup] == 5 || playerInfo[playerid][pGroup] == 6 || playerInfo[playerid][pGroup] == 7 || playerInfo[playerid][pGroup] == 8 || playerInfo[playerid][pGroup] == 9)
			return SCM(playerid, COLOR_GREY, "Error:{ffffff} Factiunea ta nu dispune de aceasta comanda. Foloseste comanda /f pentru a utiliza chat-ul factiunii.");

	new message[96];
	if(sscanf(params, "s[96]", message)) return SCM(playerid, COLOR_GREY, "Usage: {ffffff}/r(adio) [message]");

	new g = playerInfo[playerid][pGroup];
	switch(playerInfo[playerid][pGroupRank]) {
		case 1: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName1], GetName(playerid), message);
		case 2: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName2], GetName(playerid), message);
		case 3: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName3], GetName(playerid), message);
		case 4: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName4], GetName(playerid), message);
		case 5: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName5], GetName(playerid), message);
		case 6: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName6], GetName(playerid), message);
		case 7: SendGroupMessage(g, COLOR_RADIO, "* %s %s: %s", groupVariables[g][gRankName7], GetName(playerid), message);
	}

	gString[0] = EOS;
	format(gString, sizeof(gString), "(radio) \"%s\"", message);
	SetPlayerChatBubble(playerid, gString, 0xFFFFFFCC, 10.0, 10000);
	return 1;
}

YCMD:d(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] < 1 && groupVariables[playerInfo[playerid][pGroup]][gType] > 2) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not in a department.");

	new message[96];
	if(sscanf(params, "s[96]", message)) return SCM(playerid, COLOR_GREY, "Usage: {ffffff}/d [message]");

	new g = playerInfo[playerid][pGroup];
	for(new x = 1; x < 4; x++) {
		switch(playerInfo[playerid][pGroupRank]) {
			case 1: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName1], GetName(playerid), message);
			case 2: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName2], GetName(playerid), message);
			case 3: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName3], GetName(playerid), message);
			case 4: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName4], GetName(playerid), message);
			case 5: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName5], GetName(playerid), message);
			case 6: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName6], GetName(playerid), message);
			case 7: SendGroupMessage(x, COLOR_D, "* %s %s: %s", groupVariables[g][gRankName7], GetName(playerid), message);
		}
	}

	gString[0] = EOS;
	format(gString, sizeof(gString), "(departments) \"%s\"", message);
	SetPlayerChatBubble(playerid, gString, 0xFFFFFFCC, 10.0, 10000);
	return 1;
}

YCMD:f(playerid, params[], help) {
	new group = playerInfo[playerid][pGroup];
	if(group == 0) return 1;
	if(playerInfo[playerid][pGroup] == 0)
		return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte dintr-o factiune.");
	
	if(groupVariables[group][gType] == 1 || groupVariables[group][gType] == 2) return SendClientMessage(playerid, COLOR_GREY, "Error:{ffffff} Factiunea ta nu dispune de aceasta comanda. Foloseste comanda /r pentru a putea vorbi pe chat-ul factiunii.");
	if(isnull(params)) return SendClientMessage(playerid, COLOR_GREY, "Usage: {ffffff}/f [message]");

	new str[256];
	switch(playerInfo[playerid][pGroupRank]) {
		case 1: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName1], GetName(playerid), params);
		case 2: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName2], GetName(playerid), params);
		case 3: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName3], GetName(playerid), params);
		case 4: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName4], GetName(playerid), params);
		case 5: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName5], GetName(playerid), params);
		case 6: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName6], GetName(playerid), params);
		case 7: format(str, sizeof(str), "%s %s: %s", groupVariables[group][gRankName7], GetName(playerid), params);
	}

	if(playerInfo[playerid][pGroupRank] >= 6) SendFactionMessage(group, COLOR_TEAL, str);
	else SendFactionMessage(group, 0x2BCEC9FF, str);
	return true;
}

YCMD:duty(playerid, params[], help)
{
	if(playerInfo[playerid][pGroup] == 0) return SCM(playerid, COLOR_GREY, "Error:{ffffff} You are not a member of faction.");
	if(GetPVarInt(playerid, "in_hq") == 0) return SCM(playerid, COLOR_GREY, "Error:{ffffff} Poti folosi aceasta comanda doar din interiorul hq-ului/casei."); 
	new group = playerInfo[playerid][pGroup];
	if(Iter_Contains(DutyMember, playerid)) {
		SetPlayerSkin(playerid, playerInfo[playerid][pSkin]);
		Iter_Remove(DutyMember, playerid);
		SetPlayerColor(playerid, COLOR_WHITE);
		SCM(playerid, COLOR_GREEN, "Faction:{ffffff} Nu mai esti la datorie in cadrul factiunii.");
		TogglePlayerControllable(playerid, true);
		if(playerInfo[playerid][pGroup] == 1)
		{
			ResetPlayerWeapons(playerid);
		}
	}
	else {
		if(playerInfo[playerid][pGender] == 2) SetPlayerSkin(playerid, groupVariables[group][gSkins][playerInfo[playerid][pGroupRank]-1]);
		else SetPlayerSkin(playerid, groupVariables[group][gSkins][8]);
		Iter_Add(DutyMember, playerid);
		SetPlayerColorEx(playerid);
		SCM(playerid, COLOR_GREEN, "Faction:{ffffff} Acum esti la datorie.");
		TogglePlayerControllable(playerid, true);
		if(playerInfo[playerid][pGroup] == 1)
		{
			GivePlayerWeapon(playerid, 31, 999);
			GivePlayerWeapon(playerid, 24, 999);
			GivePlayerWeapon(playerid, 29, 999);
			GivePlayerWeapon(playerid, 27, 999);

			sendNearbyMessage(playerid, COLOR_PURPLE, 5.0, "* Officer %s takes some guns and a badge from his locker.", GetName(playerid));
		}
	}
	return 1;
}

YCMD:raport(playerid, params[], help)
{
	if(playerInfo[playerid][pGroup] == 0)
		return SCM(playerid, COLOR_GREY, "You are not a member of faction.");

	ShowPlayerRaport(playerid, playerid);
	return true;
}

YCMD:changerank(playerid, params[], help)
{
    if(playerInfo[playerid][pGroupRank] < 7)
        return SCM(playerid, -1, "You are not a leader.");

    new
        targetId, rankLevel;
    
    if(sscanf(params, "ui", targetId, rankLevel))
        return SCM(playerid, COLOR_GREY, "Usage:{ffffff} /changerank [name/playerid] [1-6]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, -1, "Player not connected.");
    
    if(rankLevel > 6 || rankLevel < 1)
        return SCM(playerid, -1, "Minimum rank is 1 and maximum is 6.");

    if(playerInfo[targetId][pGroup] != playerInfo[playerid][pGroup])
        return SCM(playerid, -1, "This member is not in your faction.");

    if(playerInfo[targetId][pGroupRank] == 7)
        return SCM(playerid, -1, "This player is a leader.");

    SCMf(playerid, COLOR_LIGHTRED, "Group:{ffffff} You have promoted %s to rank %d.", GetName(targetId), rankLevel);
    SCMf(targetId, COLOR_LIGHTRED, "Group:{ffffff} %s has promoted you to rank %d.", GetName(playerid), rankLevel);
    
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_GENANNOUNCE, "%s changed %s's faction rank to %d.", GetName(playerid), GetName(targetId), rankLevel);

    playerInfo[targetId][pGroup] = playerInfo[playerid][pGroup];

    playerInfo[targetId][pGroupRank] = rankLevel;

    playerInfo[targetId][pFactionRaport1] = 0;
    playerInfo[targetId][pFactionRaport2] = 0;
	playerInfo[targetId][pFactionRaport3] = 0;
	playerInfo[targetId][pRaportPlaying] = 0;

    mysql_format(SQL, gString, sizeof gString, "update `server_users` set `playerGroupRank` = '%d', `FactionRaport1` = '0', `FactionRaport2` = '0', `FactionRaport3` = '0', `RaportPlaying` = '0' where `ID` = '%d';", playerInfo[targetId][pGroupRank], playerInfo[targetId][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

YCMD:members(playerid, params[], help)
{
    if(!playerInfo[playerid][pGroup])
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte dintr-o factiune!");

    mysql_format(SQL, gString, sizeof gString, "select * from `server_users` where `playerGroup` = '%d' order by `playerGroupRank` desc limit 20", playerInfo[playerid][pGroup]);
    mysql_tquery(SQL, gString, "ShowFactionMembers", "d", playerid);
    return 1;
}

YCMD:invite(playerid, params[], help) {
    if(playerInfo[playerid][pGroup] >= 1 && playerInfo[playerid][pGroupRank] >= 6) {
        new player;
        if(sscanf(params, "u", player)) return SendClientMessage(playerid, COLOR_GREY, "Usage: {ffffff}/invite [playerid]");
        else {
            if(!IsPlayerConnected(player)) return SendClientMessage(playerid, COLOR_GREY, "Error:{ffffff} The specified player/name is not connected.");
            if(player == playerid) return true;
			else if(playerInfo[player][pGroup] > 0) return SendClientMessage(playerid, COLOR_GREY, "Error:{ffffff} That player is already in a group.");
			else if(playerInfo[player][pFactionPunish] > 0) return SendClientMessage(playerid, COLOR_GREY, "Error:{ffffff} This player have FP!");

			if(!IsPlayerInRangeOfPlayer(playerid, player, 10.0))
				return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not near you.");

			SendClientMessage(playerid, COLOR_LGREEN, "Processing invite...");
			SCMf(playerid, COLOR_WHITE, "You have invited %s to join your group.", GetName(player));
			SCMf(player, COLOR_LGREEN,  "%s has invited you to join group %s (to accept the invitation, type '/acceptinvite').", GetName(playerid), groupVariables[playerInfo[playerid][pGroup]][gName]);
			SetPVarInt(player, "invID", playerInfo[playerid][pGroup]);
			SetPVarString(player, "invName", GetName(playerid)); 
		}
    }
    return 1;
}

YCMD:acceptinvite(playerid, params[], help)
{
	if(GetPVarInt(playerid, "invID") >= 1) 
	{
		if(playerInfo[playerid][pGroup] == 0) 
		{
			if(playerInfo[playerid][pFactionPunish] == 0) 
			{
				new members, query[128];
				format(query, 128, "SELECT * FROM `server_users` WHERE `server_users`.`playerGroup` = '%d'", GetPVarInt(playerid, "invID"));
				new Cache: mastau = mysql_query(SQL, query);
				members = cache_num_rows();
				cache_delete(mastau);
				if(members < groupVariables[GetPVarInt(playerid, "invID")][gMaxMembers]) 
				{
					playerInfo[playerid][pGroup] = GetPVarInt(playerid, "invID");
					playerInfo[playerid][pGroupRank] = 1;
					playerInfo[playerid][pFactionWarns] = 0;

					Iter_Add(FactionMembers<playerInfo[playerid][pGroup]>, playerid);

					new name[MAX_PLAYER_NAME];
					GetPVarString(playerid, "invName", name, MAX_PLAYER_NAME);
					SCMf(playerid, COLOR_LGREEN, "You are now a member of the %s.", groupVariables[playerInfo[playerid][pGroup]][gName]);

					new str[128];
					format(str, sizeof(str), "%s has joined the group (invited by %s).", GetName(playerid), name);
					SendGroupMessage(playerInfo[playerid][pGroup], COLOR_LGREEN, str);
					DeletePVar(playerid, "invID");

					gString[0] = (EOS);
					format(gString, sizeof gString, "%s has joined the group %s (invited by %s).", GetName(playerid), groupVariables[playerInfo[playerid][pGroup]][gName], name);
					
					gQuery[0] = EOS;
					mysql_format(SQL, gQuery, sizeof(gQuery), "insert into `logs_factions` (Player, Date, Log, ShowInFH) values ('%d', '%d', '%e', '1')", playerInfo[playerid][pSQLID], gettime(), gString);
					mysql_tquery(SQL, gQuery, "", "");

					gQuery[0] = EOS;
					mysql_format(SQL, gQuery, sizeof(gQuery), "UPDATE `server_users` set `playerGroup` = '%d', `playerGroupJoin` = '%d', `playerGroupRank` = '1', `playerFactionWarns`= '0' WHERE `playerID` = '%d'", playerInfo[playerid][pGroup], gettime(), playerInfo[playerid][pSQLID]);
					mysql_tquery(SQL, gQuery, "", "");
				}
				else 
				{
					SendClientMessage(playerid, -1, "This faction is full!");
					DeletePVar(playerid, "invID");
				}
			}
			else 
			{
				SendClientMessage(playerid, -1, "You have FP!");
				DeletePVar(playerid, "invID");
			}
		}
		else 
		{
			SendClientMessage(playerid, -1, "You are already in a faction!");
			DeletePVar(playerid, "invID");
		}
	}
	else return SendClientMessage(playerid, COLOR_GREY, "You don't have an active group invite request.");	
	return 1;
}

YCMD:quitgroup(playerid, params[], help)
{
	if(playerInfo[playerid][pGroup] == 0) return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte dintr-o factiune.");

	gString[0] = EOS;
	format(gString, sizeof gString, "{ffffff}Esti sigur ca vrei sa parestesti factiunea %s?\n{FF0000}Info:{ffffff} Aceasta actiune este ireversibila si vei primii 40 faction punish.", groupVariables[playerInfo[playerid][pGroup]][gName]);

	Dialog_Show(playerid, DIALOG_QUITGROUP, DIALOG_STYLE_MSGBOX, "{f9f9f9}Quit Group", gString, "Ok", "Cancel");
	return 1;
}

YCMD:service(playerid, params[], help)
{
	if(playerInfo[playerid][pGroup] == 4)
		return SCM(playerid, COLOR_GREY, "You can't use this command because you are in Paramedic.");

	new STR[64];
	switch(haveServiceActive[playerid]) {
		case 0: STR = "None"; case 1: STR = "Paramedic";
	}

	if(haveServiceActive[playerid] != 0)
		return SCMf(playerid, COLOR_GREY, "You already have active service on %s.", STR);

	if(GetPVarInt(playerid, "deelayService") > gettime())
		return SCMf(playerid, COLOR_GREY, "Ai sunat recent la serviciile de Paramedic. Trebuie sa astepti %d secunde pentru un nou apel.", GetPVarInt(playerid, "deelayService") - gettime());

	new serviceType[64];
	if(sscanf(params, "s[64]", serviceType))
		return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/service <medic>");

	switch(YHash(serviceType))
	{
		/*case _H<Taxi>, _H<taxi>: {
			gString[0] = (EOS);
			format(gString, sizeof gString, "* Service: %s (%d) calling on Taxi Company. Use /calls to accept.", GetName(playerid), playerid);
			SendFactionMessage(10, COLOR_YELLOW, gString);
			SCM(playerid, COLOR_TEAL, "You are calling the Taxi Company. Please wait for answer.");
			taxiServices ++;
			haveServiceActive[playerid] = 1;
		}*/
		case _H<medic>, _H<Medic>: {
			gString[0] = (EOS);
			format(gString, sizeof gString, "* Service: %s (%d) calling on Paramedic & Firemen Department. Use /calls to accept.", GetName(playerid), playerid);
			SendFactionMessage(3, COLOR_YELLOW, gString);
			SCM(playerid, COLOR_TEAL, "You are calling the Paramedic & Firemen Department. Please wait for answer.");
			medicServices ++;
			haveServiceActive[playerid] = 3;
		}
		default: return SCM(playerid, COLOR_GREY, "Invalid service! (taxi or medic)");
	}

	SetPVarInt(playerid, "deelayService", gettime() + 120);
	return true;
}

YCMD:calls(playerid, params[], help)
{
	if(playerInfo[playerid][pGroup] != 10 && playerInfo[playerid][pGroup] != 11 && playerInfo[playerid][pGroup] != 3)
		return SCM(playerid, COLOR_GREY, "This command is only for Taxi, School and Paramedic.");

	new Float: yourPos[3], typeTime[64], time[64], services;
	GetPlayerPos(playerid, yourPos[0], yourPos[1], yourPos[2]);
	if(playerInfo[playerid][pGroup] == 3)
	{
		gString[0] = (EOS);
		foreach(new i : Player)
		{
			if(haveServiceActive[i] == 3) {
				if(activeServiceTimer[i] <= 60) format(typeTime, sizeof typeTime, "%d", activeServiceTimer[i]), time = "seconds";
				else if(activeServiceTimer[i] > 60 && activeServiceTimer[i] < 3600) format(typeTime, sizeof typeTime, "%s", ConvertToMinutes(activeServiceTimer[i])), time = "minutes";
				else if(activeServiceTimer[i] >= 3600) format(typeTime, sizeof typeTime, "%s", ConvertToHours(activeServiceTimer[i])), time = "hours";
					
				selected_service[playerid][services] = i;

				format(gString, sizeof gString, "%s%s (%.2f meters) - calling now %s %s\n", gString, GetName(i), GetPlayerDistanceFromPoint(i, yourPos[0], yourPos[1], yourPos[2]), typeTime, time);
				services++;
			}
		}
		if(services == 0) return SCM(playerid, COLOR_GREY, "* There are no active services.");
		Dialog_Show(playerid, DIALOG_SERVICE_MEDIC, DIALOG_STYLE_LIST, "Paramedic Services", gString, "Accept", "Cancel");
	}
	/*else if(playerInfo[playerid][pGroup] == 10)
	{
		if(TaxiFare[playerid] <= 0)
			return SCM(playerid, COLOR_GREY, "You are not On Duty (/fare) for accept the command.");

		gString[0] = (EOS);
		foreach(new i : Player)
		{
			if(haveServiceActive[i] == 1) {
				if(activeServiceTimer[i] <= 60) format(typeTime, sizeof typeTime, "%d", activeServiceTimer[i]), time = "seconds";
				else if(activeServiceTimer[i] > 60 && activeServiceTimer[i] < 3600) format(typeTime, sizeof typeTime, "%s", ConvertToMinutes(activeServiceTimer[i])), time = "minutes";
				else if(activeServiceTimer[i] >= 3600) format(typeTime, sizeof typeTime, "%s", ConvertToHours(activeServiceTimer[i])), time = "hours";
				
				selected_service[playerid][services] = i;

				format(gString, sizeof gString, "%s%s (%.2f meters) - calling now %s %s\n", gString, GetName(i), GetPlayerDistanceFromPoint(i, yourPos[0], yourPos[1], yourPos[2]), typeTime, time);
				services++;
			}
		}
		if(services == 0) return SCM(playerid, COLOR_GREY, "* There are no active services.");
		Dialog_Show(playerid, DIALOG_SERVICE_TAXI, DIALOG_STYLE_LIST, "Taxi Services", gString, "Accept", "Cancel");
	}*/
	return true;
}

// ------------------------------------- //
//                Dialogs                //
// ------------------------------------- //

/*
Dialog:DIALOG_SERVICE_TAXI(playerid, response, listitem, inputtext[]) {
	if(!response)
		return true;

	if(TaxiFare[playerid] == 0)
		return SCM(playerid, COLOR_GREY, "You are not a /fare active.");

	selected_service_faction[playerid] = selected_service[playerid][listitem];

	if(activeServiceTimer[selected_service_faction[playerid]] <= 60) str2 = "seconds";
	else if(activeServiceTimer[selected_service_faction[playerid]] > 60 && activeServiceTimer[selected_service_faction[playerid]] < 3600) str2 = "minutes";
	else if(activeServiceTimer[selected_service_faction[playerid]] >= 3600) str2 = "hours";

	if(activeServiceTimer[selected_service_faction[playerid]] <= 60) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]]);
	else if(activeServiceTimer[selected_service_faction[playerid]] > 60 && activeServiceTimer[selected_service_faction[playerid]] < 3600) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]] / 60);
	else if(activeServiceTimer[selected_service_faction[playerid]] >= 3600) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]] / 60);

	SCMf(playerid, COLOR_YELLOW, "* You accepted %s service. Go to the checkpoint (%.2f meters).", GetName(selected_service_faction[playerid]), GetPlayerDistanceFromPoint(playerid, yourPos[0], yourPos[1], yourPos[2]));
	findFunction(playerid, selected_service_faction[playerid]);
	SCMf(selected_service_faction[playerid], COLOR_YELLOW, "Taxi Driver %s has accepted your service. Please wait here.", GetName(playerid));
	
	gString[0] = EOS;
	format(gString, sizeof gString, "* %s has accepted %s service after %s %s of waiting.", GetName(playerid), GetName(selected_service_faction[playerid]), str, str2);
	SendFactionMessage(playerInfo[playerid][pGroup], COLOR_YELLOW, gString);

	haveServiceActive[selected_service_faction[playerid]] = 0;
	activeServiceTimer[selected_service_faction[playerid]] = -1;
	taxiServices--;
	return true;
}*/

Dialog:DIALOG_SERVICE_MEDIC(playerid, response, listitem, inputtext[]) {
	if(!response)
		return true;

	selected_service_faction[playerid] = selected_service[playerid][listitem];

	if(activeServiceTimer[selected_service_faction[playerid]] <= 60) str2 = "seconds";
	else if(activeServiceTimer[selected_service_faction[playerid]] > 60 && activeServiceTimer[selected_service_faction[playerid]] < 3600) str2 = "minutes";
	else if(activeServiceTimer[selected_service_faction[playerid]] >= 3600) str2 = "hours";

	if(activeServiceTimer[selected_service_faction[playerid]] <= 60) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]]);
	else if(activeServiceTimer[selected_service_faction[playerid]] > 60 && activeServiceTimer[selected_service_faction[playerid]] < 3600) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]] / 60);
	else if(activeServiceTimer[selected_service_faction[playerid]] >= 3600) format(str, sizeof str, "%d", activeServiceTimer[selected_service_faction[playerid]] / 60);

	//SCMf(playerid, COLOR_YELLOW, "* You accepted %s service. Go to the checkpoint (%.2f meters).", GetName(selected_service_faction[playerid]), GetPlayerDistanceFromPoint(playerid, yourPos[0], yourPos[1], yourPos[2]));
	findFunction(playerid, selected_service_faction[playerid]);
	SCMf(selected_service_faction[playerid], COLOR_YELLOW, "Medic %s has accepted your service. Please wait here.", GetName(playerid));
	
	gString[0] = EOS;
	format(gString, sizeof gString, "* %s has accepted %s service after %s %s of waiting.", GetName(playerid), GetName(selected_service_faction[playerid]), str, str2);
	SendFactionMessage(playerInfo[playerid][pGroup], COLOR_YELLOW, gString);

	haveServiceActive[selected_service_faction[playerid]] = 0;
	activeServiceTimer[selected_service_faction[playerid]] = -1;
	medicServices--;
	return true;
}	

Dialog:DIALOG_QUITGROUP(playerid, response, listitem, inputtext[])
{
	if(!response) return true;

	SendGroupMessage(playerInfo[playerid][pGroup], COLOR_ANNOUNCE, "%s a parasit factiunea. (/quitgroup).", GetName(playerid));

	Iter_Remove(FactionMembers<playerInfo[playerid][pGroup]>, playerid);
	if(Iter_Contains(DutyMember, playerid)) Iter_Remove(DutyMember, playerid);

	DestroySpawnedVehicle(playerid);

	playerInfo[playerid][pGroup] = 0;
	playerInfo[playerid][pGroupRank] = 0;
	playerInfo[playerid][pGroupJoin] = 0;
	playerInfo[playerid][pFactionWarns] = 0;
	playerInfo[playerid][pFactionPunish] = 40;
	playerInfo[playerid][pFactionRaport1] = 0;
	playerInfo[playerid][pFactionRaport2] = 0;
	playerInfo[playerid][pFactionRaport3] = 0;
	playerInfo[playerid][pRaportPlaying] = 0;

	SetPlayerSkin(playerid, playerInfo[playerid][pSkin]);
	SetPlayerColorEx(playerid);
	SpawnPlayer(playerid);

	// query
	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `playerGroup` = '0', `playerGroupRank` = '0', `playerGroupJoin` = '0', `playerFactionPunish` = '40', `playerFactionWarns` = '0', `FactionRaport1` = '0', `FactionRaport2` = '0', `FactionRaport3` = '0', `RaportPlaying` = '0' WHERE `ID` = '%d'", playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	return 1;
}

Dialog:DIALOG_MEMBERS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(listitem >= 0)
    {
        if(playerInfo[playerid][pGroupRank] >= 6)
        {
            new name[30],result[30],query[300],test[5],strings[300];
            format(query, sizeof(query), "SELECT * FROM `server_users` WHERE `ID` = '%d'",dSelected[playerid][listitem]);
            new Cache: membresult = mysql_query(SQL,query);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                cache_get_field_content(i, "Name", result); format(name, 30, result);
                cache_get_field_content(i, "playerGroupRank", result); format(test, 5, result);
            }
            cache_delete(membresult);
            MemberSelect[playerid] = dSelected[playerid][listitem];
            format(strings, sizeof(strings),"%s - %s",test,name);
            Dialog_Show(playerid, DIALOG_MEMBERS2, DIALOG_STYLE_LIST, strings, "Change Rank\nFaction Warn\nClear FW\nUninvite - 40 FP\nUninvite - 0 FP\nView raport", "OK", "Exit");
        }
    }
    return 1;
}

Dialog:DIALOG_MEMBERS2(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0: SCM(playerid, COLOR_GREY, "Usage:{ffffff} /changerank [id] [rank]");
        case 1:
        {
            new string1[256],rank;
            if(playerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't give a fw to yourself.");
            foreach(new i : FactionMembers<playerInfo[playerid][pGroup]>)
            {
                if(playerInfo[i][pSQLID] == MemberSelect[playerid])
                {
                    if(playerInfo[playerid][pGroupRank] == 6 && playerInfo[i][pGroupRank] == 7 || playerInfo[playerid][pGroupRank] == 6 && playerInfo[i][pGroupRank] == 6) return SendClientMessage(playerid, -1, "You can't give a FW to a member with rank 6-7.");
                }
            }
            format(string1, sizeof(string1), "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                rank = cache_get_field_content_int(i, "playerGroupRank");
            }
            cache_delete(membresult);
            if(playerInfo[playerid][pGroupRank] == 6 && rank == 6 || playerInfo[playerid][pGroupRank] == 6 && rank == 7) return SendClientMessage(playerid, -1, "You can't give a FW to a member with rank 6-7.");
            Dialog_Show(playerid, DIALOG_FWARN, DIALOG_STYLE_MSGBOX, "You are sure?", "You are sure to give FW to this member?", "Yes", "No");
        }
        case 2:
        {
            if(playerInfo[playerid][pGroupRank] != 7) return SendClientMessage(playerid, -1, "Only leaders have acces to fw clear.");
            Dialog_Show(playerid, DIALOG_FUNWARN, DIALOG_STYLE_MSGBOX, "You are sure?", "You are sure to delete FW from this member?", "Yes", "No");
        }
        case 3:
        {
            if(playerInfo[playerid][pGroupRank] != 7) return SendClientMessage(playerid, -1, "Only leaders can uninvite a member.");
            if(playerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't uninvite yourself.");
            new stringtotal[500],string1[256],ftime,result[30],name[30],frank;
            format(string1, sizeof(string1), "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                ftime = cache_get_field_content_int(i, "playerGroupJoin");
                frank = cache_get_field_content_int(i, "playerGroupRank");
                cache_get_field_content(i, "name", result); format(name, 30, result);
            }
            cache_delete(membresult);
            if(frank == 7) return SendClientMessage(playerid, -1, "You can't uninvite a leader.");
            format(string1, sizeof(string1),"Esti pe cale sa-i dai uninvite lui %s CU 20 FP.\nAcesta are %d zile in factiune.\nScrie motivul pentru uninvite mai jos:", name, TSToDays(ftime));
            format(stringtotal, sizeof(stringtotal),"Atentie!!! Playerii ce au peste 14 zile se vor da afara fara FP, cu exceptia cazurilor in care acesta incalca regulile factiunii.\n%s", string1);
            Dialog_Show(playerid, DIALOG_FPUNINVITE, DIALOG_STYLE_INPUT, "Uninvite - 20 FP", stringtotal, "Uninvite", "Exit");
        }
        case 4:
        {
            if(playerInfo[playerid][pGroupRank] != 7) return SendClientMessage(playerid, -1, "Only leaders can uninvite a member.");
            if(playerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't uninvite yourself.");
            new stringtotal[500],string1[256],ftime,result[30],name[30],frank;
            format(string1, sizeof(string1), "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                ftime = cache_get_field_content_int(i, "playerGroupJoin");
                frank = cache_get_field_content_int(i, "playerGroupRank");
                cache_get_field_content(i, "Name", result); format(name, 30, result);
            }
            cache_delete(membresult);
            if(frank == 7) return SendClientMessage(playerid, -1, "You can't uninvite a leader.");
            format(string1, sizeof(string1),"Esti pe cale sa-i dai uninvite lui %s FARA FP.\nAcesta are %d zile in factiune.\nScrie motivul pentru uninvite mai jos:", name, TSToDays(ftime));
            format(stringtotal, sizeof(stringtotal),"Atentie!!! Playerii ce au sub 14 zile in factiune se vor da afara cu FP, cu exceptia cazurilor in care un owner iti spune ca e ok sa dai uninvite fara FP.\n%s", string1);
            Dialog_Show(playerid, DIALOG_NOUNINVITE, DIALOG_STYLE_INPUT, "Uninvite - 0 FP", stringtotal, "Uninvite", "Exit");
        }
        case 5:
        {
        	ShowPlayerRaport(playerid, MemberSelect[playerid]);
        }
    }
    return 1;
}

Dialog:DIALOG_FWARN(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new str[256],stringg[128],fwarn,name[30],name2[30],result[30],fcttime;
    format(stringg, sizeof(stringg), "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL,stringg);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "Name", result); format(name2, 30, result);
        fwarn = cache_get_field_content_int(i, "playerFactionWarns");
        fcttime = cache_get_field_content_int(i, "playerGroupJoin");
    }
    cache_delete(membresult);
    if(fwarn >= 2) return SendClientMessage(playerid, -1, "Poti da maxim 2 FW unui membru, la al 3-lea FW se da uninvite.");
    mysql_format(SQL,str,sizeof(str),"update server_users set `playerFactionWarns` = '%d',`playerGroupJoin` = '%d' WHERE `ID` = '%d'",fwarn+1,fcttime + 7*86400,MemberSelect[playerid]);
    mysql_tquery(SQL,str,"","");
    GetPlayerName(playerid, name, sizeof(name));
    foreach(new i : FactionMembers<playerInfo[playerid][pGroup]>)
    {
        if(playerInfo[i][pSQLID]  == MemberSelect[playerid])
        {
            playerInfo[i][pFactionWarns]++;
            playerInfo[i][pGroupJoin] += 7*86400;
            format(stringg, sizeof(stringg),"%s gived you a FW (faction warn). Your rank up date was changed (+7 days from now)",name);
            SendClientMessage(i, COLOR_GENANNOUNCE, stringg);
        }
    }
    format(str,sizeof(str),"%s received a faction warn from %s. FW: %d/3.",name2,name,(fwarn+1));
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_GENANNOUNCE, str);
    // log factiune
    return 1;
}

Dialog:DIALOG_FUNWARN(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new str[256],stringg[128],fwarn,name[30],name2[30],result[30],fcttime;
    format(stringg, sizeof(stringg), "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL,stringg);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        //idd = cache_get_field_content_int(i, "id");
        cache_get_field_content(i, "Name", result); format(name2, 30, result);
        fwarn = cache_get_field_content_int(i, "playerFactionWarns");
        fcttime = cache_get_field_content_int(i, "playerGroupJoin");
    }
    cache_delete(membresult);
    if(fwarn == 0) return SendClientMessage(playerid, -1, "Acel membru nu are niciun FW.");
    mysql_format(SQL,str,sizeof(str),"update server_users set `playerFactionWarns` = '%d',`playerGroupJoin` = '%d' WHERE `ID` = '%d'",fwarn-1,fcttime-7*86400,MemberSelect[playerid]);
    mysql_tquery(SQL,str,"","");
    GetPlayerName(playerid, name, sizeof(name));
    foreach(new i : FactionMembers<playerInfo[playerid][pGroup]>)
    {
        if(playerInfo[i][pSQLID] == MemberSelect[playerid])
        {
            playerInfo[i][pFactionWarns]--;
            playerInfo[i][pGroupJoin] -= 7*86400;
            format(stringg, sizeof(stringg),"%s cleared a FW (faction warn).",name);
            SendClientMessage(i, COLOR_GENANNOUNCE, stringg);
        }
    }
    format(str,sizeof(str),"%s got a FW clear from %s.",name2,name);
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_GENANNOUNCE, str);
    // log factiune
    return 1;
}

Dialog:DIALOG_FPUNINVITE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        result[30],name[30], reason[128], rank,ftime;
    
    format(gString, sizeof gString, "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL, gString);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "Name", result); format(name, 30, result);
        ftime = cache_get_field_content_int(i, "playerGroupJoin");
        rank = cache_get_field_content_int(i, "playerGroupRank");
    }
    cache_delete(membresult);

    mysql_format(SQL, gString, sizeof gString, "update `server_users` set `playerGroup` = '0', `playerGroupRank` = '0', `playerFactionPunish` = '40', `playerFactionWarns` = '0', `playerGroupJoin` = '0' where `ID` = '%d';", MemberSelect[playerid]);
    mysql_tquery(SQL, gString, "", "");
    
    mysql_real_escape_string(inputtext, reason);

    foreach(new i : FactionMembers<playerInfo[playerid][pGroup]>)
    {
        if(playerInfo[i][pSQLID] == MemberSelect[playerid])
        {
       		gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerGroup` = '0', `playerGroupRank` = '0', `playerGroupJoin` = '0', `playerFactionPunish` = '0', `playerFactionWarns` = '0' where `ID` = '%d'", playerInfo[i][pSQLID]);
			mysql_tquery(SQL, gQuery, "", "");

			playerInfo[i][pFactionRaport1] = 0;
			playerInfo[i][pFactionRaport2] = 0;
			playerInfo[i][pFactionRaport3] = 0;
			playerInfo[i][pRaportPlaying] = 0;

			gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `FactionRaport1` = '%d', `FactionRaport2`= '%d', `FactionRaport3`= '%d', `RaportPlaying`= '%f' where `ID` = '%d'",
		    playerInfo[i][pFactionRaport1], playerInfo[i][pFactionRaport2], playerInfo[i][pFactionRaport3], playerInfo[i][pRaportPlaying], playerInfo[i][pSQLID]);
			mysql_tquery(SQL, gQuery, "", "");

			Iter_Remove(FactionMembers<playerInfo[i][pGroup]>, i);
			DestroySpawnedVehicle(i);
			if(Iter_Contains(DutyMember, i)) Iter_Remove(DutyMember, i);

			playerInfo[i][pGroup] = 0;
			playerInfo[i][pGroupRank] = 0;
			playerInfo[i][pGroupJoin] = 0;
			playerInfo[i][pFactionWarns] = 0;
			playerInfo[i][pFactionPunish] = 0;
			SetPlayerColorEx(i);
			SetPlayerSkin(i, playerInfo[i][pSkin]);
			SpawnPlayer(i);
			Iter_Remove(FactionMembers<playerInfo[i][pGroup]>, i);

            format(gString, sizeof gString, "Ai fost demis de liderul %s\n din factiunea din care faceai parte %s (rank %d)\n dupa %d days, cu 40 FP. Motiv: %s.", playerInfo[playerid][pName], NumeFactiune(playerInfo[playerid][pGroup]), rank, TSToDays(ftime), reason);
            Dialog_Show(i, 0, DIALOG_STYLE_MSGBOX, "Uninvite", gString, "Inchide", "");
            break;
        }
    }
    format(gString, sizeof gString, "%s was uninvited by %s from faction %s (rank %d) after %d days, with 40 FP. Reason: %s.", name,playerInfo[playerid][pName],groupVariables[playerInfo[playerid][pGroup]][gName],rank,TSToDays(ftime),reason);
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_GENANNOUNCE, gString);
    return 1;
}

Dialog:DIALOG_NOUNINVITE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        result[30],name[30], reason[128], rank,ftime, dialogString[144];
    
    format(gString, sizeof gString, "SELECT * FROM `server_users` WHERE `ID` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL, gString);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "Name", result); format(name, 30, result);
        ftime = cache_get_field_content_int(i, "playerGroupJoin");
        rank = cache_get_field_content_int(i, "playerGroupRank");
    }
    cache_delete(membresult);

    mysql_format(SQL, gString, sizeof gString, "update `server_users` set `playerGroup` = '0', `playerGroupRank` = '0', `playerFactionPunish` = '0', `playerFactionWarns` = '0', `playerGroupJoin` = '0' where `ID` = '%d';", MemberSelect[playerid]);
    mysql_tquery(SQL, gString, "", "");
    
    mysql_real_escape_string(inputtext, reason);

    foreach(new i : FactionMembers<playerInfo[playerid][pGroup]>)
    {
        if(playerInfo[i][pSQLID] == MemberSelect[playerid])
        {
       		gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerGroup` = '0', `playerGroupRank` = '0', `playerGroupJoin` = '0', `playerFactionPunish` = '0', `playerFactionWarns` = '0' where `ID` = '%d'", playerInfo[i][pSQLID]);
			mysql_tquery(SQL, gQuery, "", "");

			playerInfo[i][pFactionRaport1] = 0;
			playerInfo[i][pFactionRaport2] = 0;
			playerInfo[i][pFactionRaport3] = 0;
			playerInfo[i][pRaportPlaying] = 0;

			gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `FactionRaport1` = '%d', `FactionRaport2`= '%d', `FactionRaport3`= '%d', `RaportPlaying`= '%f' where `ID` = '%d'",
		    playerInfo[i][pFactionRaport1], playerInfo[i][pFactionRaport2], playerInfo[i][pFactionRaport3], playerInfo[i][pRaportPlaying], playerInfo[i][pSQLID]);
			mysql_tquery(SQL, gQuery, "", "");

			if(Iter_Contains(DutyMember, i)) Iter_Remove(DutyMember, i);
			Iter_Remove(FactionMembers<playerInfo[i][pGroup]>, i);
			DestroySpawnedVehicle(i);

			playerInfo[i][pGroup] = 0;
			playerInfo[i][pGroupRank] = 0;
			playerInfo[i][pGroupJoin] = 0;
			playerInfo[i][pFactionWarns] = 0;
			playerInfo[i][pFactionPunish] = 0;
			SetPlayerColorEx(i);
			SetPlayerSkin(i, playerInfo[i][pSkin]);
			SpawnPlayer(i);

            format(dialogString, sizeof dialogString, "Ai fost demis de liderul %s\n din factiunea din care faceai parte %s (rank %d)\n dupa %d days, cu 0 FP. Motiv: %s.", playerInfo[playerid][pName], NumeFactiune(playerInfo[playerid][pGroup]), rank, TSToDays(ftime), reason);
            Dialog_Show(i, 0, DIALOG_STYLE_MSGBOX, "Uninvite", dialogString, "Inchide", "");

            break;
        }
    }
    format(gString, sizeof gString, "%s was uninvited by %s from faction %s (rank %d) after %d days, with 0 FP. Reason: %s.", name,playerInfo[playerid][pName],groupVariables[playerInfo[playerid][pGroup]][gName],rank,TSToDays(ftime),reason);
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_GENANNOUNCE, gString);
    return 1;
}