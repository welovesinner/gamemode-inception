// ------------------------------------- //
//              List Command             //
// ------------------------------------- //

YCMD:animlist(playerid, params[], help) {
    SCM(playerid,COLOR_GREY,"------------------- Anim list: -------------------");
    SCM(playerid,COLOR_WHITE,"/robman, /lifejump, /rcarjack1, /lcarjack1, /rcarjack2, /lcarjack2, /hoodfrisked, ...");
    SCM(playerid,COLOR_WHITE,"/lightcig, /tapcig, /bat, /lean, /dancing, /box, /lowthrow, /highthrow, ...");
    SCM(playerid,COLOR_WHITE,"/leftslap, /handsup, /fall, /fallback, /sup, /rap, /push, /akick, /lowbodypush, ...");
    SCM(playerid,COLOR_WHITE,"/headbutt, /pee, /koface, /kostomach, /kiss, /rollfall, /lay2, /hitch, ...");
    SCM(playerid,COLOR_WHITE,"/beach, /medic, /scratch, /sit, /drunk, /bomb, /arrest, /laugh, /lookout, ...");
    SCM(playerid,COLOR_WHITE,"/aim, /crossarms, /lay, /hide, /vomit, /wave, /shouting, /chant, ...");
    SCM(playerid,COLOR_WHITE,"/frisked, /exhausted, /injured, /slapass, /deal, /dealstance, /crack, /wank, /gro, ...");
    SCM(playerid,COLOR_WHITE,"/sit, /chat, /fucku, /taichi, /knife, /basket, /jumpwater.");
    SCM(playerid,COLOR_GREY,"--------------------------------------------------");
    return 1;
}

// ------------------------------------- //
//              Anims                    //
// ------------------------------------- //

YCMD:carhand(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");
   
    ApplyAnimationEx(playerid,"CAR","Tap_hand",4.1,0,1,1,1,1);
    return 1;
}

YCMD:lifejump(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");
   
    ApplyAnimationEx(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
    return 1;
}

YCMD:robman(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:exhaust(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","IDLE_tired",3.0,1,0,0,0,0);
    return 1;
}

YCMD:rcarjack1(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","CAR_pulloutL_LHS",4.0,0,0,0,0,0);
    return 1;
}

YCMD:lcarjack1(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","CAR_pulloutL_RHS",4.0,0,0,0,0,0);
    return 1;
}

YCMD:rcarjack2(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","CAR_pullout_LHS",4.0,0,0,0,0,0);
    return 1;
}

YCMD:lcarjack2(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","CAR_pullout_RHS",4.0,0,0,0,0,0);
    return 1;
}

YCMD:hoodfrisked(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"POLICE","crm_drgbst_01",4.0,0,1,1,1,0);
    return 1;
}

YCMD:lightcig(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"SMOKING","M_smk_in",3.0,0,0,0,0,0);
    return 1;
}

YCMD:tapcig(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"SMOKING","M_smk_tap",3.0,0,0,0,0,0);
    return 1;
}

YCMD:bat(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"BASEBALL","Bat_IDLE",4.0,1,1,1,1,0);
    return 1;
}

YCMD:lean(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 2)
        return sendUsage(playerid, "/lean <1 or 2>");
   
    ApplyAnimationEx(playerid, strval(params) == 1 ? "GANGS" : "MISC", strval(params) == 1 ? "leanIDLE" : "Plyrlean_loop", 4.0, 0, 1, 1, 1, 0);
    return 1;
}

YCMD:dancing(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 7) 
        return sendUsage(playerid, "/dancing <1 - 7>");
    
    ApplyAnimationEx(playerid, "STRIP", strval(params) == 1 ? "strip_A" : strval(params) == 2 ? "strip_B" : strval(params) == 3 ? "strip_C" : strval(params) == 4 ? "strip_D" : strval(params) == 5 ? "strip_E" : strval(params) == 6 ? "strip_F" : "strip_G", 4.1, 1, 1, 1, 1, 1);
    return 1;
}

YCMD:box(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
    return 1;
}

YCMD:lowthrow(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
    return 1;
}

YCMD:highthrow(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"GRENADE","WEAPON_throw",4.0,0,0,0,0,0);
    return 1;
}

YCMD:leftslap(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","BIKE_elbowL",4.0,0,0,0,0,0);
    return 1;
}

// YCMD:handsup(playerid, params[], help) {
//     if(playerVars[playerid][var_freezed] == true)
//         return 1;

//     if(IsPlayerInAnyVehicle(playerid)) 
//         return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

//     if(isPlayerFalling(playerid)) 
//         return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

//     SetPlayerSpecialAction(playerid,SPECIAL_ACTION_HANDSUP);
//     return 1;
// }

YCMD:fall(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","KO_skid_front",4.1,0,1,1,1,0);
    return 1;
}

YCMD:fallback(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "PED","FLOOR_hit_f", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:laugh(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:lookout(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:aim(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:crossarms(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
    return 1;
}

YCMD:lay(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:hide(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:vomit(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:wave(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:shouting(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"RIOT","RIOT_shout",4.0,1,0,0,0,0);
    return 1;
}

YCMD:chant(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,0);
    return 1;
}

YCMD:frisked(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"POLICE","crm_drgbst_01",4.0,0,1,1,1,0);
    return 1;
}

YCMD:exhausted(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","IDLE_tired",3.0,1,0,0,0,0);
    return 1;
}

YCMD:injured(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:slapass(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:deal(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:dealstance(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
    return 1;
}

YCMD:crack(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:wank(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PAULNMAC", "wank_loop", 1.800001, 1, 0, 0, 1, 600);
    return 1;
}

YCMD:salute(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:gro(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:sup(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 3) 
        return sendUsage(playerid, "/sup <1 - 3>");

    ApplyAnimationEx(playerid, "GANGS", strval(params) == 1 ? "hndshkba" : strval(params) == 2 ? "hndshkda" : "hndshkfa_swt", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:rap(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 4) 
        return sendUsage(playerid, "/rap <1 - 4>");
    
    ApplyAnimationEx(playerid, strval(params) >= 3 ? "GANGS" : "RAPPING", strval(params) == 4 ? "prtial_gngtlkH" : strval(params) == 3 ? "prtial_gngtlkD" : strval(params) == 2 ? "RAP_C_Loop" : "RAP_A_Loop", 4.0, 1, 0, 0, 1, 1);
    return 1;
}

YCMD:push(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
    return 1;
}

YCMD:akick(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
    return 1;
}

YCMD:lowbodypush(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
    return 1;
}

YCMD:headbutt(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"WAYFARER","WF_Fwd",4.0,0,0,0,0,0);
    return 1;
}

YCMD:pee(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    SetPlayerSpecialAction(playerid, 68);
    return 1;
}

YCMD:koface(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
    return 1;
}

YCMD:kostomach(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
    return 1;
}

YCMD:kiss(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"KISSING", "Grlfrd_Kiss_02", 1.800001, 1, 0, 0, 1, 600);
    return 1;
}

YCMD:rollfall(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
    return 1;
}

YCMD:lay2(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
    return 1;
}

YCMD:hitch(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"MISC","Hiker_Pose", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:beach(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"BEACH","SitnWait_loop_W",4.1,0,1,1,1,1);
    return 1;
}

YCMD:medic(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"MEDIC","CPR",4.1,0,1,1,1,1);
    return 1;
}

YCMD:scratch(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"MISC","Scratchballs_01", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:sit(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","SEAT_idle", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:drunk(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","WALK_DRUNK",4.0,1,1,1,1,0);
    return 1;
}

YCMD:bomb(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

YCMD:chat(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","IDLE_CHAT",4.0,0,0,0,0,0);
    return 1;
}

YCMD:fucku(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PED","fucku",4.0,0,0,0,0,0);
    return 1;
}

YCMD:taichi(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
    return 1;
}

YCMD:knife(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 4) 
        return sendUsage(playerid, "/knife <1 - 4>");

    ApplyAnimationEx(playerid, "KNIFE", strval(params) == 1 ? "KILL_Knife_Ped_Damage" : strval(params) == 2 ? "KILL_Knife_Ped_Die" : strval(params) == 3 ? "KILL_Knife_Player" : "KILL_Partial", 4.0, 0, 1, 1, 1, 0);
    return 1;
}

YCMD:basket(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 6) 
        return sendUsage(playerid, "/basket <1 - 6>");
    
    ApplyAnimationEx(playerid, "BSKTBALL", strval(params) == 1 ? "BBALL_idleloop" : strval(params) == 2 ? "BBALL_Jump_Shot" : strval(params) == 3 ? "BBALL_pickup" : strval(params) == 4 ? "BBALL_run" : strval(params) == 5 ? "BBALL_def_loop" : "BBALL_Dnk", 4.0, 1, 0, 0, 0, 0);
    return 1;
}

YCMD:dance(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    if(!isnumeric(params) || strval(params) < 1 || strval(params) > 4) 
        return sendUsage(playerid, "/dance <1 - 4>");

    SetPlayerSpecialAction(playerid, strval(params) == 1 ? SPECIAL_ACTION_DANCE1 : strval(params) == 2 ? SPECIAL_ACTION_DANCE2 : strval(params) == 3 ? SPECIAL_ACTION_DANCE3 : SPECIAL_ACTION_DANCE4);
    return 1;
}

YCMD:jumpwater(playerid, params[], help) {
    if(playerVars[playerid][var_freezed] == true)
        return 1;

    if(IsPlayerInAnyVehicle(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti intr-un vehicul.");

    if(isPlayerFalling(playerid)) 
        return sendError(playerid, "Nu poti folosi animatiile daca esti in cadere.");

    ApplyAnimationEx(playerid,"DAM_JUMP","DAM_LAUNCH",2,0,1,1,0,0);
    return 1;
}

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

stock ApplyAnimationEx(playerid, const animlib[], const animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync=0) {
    if(GetPlayerVehicleID(playerid))
        return 0;

    playerVars[playerid][var_usingAnimation] = true; 
    playerVars[playerid][var_loopingAnimation] = bool:loop;
    return ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
}