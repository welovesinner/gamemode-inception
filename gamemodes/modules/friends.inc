// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_FRIENDS 15

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

static 
    friendsSQLIDs[MAX_PLAYERS][MAX_FRIENDS], 
    friendsSelect[MAX_PLAYERS][MAX_FRIENDS],
    friendsNames[MAX_PLAYERS][MAX_FRIENDS][MAX_PLAYER_NAME],
    Iterator:friends[MAX_PLAYERS]<MAX_FRIENDS>;

// ------------------------------------- //
//            Load Function              //
// ------------------------------------- //

query_function loadPlayerFriends(const playerid, const dbid) {
    if(dbid != playerInfo[playerid][pSQLID])
        return 1;

    new const rows = cache_num_rows();

    if(!rows)
        return 1;

    new onlinefriends;

    for(new i = 0; i < rows; ++i) {
        cache_get_field_content(i, "FriendName", friendsNames[playerid][i], SQL, MAX_PLAYER_NAME);

        friendsSQLIDs[playerid][i] = cache_get_field_content_int(i, "FriendSQLID");

        if(MAP_contains_val(playersSQLID, friendsSQLIDs[playerid][i]))
            ++onlinefriends;                

        Iter_Add(friends[playerid], i);
    }

    gString[0] = EOS;
    format(gString, sizeof gString, "Ai ~Y~%d ~W~~H~/ ~Y~%d ~W~~H~prieteni conectati pe server.", onlinefriends, rows);

    playerTextdraws[playerid][FriendsTD] = CreatePlayerTextDraw(playerid, 74.800018, 296.688873, gString);
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][FriendsTD], 0.206000, 0.959110);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][FriendsTD], 0.000000, 111.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][FriendsTD], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][FriendsTD], -1);
    PlayerTextDrawUseBox(playerid, playerTextdraws[playerid][FriendsTD], 1);
    PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][FriendsTD], 255);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][FriendsTD], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][FriendsTD], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][FriendsTD], 1);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][FriendsTD], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][FriendsTD], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][FriendsTD]);

    defer friendsTextdrawDestroy(playerid);
    return 1;
}

query_function checkIfHaveThatFriend(const playerid, const userid) {
    if(!IsPlayerConnected(playerid))
        return 1;

    if(cache_num_rows())
        return sendError(playerid, "Il ai deja adaugat pe %s in lista ta de prieteni.", GetName(userid));

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_friends` (PlayerSQLID, FriendSQLID, FriendName) VALUES (%d, %d, '%e')", playerInfo[playerid][pSQLID], playerInfo[userid][pSQLID], GetName(userid));
    mysql_tquery(SQL, gQuery, "", "");

    new const id = Iter_Free(friends[playerid]);

    Iter_Add(friends[playerid], id);

    strcpy(friendsNames[playerid][id], GetName(userid));
    friendsSQLIDs[playerid][id] = playerInfo[userid][pSQLID];

    SCMf(playerid, COLOR_GREEN, "(Friends): {FFFFFF}L-ai adaugat cu succes pe %s (%d) in lista ta de prieteni.", GetName(userid), userid);
    SCMf(userid, COLOR_GREEN, "(Friends): {FFFFFF}%s (%d) te-a adaugat in lista lui de prieteni.", GetName(playerid), playerid);
    return 1;
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:friends(playerid, params[], help) {
    if(!Iter_Count(friends[playerid]))
        return sendError(playerid, "Nu ai prieteni adaugati in lista ta.");

    new idx;

    gDialog = "Friend Name\tStatus\n";

    foreach(new i : friends[playerid]) {
        format(gDialog, sizeof gDialog, "%s%s\t%s\n", gDialog, friendsNames[playerid][i], MAP_contains_val(playersSQLID, friendsSQLIDs[playerid][i]) ? "{1fad1f}online" : "{990000}offline");
        
        friendsSelect[playerid][idx++] = i;
    }

    return Dialog_Show(playerid, FRIENDSCHOOSE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Friends", gDialog, "Select", "Exit");
}

YCMD:addfriend(playerid, params[], help) {
    if(Iter_Count(friends[playerid]) >= MAX_FRIENDS)
        return sendError(playerid, "Poti avea maxim %d prieteni in lista.", MAX_FRIENDS);

    if(playerVars[playerid][var_addfriend_delay] > gettime())
        return sendError(playerid, "Trebuie sa astepti %d secunde pana a folosi iar aceasta comanda.", playerVars[playerid][var_addfriend_delay] - gettime());

    new userID; if(sscanf(params, "u", userID))
        return sendUsage(playerid, "/addfriend <playerid/name>");

    if(userID == playerid)
        return sendError(playerid, "Nu poti face acest lucru asupra ta.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este logat.");

    playerVars[playerid][var_addfriend_delay] = gettime() + 30;

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT (ID) FROM `server_friends` WHERE `PlayerSQLID` = %d AND `FriendSQLID` = %d LIMIT 1", playerInfo[playerid][pSQLID], playerInfo[userID][pSQLID]); 
    mysql_tquery(SQL, gQuery, "checkIfHaveThatFriend", "dd", playerid, userID);
    return 1;
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:FRIENDSCHOOSE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    SetPVarInt(playerid, "choosedListitem", listitem);

    if(MAP_contains_val(playersSQLID, friendsSQLIDs[playerid][friendsSelect[playerid][listitem]])) 
        return Dialog_Show(playerid, FRIENDSMANAGEONLINE, DIALOG_STYLE_LIST, "SERVER: Manage Friend", "Get Friend Number\nCall Friend\nRemove Friend", "Select", "Exit");

    return Dialog_Show(playerid, FRIENDSMANAGEOFFLINE, DIALOG_STYLE_LIST, "SERVER: Manage Friend", "Remove Friend", "Select", "Exit");
}

Dialog:FRIENDSMANAGEONLINE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new 
        pvar = GetPVarInt(playerid, "choosedListitem"), 
        userID = MAP_get_val_val(playersSQLID, friendsSQLIDs[playerid][friendsSelect[playerid][pvar]]);

    DeletePVar(playerid, "choosedListitem");

    switch(listitem) {
        case 0: {
            if(!playerInfo[userID][pPhoneNumber])
                return sendError(playerid, "Acel player nu are un numar de telefon.");

            SCMf(playerid, COLOR_GREEN, "(Friends): {FFFFFF}Prietenul tau %s, are numarul de telefon: %d", friendsNames[playerid][friendsSelect[playerid][pvar]], playerInfo[userID][pPhoneNumber]);
        }
        case 1: {
            if(!playerInfo[userID][pPhoneNumber])
                return sendError(playerid, "Acel player nu are un numar de telefon.");

            Command_ReProcess(playerid, va_return("/call %d", playerInfo[userID][pPhoneNumber]), false);
        }
        case 2: {
            Iter_Remove(friends[playerid], friendsSelect[playerid][friendsSelect[playerid][pvar]]);

            va_mysql_tquery("DELETE FROM `server_friends` WHERE `PlayerSQLID` = %d AND `FriendSQLID` = %d", playerInfo[playerid][pSQLID], friendsSQLIDs[playerid][friendsSelect[playerid][pvar]]); 

            SCMf(playerid, COLOR_GREEN, "(Friends): {FFFFFF}L-ai sters pe %s din lista ta de prieteni.", friendsNames[playerid][friendsSelect[playerid][pvar]]); 
            SCMf(userID, COLOR_GREEN, "(Friends): {FFFFFF}%s (%d) te-a sters din lista lui de prieteni.", GetName(playerid), playerid);
        }
    }
    return 1;
}

Dialog:FRIENDSMANAGEOFFLINE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new 
        pvar = GetPVarInt(playerid, "choosedListitem");

    DeletePVar(playerid, "choosedListitem");

    Iter_Remove(friends[playerid], friendsSelect[playerid][friendsSelect[playerid][pvar]]);

    va_mysql_tquery("DELETE FROM `server_friends` WHERE `PlayerSQLID` = %d AND `FriendSQLID` = %d", playerInfo[playerid][pSQLID], friendsSQLIDs[playerid][friendsSelect[playerid][pvar]]); 

    return SCMf(playerid, COLOR_GREEN, "(Friends): {FFFFFF}L-ai sters pe %s din lista ta de prieteni.", friendsNames[playerid][friendsSelect[playerid][pvar]]);
}

// ------------------------------------- //
//              Hooks                    //
// ------------------------------------- //

hook OnPlayerDisconnect(playerid, reason) {
    Iter_Clear(friends[playerid]);
    return 1;
}

// ------------------------------------- //
//              Destroy Textdraw Timer   //
// ------------------------------------- //

timer friendsTextdrawDestroy[5000](const playerid) 
    return playerTextDrawDestroy(playerid, playerTextdraws[playerid][FriendsTD]);