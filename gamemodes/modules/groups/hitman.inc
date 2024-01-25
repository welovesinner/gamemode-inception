// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ----------------------------------------//
//             Variables                  //
// --------------------------------------//

new 
    Iterator: Contracts<MAX_PLAYERS>,
    Undercover[MAX_PLAYERS],
    contract_get[MAX_PLAYERS];

// ----------------------------------------//
//             Query Functions            //
// --------------------------------------//

query_function pUpdateInt(playerid, varname[], varnameingame) {
	gString[0] = (EOS);
	mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `%s` = '%d' WHERE `id` = '%d' LIMIT 1", varname, varnameingame, playerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gQuery, "", "");
	return true;
}

// ----------------------------------------//
//                Hooks                   //
// --------------------------------------//

hook OnPlayerConnect(playerid)
{
    contract_get[playerid] = -1;
    Undercover[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid)
{
    if(Iter_Contains(Contracts, playerid)) Iter_Remove(Contracts, playerid);
    return 1;
}


hook OnGameModeInit()
{
    Iter_Clear(Contracts);	
    return 1;
}

hook OnPlayerStreamIn(playerid, forplayerid)
{
    if(contract_get[playerid] >= 0) ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    Undercover[playerid] = 0;
    return 1;
}

// ------------------------------------- //
//             Commands                  //
// ------------------------------------- //

YCMD:contract(playerid, params[], help) {
	if(playerInfo[playerid][pLevel] < 3) 
        return SCM(playerid, -1, "Nu ai level 3.");

	if(playerInfo[playerid][pGroup] == 5) 
        return SCM(playerid, -1, "Nu poti folosi aceasta comanda deoarece esti hitman.");
    
	new id, money;
	if(sscanf(params, "ui", id, money)) 
        return SCM(playerid, COLOR_GREY, "Usage:{ffffff} /contract [name/playerid] [money]");

	if(money < 10000 || money > 10000000) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Invalid money.");

	if(!IsPlayerConnected(id)) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Invalid id.");

	if(id == playerid) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti folosi aceasta comanda pe tine.");

	if(GetPlayerVirtualWorld(id) >= 1) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti pune un contract pe acel jucator deoarece se afla in virtual world.");

	if(playerInfo[id][pAdmin] >= 1) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti pune un contract pe acel jucator deoarece este admin.");

	if(playerInfo[id][pGroup] == 5) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti pune un contract pe acel player deoarece este hitman.");

	if(GetMoney(playerid) < money && GetMilliards(playerid) < 1) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu ai bani.");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false);

	playerInfo[id][pHeadValue] += money; pUpdateInt(id, "HeadValue", playerInfo[id][pHeadValue]);
	Iter_Add(Contracts, id);
	
    SendGroupMessage(5, COLOR_SERVER, "(Hitman) {ffffff}New hit available! Target: %s. Price: $%s.", GetName(id), formatNumber(playerInfo[id][pHeadValue]));
	SCM(playerid, COLOR_SERVER, "Contract placed!");
	return true;
}

YCMD:contracts(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] != 5) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte din Hitman Agency.");

	if(!Iter_Contains(DutyMember, playerid)) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti folosi aceasta comanda deoarece nu esti on duty.");

	SCM(playerid, COLOR_GREY, "----- Contracts -----");
	foreach(new x : Contracts) { SCMf(playerid, -1, "%s [id: %d, jail time: %d]", GetName(x), x, playerInfo[x][pJailTime]); }
	SCMf(playerid, COLOR_SERVER, "Total targets: %d", Iter_Count(Contracts));
	SCM(playerid, COLOR_GREY, "----------");
	return true;
}

YCMD:undercover(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] != 5) 
        return SCM(playerid, -1, "Nu faci parte din Hitman Agency.");

	if(!Iter_Contains(DutyMember, playerid)) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti folosi aceasta comanda deoarece nu esti on duty.");

	switch(Undercover[playerid]) {
		case 0: {
			Undercover[playerid] = 1;
			foreach(new i : Player) ShowPlayerNameTagForPlayer(i, playerid, 0);
			SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}You are now undercover.");
		}
		case 1: {
			Undercover[playerid] = 0;
			foreach(new i : Player) ShowPlayerNameTagForPlayer(i, playerid, 1);
			SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}You are not undercover anymore.");
		}
	}
	return true;
}

YCMD:mycontract(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] != 5) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte din Hitman Agency.");

	if(contract_get[playerid] < 0) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu ai un contract.");

	SCMf(playerid, COLOR_SERVER, "(Hitman) {ffffff}You have a contract on %s (id: %d, money: $%s).", GetName(contract_get[playerid]), contract_get[playerid], formatNumber(playerInfo[contract_get[playerid]][pHeadValue]));
	return true;
}	

YCMD:cancelhit(playerid, params[], help) {
	if(playerInfo[playerid][pGroup] != 5) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu faci parte din Hitman Agency.");

	if(contract_get[playerid] < 0) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu ai un contract.");

	contract_get[playerid] = -1; Command_ReProcess(playerid, va_return("/killcp"), false);
	SendGroupMessage(5, COLOR_SERVER, "(Hitman) {ffffff}%s canceled and deleted his contract.", GetName(playerid));
	return true;
}

YCMD:gethit(playerid, params[], help) {
    new gasit = 0, x = Iter_Random(Contracts);

	if(playerInfo[playerid][pGroup] != 5) 
        return SCM(playerid, -1, "Nu faci parte din Hitman Agency.");

    if(!Iter_Contains(DutyMember, playerid)) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Nu poti folosi aceasta comanda deoarece nu esti on duty.");

	if(contract_get[playerid] >= 0) 
        return SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}You have already a contract.");

	if(Iter_Count(Contracts) < 1) 
        return SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}No contracts available.");

	if(playerInfo[x][pHeadValue] > 0 && playerInfo[x][pGroup] != 5 && playerInfo[x][pJailTime] < 1 && playerInfo[x][pAdmin] < 1) {
		contract_get[playerid] = x;
		Iter_Remove(Contracts, x);
		gasit = 1;
	}
	if(gasit == 0) return SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}Ai nimerit un contract neacceptat, foloseste din nou /gethit.");
	SendGroupMessage(5, COLOR_SERVER, "(Hitman) {ffffff}%s received a contract. Target: %s. Money: $%s.", GetName(playerid), GetName(contract_get[playerid]), formatNumber(playerInfo[contract_get[playerid]][pHeadValue]));
	SCM(playerid, COLOR_SERVER, "(Hitman) {ffffff}You have a new contract (/mycontract).");
	return true;
}