// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Enums                    //
// ------------------------------------- //

enum e_pinInsertTypes {
    PIN_INVALID_TYPE,
    PIN_SET_TYPE,
    PIN_LOGIN_TYPE
}

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static  
    pinInsertIndex[MAX_PLAYERS],
    pinInserted[MAX_PLAYERS][5],
    e_pinInsertTypes:pinInsertType[MAX_PLAYERS];

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

static destroyPlayerPinTextdraws(const playerid) {
    for(new i = 0; i < 19; ++i) playerTextDrawDestroy(playerid, playerTextdraws[playerid][PinTD][i]);

    pinInsertType[playerid] = PIN_INVALID_TYPE;
    return CancelSelectTextDraw(playerid);
}

showPlayerPinTextdraws(const playerid, const e_pinInsertTypes:type) {
    playerTextdraws[playerid][PinTD][0] = CreatePlayerTextDraw(playerid, 324.009490, 121.166625, "box");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][0], 0.000000, 21.000000);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][PinTD][0], 0.000000, 104.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][0], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][0], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][PinTD][0], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][PinTD][0], 151);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][0], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][0], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][0], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][0], 1);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][0], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][0], 0);

    playerTextdraws[playerid][PinTD][1] = CreatePlayerTextDraw(playerid, 272.089233, 141.583312, "box");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][1], 0.000000, 1.818330);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][PinTD][1], 375.800506, 0.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][1], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][1], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][PinTD][1], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][PinTD][1], 255);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][1], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][1], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][1], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][1], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][1], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][1], 0);

    playerTextdraws[playerid][PinTD][2] = CreatePlayerTextDraw(playerid, 325.713623, 141.800033, "----");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][2], 0.400936, 1.664165);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][2], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][2], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][2], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][2], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][2], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][2], 3);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][2], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][2], 0);

    if(type == PIN_SET_TYPE) {
        playerTextdraws[playerid][PinTD][3] = CreatePlayerTextDraw(playerid, 369.617126, 121.166648, "x");
        PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][3], 0.346118, 0.824163);
        PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][PinTD][3], 376.049926, 5.500000);
        PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][3], 1);
        PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][3], -1);
        PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][PinTD][3], 1);
        PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][PinTD][3], -2147483393);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][3], 0);
        PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][3], 1);
        PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][3], 255);
        PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][3], 3);
        PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][3], 1);
        PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][3], 0);
        PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][PinTD][3], true);
    }

    playerTextdraws[playerid][PinTD][4] = CreatePlayerTextDraw(playerid, 324.099304, 279.023498, "0");
    playerTextdraws[playerid][PinTD][5] = CreatePlayerTextDraw(playerid, 293.297454, 167.516693, "1");
    playerTextdraws[playerid][PinTD][6] = CreatePlayerTextDraw(playerid, 324.099334, 167.516693, "2");
    playerTextdraws[playerid][PinTD][7] = CreatePlayerTextDraw(playerid, 354.901214, 167.516693, "3");
    playerTextdraws[playerid][PinTD][8] = CreatePlayerTextDraw(playerid, 293.297454, 205.118986, "4");
    playerTextdraws[playerid][PinTD][9] = CreatePlayerTextDraw(playerid, 324.099304, 205.118896, "5");
    playerTextdraws[playerid][PinTD][10] = CreatePlayerTextDraw(playerid, 354.901214, 205.118896, "6");
    playerTextdraws[playerid][PinTD][11] = CreatePlayerTextDraw(playerid, 293.297454, 243.121307, "7");
    playerTextdraws[playerid][PinTD][12] = CreatePlayerTextDraw(playerid, 324.099304, 243.121307, "8");
    playerTextdraws[playerid][PinTD][13] = CreatePlayerTextDraw(playerid, 354.901214, 243.121307, "9");

    playerTextdraws[playerid][PinTD][14] = CreatePlayerTextDraw(playerid, 272.916992, 123.833328, "PIN CODE:");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][14], 0.189633, 1.133334);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][14], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][14], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][14], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][14], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][14], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][14], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][14], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][14], 0);

    playerTextdraws[playerid][PinTD][15] = CreatePlayerTextDraw(playerid, 345.286163, 276.166748, "ld_chat:thumbup");
    playerTextdraws[playerid][PinTD][16] = CreatePlayerTextDraw(playerid, 283.399902, 276.166748, "ld_chat:thumbdn");
    playerTextdraws[playerid][PinTD][17] = CreatePlayerTextDraw(playerid, 344.400268, 300.566864, "INSERT");
    playerTextdraws[playerid][PinTD][18] = CreatePlayerTextDraw(playerid, 283.598999, 300.566864, "RESET");

    for(new i = 0; i < 19; ++i) {
        if(i < 10) {
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][4 + i], 0.590687, 1.979168);
            PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][PinTD][4 + i], 19.000000, 19.000000);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][4 + i], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][4 + i], -1);
            PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][PinTD][4 + i], 1);
            PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][PinTD][4 + i], -1061109685);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][4 + i], 0);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][4 + i], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][4 + i], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][4 + i], 3);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][4 + i], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][4 + i], 0);
            PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][PinTD][4 + i], true);

            if(i < 2) {
                PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][15 + i], 0.000000, 0.000000);
                PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][PinTD][15 + i], 19.000000, 22.000000);
                PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][15 + i], 1);
                PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][15 + i], -1);
                PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][15 + i], 0);
                PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][15 + i], 0);
                PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][15 + i], 255);
                PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][15 + i], 4);
                PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][15 + i], 0);
                PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][15 + i], 0);
                PlayerTextDrawSetSelectable(playerid, playerTextdraws[playerid][PinTD][15 + i], true);

                PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][PinTD][17 + i], 0.138564, 0.829999);
                PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][PinTD][17 + i], 1);
                PlayerTextDrawColor(playerid, playerTextdraws[playerid][PinTD][17 + i], -1);
                PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][17 + i], 0);
                PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][PinTD][17 + i], 1);
                PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][PinTD][17 + i], 255);
                PlayerTextDrawFont(playerid, playerTextdraws[playerid][PinTD][17 + i], 2);
                PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][PinTD][17 + i], 1);
                PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][PinTD][17 + i], 0);
            }
        }
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][PinTD][i]);
    }

    pinInsertType[playerid] = type;
    pinInserted[playerid] = "----";
    pinInsertIndex[playerid] = 0;
    return SelectTextDraw(playerid, 0x3A9937FF);
}

e_pinInsertTypes:getPlayerPinInsertType(const playerid) 
    return pinInsertType[playerid];

// ------------------------------------- //
//              Timers                   //
// ------------------------------------- //

timer pinTimer[20000](const playerid) {
    if(!IsPlayerConnected(playerid))
        return 1;
    
    defer delayedKick(playerid); 
    playerInfo[playerid][pLoginTimer] = Timer: 0;
    return SCM(playerid, COLOR_RED, "* Ai primit kick deoarece nu ai introdus codul pin in 20 secunde.");
}

// ------------------------------------- //
//              Command                  //
// ------------------------------------- //

YCMD:changepin(playerid, params[], help) {
    if(getPlayerPinInsertType(playerid) != PIN_INVALID_TYPE || playerVars[playerid][b_CLOTHES_SHOW] || playerVars[playerid][b_GUNSHOP_SHOW]) 
        return 1;

    return showPlayerPinTextdraws(playerid, PIN_SET_TYPE);
}

// ------------------------------------- //
//              Hooks                    //
// ------------------------------------- //

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    if(getPlayerPinInsertType(playerid) != PIN_INVALID_TYPE) {
        if(playertextid == playerTextdraws[playerid][PinTD][3]) {
            destroyPlayerPinTextdraws(playerid);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        }
        else if(playertextid >= playerTextdraws[playerid][PinTD][4] && playertextid <= playerTextdraws[playerid][PinTD][13]) {
            if(pinInserted[playerid][3] != '-') 
                return 1;

            pinInserted[playerid][pinInsertIndex[playerid] ++] = '0' + (_:playertextid - _:playerTextdraws[playerid][PinTD][4]);
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][PinTD][2], pinInserted[playerid]);

            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        }
        else if(playertextid == playerTextdraws[playerid][PinTD][16]) {
            if(pinInserted[playerid][0] == '-')
                return 1;

            pinInsertIndex[playerid] = 0;

            pinInserted[playerid] = "----";
            PlayerTextDrawSetString(playerid, playerTextdraws[playerid][PinTD][2], "----");

            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        }
        else if(playertextid == playerTextdraws[playerid][PinTD][15]) {
            if(pinInserted[playerid][3] == '-')
                return 1;

            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);

            if(getPlayerPinInsertType(playerid) == PIN_LOGIN_TYPE) {
                stop playerInfo[playerid][pLoginTimer];

                if(playerInfo[playerid][pPin] != strval(pinInserted[playerid])) {
                    SCM(playerid, COLOR_YELLOW, "* Your pin is wrong, you got kicked from the server.");
                    
                    defer delayedKick(playerid);

                    return destroyPlayerPinTextdraws(playerid);
                }
                
                SCM(playerid, COLOR_YELLOW, "* Your pin is correct. You are logged in to your account.");
            }
            else if(getPlayerPinInsertType(playerid) == PIN_SET_TYPE) {
                va_mysql_tquery("UPDATE `server_users` SET `Pin` = %d WHERE `ID` = %d", strval(pinInserted[playerid]), playerInfo[playerid][pSQLID]);

                SCMf(playerid, COLOR_YELLOW, "* Your new pin is *%s*. You will need this pin every time you log in. Remember it!", pinInserted[playerid]);
            }
            destroyPlayerPinTextdraws(playerid);
        }
    }
    return 1;
}

hook OP_ClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == INVALID_TEXT_DRAW && getPlayerPinInsertType(playerid) != PIN_INVALID_TYPE) 
        return SelectTextDraw(playerid, 0x3A9937FF);
    
    return 1;
}

hook OnPlayerConnect(playerid) {
    pinInsertType[playerid] = PIN_INVALID_TYPE;
    return 1;
}