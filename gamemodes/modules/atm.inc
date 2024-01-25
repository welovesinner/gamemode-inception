// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Arrays                   //
// ------------------------------------- //

new const Float:atmPositions[][] = {
    {1102.180000, -1460.640000, 15.360000, 88.560000},
    {1462.380000, -1010.200000, 26.450000, 0.000000},
    {1224.910000, -1811.670000, 16.200000, 0.000000},
    {1643.291870, -2298.111816, -1.572660, 90.20},
    {476.755584, -1481.155517, 19.481248, 76.899955},
    {1008.346801, -1115.500854, 23.509809, 0.000000},
    {534.597839, -1293.977905, 16.852178, -179.999694},
    {333.300903, -1505.723754, 35.649101, 45.400028},
    {808.760253, -1627.097534, 12.952804, 0.000000},
    {1796.177368, -1165.027221, 23.428117, -14.500005},
    {1367.327758, -1290.322875, 13.146868, -89.299919},
    {1054.864624, 2152.916259, 10.440304, -89.999923},
    {1837.376098, -1690.670532, 12.917483, -89.999969},
    {2228.407714, -1716.143188, 13.107613, -89.299888},
    {1348.177612, -1759.263061, 13.122047, -179.899810},
    {1787.090454, -1867.361938, 13.184904, 179.600021}
};

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

bool:isNearATM(const playerid) {
    new 
        nearbyATM[1] = -1, Float: X, Float: Y, Float: Z;

    GetPlayerPos(playerid, X, Y, Z); 

    Streamer_GetNearbyItems(X, Y, Z, STREAMER_TYPE_OBJECT, nearbyATM, 1, 2.5);
    
    return nearbyATM[0] != -1 ? Streamer_GetIntData(STREAMER_TYPE_OBJECT, nearbyATM[0], E_STREAMER_MODEL_ID) == 2942 : false;
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:ATM(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!listitem)
        return Dialog_Show(playerid, ATMWITHDRAW, DIALOG_STYLE_INPUT, "SERVER: Automated Teller Machine", "Write in the box below the value of the money you want to withdraw.\nYou can withdraw up to $10.000 money.", "Withdraw", "Cancel");

    return Dialog_Show(playerid, NULL, DIALOG_STYLE_MSGBOX, "SERVER: Automated Teller Machine", "The current balance in your bank account is: $%s.", "Exit", "", formatMoney(playerInfo[playerid][pBankStore], playerInfo[playerid][pBank]));
}

Dialog:ATMWITHDRAW(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(!isnumeric(inputtext))
        return Dialog_Show(playerid, ATMWITHDRAW, DIALOG_STYLE_INPUT, "SERVER: Automated Teller Machine", "Write in the box below the value of the money you want to withdraw.\nYou can withdraw up to $10.000 money.", "Withdraw", "Cancel");

    new money = strval(inputtext), tax = money / 100;

    if(money > 10000 || money < 1)
        return sendError(playerid, "Invalid Money! ($1 - $10.000)");

    if(playerInfo[playerid][pBank] < money + tax && playerInfo[playerid][pBankStore] < 1)
        return sendError(playerid, "Nu ai suma necesara de bani in banca. Ai nevoie de $%s (taxa: $%s).", formatNumber(money + tax), formatNumber(tax));

    if(money >= 1000)
        updatePlayerQuestProgress(playerid, QUEST_TYPE_WITHDRAWATM);

    addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false); 
    substractBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], 0, money+tax, false);

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `BankStore` = %d, `Bank` = %d WHERE `ID` = %d", playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], playerInfo[playerid][pSQLID]);
    
    playerVars[playerid][var_atm_delay] = gettime() + 30; 

    return SCMf(playerid, COLOR_DARKGREEN, "* You withdrawed succesfully $%s (fee: $%s) money from your bank account.", formatNumber(money), formatNumber(tax));
}

// ------------------------------------- //
//              Hooks                    //
// ------------------------------------- //

hook OP_KeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SECONDARY_ATTACK)) {
        if(isNearATM(playerid) && !IsPlayerInAnyVehicle(playerid)) {
            if(playerVars[playerid][var_atm_delay] > gettime())
                return sendError(playerid, "Trebuie sa astepti %d secunde inainte sa folosesti ATM-ul din nou.", playerVars[playerid][var_atm_delay] - gettime());

            return Dialog_Show(playerid, ATM, DIALOG_STYLE_LIST, "SERVER: Automated Teller Machine", "Withdraw Money\nBalance", "Select", "Cancel");
        }
    }
    return 1;
}

hook OnGameModeInit() {
    for(new i = 0; i < sizeof atmPositions; ++i) {
        CreateDynamicObject(2942, atmPositions[i][0], atmPositions[i][1], atmPositions[i][2], 0.0, 0.0, atmPositions[i][3]);
        CreateDynamic3DTextLabel("Automated Teller Machine{FFFFFF}\nPress {1C8A15}'F'{FFFFFF} to enter on menu.", COLOR_GREEN, atmPositions[i][0], atmPositions[i][1], atmPositions[i][2], 3.0);
    }
    return 1;
}