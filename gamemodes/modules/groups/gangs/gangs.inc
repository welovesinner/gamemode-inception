/*
    GANGS
*/

#include <YSI_Coding\y_hooks>

new gangOrder[6][3] = {
    {24, 100, 300},
    {24, 30, 500},
    {31, 150, 1000},
    {30, 150, 1100},
    {29, 90, 1000},
    {33, 25, 2000}
};

new hitmanOrder[2][3] = {
    {4, 1, 500},
    {34, 10, 2000}
};

stock IsInAGang(playerid)
{
    if(groupVariables[playerInfo[playerid][pGroup]][gType] == 5) return 1;
    return 0;
}

CMD:order(playerid, params[])
{
    if(playerInfo[playerid][pGroup] != 5 && !IsInAGang(playerid))
    {
        return 1;
    }

    if(isnull(params)) 
    {
        SCM(playerid, COLOR_GREY, "Syntax: {ffffff}/order [option]");

        if(IsInAGang(playerid))
        {   
            SCM(playerid, COLOR_GREY, "Options: {ffffff}1 - Deagle | 2 - Shotgun | 3 - M4 | 4 - AK47 | 5 - MP5 | 6 - Rifle");
        }

        else SCM(playerid, COLOR_GREY, "Options: {ffffff}1 - Knife | 2 - Sniper");
        return 1;
    }

    new order = strval(params);
    if(IsInAGang(playerid))
    {
        if(order > sizeof(gangOrder)) return 1;

        if(GetMoney(playerid) < gangOrder[order - 1][2] && GetMilliards(playerid) < 1)
            return sendError(playerid, "Nu ai $%s.", formatNumber(gangOrder[order - 1][2]));
        GivePlayerWeapon(playerid, gangOrder[order - 1][0], gangOrder[order - 1][1]);
        SCMf(playerid, COLOR_WHITE, "Ti-ai cumparat un %s cu %d gloante (pret $%s).", WeaponNames[gangOrder[order - 1][0]], gangOrder[order - 1][1], formatNumber(gangOrder[order - 1][2]));
        substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, gangOrder[order - 1][2]);
    }

    else
    {
        if(order > sizeof(hitmanOrder)) return 1;

        if(GetMoney(playerid) < hitmanOrder[order - 1][2] && GetMilliards(playerid) < 1)
            return sendError(playerid, "Nu ai $%s.", formatNumber(hitmanOrder[order - 1][2]));

        GivePlayerWeapon(playerid, hitmanOrder[order - 1][0], hitmanOrder[order - 1][1]);
        SCMf(playerid, COLOR_WHITE, "Ti-ai cumparat un %s cu %d gloante (pret $%s).", WeaponNames[hitmanOrder[order - 1][0]], hitmanOrder[order - 1][1], formatNumber(hitmanOrder[order - 1][2]));
        substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, hitmanOrder[order - 1][2]);

    }

    return 1;
}