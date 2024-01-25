/*
    PARAMEDICS
*/

stock IsAMedic(playerid)
{
    if(groupVariables[playerInfo[playerid][pGroup]][gType] == 2) return 1;
    return 0;
}
CMD:giveheal(playerid, params[])
{
    new carid = GetPlayerVehicleID(playerid);
    if(!IsAMedic(playerid)) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not a medic.");
    if(!IsAnAmbulance(carid)) return SCM(playerid, COLOR_GREY, "Error:{ffffff} You are not in a ambulance.");
    
    new player, price;
    if(sscanf(params, "ui", player, price)) 
        return SCM(playerid, COLOR_GREY, "Usage:{ffffff} /giveheal [name/playerid] [money]");

    if(!IsPlayerConnected(player)) return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(price < 1 || price > 1000) 
        return SCM(playerid, COLOR_GREY, "Error:{ffffff} Invalid money.");
    
    if(GetMoney(player) < price && GetMilliards(player) < 1)
        return sendError(playerid, "Error: {ffffff}That player doesn't have $%s.", formatNumber(price));

    if(GetPlayerVehicleID(player) != GetPlayerVehicleID(playerid))
    {
        return SCM(playerid, COLOR_GREY, "Error: {ffffff}That player is not in your vehicle.");
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, COLOR_GREY, "Error: {ffffff}You are not the driver of this vehicle.");

    new Float:hp; 
    GetPlayerHealth(player, hp);

    if(hp >= 95.0) 
        return sendError(playerid, "Acel jucator nu are nevoie de heal..");

    SetPlayerHealth(player, 100);
    substractMoney(player, playerInfo[player][pMoneyStore], playerInfo[player][pMoney], 0, -price);

    va_GameTextForPlayer(player, "~r~-$%s", 3000, 1, formatNumber(price));

    sendNearbyMessage(playerid, COLOR_PURPLE, 15.0, "* %s healed %s for $%s.", GetName(playerid), GetName(player), formatNumber(price));
    return 1;
}