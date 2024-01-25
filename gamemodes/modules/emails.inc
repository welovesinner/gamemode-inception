// ------------------------------------- //
//              Includes                 //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define EMAILS_DIALOG_PAGE_LIMIT 15

// ------------------------------------- //
//          Variables and enums          //
// ------------------------------------- //

static enum e_emailsInfo {
    emailID, emailFrom[MAX_PLAYER_NAME], emailDate[20], emailMessage[144], bool:emailReaded 
}

static 
    Vector:playerEmails[MAX_PLAYERS], 
    pageIndexEmails[MAX_PLAYERS],
    emailsCount[MAX_PLAYERS],
    unreadedEmailsCount[MAX_PLAYERS],
    selectedEmail[MAX_PLAYERS][e_emailsInfo];

// ------------------------------------- //
//          Query Functions              //
// ------------------------------------- //

query_function loadPlayerEmails(const playerid, const dbid) {
    if(dbid != playerInfo[playerid][pSQLID])
        return 1;

    if(!(emailsCount[playerid] = cache_num_rows()))
        return 1;

    new emails[e_emailsInfo];

    for(new i = 0; i < emailsCount[playerid]; ++i) {
        emails[emailID] = cache_get_field_content_int(i, "ID");
        
        if(!(emails[emailReaded] = bool:cache_get_field_content_int(i, "Readed"))) 
            unreadedEmailsCount[playerid] ++;

        cache_get_field_content(i, "From", emails[emailFrom], SQL, MAX_PLAYER_NAME);
        cache_get_field_content(i, "Date", emails[emailDate], SQL, 20);
        cache_get_field_content(i, "Message", emails[emailMessage], SQL, 144);

        VECTOR_push_back_arr(playerEmails[playerid], emails);
    }

    if(getPlayerUnreadedEmailsCount(playerid))
        SCMf(playerid, COLOR_YELLOW, "* You have {FF0000}%d{FFFF00} unreaded notifications. Write [/emails] to see them.", getPlayerUnreadedEmailsCount(playerid));

    return 1;
}

query_function onInsertPlayerEmail(const playerid, const dbid, const from[], const date[], const message[]) {
    if(dbid != playerInfo[playerid][pSQLID])
        return 1;

    new email[e_emailsInfo];

    email[emailID] = cache_insert_id();
    
    strcat(email[emailFrom], from);
    strcat(email[emailMessage], message);
    strcat(email[emailDate], date);

    VECTOR_push_back_arr(playerEmails[playerid], email);

    emailsCount[playerid] ++;
    unreadedEmailsCount[playerid] ++;
    return 1;
}

// ------------------------------------- //
//          Functions                    //
// ------------------------------------- //

insertEmail(const playerid = INVALID_PLAYER_ID, const name[], const from[] = "AdmBot", const message[], va_args<>) {
    new 
        query[256], str[128];

    va_format(str, sizeof str, message, va_start<4>);

    if(playerid != INVALID_PLAYER_ID) {
        mysql_format(SQL, query, sizeof query, "INSERT INTO `server_users_emails` (`To`, `From`, `Date`, `Message`, `Readed`) VALUES (%d, '%e', '%e', '%e', 0)", playerInfo[playerid][pSQLID], from, getDateTime(), str);
        mysql_tquery(SQL, query, "onInsertPlayerEmail", "ddsss", playerid, playerInfo[playerid][pSQLID], from, getDateTime(), str);

        return SCM(playerid, COLOR_YELLOW, "* A new notification has appeared in /emails. Check it!");
    }

    mysql_format(SQL, query, sizeof query, "INSERT INTO `server_users_emails` (`To`, `From`, `Date`, `Message`, `Readed`) VALUES ((SELECT (ID) FROM `server_users` WHERE `Name` = '%e' LIMIT 1), '%e', '%e', '%e', 0)", name, from, getDateTime(), str);
    mysql_tquery(SQL, query, "", "");
    return 1;
}

static showPlayerEmails(const playerid, &index_start) {
    gDialog = "#\tFrom\tDate\tReaded\n";

    for(new emails[e_emailsInfo]; index_start < getPlayerEmailsCount(playerid); ++index_start) {
        VECTOR_get_arr(playerEmails[playerid], index_start, emails);

        format(gDialog, sizeof gDialog, "%s%d.\t%s\t%s\t%s\n", gDialog, index_start + 1, emails[emailFrom], emails[emailDate], emails[emailReaded] ? "Yes" : "No");   

        if(index_start % EMAILS_DIALOG_PAGE_LIMIT == EMAILS_DIALOG_PAGE_LIMIT - 1) {
            if(getPlayerEmailsCount(playerid) > index_start + 1)
                strcat(gDialog, "> Next Page\n");

            break;
        }
    }

    if(index_start > EMAILS_DIALOG_PAGE_LIMIT) 
        strcat(gDialog, "< Previous Page");

    gString[0] = EOS;
    format(gString, sizeof gString, "SERVER: Notifications (page: %d)", (index_start / EMAILS_DIALOG_PAGE_LIMIT) + 1);

    return Dialog_Show(playerid, EMAILS, DIALOG_STYLE_TABLIST_HEADERS, gString, gDialog, "Select", "Exit");
}

getPlayerUnreadedEmailsCount(const playerid)
    return unreadedEmailsCount[playerid];

getPlayerEmailsCount(const playerid)
    return emailsCount[playerid];

// ------------------------------------- //
//          Command                      //
// ------------------------------------- //

YCMD:emails(playerid, params[], help) {
    if(!getPlayerEmailsCount(playerid))
        return SCM(playerid, COLOR_GREEN, "(Notifications): {FFFFFF}You don't have notifications.");

    SCMf(playerid, COLOR_GREEN, "(Notifications): {FFFFFF}You have %d notifications (%d unreaded) in total.", getPlayerEmailsCount(playerid), getPlayerUnreadedEmailsCount(playerid));

    pageIndexEmails[playerid] = 0;
    return showPlayerEmails(playerid, pageIndexEmails[playerid]);
}

// ------------------------------------- //
//          Dialogs                      //
// ------------------------------------- //

Dialog:EMAILS(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    if(inputtext[0] == '>') {
        pageIndexEmails[playerid] ++;
        return showPlayerEmails(playerid, pageIndexEmails[playerid]);
    }
    else if(inputtext[0] == '<') { 
        pageIndexEmails[playerid] = ((pageIndexEmails[playerid] / EMAILS_DIALOG_PAGE_LIMIT) * EMAILS_DIALOG_PAGE_LIMIT) - EMAILS_DIALOG_PAGE_LIMIT;
        return showPlayerEmails(playerid, pageIndexEmails[playerid]);
    }

    new const idx = ((pageIndexEmails[playerid] / EMAILS_DIALOG_PAGE_LIMIT) * EMAILS_DIALOG_PAGE_LIMIT) + listitem;

    VECTOR_get_arr(playerEmails[playerid], idx, selectedEmail[playerid]);

    gDialog[0] = EOS; 
    format(gDialog, sizeof gDialog, "%s\n\n\tThis e-mail is created by %s (date: %s).", selectedEmail[playerid][emailMessage], selectedEmail[playerid][emailFrom], selectedEmail[playerid][emailDate]);

    if(!selectedEmail[playerid][emailReaded]) {
        gQuery[0] = EOS; 
        mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users_emails` SET `Readed` = 1 WHERE `ID` = %d LIMIT 1", selectedEmail[playerid][emailID]);
        mysql_tquery(SQL, gQuery, "", "");

        selectedEmail[playerid][emailReaded] = true;

        unreadedEmailsCount[playerid] --;

        VECTOR_set_arr(playerEmails[playerid], idx, selectedEmail[playerid]);
    }

    return Dialog_Show(playerid, DELETEEMAIL, DIALOG_STYLE_MSGBOX, "SERVER: Notifications", gDialog, "Delete", "Exit"); 
}

Dialog:DELETEEMAIL(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    VECTOR_remove_arr(playerEmails[playerid], selectedEmail[playerid]);

    emailsCount[playerid] --;

    gQuery[0] = EOS; 
    mysql_format(SQL, gQuery, sizeof gQuery, "DELETE FROM `server_users_emails` WHERE `ID` = %d LIMIT 1", selectedEmail[playerid][emailID]); 
    mysql_tquery(SQL, gQuery, "", ""); 

    return SCM(playerid, COLOR_GREEN, "(Notifications): {ffffff}You deleted this e-mail successfully.");
}

// ------------------------------------- //
//          Hooks                        //
// ------------------------------------- //

hook OnPlayerDisconnect(playerid) {
    VECTOR_clear(playerEmails[playerid]);

    emailsCount[playerid] = unreadedEmailsCount[playerid] = 0;
    return 1;
}
