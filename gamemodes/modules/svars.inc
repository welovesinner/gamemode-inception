// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_SVARS 12

// ------------------------------------- //
//              Variables                //
// ------------------------------------- //

enum e_serverVars {
    svar_ID, svar_Name[32], svar_Value
}

new serverVars[MAX_SVARS][e_serverVars];

// ------------------------------------- //
//              Load Query Function      //
// ------------------------------------- //

query_function load_server_vars() {
    if(!cache_num_rows())
        return printf("[MYSQL INFO] No server variables were found in the database.");

    for(new x = 1; x <= cache_num_rows(); x++) {
        serverVars[x][svar_ID] = cache_get_field_content_int(x-1, "varID");
        serverVars[x][svar_Value] = cache_get_field_content_int(x-1, "varValue");

        cache_get_field_content(x-1, "varName", serverVars[x][svar_Name], SQL, 32); 
    }
    serverStuff[sVars] = cache_num_rows();
    return printf("[MYSQL LOADED] Server variables loaded: %d", serverStuff[sVars]);
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:svars(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 8)
        return 1;

    if(!serverStuff[sVars])
        return sendError(playerid, "Nu au fost gasite variabile pentru server.");

    gDialog[0] = EOS;

    gDialog = "SVar - DBID\tName\tValue\n";

    for(new i = 1; i <= serverStuff[sVars]; i++) 
        format(gDialog, sizeof gDialog, "%s%d.\t%s\t%d\n", gDialog, serverVars[i][svar_ID], serverVars[i][svar_Name], serverVars[i][svar_Value]);
    
    return Dialog_Show(playerid, SVARS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Server Variables", gDialog, "Select", "Exit");
}

YCMD:addsvar(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 8)
        return 1;

    if(serverStuff[sVars] == MAX_SVARS-1)
        return sendError(playerid, "Limita de variabile pentru server a fost atinsa. (%d)", MAX_SVARS-1);

    gString[0] = EOS;

    new value, id = serverStuff[sVars]+1; if(sscanf(params, "s[64]d", gString, value))
        return sendUsage(playerid, "/addsvar <variable name> <value>");

    if(strlen(gString) < 1 || strlen(gString) > 64)
        return sendError(playerid, "Numele variabilei trebuie sa fie cuprinsa intre 1 si 64 caractere.");

    strcpy(serverVars[id][svar_Name], gString, 65);
    serverVars[id][svar_Value] = value; 
    serverVars[id][svar_ID] = id; 
    ++serverStuff[sVars];

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "INSERT INTO `server_svars` (varName, varValue) VALUES ('%e', %d)", gString, value);
    mysql_tquery(SQL, gQuery, "", "");
    
    return SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s added a new server variable. (dbid: %d, name: %s, value: %d)", GetName(playerid), id, gString, value);
}

// ------------------------------------- //
//              Dialogs                  //
// ------------------------------------- //

Dialog:SVARS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    gDialog[0] = EOS;

    gDialog = "Item\tValue\n";

    SetPVarInt(playerid, "choosedListitem", listitem+1);

    format(gDialog, sizeof gDialog, "%sVariable Name\t%s\nValue\t%d\n", gDialog, serverVars[listitem+1][svar_Name], serverVars[listitem+1][svar_Value]);

    return Dialog_Show(playerid, SVARS_CHANGE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Server Variables", gDialog, "Ok", "Cancel");
}

Dialog:SVARS_CHANGE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const choosedlistitem = GetPVarInt(playerid, "choosedListitem");

    switch(listitem) {
        case 0: Dialog_Show(playerid, SVARS_VALUE, DIALOG_STYLE_INPUT, "SERVER: Change SVar", "Change variable name for '%s':", "Change", "Cancel", serverVars[choosedlistitem][svar_Name]);
        case 1: Dialog_Show(playerid, SVARS_VALUE, DIALOG_STYLE_INPUT, "SERVER: Change SVar", "Change variable value for '%s':", "Change", "Cancel", serverVars[choosedlistitem][svar_Name]);
    }
    return SetPVarInt(playerid, "changeName", !listitem);
}

Dialog:SVARS_VALUE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new const id = GetPVarInt(playerid, "choosedListitem");

    switch(GetPVarInt(playerid, "changeName")) {
        case 1: {
            if(isnumeric(inputtext))
                return Dialog_Show(playerid, SVARS_VALUE, DIALOG_STYLE_INPUT, "SERVER: Change SVar", "Change variable name for '%s':", "Change", "Cancel", serverVars[id][svar_Name]);

            SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s edited name for server variable '%s' [DBID: %d] in '%s'.", GetName(playerid), serverVars[id][svar_Name], serverVars[id][svar_ID], inputtext); 
            strcpy(serverVars[id][svar_Name], inputtext);
        }
        case 0: {
            if(!isnumeric(inputtext))
                return Dialog_Show(playerid, SVARS_VALUE, DIALOG_STYLE_INPUT, "SERVER: Change SVar", "Change variable value for '%s':", "Change", "Cancel", serverVars[id][svar_Name]);
        
            new const value = strval(inputtext);

            SendAdmins(COLOR_LIGHTRED, "(AdmCmd): {ffffff}%s edited value for server variable '%s' [DBID: %d] from %d to %d.", GetName(playerid), serverVars[id][svar_Name], serverVars[id][svar_ID], serverVars[id][svar_Value], value); 
            serverVars[id][svar_Value] = value;
        }
    }
    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_svars` SET `varName` = '%e', `varValue` = %d WHERE `varID` = %d", serverVars[id][svar_Name], serverVars[id][svar_Value], serverVars[id][svar_ID]); 
    mysql_tquery(SQL, gQuery, "", "");
    
    DeletePVar(playerid, "choosedListitem"); 
    DeletePVar(playerid, "changeName");
    return 1;
}