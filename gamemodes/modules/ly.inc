// ------------------------------------- //
//         Add/Substract functions       //
// ------------------------------------- //

addBankMoney(playerid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) { 
    suffix_val += suffix;
    
    if(suffix_val >= 1000000000) {
        ++prefix_val;
        suffix_val -= 1000000000;
    }

    prefix_val += prefix;

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `BankStore` = %d, `Bank` = %d WHERE `ID` = %d", prefix_val, suffix_val, playerInfo[playerid][pSQLID]);
    
    return 1;
}

substractBankMoney(playerid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) {
    if((!prefix_val && suffix > suffix_val) || suffix > 999999999) 
        return 0;
    
    suffix_val -= suffix;
    
    if(suffix_val < 0 && prefix_val > 0) {
        --prefix_val;
        suffix_val += 1000000000;
    }

    if(prefix != 0) {
        prefix_val -= prefix;

        if(prefix_val < 0)
            prefix_val = 0;
    }

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `BankStore` = %d, `Bank` = %d WHERE `ID` = %d", prefix_val, suffix_val, playerInfo[playerid][pSQLID]);
    
    return 1;
}

stock addMoneyOffline(sqlid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) {   
    suffix_val += suffix;
    
    if(suffix_val >= 1000000000) {
        ++prefix_val;
        suffix_val -= 1000000000;
    }

    prefix_val += prefix;

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", prefix_val, suffix_val, sqlid);
    
    return 1;
}

stock substractMoneyOffline(sqlid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) {
    if((!prefix_val && suffix > suffix_val) || suffix > 999999999) 
        return 0;
    
    suffix_val -= suffix;
    
    if(suffix_val < 0 && prefix_val > 0) {
        --prefix_val;
        suffix_val += 1000000000;
    }

    if(prefix != 0) {
        prefix_val -= prefix;

        if(prefix_val < 0)
            prefix_val = 0;
    }

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", prefix_val, suffix_val, sqlid);
    
    return 1;
}

addMoney(playerid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) { 
    suffix_val += suffix;
    
    if(suffix_val >= 1000000000) {
        ++prefix_val;
        suffix_val -= 1000000000;
    }

    prefix_val += prefix;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetMoney(playerid) <= 999999998 && GetMilliards(playerid) < 1 ? suffix_val : 999999999);

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", prefix_val, suffix_val, playerInfo[playerid][pSQLID]);
    
    return 1;
}

substractMoney(playerid, &prefix_val, &suffix_val, prefix, suffix, const bool:query = true) {
    if((!prefix_val && suffix > suffix_val) || suffix > 999999999) 
        return 0;
    
    suffix_val -= suffix;
    
    if(suffix_val < 0 && prefix_val > 0) {
        --prefix_val;
        suffix_val += 1000000000;
    }

    if(prefix != 0) {
        prefix_val -= prefix;

        if(prefix_val < 0)
            prefix_val = 0;
    }

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetMoney(playerid) <= 999999998 && GetMilliards(playerid) < 1 ? suffix_val : 999999999);

    if(query)
        va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", prefix_val, suffix_val, playerInfo[playerid][pSQLID]);
    
    return 1;
}

// ------------------------------------- //
//               Utils                   //
// ------------------------------------- //

delimiteMoneyFromString(&prefix_val, &suffix_val, const value[]) { 
    new const length = strlen(value);

    if(length <= 9) {
        prefix_val = 0;
        suffix_val = strval(value);
        return 0;
    }

    new copy_value[20];

    strcat(copy_value, value);
    copy_value[length - 9] = EOS;

    suffix_val = strval(value[length - 9]);
    prefix_val = strval(copy_value);
    return 1;
}

formatMoney(prefix_val, suffix_val) {
    new 
        str[64];

    if(prefix_val > 0) 
        format(str, sizeof str, "%d%09d", prefix_val, suffix_val);
    
    else 
        format(str, sizeof str, "%d", suffix_val); 

    for(new i = strlen(str) - 3; i > 0; i -= 3)  
        strins(str, ".", i); 
    
    return str;
}