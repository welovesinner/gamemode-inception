// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//               Variables               //
// -------------------------------------//

new 
	PlayerText: ptd_wanted,
	WantedPlayers[MAX_PLAYERS][50],
    Somated[MAX_PLAYERS],
	PlayerHandsup[MAX_PLAYERS],
	FreeExpire[MAX_PLAYERS],
	FreePrice[MAX_PLAYERS],
	FreeOffer[MAX_PLAYERS],
	FreePlayer[MAX_PLAYERS];

new Float:jail_pos[3][3] = {
	{263.7529, 86.3880, 1001.0391},
	{264.2143, 82.0242, 1001.0391},
	{263.9700, 77.4552, 1001.0391}
};

// ------------------------------------- //
//               Defines                //
// -------------------------------------//

#define check_cop  if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not a cop.");
#define check_duty if(!Iter_Contains(DutyMember, playerid)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not on duty.");


// ------------------------------------- //
//                  Stock                //
// -------------------------------------//

stock SetPlayerWantedLevelEx(playerid, wanted, const reason[]) {
	playerInfo[playerid][pWantedLevel] = wanted;
	SetPlayerWantedLevel(playerid, wanted);

	if(wanted > 0) {
		playerInfo[playerid][pWantedExpire] = 300;
		PlayerTextDrawSetString(playerid, ptd_wanted, "wanted expires in ~g~10:00 minutes");
		PlayerTextDrawShow(playerid, ptd_wanted);

	 	new crime;
		if(strsame(playerInfo[playerid][pCrime1], "no crime", true)) {
			format(playerInfo[playerid][pCrime1], 48, reason);
			crime = 1;
		}
		
		if(strsame(playerInfo[playerid][pCrime2], "no crime", true) && crime == 0) {
			format(playerInfo[playerid][pCrime2], 48, reason);
			crime = 1;
		}

		if(strsame(playerInfo[playerid][pCrime3], "no crime", true) && crime == 0) {
			format(playerInfo[playerid][pCrime3], 48, reason);
			crime = 1;
		}
	}

	else if(wanted == 0) {
		format(playerInfo[playerid][pCrime1], 48, "no crime");
		format(playerInfo[playerid][pCrime2], 48, "no crime");
		format(playerInfo[playerid][pCrime3], 48, "no crime");

		PlayerTextDrawHide(playerid, ptd_wanted);
	}

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerWantedLevel` = '%d', `playerCrime1` = '%e', `playerCrime2` = '%e', `playerCrime3` = '%e' where `ID` = '%d'", wanted, playerInfo[playerid][pCrime1], playerInfo[playerid][pCrime2], playerInfo[playerid][pCrime3], playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	return 1;
}

stock GetWantedPlayers()
{
    new count;
    foreach(new playerid : Player) if(playerInfo[playerid][pWantedLevel] > 0) count++;
    return count;
}

stock Megaphone(playerid, const message[], va_args<>)
{   
    new out[200];
    va_format(out, sizeof(out), message, va_start<2>);

    sendNearbyMessage(playerid, COLOR_YELLOW, 100.0, "(megaphone) Politist %s: %s", GetName(playerid), out);
    return 1;
}
stock CrimInRange(Float:radi, playerid, copid) {
	if(IsPlayerConnected(playerid) && IsPlayerConnected(copid)) {
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		GetPlayerPos(copid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)))
 			return 1;
	}
	return 0;
}
stock SendGroupTypeMessage(type, color, const text[]) {
    foreach(new i : Player) {
    	if(groupVariables[playerInfo[i][pGroup]][gType] == type) 
    		SendClientMessage(i, color, text);
    }
    return 1;
}
function ProxDetectorS(Float:radi, playerid, targetid)
{
    if(IsPlayerConnected(playerid)&&IsPlayerConnected(targetid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		GetPlayerPos(targetid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}
// ------------------------------------- //
//                 Hooks                //
// -------------------------------------//

hook OnPlayerDisconnect(playerid)
{
	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_users` set `playerWantedLevel` = '%d', `playerJailTime` = '%d', `playerCrime1` = '%e', `playerCrime2` = '%e', `playerCrime3` = '%e' where `ID` = '%d'", playerInfo[playerid][pWantedLevel], playerInfo[playerid][pJailTime], playerInfo[playerid][pCrime1], playerInfo[playerid][pCrime2], playerInfo[playerid][pCrime3], playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");

    Somated[playerid] = 0;
    FreeExpire[playerid] = 0;
    FreeOffer[playerid] = -1;
    FreePrice[playerid] = 0;
	return 1;
}

hook OnPlayerConnect(playerid)
{
    ptd_wanted = CreatePlayerTextDraw(playerid, 322.000000, 410.000000, "wanted expires in ~g~10:00 minutes");
	PlayerTextDrawLetterSize(playerid, ptd_wanted, 0.174000, 1.388445);
	PlayerTextDrawAlignment(playerid, ptd_wanted, 2);
	PlayerTextDrawColor(playerid, ptd_wanted, -1);
	PlayerTextDrawSetOutline(playerid, ptd_wanted, 1);
	PlayerTextDrawBackgroundColor(playerid, ptd_wanted, 255);
	PlayerTextDrawFont(playerid, ptd_wanted, 2);
	PlayerTextDrawSetProportional(playerid, ptd_wanted, 1);
    return 1;
}

hook OnGameModeInit()
{
    gString[0] = EOS;   
    format(gString, sizeof(gString), "{1C8A15}Arrest Place:{ffffff}\nType {1C8A15}/arrest{ffffff} to arrest a player!");
    CreateDynamic3DTextLabel(gString, -1, 1527.7622,-1678.2057,5.8906, 40.0); 
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_WASTED)
	{
		if(playerInfo[playerid][pWantedLevel] >= 1) 
		{
			new str[24], killers[24*5], string[192], price = playerInfo[playerid][pWantedLevel] * 1000, count;
			if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) 
			{
				foreach(new i : Player) 
				{
					if((groupVariables[playerInfo[i][pGroup]][gType] == 1 && Iter_Contains(DutyMember, i)) && CrimInRange(30.0, playerid, i)) 
					{
						count++;
						if(count <= 5 && count > 1) {
							format(str, 24, "%s,", GetName(i));
							strcat(killers, str);
						}
						if(count == 1) format(killers, 24, "%s", GetName(i));

						va_GameTextForPlayer(i, "~w~Running suspect bonus!~n~~y~$%s", 5000, 1, formatNumber(price));
                        addMoney(i, GetMilliards(i), GetMoney(i), 0, price);
						PlayerPlaySound(i, 1058, 0.0, 0.0, 0.0);
						giveRaportPoint(i, 1);
					}
				}
				if(count > 0) 
				{
					playerInfo[playerid][pJailTime] = 150 * GetPlayerWantedLevel(playerid);

					new rand = random(2);
					SetPlayerPos(playerid, jail_pos[rand][0], jail_pos[rand][1], jail_pos[rand][2]);
					SetPlayerFacingAngle(playerid, 270.0);

					SetPlayerInterior(playerid, 6);
					SetPlayerVirtualWorld(playerid, 40001);

					SetPlayerHealth(playerid, 100);

					sendNearbyMessage(playerid, COLOR_PURPLE, 20.0, "* %s is now in jail thanks to %s!", GetName(playerid), killers);
					SCMf(playerid, COLOR_SERVER, "Arrest: {FFFFFF}You have been arrested for %d seconds.", playerInfo[playerid][pJailTime]);
					playerInfo[playerid][pWantedLevel] = 0;
					SetPlayerWantedLevel(playerid, 0);

					format(string, sizeof(string), "Dispatch: %s (%d) is now jailed for %d seconds.", GetName(playerid), playerid, playerInfo[playerid][pJailTime]);
					SendGroupTypeMessage(1, COLOR_BLUE, string);

					gQuery[0] = EOS;
					mysql_format(SQL, gQuery, sizeof(gQuery), "UPDATE `server_users` set `playerJailTime` = '%d' where `ID` = '%d'", playerInfo[playerid][pJailTime], playerInfo[playerid][pSQLID]);
					mysql_tquery(SQL, gQuery, "", "");
				}
			}
		}
	}
}

hook OnPlayerSpawn(playerid)
{
    if(playerInfo[playerid][pJailTime] > 0) 
	{
		SetPlayerInterior(playerid, 6);
		SetPlayerVirtualWorld(playerid, 40001);

		new rand = random(2);
		SetPlayerPos(playerid, jail_pos[rand][0], jail_pos[rand][1], jail_pos[rand][2]);
		SetPlayerFacingAngle(playerid, 270.0);

		gString[0] = EOS;
		format(gString, sizeof(gString), "jailed for ~y~%s minutes", ConvertToMinutes(playerInfo[playerid][pJailTime]));
		PlayerTextDrawSetString(playerid, ptd_wanted, gString);
		PlayerTextDrawShow(playerid, ptd_wanted);
		SetPlayerWantedLevel(playerid, 0);
		return 1;
	}
    return 1;
}

// ------------------------------------- //
//               Commands                //
// -------------------------------------//

YCMD:su(playerid, params[], help)
{
    check_cop
    check_duty

    new player, wanted, reason[32];
    if(sscanf(params, "uds[32]", player, wanted, reason))
    {
        return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/su [player id/name] [wanted] [reason]");
    }

    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Player not connected.");
    if(playerInfo[player][pGroup] == 1 && playerInfo[player][pGroup] == 2) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You can't use this command on cops.");
    if(player == playerid) return 1;
    if(wanted < 1 || wanted > 6) return SCM(playerid, COLOR_GREY, "Invalid wanted.");

    SetPlayerWantedLevelEx(player, wanted + playerInfo[playerid][pWantedLevel], reason);
    SCMf(player, COLOR_DARKRED, "You have commited a crime - reported by: %s - wanted +%d - reason: %s.", GetName(playerid), wanted, reason);

    for(new x = 1; x <= 2; x++) SendGroupMessage(x, COLOR_D, "Dispatch: %s commited a crime (reported by %s) - + %d wanted - reason: %s.", GetName(player), GetName(playerid), wanted, reason);
    return 1;
}
YCMD:free(playerid, params[], help)
{
	
	new id,moneyfree,giveplayer[30],sendername[30],string[200],string2[200];
	check_cop
	check_duty
	if(sscanf(params, "ui", id,moneyfree)) return SendClientMessage(playerid, -1, "/free [name/playerid] [amount]");
	if(playerInfo[playerid][pJailTime] < 0)  return SendClientMessage(playerid, -1, "This player is not in jail.");
	if(playerid == id) return SendClientMessage(playerid, -1, "You can't free yourself.");
	if(FreeExpire[playerid] > 0) return SendClientMessage(playerid, -1, "You offered already a free, please wait 30 seconds before offer another free.");
	if(moneyfree < 1 || moneyfree > 1000000) return SendClientMessage(playerid,-1, "Invalid amount of money ($1 - $1,000,000).");
	if(ProxDetectorS(10.0, playerid, id))
	{
        if(IsPlayerConnected(id))
        {
            if(id != INVALID_PLAYER_ID)
            {
 				FreeOffer[id] = playerid;
 				FreePlayer[playerid] = id;
				FreePrice[id] = moneyfree;
				FreeExpire[playerid] = 30;
 				GetPlayerName(id, giveplayer, sizeof(giveplayer));
				GetPlayerName(playerid, sendername, sizeof(sendername));
				format(string, sizeof(string), "I-ai trimis lui %s o oferta de a fi eliberat pentru $%s.",giveplayer,formatNumber(moneyfree));
				format(string2, sizeof(string2), "You have send to %s an offer to be released from jail for $%s.",giveplayer,formatNumber(moneyfree));
				SCMf(playerid, -1, string, string2);
				SCMf(id, -1, "{AA3333}(Free): {FFFFFF}Politistul %s (%d) iti ofera posibilitatea de a iesi din penitenciar pentru $%s.",sendername, playerid, formatNumber(moneyfree),playerid);
				SCMf(id, -1, "{AA3333}(Free): {FFFFFF}Scrie </accept free %d> daca doresti acest lucru.", playerid);
			}
		}
		else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
	}
	else return SendClientMessage(playerid, -1, "This player is not near you.");
	return 1;
}
YCMD:mdc(playerid, params[], help)
{
    if(playerInfo[playerid][pAdmin] == 0)
    {
        check_cop
    }

    new player;
    if(sscanf(params, "u", player)) return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/mdc [player id/name]");
    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Player not connected.");
    if(playerInfo[player][pWantedLevel] == 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not chased by the police.");

    SCMf(playerid, COLOR_YELLOW, "-- MDC [%s - ID %d] [wanted %d - expires in %s minutes]", GetName(player), player, playerInfo[player][pWantedLevel], ConvertToMinutes(playerInfo[player][pWantedExpire]));
	
	if(!strsame(playerInfo[player][pCrime1], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[player][pCrime1]);
	if(!strsame(playerInfo[player][pCrime2], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[player][pCrime2]);
	if(!strsame(playerInfo[player][pCrime3], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[player][pCrime3]);
    return 1;
}

YCMD:mymdc(playerid, params[], help) 
{
	if(playerInfo[playerid][pWantedLevel] == 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not chased by the police.");

	SCMf(playerid, COLOR_YELLOW, "-- MDC [%s - ID %d] [wanted %d - expires in %s minutes]", GetName(playerid), playerid, playerInfo[playerid][pWantedLevel], ConvertToMinutes(playerInfo[playerid][pWantedExpire]));
	
	if(!strsame(playerInfo[playerid][pCrime1], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[playerid][pCrime1]);
	if(!strsame(playerInfo[playerid][pCrime2], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[playerid][pCrime2]);
	if(!strsame(playerInfo[playerid][pCrime3], "no crime", true)) SCM(playerid, COLOR_WHITE, playerInfo[playerid][pCrime3]);
	return 1;
}

YCMD:wanted(playerid, params[], help)
{
    if(playerInfo[playerid][pAdmin] == 0)
    {
        check_cop
    }

    if(GetWantedPlayers() == 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}No wanted players.");

    for(new x; x < 50; x++) WantedPlayers[playerid][x] = INVALID_PLAYER_ID;

    gDialog = "Suspect\tInfo\n";
    foreach(new player : Player)
    {
        if(playerInfo[player][pWantedLevel] > 0)
        {
            format(gDialog, sizeof(gDialog), "%s%s (/id %d)\twanted %d\n", gDialog, GetName(player), player, playerInfo[player][pWantedLevel]);

            for(new x; x < 50; x++)
            {
                if(WantedPlayers[playerid][x] == INVALID_PLAYER_ID) 
                {
                    WantedPlayers[playerid][x] = player;
                    break;
                }
            }
        }
    }
    return Dialog_Show(playerid, DIALOG_WANTED, DIALOG_STYLE_TABLIST_HEADERS, "Wanted players", gDialog, "Find", "Exit");
}
YCMD:stopanim(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] || IsPlayerInAnyVehicle(playerid) || isPlayerFalling(playerid))
        return 1;

    ClearAnimations(playerid); 
    PlayerHandsup[playerid] = 0;
    playerVars[playerid][var_usingAnimation] = playerVars[playerid][var_loopingAnimation] = false;
    return 1; 
}
YCMD:handsup(playerid, params[], help)
{
	if(isPlayerFalling(playerid)) 
		return sendError(playerid, "You cannot use this command while you are falling.");	

	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Animations are inaccessible only on foot.");
    if(playerVars[playerid][var_freezed] == true) SendClientMessage(playerid, -1, "You cannot do animations while you are freezed.");
	if(playerVars[playerid][b_IS_SLEEPING]) return SendClientMessage(playerid, -1, "You cannot do animations while you are sleeping.");
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
		PlayerHandsup[playerid] = 1;
	}
	return 1;
}
YCMD:frisk(playerid, params[], help)
{
	
    new giveplayerid,sendername[25],giveplayer[25],string[128];
    if(sscanf(params, "u",giveplayerid)) return sendError(playerid, "/frisk [name/playerid]");
	if(groupVariables[playerInfo[playerid][pGroup]][gType] == 1)
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
		    if(ProxDetectorS(8.0, playerid, giveplayerid))
			{
			    if(giveplayerid == playerid) return SendClientMessage(playerid, -1, "You can't frisk yourself.");
			    if(PlayerHandsup[giveplayerid] == 0) return SendClientMessage(playerid, -1, "This isn't with hands up.");
			    GetPlayerName(giveplayerid, giveplayer, sizeof(giveplayer));
				GetPlayerName(playerid, sendername, sizeof(sendername));
			    new text1[20], text2[20], text4[20];
			    if(playerInfo[giveplayerid][pDrugs] > 0) text1 = "| Drugs.";  
			    else text1 = "| Empty Pocket.";
			    if(playerInfo[giveplayerid][pMaterials] > 0) text2 = "| Materials."; 
			    else text2 = "| Empty Pocket."; 
			    if(playerInfo[giveplayerid][pPhoneBook] == true) text4 = "| Phone Book."; 
			    else text4 = "| Empty Pocket.";
			    format(string, sizeof(string), "** Items with {B8DBFF}%s{FFFFFF} **", giveplayer);
		        SendClientMessage(playerid, COLOR_WHITE, string);
		        format(string, sizeof(string), "%s, Grams:%d", text1,playerInfo[giveplayerid][pDrugs]);
				SendClientMessage(playerid, 0xFFFFFFAA, string);
				format(string, sizeof(string), "%s, Materials:%d", text2,playerInfo[giveplayerid][pMaterials]);
				SendClientMessage(playerid, 0xFFFFFFAA, string);
				format(string, sizeof(string), "%s.", text4);
				SendClientMessage(playerid, 0xFFFFFFAA, string);
                new Player_Weapons[13];
                new Player_Ammos[13];
                new i;
                for(i = 1;i <= 12;i++)
                {
                    GetPlayerWeaponData(giveplayerid,i,Player_Weapons[i],Player_Ammos[i]);
                    if(Player_Weapons[i] != 0)
                    {
                        new weaponName[256];
                        GetWeaponName(Player_Weapons[i],weaponName,255);
                        format(string,255,"{B8DBFF}* %s, Gun:{FFFFFF} %s{B8DBFF}, Ammo:{FFFFFF} %d",giveplayer,weaponName,Player_Ammos[i]);
                        SendClientMessage(playerid,0xFFFFFFAA,string);
                    }
                }
				sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "%s has frisked %s for any illegal items.", sendername ,giveplayer);
			}
			else return SendClientMessage(playerid, -1, "This player is not near you.");
		}
        else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
	}
    else return SendClientMessage(playerid, -1, "You are not a cop.");
    return 1;
}
YCMD:cuff(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SendClientMessage(playerid, COLOR_GREY, "You are not a cop.");
	if(!Iter_Contains(DutyMember, playerid)) return SendClientMessage(playerid, COLOR_GREY, "You are not on duty.");

	new target;
	if(sscanf(params, "u", target)) return SendClientMessage(playerid, -1, "Syntax: {ffffff}/cuff [player id/name]");
	if(!IsPlayerConnected(target)) return SendClientMessage(playerid, COLOR_GREY, "Player not connected.");
	//if(vehicleVariables[GetPlayerVehicleID(playerid)][vGroup] != playerInfo[playerid][pGroup]) return SendClientMessage(playerid, COLOR_GREY, "You are not in a group vehicle.");
	if(!IsPlayerInVehicle(target, GetPlayerVehicleID(playerid))) return SendClientMessage(playerid, COLOR_GREY, "That player is not in your vehicle.");
	if(GetPVarInt(target, "cuffed") == 1) return SendClientMessage(playerid, COLOR_GREY, "That player is already cuffed.");

	TogglePlayerControllable(target, 0);
	SetPVarInt(target, "cuffed", 1);
	GameTextForPlayer(target,"~n~~r~Handcuffed!",4000,4);
	sendNearbyMessage(playerid, COLOR_PURPLE, 20.0, "* %s has handcuffed %s.", GetName(playerid), GetName(target));
	SCMf(playerid, COLOR_LIGHTBLUE, "You have handcuffed %s.", GetName(playerid));
	ApplyAnimation(target, "PED", "cower", 4.0, true, false, false, false, false, true);
	return true;
}
YCMD:cancelfree(playerid, params[], help) {
	if(FreeOffer[playerid] == -1) return SendClientMessage(playerid,-1, "No one offered you a free.");
	FreeOffer[playerid] = -1;
	FreePrice[playerid] = 0;
	return 1;
}

YCMD:uncuff(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SendClientMessage(playerid, COLOR_GREY, "You are not a cop.");
	if(!Iter_Contains(DutyMember, playerid)) return SendClientMessage(playerid, COLOR_GREY, "You are not on duty.");

	new target;
	if(sscanf(params, "u", target)) return SendClientMessage(playerid, -1, "Syntax: {ffffff}/uncuff [player id/name]");
	if(!IsPlayerConnected(target)) return SendClientMessage(playerid, COLOR_GREY, "Player not connected.");
	if(!IsPlayerInVehicle(target, GetPlayerVehicleID(playerid))) return SendClientMessage(playerid, COLOR_GREY, "That player is not in your vehicle.");
	if(GetPVarInt(target, "cuffed") == 0) return SendClientMessage(playerid, COLOR_GREY, "That player is not cuffed.");

	TogglePlayerControllable(target, true);
	SetPVarInt(target, "cuffed", 0);
	GameTextForPlayer(target,"~n~~r~Uncuffed!",4000,4);
	sendNearbyMessage(playerid, COLOR_PURPLE, 20.0, "* %s has uncuffed %s.", GetName(playerid), GetName(target));
	SCMf(playerid, COLOR_LIGHTBLUE, "You have uncuffed %s.", GetName(playerid));
	ClearAnimations(target);
	return true;
}
YCMD:arrest(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SendClientMessage(playerid, COLOR_GREY, "You are not a cop.");
	if(!Iter_Contains(DutyMember, playerid)) return SendClientMessage(playerid, COLOR_GREY, "You are not on duty.");

	new target;
	if(sscanf(params, "u", target)) return SendClientMessage(playerid, -1, "Syntax: {ffffff}/arrest [player id/name]");
	if(!IsPlayerConnected(target)) return SendClientMessage(playerid, COLOR_GREY, "Player not connected.");

	if(GetDistanceBetweenPlayers(playerid, target) > 5) return SendClientMessage(playerid, COLOR_GREY, "You are not near that player.");
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, 1527.7622,-1678.2057,5.8906)) return SendClientMessage(playerid, COLOR_GREY, "You are not at arrest place.");
	if(playerInfo[target][pWantedLevel] == 0) return SendClientMessage(playerid, COLOR_GREY, "That player is not chased.");

	playerInfo[target][pJailTime] = 150 * GetPlayerWantedLevel(target);

	new rand = random(2);
	SetPlayerPos(target, jail_pos[rand][0], jail_pos[rand][1], jail_pos[rand][2]);
	SetPlayerFacingAngle(target, 270.0);

	SetPlayerInterior(target, 6);
	SetPlayerVirtualWorld(target, 40001);

	playerInfo[target][pWantedLevel] = 0;
	SetPlayerWantedLevel(target, 0);
	playerInfo[target][pWantedExpire] = 0;

	new query[256];
	mysql_format(SQL, query, sizeof(query), "UPDATE `server_users` SET `playerWantedLevel` = '%d', `playerJailTime` = '%d' WHERE `ID` = '%d'", playerInfo[target][pWantedLevel], playerInfo[target][pJailTime], playerInfo[target][pSQLID]);
	mysql_tquery(SQL, query, "", "");

	ResetPlayerWeapons(target);

	va_SendClientMessageToAll(COLOR_LIGHTRED, "Arrest: %s has been arrested by %s for %d seconds.", GetName(target), GetName(playerid), playerInfo[target][pJailTime]);
	giveRaportPoint(playerid, 1);
	return true;
}
YCMD:confiscate(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SendClientMessage(playerid, COLOR_GREY, "You are not a cop.");
	if(!Iter_Contains(DutyMember, playerid)) return SendClientMessage(playerid, COLOR_GREY, "You are not on duty.");

	new targetID, item[32];
	if(sscanf(params, "us[32]", targetID, item)) {
		SendClientMessage(playerid, COLOR_GREY, "Syntax: {ffffff}/confiscate [player id/name] [item]");
		SendClientMessage(playerid, COLOR_GREY, "Items: {FFFFFF}licence");
		return 1;
	}

	if(!IsPlayerInRangeOfPlayer(playerid, targetID, 5.0)) return SendClientMessage(playerid, COLOR_GREY, "You are not near that player.");
	if(Somated[targetID] == 0) return SendClientMessage(playerid, COLOR_GREY, "That player is not somated.");
	if(!IsPlayerConnected(targetID)) return SendClientMessage(playerid, COLOR_GREY, "Player not connected.");

	switch(YHash(item)) {
		case _H<licence>: {
			if(playerInfo[targetID][pDrivingLicense] == 0) return SendClientMessage(playerid, COLOR_GREY, "This player has no driving license to confiscate.");

			playerInfo[targetID][pDrivingLicense] = -(gettime() + 7200);

			gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof(gQuery), "update `server_accounts` set `playerDrivingLicense` = '%d' where `playerID` = '%d'", playerInfo[targetID][pDrivingLicense], playerInfo[targetID][pSQLID]);
			mysql_tquery(SQL, gQuery, "", "");

			sendNearbyMessage(playerid, COLOR_PURPLE, 20.0, "* %s has confiscated %s's driving license.", GetName(playerid), GetName(targetID));
			SCMf(targetID, COLOR_WHITE, "%s has confiscated your driving license.", GetName(playerid));
			SCMf(playerid, COLOR_WHITE, "You have confiscated %s's driving license.", GetName(targetID));

			giveRaportPoint(playerid, 3);
		}
	}
	return true;
}
YCMD:clear(playerid, params[], help) {
	if(groupVariables[playerInfo[playerid][pGroup]][gType] != 1) return SendClientMessage(playerid, COLOR_GREY, "You are not a cop.");
	if(!Iter_Contains(DutyMember, playerid)) return SendClientMessage(playerid, COLOR_GREY, "You are not on duty.");

	new player;
	if(sscanf(params, "u", player)) return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/clear [player id/name]");
	if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}Player not connected.");
	if(playerInfo[player][pWantedLevel] == 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not chased by the police.");

	SCMf(player, COLOR_YELLOW, "Cop %s cleared your wanted level.", GetName(playerid));
	SCMf(playerid, COLOR_LIGHTRED, "/clear: You cleared %s's wanted level.", GetName(player));

	SetPlayerWantedLevelEx(player, 0, "clear");
	PlayerTextDrawHide(player, ptd_wanted);
	return true;
}
YCMD:so(playerid, params[], help)
{
    new carid = GetPlayerVehicleID(playerid);
    check_cop
    check_duty

    if(!IsACopCar(carid)) return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu esti in unul dintre vehiculele factiunii.");

    new player;
    if(sscanf(params, "u", player)) return SCM(playerid, COLOR_GREY, "Usage:{ffffff} /so [player id/name]");
    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Error:{ffffff} Player not connected.");
    if(GetPVarInt(playerid, "so_delay") > gettime()) return SCMf(playerid, COLOR_GREY, "Error:{ffffff} You can't use this command for %d seconds.", GetPVarInt(playerid, "so_delay")-gettime());
    if(GetDistanceBetweenPlayers(playerid, player) > 30.0) return SCM(playerid, COLOR_GREY, "Error:{ffffff} You are not near that player.");

    SetPVarInt(playerid, "so_delay", gettime() + 5);
    Somated[player] = gettime();

    if(GetPlayerState(player) == PLAYER_STATE_DRIVER)
    {
        Megaphone(playerid, "{1560BD}%s{FFFF00}, esti urmarit de politie! Trage pe dreapta imediat!", GetName(player));
    }

    else 
    {
        if(GetPlayerWantedLevel(player) == 0) Megaphone(playerid, "{1560BD}%s{FFFF00}, esti urmarit de politie! Ramai pe loc!", GetName(player));
        else Megaphone(playerid, "{1560BD}%s{FFFF00}, esti urmarit de politie! Te predai?", GetName(player));
    }
    return 1;
}

// ------------------------------------- //
//                Dialogs                //
// -------------------------------------//

Dialog:DIALOG_WANTED(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(!IsPlayerConnected(WantedPlayers[playerid][listitem])) return 1;
    
    findFunction(playerid, WantedPlayers[playerid][listitem]);
    return 1;
}