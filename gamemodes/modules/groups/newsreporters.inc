/*
    NEWS REPORTERS
*/

#include <YSI_Coding\y_hooks>

#define check_reporter              if(!IsAReporter(playerid)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not a reporter.");
new Iterator:live_players<MAX_PLAYERS>;
new LiveInvite[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    LiveInvite[playerid] = INVALID_PLAYER_ID;
}
hook OnPlayerText(playerid, text[]) {
	if(Iter_Contains(live_players, playerid))
	{
		va_SendClientMessageToAll(COLOR_PURPLE, "%s %s: %s", IsAReporter(playerid) ? "NR" : "Liveplayer", GetName(playerid), text);
		return 0;
	}
    return 0;
}
hook OnPlayerDisconnect(playerid, reason)
{
    Iter_Remove(live_players, playerid);

    LiveInvite[playerid] = INVALID_PLAYER_ID;
}

function OnPlayerAcceptsLiveInvite(playerid, player)
{
    if(LiveInvite[playerid] == INVALID_PLAYER_ID) return SCM(playerid, COLOR_GREY, "Error: {ffffff}No one has sent you an offer.");
    if(LiveInvite[playerid] != player) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player didn't sent you an invite.");
    if(!IsAReporter(LiveInvite[playerid]))
    {
        LiveInvite[playerid] = INVALID_PLAYER_ID;
    }

    Iter_Add(live_players, playerid);

    SCMf(LiveInvite[playerid], COLOR_YELLOW, "%s has accepted your invite!", GetName(playerid));
    SCM(playerid, COLOR_SERVER, "You have accepted the live interview. Respect the rules!");

    LiveInvite[playerid] = INVALID_PLAYER_ID;
    return 1;
}

stock IsAReporter(playerid)
{
    if(groupVariables[playerInfo[playerid][pGroup]][gType] == 3) return 1;
    return 0;
}

YCMD:news(playerid, params[], help)
{
    check_reporter

    if(Iter_Count(live_players) > 0) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You can't place ads right now.");

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 582) 
    {
        return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not in a news van.");
    }

    if(isnull(params))
    {
        return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/news [text]");
    }

    if(GetPVarInt(playerid, "news_delay") > gettime())
    {
        return SCMf(playerid, COLOR_GREY, "Error: {ffffff}You can send another ad in %d seconds.", GetPVarInt(playerid, "news_delay") - gettime());
    }

    new hour, minute, second;
    gettime(hour, minute, second);

    if(minute >= 50 && minute <= 59) SetPVarInt(playerid, "news_delay", gettime() + 5);
    else SetPVarInt(playerid, "news_delay", gettime() + 120);

    new price = strlen(params) * 2;
    addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price);
    va_SendClientMessageToAll(COLOR_PURPLE, "NR %s: %s", GetName(playerid), params);

    SCMf(playerid, COLOR_GREY, "Ai primit $%s deoarece anuntul tau are %d caractere.", formatNumber(price), strlen(params));
    return 1;
}

YCMD:live(playerid, params[], help)
{
    if(playerInfo[playerid][pAdmin] < 6)
    {
        check_reporter

        if(playerInfo[playerid][pGroupRank] < 2) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You need rank 2+ in order to take interviews.");
    }

    new player;
    if(sscanf(params, "u", player)) return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/live [player id/name]");
    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Player not connected.");
    if(Iter_Contains(live_players, player)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is already in an interview.");
    if(GetPlayerScore(player) < 5) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player needs to have level 5+ in order to take an interview.");

    if(LiveInvite[player] == playerid) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You already sent a live request to that player.");
    LiveInvite[player] = playerid;

    SCMf(player, COLOR_D, "Reporter %s invited you to take an interview. Type /accept %d live to accept!", GetName(playerid), playerid);
    SCM(playerid, COLOR_PINK, "Invite sent!");
    return 1;
}

YCMD:endlive(playerid, params[], help)
{
    if(playerInfo[playerid][pAdmin] == 0)
    {
        check_reporter

        if(playerInfo[playerid][pGroupRank] < 2) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You need rank 2+ in order to take interviews.");
    }

    new player;
    if(sscanf(params, "u", player)) return SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/endlive [player id/name]");
    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Player not connected.");
    if(!Iter_Contains(live_players, player)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not in an interview.");

    Iter_Remove(live_players, player);

    SCMf(player, COLOR_YELLOW, "%s stopped the interview.", GetName(playerid));
    SCMf(playerid, COLOR_PURPLE, "You have stopped the interview with %s.", GetName(player));
    return 1;
}
