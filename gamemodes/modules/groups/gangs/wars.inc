/*
    WARS
*/

#include <YSI_Coding\y_hooks>
#define check_gang                      if(!IsInAGang(playerid)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not a gang member.");

enum E_WARS 
{
	wDefender,
	wAttacker,
	wAttackerScore,
	wDefenderScore,
	wTime
}

new warVariables[40][E_WARS], in_war[MAX_GROUPS],
    Iterator:active_wars<MAX_TURFS>;

new warScore[MAX_PLAYERS][2];
new PlayerText:WarTD[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    WarTD[playerid] = CreatePlayerTextDraw(playerid, 89.000000, 270.000000, "");
    PlayerTextDrawFont(playerid, WarTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, WarTD[playerid], 0.204166, 1.150000);
    PlayerTextDrawTextSize(playerid, WarTD[playerid], 400.000000, 133.500000);
    PlayerTextDrawSetOutline(playerid, WarTD[playerid], 1);
    PlayerTextDrawAlignment(playerid, WarTD[playerid], 2);
    PlayerTextDrawBoxColor(playerid, WarTD[playerid], 128);
    PlayerTextDrawUseBox(playerid, WarTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, WarTD[playerid], 1);
}

/*hook OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID)
    {
        new memberPlayer = playerInfo[playerid][pGroup], memberKiller = playerInfo[killerid][pGroup];

        foreach(new t : active_wars) 
        {
            if(IsPlayerInTurf(playerid, t) && IsPlayerInTurf(killerid, t) && in_war[playerInfo[killerid][pGroup]] && in_war[playerInfo[playerid][pGroup]] == 1) 
            {
                SCMf(killerid, COLOR_TEAL, "War: {FFFFFF}L-ai ucis pe %s.", GetName(playerid));
                SCMf(playerid, COLOR_TEAL, "War: {FFFFFF}Ai fost ucis de %s.", GetName(killerid));

                warScore[playerid][1]++;
                warScore[killerid][0]++;
                if(warVariables[t][wDefender] == memberPlayer && warVariables[t][wAttacker] == memberKiller) warVariables[t][wAttackerScore]++;
                if(warVariables[t][wDefender] == memberKiller && warVariables[t][wAttacker] == memberPlayer) warVariables[t][wDefenderScore]++;

                foreach(new i : Player) 
                {
                    if(in_war[playerInfo[i][pGroup]] == 1) 
                    {
                        if(warVariables[t][wDefender] == playerInfo[i][pGroup] || warVariables[t][wAttacker] == playerInfo[i][pGroup]) 
                        {
                            SendDeathMessageToPlayer(i, killerid, playerid, reason);
                        }
                    }
                }

                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid, x, y, z);
                CreateDeathLoot(t, x, y + 2, z);
            }
        } 
    }
}*/

hook OnPlayerEnterDynArea(playerid, areaid) 
{
    if(in_war[playerInfo[playerid][pGroup]])
    {
        new group = playerInfo[playerid][pGroup];
        foreach(new turf : server_turfs)
        {
            if((warVariables[turf][wAttacker] == group || warVariables[turf][wDefender] == group) && IsPlayerInTurf(playerid, turf))
            {
                OnPlayerEnterTurf(playerid, turf);
                break;
            }
        }
    }
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
    if(in_war[playerInfo[playerid][pGroup]])
    {
        new group = playerInfo[playerid][pGroup];
        foreach(new turf : server_turfs)
        {
            if((warVariables[turf][wAttacker] == group || warVariables[turf][wDefender] == group) && areaid == turfsVariables[turf][turf_area])
            {
                OnPlayerExitTurf(playerid, turf);
                break;
            }
        }
    }
}

function OnPlayerEnterTurf(playerid, turf)
{
    SCMf(playerid, COLOR_TEAL, "You have entered turf %d.", turf);
    SetPlayerVirtualWorld(playerid, 50000 + turf);
    return 1;
}

function OnPlayerExitTurf(playerid, turf)
{
    if(GetPlayerVirtualWorld(playerid) < 50000 || GetPlayerVirtualWorld(playerid) > 50100) return 1;

    SCMf(playerid, COLOR_TEAL, "You have left turf %d.", turf);
    SetPlayerVirtualWorld(playerid, 0);
    return 1;
}

stock IsPlayerInTurf(playerid, turf) 
{
	return IsPlayerInDynamicArea(playerid, turfsVariables[turf][turf_area]);
}

stock GetPlayerTurf(playerid) 
{
	foreach(new t : server_turfs) 
    {
		if(IsPlayerInTurf(playerid, t)) return t;
	}
	return 0;
}

stock GetFactionOnlineMembers(f) 
{
	new mem;
	foreach(new i : Player) if(playerInfo[i][pGroup] == f) mem++;
	return mem;
}

CMD:attack(playerid, params[]) 
{
	check_gang

	if(playerInfo[playerid][pGroupRank] < 4) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}You don't have rank 4+.");
    
    #if defined SERVER_1
    new h, m, s; gettime(h, m, s);
	if(h < 16 || h > 18) return SendClientMessage(playerid, COLOR_GREY, "Poti ataca un teritoriu intre orele 16 si 18.");
	#endif

    new turf = GetPlayerTurf(playerid);
    if(turf == 0) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}You are not on a gang turf.");

    if(warVariables[turf][wTime] > 0) return SendClientMessage(playerid, COLOR_GREY, "Error: {ffffff}The turf is already attacked!");
    if(turfsVariables[turf][turf_owner] == playerInfo[playerid][pGroup]) return SendClientMessage(playerid, COLOR_GREY, "You can't attack your own turf");
    if(GetFactionOnlineMembers(turfsVariables[turf][turf_owner]) == 0) return SendClientMessage(playerid, COLOR_GREY, "No online gangsters from the attacked turf.");
    if(in_war[turfsVariables[turf][turf_owner]] == 1) return SendClientMessage(playerid, COLOR_GREY, "That gang is already in a war.");
    

    SendGroupMessage(turfsVariables[turf][turf_owner], COLOR_TEAL, "[WAR] %s from %s attacked turf #%d owned by your group.", GetName(playerid), groupVariables[playerInfo[playerid][pGroup]][gName], turf);
    SendGroupMessage(playerInfo[playerid][pGroup], COLOR_TEAL, "[WAR] %s from your group attacked turf #%d owned by %s.", GetName(playerid), turf, groupVariables[turfsVariables[turf][turf_owner]][gName]);

    warVariables[turf][wAttacker] = playerInfo[playerid][pGroup];
    warVariables[turf][wDefender] = turfsVariables[turf][turf_owner];
    Iter_Add(active_wars, turf);

    #if defined SERVER_1
    warVariables[turf][wTime] = 600;
    #else
    warVariables[turf][wTime] = 60;
    #endif

    foreach(new player : Player)
    {
        if(playerInfo[player][pGroup] == warVariables[turf][wAttacker] || playerInfo[player][pGroup] == warVariables[turf][wDefender])
        {
            if(IsPlayerInTurf(player, turf))
            {
                OnPlayerEnterTurf(player, turf);
            }
        }
    }

    in_war[turfsVariables[turf][turf_owner]] = 1;
    in_war[playerInfo[playerid][pGroup]] = 1;
	return 1;
}

timer RemoveWar[1000](i) Iter_Remove(active_wars, i);

task WarTimer[1000]()
{
    foreach(new i : active_wars) 
    {
		if(warVariables[i][wTime] > 0) 
        {
			warVariables[i][wTime]--;
			new atscore = warVariables[i][wAttackerScore], defscore = warVariables[i][wDefenderScore], winner;

			foreach(new playerid : Player) 
            {
				if(in_war[playerInfo[playerid][pGroup]] == 1 && (warVariables[i][wAttacker] == playerInfo[playerid][pGroup] || warVariables[i][wDefender] == playerInfo[playerid][pGroup]))
                {
					PlayerTextDrawShow(playerid, WarTD[playerid]);
				
                    GangZoneFlashForPlayer(playerid, turfsVariables[i][turf_zone], 0xFF000099);
                }

                gString[0] = EOS;
				format(gString, sizeof(gString), "Attacker: ~y~%s (%d) ~w~turf ~y~%d~w~~n~Defender: ~y~%s (%d)~w~~n~Time left: ~y~%s~w~~h~~n~Score: ~y~%d kills ~w~and ~y~%d deaths", groupVariables[warVariables[i][wAttacker]][gName], atscore, i, groupVariables[warVariables[i][wDefender]][gName], defscore, ConvertToMinutes(warVariables[i][wTime]), warScore[playerid][0], warScore[playerid][1]);
				PlayerTextDrawSetString(playerid, WarTD[playerid], gString);
			}

			if(warVariables[i][wTime] == 0) 
            {
				if(atscore >= defscore) winner = 1;
				if(atscore == defscore) winner = 2;
				if(defscore > atscore) winner = 2;

				if(winner == 1) 
                {
					va_SendClientMessageToAll(COLOR_PURPLE, "NR AdmBot: Gruparea mafioata %s a cucerit teritoriul #%d ce era detinut de %s.", groupVariables[warVariables[i][wAttacker]][gName], i, groupVariables[warVariables[i][wDefender]][gName]);
					turfsVariables[i][turf_owner] = warVariables[i][wAttacker];

                    gQuery[0] = EOS;
					mysql_format(SQL, gQuery, sizeof(gQuery), "UPDATE `server_turfs` SET `gang` = '%d' WHERE `id` = '%d'", warVariables[i][wAttacker], i);
					mysql_tquery(SQL, gQuery, "", "");

					foreach(new playerid : Player) 
                    {
                        if(playerInfo[playerid][pGroup] == warVariables[i][wAttacker])
                        {
                            addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, 10000, false);
                        }
					}
				}

				if(winner == 2) 
                {
					va_SendClientMessageToAll(COLOR_PURPLE, "NR AdmBot: Gruparea mafiota %s nu a cucerit teritoriul #%d ce este detinut de %s.", groupVariables[warVariables[i][wAttacker]][gName], i, groupVariables[warVariables[i][wDefender]][gName]);
					foreach(new playerid : Player) 
                    {
                        if(playerInfo[playerid][pGroup] == warVariables[i][wDefender])
						{
						    addMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, 5000, false);
                        }
					}
				}

				foreach(new playerid : Player) 
                {
					SendClientMessage(playerid, COLOR_TEAL, "[War ended]");
					SCMf(playerid, COLOR_TEAL, "%s (%d) - attacker | %s (%d) - defender", groupVariables[warVariables[i][wAttacker]][gName], atscore, groupVariables[warVariables[i][wDefender]][gName], defscore);
					SCMf(playerid, COLOR_TEAL, "Your own score: %d kills and %d deaths.", warScore[playerid][0], warScore[playerid][1]);
					
                    for(new x; x < 2; x++) warScore[playerid][x] = 0;

					PlayerTextDrawHide(playerid, WarTD[playerid]);

					GangZoneStopFlashForPlayer(playerid, turfsVariables[i][turf_zone]);
                    
					for(new x; x < 5; x++) SendDeathMessageToPlayer(playerid, 1001, 1001, 1001);
					foreach(new player : Player) SetPlayerMarkerForPlayer(playerid, playerid, (GetPlayerColor(playerid) & 0xFFFFFF00));
    
                    SetPlayerVirtualWorld(playerid, 0);

                    SCM(playerid, COLOR_YELLOW, "War incheiat. Vei fi transferat in Virtual World-ul normal (0)!");
                }

				in_war[warVariables[i][wDefender]] = 0;
				in_war[warVariables[i][wAttacker]] = 0;

				warVariables[i][wAttacker] = warVariables[i][wDefender] = 0;
				warVariables[i][wDefenderScore] = 0;
				warVariables[i][wAttackerScore] = 0;
                defer RemoveWar[1000](i); 

                DestroyTurfLoots(i);
			}

			foreach(new player : Player) 
            {
				if(groupVariables[playerInfo[player][pGroup]][gType] == 5) 
                {
					foreach(new t : server_turfs)
                    {
						GangZoneHideForPlayerEx(player, turfsVariables[t][turf_zone]);
						if(turfsVariables[t][turf_owner] == 6) GangZoneShowForPlayerEx(player, turfsVariables[t][turf_zone], 0x33AA3399);
						else if(turfsVariables[t][turf_owner] == 7) GangZoneShowForPlayerEx(player, turfsVariables[t][turf_zone], 0x66003399);
						else if(turfsVariables[t][turf_owner] == 8) GangZoneShowForPlayerEx(player, turfsVariables[t][turf_zone], 0x1AFFFF99);
						else if(turfsVariables[t][turf_owner] == 9) GangZoneShowForPlayerEx(player, turfsVariables[t][turf_zone], 0xB3B30099);
					}
				}
			}
		}
	}
}