Dialog:FORCENAMECHANGE(playerid, response, listitem, inputtext[]) {
    if(!response) {
        SendAdmins(COLOR_LIGHTRED, "(AdmInfo): {ffffff}Player %s don't changed his nickname via [/forcenamechange] and got kicked from the server.", GetName(playerid)); 
        return Kick(playerid);
    }

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "SELECT (ID) FROM `server_users` WHERE `Name` = '%e'", inputtext); 
    mysql_tquery(SQL, gQuery, "forceNameChange", "ds", playerid, inputtext);
    return 1;
}

Dialog:REFERRALCOLLECT(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0: {
            if(playerInfo[playerid][pReferralCash] <= 0)
                return sendError(playerid, "Nu ai bani de colectat.");

            addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, playerInfo[playerid][pReferralCash], false);

            SCMf(playerid, COLOR_GREEN, "(Referral): {FFFFFF}You collected $%s money succesfully from your referral rewards.", formatNumber(playerInfo[playerid][pReferralCash]));
            
            playerInfo[playerid][pReferralCash] = 0;
        }
        case 1: {
            if(playerInfo[playerid][pReferralRespectPoints] <= 0)
                return sendError(playerid, "Nu ai puncte de respect de colectat.");

            playerInfo[playerid][pRespectPoints] += playerInfo[playerid][pReferralRespectPoints];

            SCMf(playerid, COLOR_GREEN, "(Referral): {FFFFFF}You collected %d respect points succesfully from your referral rewards.", playerInfo[playerid][pReferralRespectPoints]);
            
            playerInfo[playerid][pReferralRespectPoints] = 0;
        }
    }
    return va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `RespectPoints` = %d, `ReferralRespectPoints` = %d, `ReferralCash` = %d WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pRespectPoints], playerInfo[playerid][pReferralRespectPoints], playerInfo[playerid][pReferralCash], playerInfo[playerid][pSQLID]);
}

Dialog:TRUCKER(playerid, response, listitem, inputtext[]) {
    playerVars[playerid][b_ACTIVE_TIMER] = false;

    if(!playerVars[playerid][var_working])
        return 1;

    if(!response)
        return stopWork(playerid);

    switch(listitem) {
        case 8..11: {
            if(playerInfo[playerid][pTruckerSkill] < 31) {
                sendError(playerid, "Ai nevoie de minim skill 2 pentru a face acest transport.");
                return showPlayerTruckerLocations(playerid);
            }

            playerVars[playerid][var_trucker_cash_bonus] = 15000;
        }
        case 12..15: {
            if(playerInfo[playerid][pTruckerSkill] < 61) {
                sendError(playerid, "Ai nevoie de minim skill 3 pentru a face acest transport.");
                return showPlayerTruckerLocations(playerid);
            }

            playerVars[playerid][var_trucker_cash_bonus] = 20000;
        }
        default: {
            playerVars[playerid][var_trucker_cash_bonus] = 10000;
        }
    }

    if(listitem >= 8)
        listitem -= 8;

    if(playerInfo[playerid][pTruckerSkill] > 30) 
        Iter_Add(truckersChat, playerid);

    SCMf(playerid, COLOR_GREEN, "(Trucker): {FFFFFF}You selected the location named '%s' (type: %s). Distance: %0.2fkm.", truckerLocations[listitem][tr_name], playerVars[playerid][var_trucker_cash_bonus] == 10000 ? "legal" : "illegal", GetPlayerDistanceFromPoint(playerid, truckerLocations[listitem][tr_X], truckerLocations[listitem][tr_Y], truckerLocations[listitem][tr_Z])/1000);
    SCM(playerid, COLOR_GREEN, "(Trucker): {FFFFFF}If your trailer is detached from your vehicle press 'LALT' key to attach it.");
    SCM(playerid, COLOR_GREEN, "(Trucker): {FFFFFF}If you want to speak with the truckers which are working on this job use command [/trc]. (skill 2 required)");

    new 
        Float: X, Float: Y, Float: Z;

    GetPlayerPos(playerid, X, Y, Z);

    switch(random(4)) {
        case 0: playerVars[playerid][var_trucker_trailer] = createVehicle(435, X, Y, Z, 0.0, random(255), random(255), -1);
        case 1: playerVars[playerid][var_trucker_trailer] = createVehicle(450, X, Y, Z, 0.0, random(255), random(255), -1);
        case 2: playerVars[playerid][var_trucker_trailer] = createVehicle(584, X, Y, Z, 0.0, random(255), random(255), -1);
        case 3: playerVars[playerid][var_trucker_trailer] = createVehicle(591, X, Y, Z, 0.0, random(255), random(255), -1);
    }        

    defer attachTruckerTrailer(playerid);

    TogglePlayerControllableEx(playerid, true);

    playerVars[playerid][var_jobtime] = gettime();
    playerVars[playerid][var_checkpoint] = 10; 

    SetPlayerCheckpoint(playerid, truckerLocations[listitem][tr_X], truckerLocations[listitem][tr_Y], truckerLocations[listitem][tr_Z], 4.0);
    return 1;
}

Dialog:SKINS(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    if(listitem) {
        Iter_Remove(playerSkins[playerid], playerVars[playerid][var_precedentskin]);

        SCMf(playerid, COLOR_GREEN, "(Clothes Info): {FFFFFF}You removed skin %d succesfully from your owned skins.", GetPlayerSkin(playerid));

        gString[0] = EOS;
        format(gString, sizeof gString, "SKIN ID: ~P~%d~N~~W~~H~PRICE: ~G~$5.000", GetPlayerSkin(playerid)); 
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][7], gString);
        PlayerTextDrawBoxColor(playerid, playerTextdraws[playerid][ClothesTD][5], 8388863); 
        PlayerTextDrawSetString(playerid, playerTextdraws[playerid][ClothesTD][5], "BUY"); 
        PlayerTextDrawShow(playerid, playerTextdraws[playerid][ClothesTD][5]);

        if(playerInfo[playerid][pSkin] == GetPlayerSkin(playerid))
            playerInfo[playerid][pSkin] = Iter_Count(playerSkins[playerid]) ? clothesSkins[Iter_Random(playerSkins[playerid])] : (playerInfo[playerid][pGender] == MALE_GENDER ? 37 : 12);
    }
    else {
        if(playerInfo[playerid][pSkin] == GetPlayerSkin(playerid))
            return sendError(playerid, "Ai deja acest skin setat.");

        playerInfo[playerid][pSkin] = GetPlayerSkin(playerid); 

        SCMf(playerid, COLOR_GREEN, "(Clothes Info): {FFFFFF}You changed your skin (id: %d) succesfully.", playerInfo[playerid][pSkin]);
    }

    va_mysql_tquery("UPDATE `server_users` SET `Skin` = %d WHERE `ID` = %d", playerInfo[playerid][pSkin], playerInfo[playerid][pSQLID]);
    return saveSkins(playerid);
}

Dialog:SELECTMATSLOCATION(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0, 5: {
            playerVars[playerid][var_arms_dealer_materials] = 90;
            playerVars[playerid][var_arms_dealer_money] = 4000;
        }
        case 1: {
            playerVars[playerid][var_arms_dealer_materials] = 165;
            playerVars[playerid][var_arms_dealer_money] = 5500;
        }
        case 2: {
            playerVars[playerid][var_arms_dealer_materials] = 120;
            playerVars[playerid][var_arms_dealer_money] = 4750;
        }
        case 3: {
            playerVars[playerid][var_arms_dealer_materials] = 65;
            playerVars[playerid][var_arms_dealer_money] = 3500;
        }
        case 4: {
            playerVars[playerid][var_arms_dealer_materials] = 215;
            playerVars[playerid][var_arms_dealer_money] = 6350;
        }
        case 6: {
            playerVars[playerid][var_arms_dealer_materials] = 115;
            playerVars[playerid][var_arms_dealer_money] = 3700;
        }
        case 7: {
            playerVars[playerid][var_arms_dealer_materials] = 200;
            playerVars[playerid][var_arms_dealer_money] = 6000;
        }
    }

    playerVars[playerid][var_arms_dealer_materials] += random(playerInfo[playerid][pArmsDealerSkill]+15); 
    playerVars[playerid][var_arms_dealer_money] += random(playerInfo[playerid][pArmsDealerSkill]*10); 
    playerVars[playerid][b_ARMS_DEALER_WORKING] = true;

    playerVars[playerid][var_checkpoint] = 9;
    SetPlayerCheckpoint(playerid, armsDealerLocations[listitem][0], armsDealerLocations[listitem][1], armsDealerLocations[listitem][2], 3.5);

    return SCMf(playerid, COLOR_GREEN, "(Arms Dealer): {FFFFFF}Go to the marked checkpoint on the map. Distance: %0.2fkm.", GetPlayerDistanceFromPoint(playerid, armsDealerLocations[listitem][0], armsDealerLocations[listitem][1], armsDealerLocations[listitem][2])/1000);
}

Dialog:COLLECTARMSDEALER(playerid, response, listitem, inputtext[]) {
    if(!listitem) {
        playerInfo[playerid][pMaterials] += playerVars[playerid][var_arms_dealer_materials]; 
        SCMf(playerid, COLOR_GREEN, "(Arms Dealer): {FFFFFF}You received %d materials for your work.", playerVars[playerid][var_arms_dealer_materials]);
    }
    else {
        addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, playerVars[playerid][var_arms_dealer_money], false); 
        SCMf(playerid, COLOR_GREEN, "(Arms Dealer): {FFFFFF}You received $%s money for your work.", formatNumber(playerVars[playerid][var_arms_dealer_money]));
    }

    if(playerInfo[playerid][pArmsDealerSkill] < 90) 
        ++playerInfo[playerid][pArmsDealerSkill];

    va_mysql_tquery("UPDATE `server_users` SET `MoneyStore` = %d, `Money` = %d, `Materials` = %d, `ArmsDealerSkill` = %d WHERE `ID` = %d", GetMilliards(playerid), GetMoney(playerid), playerVars[playerid][var_arms_dealer_materials], playerInfo[playerid][pArmsDealerSkill], playerInfo[playerid][pSQLID]);
    
    playerVars[playerid][var_arms_dealer_materials] = playerVars[playerid][var_arms_dealer_money] = -1;
    playerVars[playerid][b_ARMS_DEALER_WORKING] = false;
    return 1;
}

Dialog:HELP(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0: gDialog = "/w(whisper) /me /s(shouts) /cw(carwhisper)";
        case 1: {
            switch(playerInfo[playerid][pJob]) {
                case 0: gDialog = "You don't have a job.";
                case 1: gDialog = "/find";
                case 2: gDialog = "/fish";
                case 8: gDialog = "/getseeds /plantseeds /getdrugs /selldrugs";
                case 9: gDialog = "/getmaterials /sellmaterials /creategun";
                case 10: gDialog = "/work /stopwork /trc";
                default: gDialog = "/work /stopwork";
            }
        }
        case 2: gDialog = "/buylevel /stats /admins /helpers /licenses /showlicenses /jobs\n/lights /engine /time /id /hud /changepass /x /report /tog\n/n(newbie) /spawnchange /findhouse /findbusiness /locations\n/ph(puthelmet) /eject /killcp /forum /panel /sleep /pay /heal /carradio /balance /deposit /withdraw /rentroom /unrentroom\nand others ...";
        case 3: {
            if(playerInfo[playerid][pBusiness] == -1) 
                gDialog = "You don't have a business.";

            else 
                gDialog = "/bmenu(bizzmenu) /sellbizztostate";
        }
        case 4: {
            if(playerInfo[playerid][pHouse] == -1) 
                gDialog = "You don't have a house.";

            else 
                gDialog = "/hmenu(housemenu) /sellhousetostate";
        }
    }

    return Dialog_Show(playerid, NULL, DIALOG_STYLE_MSGBOX, "SERVER: Help", gDialog, "Exit", "");
}

Dialog:CHANGESTYLE(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    if(GetMoney(playerid) < 500 && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai suficienti bani.");

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, 500, false);

    playerInfo[playerid][pFightingStyle] = fightingStyle[listitem][0]; 
    SetPlayerFightingStyle(playerid, playerInfo[playerid][pFightingStyle]);

    va_mysql_tquery("UPDATE `server_users` SET `FightingStyle` = %d, `MoneyStore` = %d, `Money` = %d WHERE `ID` = %d", playerInfo[playerid][pFightingStyle], GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pSQLID]);
    
    SCMf(playerid, COLOR_GREEN, "(GYM): {ffffff}You learned the %s fighting style for $500.", fightingStyle[listitem][1]); 
    
    return updatePlayerQuestProgress(playerid, QUEST_TYPE_LEARNFIGHTGYM);
}

Dialog:TOG(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    switch(listitem) {
        case 0: {
            if(!playerInfo[playerid][pWalkieTalkie])
                return sendError(playerid, "Nu ai un walkie talkie.");

            if(!playerInfo[playerid][pFrequency]) 
                return sendError(playerid, "Ai frecventa oprita.");

            if(Iter_Remove(serverFrequency[playerInfo[playerid][pFrequency]], playerid) != INVALID_ITERATOR_SLOT) {
                va_mysql_tquery("UPDATE `server_users` SET `TOGWalkieTalkie` = 0 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);

                return SCM(playerid, -1, "Your TOG has been updated! (Walkie Talkie disabled)");
            }

            Iter_Add(serverFrequency[playerInfo[playerid][pFrequency]], playerid);

            va_mysql_tquery("UPDATE `server_users` SET `TOGWalkieTalkie` = 1 WHERE `ID` = %d", playerInfo[playerid][pSQLID]);

            return SCM(playerid, -1, "Your TOG has been updated! (Walkie Talkie enabled)");
        }
        case 1: {
            playerInfo[playerid][pTOGSurf] = !playerInfo[playerid][pTOGSurf];

            va_mysql_tquery("UPDATE `server_users` SET `TOGSurf` = %d WHERE `ID` = %d", playerInfo[playerid][pTOGSurf], playerInfo[playerid][pSQLID]);

            return SCM(playerid, -1, playerInfo[playerid][pTOGSurf] ? "Your TOG has been updated! (Vehicle Surf enabled)" : "Your TOG has been updated! (Vehicle Surf disabled)");
        }
        case 2: {
            playerInfo[playerid][pTOGPay] = !playerInfo[playerid][pTOGPay];

            va_mysql_tquery("UPDATE `server_users` SET `TOGPay` = %d WHERE `ID` = %d", playerInfo[playerid][pTOGPay], playerInfo[playerid][pSQLID]);

            return SCM(playerid, -1, playerInfo[playerid][pTOGPay] ? "Your TOG has been updated! (Pay enabled)" : "Your TOG has been updated! (Pay disabled)");
        }
        case 3: {
            if(!playerInfo[playerid][pAdmin])
                return sendError(playerid, "Nu ai gradul administrativ necesar.");

            playerInfo[playerid][pTOGFind] = !playerInfo[playerid][pTOGFind];

            va_mysql_tquery("UPDATE `server_users` SET `TOGFind` = %d WHERE `ID` = %d", playerInfo[playerid][pTOGFind], playerInfo[playerid][pSQLID]);

            return SCM(playerid, -1, playerInfo[playerid][pTOGFind] ? "Your TOG has been updated! (Find enabled)" : "Your TOG has been updated! (Find disabled)");
        }
    }
    return 1;
}

Dialog:DRINK(playerid, response, listitem, inputtext[]) {
    if(!response) 
        return 1;

    if(GetMoney(playerid) < drinkTypes[listitem][0] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti pentru a face asta.");

    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, drinkTypes[listitem][0]); 
    
    SetPlayerSpecialAction(playerid, drinkTypes[listitem][1]); 
    
    SCMf(playerid, COLOR_GREEN, "(Bar): {ffffff}You purchased %s for $%d money.", drinkTypes[listitem][2], drinkTypes[listitem][0]);
    
    return updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYBARDRINK);
}

Dialog:FOOD(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;
    
    if(GetMoney(playerid) < foodTypes[listitem][0] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti pentru a face asta.");

    new Float:health; 
    GetPlayerHealth(playerid, health); 
    SetPlayerHealth(playerid, (health >= 70.0 ? 99.0 : health+float(drinkTypes[listitem][1]))); 
    
    substractMoney(playerid, playerInfo[playerid][pMoneyStore], playerInfo[playerid][pMoney], 0, foodTypes[listitem][0]); 

    ApplyAnimationEx(playerid,"FOOD","EAT_Burger", 3.0, 0, 0, 0, 0, 0); 

    SCMf(playerid, COLOR_GREEN, "(Food Shop): {ffffff}You purchased %s for $%d money.", foodTypes[listitem][2], foodTypes[listitem][0]);
    
    return updatePlayerQuestProgress(playerid, QUEST_TYPE_EAT);
}

Dialog:BUYTOYS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(listitem == 4)
        updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYFLOWERS);

    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, sexShop[listitem][0]); 

    GivePlayerWeapon(playerid, 10+listitem, 1);

    return SCMf(playerid, COLOR_GREEN, "(Shop): {ffffff}You purchased %s for $%d.", sexShop[listitem][1], sexShop[listitem][0]);
}

Dialog:BUY(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(GetMoney(playerid) < buyShop[listitem] && GetMilliards(playerid) < 1)
        return sendError(playerid, "Nu ai bani suficienti pentru a face asta.");

    switch(listitem) {
        case 0: {
            if(playerInfo[playerid][pPhoneBook])
                return sendError(playerid, "Nu poti face asta deoarece ai deja achizitionata o carte de telefoane.");

            playerInfo[playerid][pPhoneBook] = true;
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased a phone book for $500. Use command [/number].");
        }
        case 1: {
            if(playerInfo[playerid][pPhoneNumber] == 0)
                return sendError(playerid, "Nu ai un telefon.");

            if(playerInfo[playerid][pPhoneCredit] > 200)
                return sendError(playerid, "Nu poti cumpara credit deoarece detii mai mult de 200.");

            playerInfo[playerid][pPhoneCredit] += 50;
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased 50 credit for your phone for $1.000.");
        }
        case 2: {
            new const number = random(999999 - 100000 + 1) + 100000;

            gQuery[0] = EOS;
            mysql_format(SQL, gQuery, sizeof gQuery, "SELECT (ID) FROM `server_users` WHERE `PhoneNumber` = %d LIMIT 1", number);
            return mysql_tquery(SQL, gQuery, "buyPhoneNumber", "dd", playerid, number);
        }
        case 3: {
            if(playerInfo[playerid][pWalkieTalkie])
                return sendError(playerid, "Ai deja un Walkie Talkie.");

            playerInfo[playerid][pWalkieTalkie] = true;
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased an Walkie Talkie for $750.");
        }
        case 4: {
            playerVars[playerid][var_cigarettes] += 3;
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased 3 cigarettes for $250. Use command [/smoke].");
        }
        case 5: {
            GivePlayerWeapon(playerid, 43, 25); 
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased a photo camera for $500.");

            updatePlayerQuestProgress(playerid, QUEST_TYPE_BUYPHOTOCAMERA);
        }
        case 6: {
            if(playerVars[playerid][var_gascan]) 
                return sendError(playerid, "Ai deja o canistra cu combustibil.");

            playerVars[playerid][var_gascan] = true;
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased a gas can for $4.500.");
        }
        case 7: {
            if(playerInfo[playerid][pRepairKits] >= 10)
                return sendError(playerid, "Nu poti avea mai mult de 10 kit-uri de reparare.");

            ++playerInfo[playerid][pRepairKits];
            SCM(playerid, COLOR_GREEN, "(Shop): {FFFFFF}You purchased a repair kit for $15.000.");
        }
    }
    substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, buyShop[listitem], false);

    va_mysql_tquery("UPDATE `server_users` SET `PhoneCredit` = %d, `PhoneBook` = %d, `WalkieTalkie` = %d, `MoneyStore` = %d, `Money` = %d, `RepairKits` = %d WHERE `ID` = %d", playerInfo[playerid][pPhoneCredit], playerInfo[playerid][pPhoneBook], playerInfo[playerid][pWalkieTalkie], GetMilliards(playerid), GetMoney(playerid), playerInfo[playerid][pRepairKits], playerInfo[playerid][pSQLID]); 
    
    playerVars[playerid][var_buy_delay] = gettime() + 5;
    return 1;
}

Dialog:BANKTRANSFER(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    new 
        money = GetPVarInt(playerid, "transferMoney"),
        userID = GetPVarInt(playerid, "transferPlayer");

    if(playerInfo[playerid][pBank] < money && playerInfo[playerid][pBankStore] < 1)
        return sendError(playerid, "Nu ai banii necesari in banca.");

    substractBankMoney(playerid, playerInfo[playerid][pBankStore], playerInfo[playerid][pBank], 0, money);
    addBankMoney(userID, playerInfo[userID][pBankStore], playerInfo[userID][pBank], 0, money);

    SCMf(playerid, COLOR_DARKGREEN, "* You transfered succesfully $%s money to player %s. New balance: $%s.", formatNumber(money), GetName(userID), formatMoney(playerInfo[playerid][pBankStore], playerInfo[playerid][pBank]));
    SCMf(userID, COLOR_DARKGREEN, "* %s transfered to your bank account, $%s money.", GetName(playerid), formatNumber(money));

    DeletePVar(playerid, "transferMoney"); 
    DeletePVar(playerid, "transferPlayer");
    return 1;
}

Dialog:STAFF(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    return mysql_tquery(SQL, listitem == 0 ? "SELECT * FROM `server_users` WHERE `Admin` >= 1 ORDER BY `server_users`.`Admin` DESC LIMIT 25" : "SELECT * FROM `server_users` WHERE `Helper` >= 1 ORDER BY `server_users`.`Helper` DESC LIMIT 25", "checkStaffCategory", "dd", playerid, listitem);
}

Dialog:RADIO(playerid, response, listitem, inputtext[]) {
    if(!response || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return 1;

    new const vehicleid = GetPlayerVehicleID(playerid);

    if(vehicleVars[vehicleid][var_carRadio] == listitem) 
        return sendError(playerid, "%s", !listitem ? "Vehiculul acesta are deja radio-ul oprit." : "Vehiculul acesta are deja acest post de radio.");       

    playerVars[playerid][var_radio_delay] = gettime() + 5;

    if(listitem) {
        if(vehicleVars[vehicleid][var_carRadio]) 
            radioListeners[vehicleVars[vehicleid][var_carRadio] - 1] -= getVehicleOccupantsCount(vehicleid);

        vehicleVars[vehicleid][var_carRadio] = listitem; 
        PlayAudioStreamForPlayers(vehicleid, radioSelected[listitem - 1][0]);

        return sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s is listening now %s.", GetName(playerid), radioSelected[listitem - 1][1]);
    }
    
    StopAudioStreamForPlayers(vehicleid); 
    vehicleVars[vehicleid][var_carRadio] = 0; 

    return sendNearbyMessage(playerid, COLOR_PURPLE, 25.0, "* %s stopped his vehicle radio.", GetName(playerid));
}

Dialog:LOCATIONS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0: {
            Dialog_Show(playerid, LOCATIONSCHOOSE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Other Locations", "Name\tDistance\nDMV\t%0.2fkm\nDealership\t%0.2fkm", "Select", "Cancel", GetPlayerDistanceFromPoint(playerid, 1219.2386, -1812.8556, 16.5938) / 1000, GetPlayerDistanceFromPoint(playerid, dealership_Location_X, dealership_Location_Y, dealership_Location_Z) / 1000); 
        }
        case 1: {
            gDialog = "ID\tName\tDistance\n"; 
            
            for(new i = 0; i < serverStuff[business]; ++i) 
                format(gDialog, sizeof gDialog, "%s#%d\t%s\t%0.2fkm\n", gDialog, i + 1, bizzTypeName[bizzInfo[i][bType] - 1], GetPlayerDistanceFromPoint(playerid, bizzInfo[i][bX], bizzInfo[i][bY], bizzInfo[i][bZ]) / 1000);
        
            Dialog_Show(playerid, LOCATIONSCHOOSE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Businesses", gDialog, "Select", "Cancel"); 
        }
        case 2: {
            gDialog = "No.\tDistance\n"; 
            
            for(new i = 0; i < sizeof atmPositions; ++i) 
                format(gDialog, sizeof gDialog, "%s#%d\t%0.2fkm\n", gDialog, i + 1, GetPlayerDistanceFromPoint(playerid, atmPositions[i][0], atmPositions[i][1], atmPositions[i][2]) / 1000);
        
            Dialog_Show(playerid, LOCATIONSCHOOSE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Server ATMs", gDialog, "Select", "Cancel"); 
        }
        case 3: {
            gDialog = "No.\tDistance\n";
            
            for(new i = 0; i < sizeof vendingMachines; ++i) 
                format(gDialog, sizeof gDialog, "%s#%d\t%0.2fkm\n", gDialog, i + 1, GetPlayerDistanceFromPoint(playerid, vendingMachines[i][vending_X], vendingMachines[i][vending_Y], vendingMachines[i][vending_Z]) / 1000);
        
            Dialog_Show(playerid, LOCATIONSCHOOSE, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Vending Machines", gDialog, "Select", "Cancel"); 
        }
    }
    SetPVarInt(playerid, "choosedListitem", listitem);
    return 1;
}

Dialog:LOCATIONSCHOOSE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return DeletePVar(playerid, "choosedListitem");

    switch(GetPVarInt(playerid, "choosedListitem")) {
        case 0: {
            switch(listitem) {
                case 0: SetPlayerCheckpoint(playerid, 1219.2386, -1812.8556, 16.5938, 2.0);
                case 1: SetPlayerCheckpoint(playerid, dealership_Location_X, dealership_Location_Y, dealership_Location_Z, 2.0);
            }
        }
        case 1: SetPlayerCheckpoint(playerid, bizzInfo[listitem][bX], bizzInfo[listitem][bY], bizzInfo[listitem][bZ], 2.0);
        case 2: SetPlayerCheckpoint(playerid, atmPositions[listitem][0], atmPositions[listitem][1], atmPositions[listitem][2], 2.0);
        case 3: SetPlayerCheckpoint(playerid, vendingMachines[listitem][vending_X], vendingMachines[listitem][vending_Y], vendingMachines[listitem][vending_Z], 2.0);
    }
    playerVars[playerid][var_checkpoint] = 1;

    DeletePVar(playerid, "choosedListitem"); 

    return SCM(playerid, COLOR_GREEN, "(GPS Info): {FFFFFF}A checkpoint has been placed to selected location.");
}

Dialog:CHECKPOINT(playerid, response, listitem, inputtext[]) { 
    if(!response)
        return 1;

    if(isPlayerInDMVExamen(playerid) || playerVars[playerid][var_working] || playerVars[playerid][b_ARMS_DEALER_WORKING])
        return sendError(playerid, "Nu poti face asta in momentul acesta.");

    DisablePlayerCheckpointEx(playerid); 
    SCM(playerid, COLOR_YELLOW, "* Your current checkpoint was removed from your map.");

    if(playerVars[playerid][var_findon] != -1) {
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][0]); 
        playerTextDrawDestroy(playerid, playerTextdraws[playerid][FindTD][1]); 
        
        playerVars[playerid][var_findon] = -1; 
        
        stop playerVars[playerid][var_find_timer]; 
    }
    return 1;
}

Dialog:SPAWNCHANGE(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(playerInfo[playerid][pSpawnType] == e_pSpawnTypes:(listitem + 1))
        return sendError(playerid, "Tipul acesta de spawn este deja setat.");

    if(listitem == 1 && (playerInfo[playerid][pRent] == -1 && playerInfo[playerid][pHouse] == -1))
        return sendError(playerid, "Nu ai casa sau nu esti chirias.");

    SCM(playerid, COLOR_GREY, "* Tipul spawn-ului a fost schimbat cu succes!"); 

    playerInfo[playerid][pSpawnType] = e_pSpawnTypes:(listitem + 1);

    va_mysql_tquery("UPDATE `server_users` SET `SpawnType` = %d WHERE `ID` = %d", playerInfo[playerid][pSpawnType], playerInfo[playerid][pSQLID]);
    return 1;
}

Dialog:REPORT(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0: {
            Iter_Add(serverReports, playerid); 

            reportInfo[playerid][rReportType] = REPORT_TYPE_STUCK;  

            SCM(playerid, COLOR_YELLOW, "* Report-ul tau a fost trimis cu succes la administratori.");
            SendAdmins(COLOR_LIGHTRED, "New Report: %s (%d) is stuck.", GetName(playerid), playerid);
        }
        case 1: Dialog_Show(playerid, REPORT1, DIALOG_STYLE_INPUT, "SERVER: Report", "Scrie aici problema pe care o ai:", "Send", "Cancel");
        case 2: Dialog_Show(playerid, REPORT2, DIALOG_STYLE_INPUT, "SERVER: Report", "Scrie ID-ul jucatorului pe care vrei sa il raportezi:", "Send", "Cancel");
    }
    return 1;
}

Dialog:REPORT1(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    if(strlen(inputtext) < 5)
        return sendError(playerid, "Propozitia trebuie sa contina minim 5 caractere.");

    Iter_Add(serverReports, playerid); 

    strcpy(reportInfo[playerid][rReportText], inputtext); 
    reportInfo[playerid][rReportType] = REPORT_TYPE_MESSAGE;

    SCM(playerid, COLOR_YELLOW, "* Report-ul tau a fost trimis cu succes catre administratori.");
    SendAdmins(COLOR_LIGHTRED, "New Report: %s (%d): %s", GetName(playerid), playerid, inputtext);
    return 1;
}

Dialog:REPORT2(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1; 

    new const userID = strval(inputtext);

    if(!isnumeric(inputtext))
        return sendError(playerid, "ID-ul poate contine doar cifre.");

    if(!IsPlayerLogged(userID))
        return sendError(playerid, "Acel player nu este conectat.");

    if(userID == playerid)
        return sendError(playerid, "Nu te poti raporta pe tine.");

    if(playerInfo[userID][pAdmin] || playerInfo[userID][pHelper]) 
        return sendError(playerid, "Acel player este un membru staff, nu il poti raporta.");

    if(reportInfo[userID][rReported])
        return sendError(playerid, "Acel player a fost raportat deja.");

    reportInfo[playerid][rReportType] = REPORT_TYPE_DM; 
    reportInfo[playerid][rReportedPlayer] = userID; 
    reportInfo[userID][rReportedBy] = playerid; 
    reportInfo[userID][rReported] = 1; 

    Iter_Add(serverReports, playerid);

    SCM(playerid, COLOR_YELLOW, "* Report-ul tau a fost trimis cu succes catre administratori."); 
    SendAdmins(COLOR_LIGHTRED, "New Report: %s reported %s (%d) for DM/cheats.", GetName(playerid), GetName(userID), userID);
    return 1;
}

Dialog:CHANGEPASS(playerid, response, listitem, inputtext[]) {
    if(!response)
        return DeletePVar(playerid, "changePassPass");

    if(GetPVarInt(playerid, "changePassPass") == 1) 
        return bcrypt_verify(playerid, "OnChangePass", inputtext, playerInfo[playerid][pPassword]);
    
    if(strlen(inputtext) < 8 || !IsValidPassword(inputtext)) 
        return Dialog_Show(playerid, CHANGEPASS, DIALOG_STYLE_PASSWORD, "SERVER: Change Pass", "Insert your new password in box below:\n{FF0000}Your password must contain one upper letter, one lower letter, one number, and must have at least 8 characters.", "Ok", "Exit");

    return bcrypt_hash(playerid, "OnChangePass", inputtext, BCRYPT_COST);
}

Dialog:HUD(playerid, response, listitem, inputtext[]) {
    if(!response)
        return 1;

    switch(listitem) {
        case 0: {
            playerInfo[playerid][pHUDFps] = !playerInfo[playerid][pHUDFps];

            va_mysql_tquery("UPDATE `server_users` SET `HUDFps` = %d WHERE `ID` = %d", playerInfo[playerid][pHUDFps], playerInfo[playerid][pSQLID]);

            if(!playerInfo[playerid][pHUDFps]) {
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][FpsTD]);

                return SCM(playerid, -1, "Your HUD has been updated! (FPS disabled)");
            }
            
            playerTextdraws[playerid][FpsTD] = CreatePlayerTextDraw(playerid, 2.000000, 432.044616, "~y~...");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][FpsTD], 0.400000, 1.600000);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][FpsTD], 1);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][FpsTD], -16776961);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][FpsTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][FpsTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][FpsTD], 3);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][FpsTD], 1);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][FpsTD]);

            return SCM(playerid, -1, "Your HUD has been updated! (FPS enabled)");
        }
        case 1: {
            playerInfo[playerid][pHUDShowAHp] = !playerInfo[playerid][pHUDShowAHp];

            va_mysql_tquery("UPDATE `server_users` SET `HUDShowAHp` = %d WHERE `ID` = %d", playerInfo[playerid][pHUDShowAHp], playerInfo[playerid][pSQLID]);

            if(!playerInfo[playerid][pHUDShowAHp]) {
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][ArmourTD]); 
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][HealthTD]);

                stop playerVars[playerid][var_healtharmourhudtimer];

                return SCM(playerid, -1, "Your HUD has been updated! (Health & Armour disabled)");
            }

            playerTextdraws[playerid][HealthTD] = CreatePlayerTextDraw(playerid, 577.500000, 64.310974, "...");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][HealthTD], 0.238500, 1.276444);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][HealthTD], 2);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][HealthTD], -1);
            PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][HealthTD], 1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][HealthTD], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][HealthTD], 2);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][HealthTD], 1);
            PlayerTextDrawShow(playerid, playerTextdraws[playerid][HealthTD]);

            playerVars[playerid][var_healtharmourhudtimer] = repeat healthArmourHUDUpdate(playerid);

            return SCM(playerid, -1, "Your HUD has been updated! (Health & Armour enabled)");
        }
        case 2: {
            playerInfo[playerid][pHUDDMG] = !playerInfo[playerid][pHUDDMG];

            va_mysql_tquery("UPDATE `server_users` SET `HUDDMG` = %d WHERE `ID` = %d", playerInfo[playerid][pHUDDMG], playerInfo[playerid][pSQLID]);

            if(!playerInfo[playerid][pHUDDMG]) {
                playerTextDrawDestroy(playerid, playerTextdraws[playerid][DMG]);

                return SCM(playerid, -1, "Your HUD has been updated! (Damage Informer & Ding disabled)");
            }

            playerTextdraws[playerid][DMG] = CreatePlayerTextDraw(playerid, 145.000000, 320.666809, "");
            PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][DMG], 0.240500, 0.921776);
            PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][DMG], 1);
            PlayerTextDrawColor(playerid, playerTextdraws[playerid][DMG], -1);
            PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][DMG], 255);
            PlayerTextDrawFont(playerid, playerTextdraws[playerid][DMG], 1);
            PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][DMG], 1);
            PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][DMG], 1);

            return SCM(playerid, -1, "Your HUD has been updated! (Damage Informer & Ding enabled)");
        }
        case 3: {
            playerInfo[playerid][pHUDSpeedometer] = !playerInfo[playerid][pHUDSpeedometer]; 

            va_mysql_tquery("UPDATE `server_users` SET `HUDSpeedometer` = %d WHERE `ID` = %d", playerInfo[playerid][pHUDSpeedometer], playerInfo[playerid][pSQLID]);

            if(playerInfo[playerid][pHUDSpeedometer]) {
                if(IsPlayerInAnyVehicle(playerid)) 
                    PlayerTextDrawSetString(playerid, playerTextdraws[playerid][kmTD], "mp/h");

                return SCM(playerid, -1, "Your HUD has been updated! (Speedometer: mp/h)");
            }

            if(IsPlayerInAnyVehicle(playerid)) 
                PlayerTextDrawSetString(playerid, playerTextdraws[playerid][kmTD], "km/h");

            return SCM(playerid, -1, "Your HUD has been updated! (Speedometer: km/h)");
        }
        case 4: {
            playerInfo[playerid][pHUDAdminStats] = !playerInfo[playerid][pHUDAdminStats];

            va_mysql_tquery("UPDATE `server_users` SET `HUDAdminStats` = %d WHERE `ID` = %d", playerInfo[playerid][pHUDAdminStats], playerInfo[playerid][pSQLID]);

            if(!playerInfo[playerid][pHUDAdminStats]) {
                TextDrawHideForPlayer(playerid, AStatsTD); 
                TextDrawHideForPlayer(playerid, ReportsTD);

                return SCM(playerid, -1, "Your HUD has been updated! (Admin Stats disabled)");
            }

            TextDrawShowForPlayer(playerid, ReportsTD);

            if(playerInfo[playerid][pAdmin] > 4) 
                TextDrawShowForPlayer(playerid, AStatsTD);

            return SCM(playerid, -1, "Your HUD has been updated! (Admin Stats enabled)");
        }
    }
    return 1;
}

Dialog:EMAIL(playerid, response, listitem, inputtext[]) {
    if(!response)
        return Dialog_Show(playerid, EMAIL, DIALOG_STYLE_INPUT, "SERVER: Register", "Enter your e-mail address below:", "Ok", "");

    if(!IsValidEmail(inputtext)) {
    	sendError(playerid, "Your e-mail address is invalid, please enter a correct e-mail address!");
        return Dialog_Show(playerid, EMAIL, DIALOG_STYLE_INPUT, "SERVER: Register", "Enter your e-mail address below:", "Ok", "");
    }

    strcpy(playerInfo[playerid][pEMail], inputtext); 

    SCMf(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your e-mail address is: %s", inputtext); 

    return Dialog_Show(playerid, AGE, DIALOG_STYLE_INPUT, "SERVER: Age", "Enter your real age below:", "Ok", "");
}

Dialog:AGE(playerid, response, listitem, inputtext[]) {
    new const age = strval(inputtext);

    if(!response || !isnumeric(inputtext) || (age > 40 || age <= 6))
        return Dialog_Show(playerid, AGE, DIALOG_STYLE_INPUT, "SERVER: Age", "Enter your real age below:", "Ok", "");

    playerInfo[playerid][pAge] = age; 

    SCMf(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your age is: %d", playerInfo[playerid][pAge]); 

    return Dialog_Show(playerid, GENDER, DIALOG_STYLE_MSGBOX, "SERVER: Gender", "Please select your character sex below:", "Male", "Female");
}

Dialog:GENDER(playerid, response, listitem, inputtext[]) {
    if(response) {
        playerInfo[playerid][pSkin] = 37; 
        SCM(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your gender is: Male");
    }
    else {
        playerInfo[playerid][pSkin] = 12; 
        SCM(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your gender is: Female");
    }

    playerInfo[playerid][pGender] = response+1;

    SetPlayerSkin(playerid, playerInfo[playerid][pSkin]); 

    return Dialog_Show(playerid, REFERRAL, DIALOG_STYLE_INPUT, "SERVER: Referral", "Insert in the box below the name of the player who brought you on the server:", "Ok", "Cancel");
}

Dialog:REFERRAL(playerid, response, listitem, inputtext[]) {
    playerInfo[playerid][pTutorial] = true;

    if(!response) {
        playerInfo[playerid][pReferral] = '-'; 
        playerInfo[playerid][pReferralSQLID] = -1;

        SCM(playerid, COLOR_GREEN, "REGISTER: {ffffff}Your referral is: -");
    }
    else {
        if(strlen(inputtext) < 3 || strlen(inputtext) > MAX_PLAYER_NAME)
            return Dialog_Show(playerid, REFERRAL, DIALOG_STYLE_INPUT, "SERVER: Referral", "Insert in the box below the name of the player who brought you on the server:\n{FF0000}Invalid name length.", "Ok", "Cancel");

        gQuery[0] = EOS;
        mysql_format(SQL, gQuery, sizeof gQuery, "SELECT (ID) FROM `server_users` WHERE `Name` = BINARY '%e' LIMIT 1", inputtext);
        return mysql_tquery(SQL, gQuery, "searchPlayerNameInDB", "ds", playerid, inputtext);
    }

    TogglePlayerSpectating(playerid, false);

    clearChat(playerid, 3); 

    SCM(playerid, COLOR_GREEN, "SERVER: {ffffff}You are successfully registered!");
    SCMf(playerid, COLOR_GREEN, "SERVER: {ffffff}Welcome, %s.", GetName(playerid)); 

    gQuery[0] = EOS;
    mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_users` SET `EMail` = '%e', `Gender` = %d, `Age` = %d, `Skin` = %d, `Referral` = '-', `ReferralSQLID` = -1, `Tutorial` = 1 WHERE `ID` = %d", playerInfo[playerid][pEMail], playerInfo[playerid][pGender], playerInfo[playerid][pAge], playerInfo[playerid][pSkin], playerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");

    SCM(playerid, COLOR_YELLOW, "* You need to set a 4-digits pin, recommended for your account security.");
    showPlayerPinTextdraws(playerid, PIN_SET_TYPE);
    return 1;
}

Dialog:REGISTER(playerid, response, listitem, inputtext[]) { 
    if(!response)
        return Kick(playerid);

    if(strlen(inputtext) < 8 || !IsValidPassword(inputtext)) 
        return Dialog_Show(playerid, REGISTER, DIALOG_STYLE_PASSWORD, "SERVER: Register", "Hello %s,\nWelcome to rpg.Lurk.ro! Please enter a password for register your account.\n{FF0000}Your password must contain one upper letter, one lower letter, one number, and must have at least 8 characters.", "Register", "Quit", GetName(playerid)); 
    
    return bcrypt_hash(playerid, "OnLoginRegisterPassword", inputtext, BCRYPT_COST, "d", 2);
}

Dialog:LOGIN(playerid, response, listitem, inputtext[]) {
    if(!response)
        return Kick(playerid);

    if(strlen(inputtext) < 8)
        return Dialog_Show(playerid, LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "Your password was invalid!\nPlease enter your correct account password.", "Login", "Quit");
    
    return bcrypt_verify(playerid, "OnLoginRegisterPassword", inputtext, playerInfo[playerid][pPassword]);
}