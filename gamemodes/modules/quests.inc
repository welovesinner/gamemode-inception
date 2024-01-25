// ------------------------------------- //
//      Quest Types Enumeration          //
// ------------------------------------- //

enum {
    QUEST_TYPE_DICE,
    QUEST_TYPE_BUYPHOTOCAMERA,
    QUEST_TYPE_BUYPARACHUTE,
    QUEST_TYPE_BUYBARDRINK,
    QUEST_TYPE_BUYCLOTHES,
    QUEST_TYPE_REPAIRPNS,
    QUEST_TYPE_REPAIRKIT,
    QUEST_TYPE_FUELVEHICLE,
    QUEST_TYPE_BUYFLOWERS,
    QUEST_TYPE_FINDPLAYER,
    QUEST_TYPE_WITHDRAWATM,
    QUEST_TYPE_PLACEADCNN,
    QUEST_TYPE_LEARNFIGHTGYM,
    QUEST_TYPE_BANKDEPOSIT,
    QUEST_TYPE_PAYPLAYER,
    QUEST_TYPE_BUYLEVEL,
    QUEST_TYPE_PLAYTIME,
    QUEST_TYPE_BUYWEAPON,
    QUEST_TYPE_RENTCAR,
    QUEST_TYPE_EAT,
    QUEST_TYPE_BUYVENDINGDRINK
}

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_QUESTS 3
#define QUESTS_COUNT 21

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

returnQuestName(const type) {
    new questName[64];

    switch(type) {
        case QUEST_TYPE_DICE: questName = "Go to a casino and win 5 dice hands.";
        case QUEST_TYPE_BUYPHOTOCAMERA: questName = "Go to a 24/7 and buy a photo camera."; 
        case QUEST_TYPE_BUYPARACHUTE: questName = "Go to chilliad mountain and get a parachute.";
        case QUEST_TYPE_BUYBARDRINK: questName = "Go to a bar and buy a drink.";
        case QUEST_TYPE_BUYCLOTHES: questName = "Go to a clothing store and buy a skin.";
        case QUEST_TYPE_REPAIRPNS: questName = "Go to a Pay & Spray and repair your vehicle.";
        case QUEST_TYPE_REPAIRKIT: questName = "Repair someone's vehicle with a repair kit."; 
        case QUEST_TYPE_FUELVEHICLE: questName = "Go to a gas station and fuel up your vehicle.";
        case QUEST_TYPE_BUYFLOWERS: questName = "Go to a sex shop and buy flowers.";
        case QUEST_TYPE_FINDPLAYER: questName = "Find a player by using command [/find].";
        case QUEST_TYPE_WITHDRAWATM: questName = "Go to an ATM and withdraw at least $1.000 money.";
        case QUEST_TYPE_PLACEADCNN: questName = "Go to an CNN and place an advert.";
        case QUEST_TYPE_LEARNFIGHTGYM: questName = "Go to a GYM and learn a new fighting style.";
        case QUEST_TYPE_BANKDEPOSIT: questName = "Go to a bank and deposit at least $50.000 money.";
        case QUEST_TYPE_PAYPLAYER: questName = "Give money to a player using command [/pay]."; 
        case QUEST_TYPE_BUYLEVEL: questName = "Upgrade your level by using command [/buylevel].";
        case QUEST_TYPE_PLAYTIME: questName = "Play 30 minutes in one payday.";
        case QUEST_TYPE_BUYWEAPON: questName = "Go to a gun shop and buy a weapon."; 
        case QUEST_TYPE_RENTCAR: questName = "Go to a rent car and rent a car."; 
        case QUEST_TYPE_EAT: questName = "Go to a food shop and eat some food.";
        case QUEST_TYPE_BUYVENDINGDRINK: questName = "Go to a vending machine and buy a drink.";
    }
    return questName;
}

returnQuestProgress(const type) {
    switch(type) {
        case QUEST_TYPE_DICE: return 5;
        default: return 1;
    }
    return 0;
}

loadPlayerQuests(const playerid) {
    gQuery[0] = EOS; 
    cache_get_field_content(0, "Quests", gQuery, SQL, sizeof gQuery); 
    
    sscanf(gQuery, "p<|>dddddd", playerInfo[playerid][pQuestType][0], playerInfo[playerid][pQuestType][1], playerInfo[playerid][pQuestType][2], playerInfo[playerid][pQuestProgress][0], playerInfo[playerid][pQuestProgress][1], playerInfo[playerid][pQuestProgress][2]);

    if(playerInfo[playerid][pLevel] < 5)
        return 1;

    if(playerInfo[playerid][pDayQuest] != getdate()) {
        givePlayerRandomQuests(playerid); 
        va_mysql_tquery("UPDATE `server_users` SET `DayQuest` = %d, `Quests` = '%d|%d|%d|%d|%d|%d' WHERE `ID` = %d", getdate(), playerInfo[playerid][pQuestType][0], playerInfo[playerid][pQuestType][1], playerInfo[playerid][pQuestType][2], playerInfo[playerid][pQuestProgress][0], playerInfo[playerid][pQuestProgress][1], playerInfo[playerid][pQuestProgress][2], playerInfo[playerid][pSQLID]);
    }
    return showPlayerQuests(playerid);
}

givePlayerRandomQuests(const playerid) {
    const dividedCount = QUESTS_COUNT / 3;

    playerInfo[playerid][pQuestType][0] = random(dividedCount);
    playerInfo[playerid][pQuestType][1] = dividedCount + random(dividedCount);
    playerInfo[playerid][pQuestType][2] = dividedCount * 2 + random(dividedCount);

    return playerInfo[playerid][pQuestProgress][0] = playerInfo[playerid][pQuestProgress][1] = playerInfo[playerid][pQuestProgress][2] = 0;
}

showPlayerQuests(const playerid) {
    for(new i = 0; i < MAX_QUESTS; ++i) 
        SCMf(playerid, 0xf59842ff, "(Quest #%d): {ffffff}%s (progress: %d/%d, status: %s)", i + 1, returnQuestName(playerInfo[playerid][pQuestType][i]), playerInfo[playerid][pQuestProgress][i], returnQuestProgress(playerInfo[playerid][pQuestType][i]), playerInfo[playerid][pQuestProgress][i] >= returnQuestProgress(playerInfo[playerid][pQuestType][i]) ? "finished" : "unfinished");

    return 1;
}

updatePlayerQuestProgress(const playerid, const type) {
    if(playerInfo[playerid][pLevel] < 5)
        return 1;

    new const row = playerInfo[playerid][pQuestType][0] == type ? 0 : playerInfo[playerid][pQuestType][1] == type ? 1 : playerInfo[playerid][pQuestType][2] == type ? 2 : -1; 

    if(row == -1 || playerInfo[playerid][pQuestProgress][row] >= returnQuestProgress(playerInfo[playerid][pQuestType][row]))
        return 1;

    ++playerInfo[playerid][pQuestProgress][row]; 

    SCMf(playerid, 0xf59842ff, "(Quest #%d): {ffffff}%s (progress: %d/%d, status: %s)", row + 1, returnQuestName(playerInfo[playerid][pQuestType][row]), playerInfo[playerid][pQuestProgress][row], returnQuestProgress(playerInfo[playerid][pQuestType][row]), playerInfo[playerid][pQuestProgress][row] >= returnQuestProgress(playerInfo[playerid][pQuestType][row]) ? "finished" : "unfinished");
    
    if(playerInfo[playerid][pQuestProgress][row] >= returnQuestProgress(playerInfo[playerid][pQuestType][row])) {
        new 
            rp = 1 + random(2), money = 2000 + random(8000);

        addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, money, false); 
        playerInfo[playerid][pRespectPoints] += rp;
        
        SCMf(playerid, 0xf59842ff, "(Quest): {ffffff}You received $%s and %d respect points because you finished this quest.", formatNumber(money), rp);
    }
    return va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `RespectPoints` = %d, `Quests` = '%d|%d|%d|%d|%d|%d' WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pRespectPoints], playerInfo[playerid][pQuestType][0], playerInfo[playerid][pQuestType][1], playerInfo[playerid][pQuestType][2], playerInfo[playerid][pQuestProgress][0], playerInfo[playerid][pQuestProgress][1], playerInfo[playerid][pQuestProgress][2], playerInfo[playerid][pSQLID]);
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:quests(playerid, params[], help) {
    if(playerInfo[playerid][pLevel] < 5)
        return sendError(playerid, "Ai nevoie de minim level 5 pentru a debloca misiunile zilnice.");

    return showPlayerQuests(playerid);
}