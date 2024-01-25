// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//             Constants                 //
// ------------------------------------- //

#define LOTTO_TICKETS_LIMIT 3
#define LOTTO_NUMBERS_LIMIT 5
#define LOTTO_ROUND_WAIT_TIME 300

// ------------------------------------- //
//             Enums                     //
// ------------------------------------- //

static enum e_lottoInfo {
    lottoNumber[LOTTO_NUMBERS_LIMIT], lottoBet, lottoNumbersCount
}

static enum e_lottoNumbers {
    Float:lottoNumberPosX, Float:lottoNumberPosY, lottoNumberTD[3]
}

// ------------------------------------- //
//             Variables                 //
// ------------------------------------- //

static const lottoNumbersTDsCoords[][e_lottoNumbers] = {
    {158.146759, 111.350173, "1"}, {166.747283, 111.350173, "2"}, {175.947845, 111.350173, "3"}, {185.148406, 111.350173, "4"}, {194.248962, 111.350173, "5"}, 
    {203.549530, 111.350173, "6"}, {212.950103, 111.350173, "7"}, {222.150665, 111.350173, "8"}, {231.951263, 111.350173, "9"}, {149.046203, 124.549537, "10"},
    {164.547149, 124.549537, "11"}, {180.048095, 124.549537, "12"}, {195.949066, 124.549537, "13"}, {211.750030, 124.549537, "14"}, {227.951019, 124.549537, "15"},
    {243.651977, 124.549537, "16"}, {149.046203, 137.749816, "17"}, {164.547149, 137.749816, "18"}, {180.348114, 137.749816, "19"}, {196.549102, 137.749816, "20"},
    {212.450073, 137.749816, "21"}, {228.051025, 137.749816, "22"}, {243.851989, 137.749816, "23"}, {149.477737, 151.133926, "24"}, {164.978683, 151.133926, "25"},
    {180.479629, 151.033920, "26"}, {196.380599, 151.033920, "27"}, {212.113067, 151.033920, "28"}, {228.114044, 151.033920, "29"}, {243.915008, 151.033920, "30"},
    {164.978683, 164.034713, "31"}, {180.379623, 164.034713, "32"}, {196.180587, 164.034713, "33"}, {212.381576, 164.034713, "34"}, {228.182540, 164.034713, "35"}
};

static const Float:lottoBetMultiplier[LOTTO_NUMBERS_LIMIT] = {
    1.5, 1.75, 2.0, 5.0, 10.0 
};

static 
    PlayerText:lottoPlayerTDs[MAX_PLAYERS][6] = {{PlayerText:-1, ...}, ...},
    PlayerText:lottoPickNumbersTDs[MAX_PLAYERS][38] = {{PlayerText:-1, ...}, ...},
    bool:lottoPlayerIn[MAX_PLAYERS],
    lottoPlayerToggle[MAX_PLAYERS],
    lottoTicketsCount[MAX_PLAYERS],
    lottoTickets[MAX_PLAYERS][LOTTO_TICKETS_LIMIT][e_lottoInfo],

    Text3D:lottoLabel,
    Text:lottoGlobalTDs[6] = {Text:-1, ...},
    Text:lottoBallsTDs[15] = {Text:-1, ...},
    Text:lottoBallsNumbersTDs[15] = {Text:-1, ...},
    Timer:lottoTimer,
    lottoSecondsLeft = LOTTO_ROUND_WAIT_TIME,
    lottoRoundsNumbers[3][LOTTO_NUMBERS_LIMIT],
    lottoPickedNumbersCount,
    SortedArray:lottoNumbers<5>,
    Iterator:lottoShown<MAX_PLAYERS>,
    Iterator:lottoPlayers<MAX_PLAYERS>;

// ------------------------------------- //
//             Functions                 //
// ------------------------------------- //

static showPlayerLotto(const playerid) {
    lottoPlayerIn[playerid] = true;
    lottoPlayerToggle[playerid] = 0;

    Iter_Add(lottoShown, playerid);

    SelectTextDraw(playerid, -1);

    TogglePlayerControllableEx(playerid, true);

    lottoPlayerTDs[playerid][0] = CreatePlayerTextDraw(playerid, 143.728073, 111.816757, "box");
    PlayerTextDrawLetterSize(playerid, lottoPlayerTDs[playerid][0], 0.000000, 15.000000);
    PlayerTextDrawTextSize(playerid, lottoPlayerTDs[playerid][0], 248.849899, 0.000000);
    PlayerTextDrawAlignment(playerid, lottoPlayerTDs[playerid][0], 1);
    PlayerTextDrawColor(playerid, lottoPlayerTDs[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, lottoPlayerTDs[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, lottoPlayerTDs[playerid][0], 159);
    PlayerTextDrawBackgroundColor(playerid, lottoPlayerTDs[playerid][0], 255);
    PlayerTextDrawFont(playerid, lottoPlayerTDs[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, lottoPlayerTDs[playerid][0], 1);
    PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][0]);

    lottoPlayerTDs[playerid][1] = CreatePlayerTextDraw(playerid, 196.397277, 94.399955, "your tickets");
    PlayerTextDrawLetterSize(playerid, lottoPlayerTDs[playerid][1], 0.339560, 1.401666);
    PlayerTextDrawTextSize(playerid, lottoPlayerTDs[playerid][1], 0.000000, 105.270484);
    PlayerTextDrawAlignment(playerid, lottoPlayerTDs[playerid][1], 2);
    PlayerTextDrawColor(playerid, lottoPlayerTDs[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, lottoPlayerTDs[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, lottoPlayerTDs[playerid][1], 8388863);
    PlayerTextDrawSetOutline(playerid, lottoPlayerTDs[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, lottoPlayerTDs[playerid][1], 255);
    PlayerTextDrawFont(playerid, lottoPlayerTDs[playerid][1], 3);
    PlayerTextDrawSetProportional(playerid, lottoPlayerTDs[playerid][1], 1);
    PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][1]);

    lottoPlayerTDs[playerid][2] = CreatePlayerTextDraw(playerid, 196.899795, 234.385391, "ADD TICKET");
    PlayerTextDrawLetterSize(playerid, lottoPlayerTDs[playerid][2], 0.190568, 1.244166);
    PlayerTextDrawTextSize(playerid, lottoPlayerTDs[playerid][2], 10.000000, 47.000000);
    PlayerTextDrawAlignment(playerid, lottoPlayerTDs[playerid][2], 2);
    PlayerTextDrawColor(playerid, lottoPlayerTDs[playerid][2], -1);
    PlayerTextDrawUseBox(playerid, lottoPlayerTDs[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, lottoPlayerTDs[playerid][2], 8388863);
    PlayerTextDrawSetOutline(playerid, lottoPlayerTDs[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, lottoPlayerTDs[playerid][2], 255);
    PlayerTextDrawFont(playerid, lottoPlayerTDs[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, lottoPlayerTDs[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, lottoPlayerTDs[playerid][2], true);
    PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][2]);

    lottoPickNumbersTDs[playerid][35] = CreatePlayerTextDraw(playerid, 234.402084, 234.385391, "EXIT");
    PlayerTextDrawLetterSize(playerid, lottoPickNumbersTDs[playerid][35], 0.190568, 1.244166);
    PlayerTextDrawTextSize(playerid, lottoPickNumbersTDs[playerid][35], 10.000000, 26.000000);
    PlayerTextDrawAlignment(playerid, lottoPickNumbersTDs[playerid][35], 2);
    PlayerTextDrawColor(playerid, lottoPickNumbersTDs[playerid][35], -1);
    PlayerTextDrawUseBox(playerid, lottoPickNumbersTDs[playerid][35], 1);
    PlayerTextDrawBoxColor(playerid, lottoPickNumbersTDs[playerid][35], -16776961);
    PlayerTextDrawSetOutline(playerid, lottoPickNumbersTDs[playerid][35], 1);
    PlayerTextDrawBackgroundColor(playerid, lottoPickNumbersTDs[playerid][35], 255);
    PlayerTextDrawFont(playerid, lottoPickNumbersTDs[playerid][35], 2);
    PlayerTextDrawSetProportional(playerid, lottoPickNumbersTDs[playerid][35], 1);
    PlayerTextDrawSetSelectable(playerid, lottoPickNumbersTDs[playerid][35], true);

    lottoPickNumbersTDs[playerid][36] = CreatePlayerTextDraw(playerid, 157.897415, 234.385391, "PLACE");
    PlayerTextDrawLetterSize(playerid, lottoPickNumbersTDs[playerid][36], 0.190568, 1.244166);
    PlayerTextDrawTextSize(playerid, lottoPickNumbersTDs[playerid][36], 10.000000, 26.000000);
    PlayerTextDrawAlignment(playerid, lottoPickNumbersTDs[playerid][36], 2);
    PlayerTextDrawColor(playerid, lottoPickNumbersTDs[playerid][36], -1);
    PlayerTextDrawUseBox(playerid, lottoPickNumbersTDs[playerid][36], 1);
    PlayerTextDrawBoxColor(playerid, lottoPickNumbersTDs[playerid][36], 8388863);
    PlayerTextDrawSetOutline(playerid, lottoPickNumbersTDs[playerid][36], 1);
    PlayerTextDrawBackgroundColor(playerid, lottoPickNumbersTDs[playerid][36], 255);
    PlayerTextDrawFont(playerid, lottoPickNumbersTDs[playerid][36], 2);
    PlayerTextDrawSetProportional(playerid, lottoPickNumbersTDs[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, lottoPickNumbersTDs[playerid][36], true);

    lottoPickNumbersTDs[playerid][37] = CreatePlayerTextDraw(playerid, 234.402084, 216.384292, "CLEAR");
    PlayerTextDrawLetterSize(playerid, lottoPickNumbersTDs[playerid][37], 0.190568, 1.244166);
    PlayerTextDrawTextSize(playerid, lottoPickNumbersTDs[playerid][37], 10.000000, 26.000000);
    PlayerTextDrawAlignment(playerid, lottoPickNumbersTDs[playerid][37], 2);
    PlayerTextDrawColor(playerid, lottoPickNumbersTDs[playerid][37], -1);
    PlayerTextDrawUseBox(playerid, lottoPickNumbersTDs[playerid][37], 1);
    PlayerTextDrawBoxColor(playerid, lottoPickNumbersTDs[playerid][37], -2147483393);
    PlayerTextDrawSetOutline(playerid, lottoPickNumbersTDs[playerid][37], 1);
    PlayerTextDrawBackgroundColor(playerid, lottoPickNumbersTDs[playerid][37], 255);
    PlayerTextDrawFont(playerid, lottoPickNumbersTDs[playerid][37], 2);
    PlayerTextDrawSetProportional(playerid, lottoPickNumbersTDs[playerid][37], 1);
    PlayerTextDrawSetSelectable(playerid, lottoPickNumbersTDs[playerid][37], true);

    new i;

    for(i = 0; i < sizeof lottoNumbersTDsCoords; ++i) {
        lottoPickNumbersTDs[playerid][i] = CreatePlayerTextDraw(playerid, lottoNumbersTDsCoords[i][lottoNumberPosX], lottoNumbersTDsCoords[i][lottoNumberPosY], lottoNumbersTDsCoords[i][lottoNumberTD]);
        PlayerTextDrawLetterSize(playerid, lottoPickNumbersTDs[playerid][i], 0.315666, 1.331666);
        PlayerTextDrawTextSize(playerid, lottoPickNumbersTDs[playerid][i], 10.0, 10.0);
        PlayerTextDrawAlignment(playerid, lottoPickNumbersTDs[playerid][i], 2);
        PlayerTextDrawColor(playerid, lottoPickNumbersTDs[playerid][i], -1);
        PlayerTextDrawSetOutline(playerid, lottoPickNumbersTDs[playerid][i], 1);
        PlayerTextDrawBackgroundColor(playerid, lottoPickNumbersTDs[playerid][i], 255);
        PlayerTextDrawFont(playerid, lottoPickNumbersTDs[playerid][i], 3);
        PlayerTextDrawSetProportional(playerid, lottoPickNumbersTDs[playerid][i], 1);
        PlayerTextDrawSetSelectable(playerid, lottoPickNumbersTDs[playerid][i], true);
    }

    for(i = 3; i < sizeof lottoPlayerTDs[]; ++i) {
        lottoPlayerTDs[playerid][i] = CreatePlayerTextDraw(playerid, 146.632537, 120.583305 + (39.20182 * (i - 3)), "");
        PlayerTextDrawLetterSize(playerid, lottoPlayerTDs[playerid][i], 0.277714, 1.203331);
        PlayerTextDrawAlignment(playerid, lottoPlayerTDs[playerid][i], 1);
        PlayerTextDrawColor(playerid, lottoPlayerTDs[playerid][i], -1);
        PlayerTextDrawSetOutline(playerid, lottoPlayerTDs[playerid][i], 1);
        PlayerTextDrawBackgroundColor(playerid, lottoPlayerTDs[playerid][i], 255);
        PlayerTextDrawFont(playerid, lottoPlayerTDs[playerid][i], 3);
        PlayerTextDrawSetProportional(playerid, lottoPlayerTDs[playerid][i], 1);
    }

    if(lottoTicketsCount[playerid]) {
        for(i = 0; i < lottoTicketsCount[playerid]; ++i) {
            formatPlayerLottoTicket(playerid, i);

            PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][i + 3]);
        }
    }

    i = 0;

    if(!lottoSecondsLeft) {
        TextDrawShowForPlayer(playerid, lottoGlobalTDs[4]);
        TextDrawShowForPlayer(playerid, lottoGlobalTDs[5]);

        i = 10;
    }

    for(; i < sizeof lottoBallsTDs; ++i) 
        TextDrawShowForPlayer(playerid, lottoBallsTDs[i]);

    for(i = 0; i < sizeof lottoBallsNumbersTDs; ++i) 
        TextDrawShowForPlayer(playerid, lottoBallsNumbersTDs[i]);       

    for(i = 0; i < 4; ++i) 
        TextDrawShowForPlayer(playerid, lottoGlobalTDs[i]);

    return 1;
}

static hidePlayerLotto(const playerid) {
    lottoPlayerIn[playerid] = false;

    Iter_Remove(lottoShown, playerid);

    TogglePlayerControllableEx(playerid, true);

    new i;

    for(; i < sizeof lottoBallsTDs; ++i) {
        TextDrawHideForPlayer(playerid, lottoBallsTDs[i]);
        TextDrawHideForPlayer(playerid, lottoBallsNumbersTDs[i]);
    }

    for(i = 0; i < sizeof lottoPlayerTDs[]; ++i) {
        TextDrawHideForPlayer(playerid, lottoGlobalTDs[i]);

        playerTextDrawDestroy(playerid, lottoPlayerTDs[playerid][i]);
    }

    for(i = 0; i < sizeof lottoPickNumbersTDs[]; ++i)
        playerTextDrawDestroy(playerid, lottoPickNumbersTDs[playerid][i]);

    return 1;   
}

static formatPlayerLottoTicket(const playerid, const ticket) {
    gString[0] = EOS;
    format(gString, sizeof gString, "%d. ", ticket + 1);

    for(new x = 0; x < lottoTickets[playerid][ticket][lottoNumbersCount]; ++x) 
        format(gString, sizeof gString, "%s%d, ", gString, lottoTickets[playerid][ticket][lottoNumber][x]);

    gString[strlen(gString) - 2] = EOS;

    format(gString, sizeof gString, "%s~n~BET: $%s", gString, formatNumber(lottoTickets[playerid][ticket][lottoBet]));

    return PlayerTextDrawSetString(playerid, lottoPlayerTDs[playerid][ticket + 3], gString);
}

static togglePlayerTicketMenu(const playerid, menu) {
    new i;

    if(!menu) {
        for(i = 0; i < sizeof lottoPickNumbersTDs[]; ++i)
            PlayerTextDrawHide(playerid, lottoPickNumbersTDs[playerid][i]);

        PlayerTextDrawSetString(playerid, lottoPlayerTDs[playerid][1], "YOUR TICKETS");

        PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][2]);

        if(lottoTicketsCount[playerid]) {
            for(i = 0; i < lottoTicketsCount[playerid]; ++i) 
                PlayerTextDrawShow(playerid, lottoPlayerTDs[playerid][i + 3]);
        }
    }
    else {
        PlayerTextDrawHide(playerid, lottoPlayerTDs[playerid][2]);

        if(lottoTicketsCount[playerid]) {
            for(i = 0; i < lottoTicketsCount[playerid]; ++i) 
                PlayerTextDrawHide(playerid, lottoPlayerTDs[playerid][i + 3]);
        }

        lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount] = 0;

        PlayerTextDrawSetString(playerid, lottoPlayerTDs[playerid][1], "ADD TICKET");

        PlayerTextDrawShow(playerid, lottoPickNumbersTDs[playerid][35]);
        PlayerTextDrawShow(playerid, lottoPickNumbersTDs[playerid][36]);
        PlayerTextDrawShow(playerid, lottoPickNumbersTDs[playerid][37]);

        for(i = 0; i < sizeof lottoNumbersTDsCoords; ++i) {
            PlayerTextDrawColor(playerid, lottoPickNumbersTDs[playerid][i], 0xFFFFFFFF);
            PlayerTextDrawSetSelectable(playerid, lottoPickNumbersTDs[playerid][i], true);
            PlayerTextDrawShow(playerid, lottoPickNumbersTDs[playerid][i]);
        }
    }

    lottoPlayerToggle[playerid] = menu;
    return 1;
}

static bool:isPlayerWinningTicket(const playerid, const ticket) {
    for(new i = 0; i < lottoTickets[playerid][ticket][lottoNumbersCount]; ++i) {
        if(!SortArray_CountOccurences(lottoNumbers, lottoTickets[playerid][ticket][lottoNumber][i])) 
            return false;
    }
    return true;    
}

static checkLottoPlayersTickets() {
    if(!Iter_Count(lottoPlayers))
        return 1;

    foreach(new playerid : lottoPlayers) {
        for(new i = 0; i < lottoTicketsCount[playerid]; ++i) {
            if(isPlayerWinningTicket(playerid, i)) {
                new const prize = floatround(floatmul(float(lottoTickets[playerid][i][lottoBet]), lottoBetMultiplier[lottoTickets[playerid][i][lottoNumbersCount] - 1]));

                addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, prize);

                SCMf(playerid, COLOR_GREEN, "(Lotto): {ffffff}Congratulations! You won $%s money because ticket #%d numbers were picked.", formatNumber(prize), i + 1);
            }

            lottoTickets[playerid][i][lottoNumbersCount] = 0;

            if(isPlayerInLotto(playerid))
                PlayerTextDrawHide(playerid, lottoPlayerTDs[playerid][i + 3]);
        }

        lottoTicketsCount[playerid] = 0;
    }

    Iter_Clear(lottoPlayers);
    return 1;
}

isPlayerInLotto(const playerid)  
    return lottoPlayerIn[playerid];

// ------------------------------------- //
//             Timers                    //
// ------------------------------------- //

timer lottoRoundWaitTimer[1000]() {
    if(--lottoSecondsLeft) {
        gString[0] = EOS;
        format(gString, sizeof gString, "NEXT ROUND IN: %s", CalculateTime(lottoSecondsLeft));
        TextDrawSetString(lottoGlobalTDs[2], gString);

        gString[0] = EOS;
        format(gString, sizeof gString, "Lotto 5/35\n{FFFFFF}Next round in: {1C8A15}%s\n\n{FFFFFF}Write {1C8A15}[/lotto]{FFFFFF} to play.", CalculateTime(lottoSecondsLeft));
        UpdateDynamic3DTextLabelText(lottoLabel, COLOR_GREEN, gString); 
        return 1;
    }

    UpdateDynamic3DTextLabelText(lottoLabel, COLOR_GREEN, "Lotto 5/35\n{FFFFFF}Picking numbers...\n\nWrite {1C8A15}[/lotto]{FFFFFF} to play.");

    TextDrawSetString(lottoGlobalTDs[2], "NUMBERS PICKED: 0/5");
    TextDrawSetString(lottoGlobalTDs[3], "PICKING NUMBERS...");
    TextDrawSetString(lottoGlobalTDs[5], "");

    foreach(new i : lottoShown) {
        if(Dialog_IsOpened(i))
            Dialog_Close(i);

        for(new x = 0; x < 10; ++x) 
            TextDrawHideForPlayer(i, lottoBallsTDs[x]);

        TextDrawShowForPlayer(i, lottoGlobalTDs[4]);
        TextDrawShowForPlayer(i, lottoGlobalTDs[5]);

        if(lottoPlayerToggle[i]) 
            togglePlayerTicketMenu(i, 0);
    }

    for(new x = 0; x < sizeof lottoBallsNumbersTDs; ++x) 
        TextDrawSetString(lottoBallsNumbersTDs[x], "");

    stop lottoTimer;
    lottoTimer = repeat lottoPickNumbersTimer();
    return 1;
}

timer lottoPickNumbersTimer[3000]() {
    if(lottoPickedNumbersCount != LOTTO_NUMBERS_LIMIT) {
        lottoRoundsNumbers[2][lottoPickedNumbersCount] = 1 + random(35);

        while(SortArray_CountOccurences(lottoNumbers, lottoRoundsNumbers[2][lottoPickedNumbersCount])) 
            lottoRoundsNumbers[2][lottoPickedNumbersCount] = 1 + random(35);

        SortArray_Insert(lottoNumbers, lottoRoundsNumbers[2][lottoPickedNumbersCount]);

        valstr(gString, lottoRoundsNumbers[2][lottoPickedNumbersCount]);

        TextDrawSetString(lottoGlobalTDs[5], gString);
        TextDrawSetString(lottoBallsNumbersTDs[10 + lottoPickedNumbersCount], gString);

        lottoPickedNumbersCount ++;

        gString[0] = EOS;
        format(gString, sizeof gString, "NUMBERS PICKED: %d/5", lottoPickedNumbersCount);
        TextDrawSetString(lottoGlobalTDs[2], gString);
    }
    else {
        checkLottoPlayersTickets();

        foreach(new i : lottoShown) {
            TextDrawHideForPlayer(i, lottoGlobalTDs[4]);
            TextDrawHideForPlayer(i, lottoGlobalTDs[5]);

            for(new x = 0; x < 10; ++x) 
                TextDrawShowForPlayer(i, lottoBallsTDs[x]);
        }

        UpdateDynamic3DTextLabelText(lottoLabel, COLOR_GREEN, "Lotto 5/35\n{FFFFFF}Next round in: {1C8A15}05:00\n\n{FFFFFF}Write {1C8A15}[/lotto]{FFFFFF} to play.");

        TextDrawSetString(lottoGlobalTDs[2], "NEXT ROUND IN: 05:00");
        TextDrawSetString(lottoGlobalTDs[3], "NUMBERS PICKED LAST 3 ROUNDS:");

        for(new i = 0; i < 5; ++i) {
            valstr(gString, lottoRoundsNumbers[0][i]);
            TextDrawSetString(lottoBallsNumbersTDs[i], gString);

            valstr(gString, lottoRoundsNumbers[1][i]);
            TextDrawSetString(lottoBallsNumbersTDs[i + 5], gString);
        }

        lottoRoundsNumbers[0] = lottoRoundsNumbers[1];
        lottoRoundsNumbers[1] = lottoRoundsNumbers[2];

        stop lottoTimer;
        lottoTimer = repeat lottoRoundWaitTimer();

        lottoSecondsLeft = LOTTO_ROUND_WAIT_TIME;

        lottoPickedNumbersCount = 0;

        SortArray_Clear(lottoNumbers);
    }
    return 1;   
}

// ------------------------------------- //
//             Commands                  //
// ------------------------------------- //

YCMD:lotto(playerid, params[], help) {
    if(isPlayerInLotto(playerid) || isPlayerDead(playerid))
        return 1;

    if(playerVars[playerid][var_inbizz] == -1 || bizzInfo[playerVars[playerid][var_inbizz]][bType] != 15)
        return sendError(playerid, "Nu esti intr-o casa de pariuri.");

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, 822.0404, 1.9177, 1004.1797)) 
        return 1;
    
    if(playerInfo[playerid][pLevel] < 3)
        return sendError(playerid, "Ai nevoie de minim level 3.");

    showPlayerLotto(playerid);
    return 1;
}

YCMD:debugtime(playerid, params[], help)
    return lottoSecondsLeft = strval(params);

// ------------------------------------- //
//             Dialogs                   //
// ------------------------------------- //

Dialog:PLACETICKET(playerid, response, listitem, inputtext[]) {
    if(!response || !isPlayerInLotto(playerid)) 
        return 1;
    
    new price; if(sscanf(inputtext, "d", price) || price < 500000 || price > 5000000)
        return Dialog_Show(playerid, PLACETICKET, DIALOG_STYLE_INPUT, "SERVER: Ticket Price", "Enter the price you want to bet:\n\nWinnings:\n1 - 1.5X\n2 - 1.75X\n3 - 2X\n4 - 5X\n5 - 10X\n\n{FF0000}Invalid amount! (min. $500.000, max. $5.000.000)", "Place", "Cancel");

    if(GetMoney(playerid) < price && GetMilliards(playerid) < 1)
        return Dialog_Show(playerid, PLACETICKET, DIALOG_STYLE_INPUT, "SERVER: Ticket Price", "Enter the price you want to bet:\n\nWinnings:\n1 - 1.5X\n2 - 1.75X\n3 - 2X\n4 - 5X\n5 - 10X\n\n{FF0000}Invalid amount!", "Place", "Cancel");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price);

    lottoTickets[playerid][lottoTicketsCount[playerid]][lottoBet] = price;

    gString[0] = EOS;

    for(new i = 0; i < lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount]; ++i) 
        format(gString, sizeof gString, "%s%d, ", gString, lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumber][i]);

    gString[strlen(gString) - 2] = EOS;

    SCMf(playerid, COLOR_GREEN, "(Lotto): {ffffff}Ticket #%d (bet: $%s, numbers: %s) has been placed successfully.", lottoTicketsCount[playerid] + 1, formatNumber(price), gString);

    formatPlayerLottoTicket(playerid, lottoTicketsCount[playerid]);

    if(++lottoTicketsCount[playerid] == 1) 
        Iter_Add(lottoPlayers, playerid);

    return togglePlayerTicketMenu(playerid, 0);
}

// ------------------------------------- //
//             Hooks                     //
// ------------------------------------- //

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    if(isPlayerInLotto(playerid) && !Dialog_IsOpened(playerid)) {
        if(playertextid == lottoPlayerTDs[playerid][2]) {
            if(!lottoSecondsLeft) 
                return sendError(playerid, "Nu poti plasa bilete in acest moment.");

            if(lottoTicketsCount[playerid] == 3)
                return sendError(playerid, "Poti plasa maxim 3 bilete.");

            togglePlayerTicketMenu(playerid, 1);
        }
        else if(playertextid >= lottoPickNumbersTDs[playerid][0] && playertextid <= lottoPickNumbersTDs[playerid][34]) {
            if(lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount] == LOTTO_NUMBERS_LIMIT)
                return sendError(playerid, "Poti adauga maxim "#LOTTO_NUMBERS_LIMIT" numere pe bilet.");

            new const selected_number = _:playertextid - _:lottoPickNumbersTDs[playerid][0];

            lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumber][lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount]++] = selected_number + 1;

            PlayerTextDrawColor(playerid, playertextid, 8388863);
            PlayerTextDrawSetSelectable(playerid, playertextid, false);
            PlayerTextDrawShow(playerid, playertextid);
        }
        else if(playertextid == lottoPickNumbersTDs[playerid][35]) {
            togglePlayerTicketMenu(playerid, 0);
        }
        else if(playertextid == lottoPickNumbersTDs[playerid][36]) {
            if(!lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount])
                return sendError(playerid, "Trebuie sa ai minim 1 numar plasat pe bilet.");

            Dialog_Show(playerid, PLACETICKET, DIALOG_STYLE_INPUT, "SERVER: Ticket Price", "Enter the price you want to bet:\n\nWinnings:\n1 - 1.5X\n2 - 1.75X\n3 - 2X\n4 - 5X\n5 - 10X", "Place", "Cancel");
        }
        else if(playertextid == lottoPickNumbersTDs[playerid][37]) {
            if(!lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount])
                return 1;

            for(new i = 0, PlayerText:id; i < lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount]; ++i) {
                id = lottoPickNumbersTDs[playerid][0] + PlayerText:lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumber][i] - PlayerText:1; 

                PlayerTextDrawColor(playerid, id, 0xFFFFFFFF);
                PlayerTextDrawSetSelectable(playerid, id, true);
                PlayerTextDrawShow(playerid, id);
            }

            lottoTickets[playerid][lottoTicketsCount[playerid]][lottoNumbersCount] = 0;
        }
    }
    return 1;
}

hook OP_ClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == INVALID_TEXT_DRAW && isPlayerInLotto(playerid))
        hidePlayerLotto(playerid);

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(Iter_Remove(lottoPlayers, playerid) != INVALID_ITERATOR_SLOT)
        lottoTicketsCount[playerid] = 0;

    if(Iter_Remove(lottoShown, playerid) != INVALID_ITERATOR_SLOT) {
        lottoPlayerIn[playerid] = false;

        memset(_:lottoPlayerTDs[playerid], -1);
        memset(_:lottoPickNumbersTDs[playerid], -1);
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if(isPlayerInLotto(playerid)) {
        hidePlayerLotto(playerid);
        CancelSelectTextDraw(playerid);
    }

    return 1;
}

hook OnGameModeInit() {
    lottoLabel = CreateDynamic3DTextLabel("Lotto 5/35\n{FFFFFF}Next round in: {1C8A15}05:00\n\n{FFFFFF}Write {1C8A15}[/lotto]{FFFFFF} to play.", COLOR_GREEN, 822.0404, 1.9177, 1004.1797, 20.0, .interiorid = 3);

    lottoTimer = repeat lottoRoundWaitTimer();

    lottoGlobalTDs[0] = TextDrawCreate(254.099349, 111.650070, "box");
    TextDrawLetterSize(lottoGlobalTDs[0], 0.000000, 22.368959);
    TextDrawTextSize(lottoGlobalTDs[0], 565.840576, 0.000000);
    TextDrawAlignment(lottoGlobalTDs[0], 1);
    TextDrawColor(lottoGlobalTDs[0], -1);
    TextDrawUseBox(lottoGlobalTDs[0], 1);
    TextDrawBoxColor(lottoGlobalTDs[0], 159);
    TextDrawBackgroundColor(lottoGlobalTDs[0], 255);
    TextDrawFont(lottoGlobalTDs[0], 1);
    TextDrawSetProportional(lottoGlobalTDs[0], 1);

    lottoGlobalTDs[1] = TextDrawCreate(409.810302, 94.333267, "LOTTO 5/35");
    TextDrawLetterSize(lottoGlobalTDs[1], 0.339560, 1.401666);
    TextDrawTextSize(lottoGlobalTDs[1], 0.000000, 311.670654);
    TextDrawAlignment(lottoGlobalTDs[1], 2);
    TextDrawColor(lottoGlobalTDs[1], -1);
    TextDrawUseBox(lottoGlobalTDs[1], 1);
    TextDrawBoxColor(lottoGlobalTDs[1], 8388863);
    TextDrawSetOutline(lottoGlobalTDs[1], 1);
    TextDrawBackgroundColor(lottoGlobalTDs[1], 255);
    TextDrawFont(lottoGlobalTDs[1], 3);
    TextDrawSetProportional(lottoGlobalTDs[1], 1);

    lottoGlobalTDs[2] = TextDrawCreate(412.028381, 301.416656, "NEXT ROUND IN: 05:00");
    TextDrawLetterSize(lottoGlobalTDs[2], 0.190568, 1.244166);
    TextDrawAlignment(lottoGlobalTDs[2], 2);
    TextDrawColor(lottoGlobalTDs[2], -1);
    TextDrawSetOutline(lottoGlobalTDs[2], 1);
    TextDrawBackgroundColor(lottoGlobalTDs[2], 255);
    TextDrawFont(lottoGlobalTDs[2], 2);
    TextDrawSetProportional(lottoGlobalTDs[2], 1);

    lottoGlobalTDs[3] = TextDrawCreate(409.728118, 116.500015, "NUMBERS PICKED LAST 3 ROUNDS:");
    TextDrawLetterSize(lottoGlobalTDs[3], 0.190568, 1.244166);
    TextDrawAlignment(lottoGlobalTDs[3], 2);
    TextDrawColor(lottoGlobalTDs[3], -1);
    TextDrawSetOutline(lottoGlobalTDs[3], 1);
    TextDrawBackgroundColor(lottoGlobalTDs[3], 255);
    TextDrawFont(lottoGlobalTDs[3], 2);
    TextDrawSetProportional(lottoGlobalTDs[3], 1);

    lottoGlobalTDs[4] = TextDrawCreate(375.713806, 164.938796, "ld_pool:ball");
    TextDrawLetterSize(lottoGlobalTDs[4], 0.000000, 0.000000);
    TextDrawTextSize(lottoGlobalTDs[4], 62.000000, 66.000000);
    TextDrawAlignment(lottoGlobalTDs[4], 1);
    TextDrawColor(lottoGlobalTDs[4], 8388863);
    TextDrawBackgroundColor(lottoGlobalTDs[4], 255);
    TextDrawFont(lottoGlobalTDs[4], 4);

    lottoGlobalTDs[5] = TextDrawCreate(408.255401, 184.372894, "");
    TextDrawLetterSize(lottoGlobalTDs[5], 0.637539, 2.696667);
    TextDrawAlignment(lottoGlobalTDs[5], 2);
    TextDrawColor(lottoGlobalTDs[5], -1);
    TextDrawSetOutline(lottoGlobalTDs[5], 1);
    TextDrawBackgroundColor(lottoGlobalTDs[5], 255);
    TextDrawFont(lottoGlobalTDs[5], 3);
    TextDrawSetProportional(lottoGlobalTDs[5], 1);

    // Creating Balls and Numbers

    for(new i = 0, Float:y; i < sizeof lottoBallsTDs; ++i) {
        y = i < 5 ? 143.916748 : i < 10 ? 194.319824 : 244.722900;

        lottoBallsTDs[i] = TextDrawCreate(309.565734 + (40.502472 * (i % 5)), y, "ld_pool:ball");
        TextDrawLetterSize(lottoBallsTDs[i], 0.000000, 0.000000);
        TextDrawTextSize(lottoBallsTDs[i], 31.180004, 32.000000);
        TextDrawAlignment(lottoBallsTDs[i], 1);
        TextDrawColor(lottoBallsTDs[i], 8388863);
        TextDrawBackgroundColor(lottoBallsTDs[i], 255);
        TextDrawFont(lottoBallsTDs[i], 4);

        lottoBallsNumbersTDs[i] = TextDrawCreate(325.706207 + (40.502472 * (i % 5)), y + 7.699981, "");
        TextDrawLetterSize(lottoBallsNumbersTDs[i], 0.400000, 1.600000);
        TextDrawAlignment(lottoBallsNumbersTDs[i], 2);
        TextDrawColor(lottoBallsNumbersTDs[i], -1);
        TextDrawSetOutline(lottoBallsNumbersTDs[i], 1);
        TextDrawBackgroundColor(lottoBallsNumbersTDs[i], 255);
        TextDrawFont(lottoBallsNumbersTDs[i], 3);
        TextDrawSetProportional(lottoBallsNumbersTDs[i], 1);
    }
    return 1;
}