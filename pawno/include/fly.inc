// =======================================================================================
// fly.inc
//
// Author: Norck
// Updated by: Sancky (2020)
//
// =======================================================================================
  
ToggleFlyMode(const playerid, bool:toggle = false) {
    playerVars[playerid][b_FLY_MODE] = toggle;

	if(toggle) {
        new 
            Float:x, Float:y, Float:z;

        GetPlayerPos(playerid, x, y, z);
        SetPlayerPos(playerid, x, y, z+5.0);

	    ApplyAnimation(playerid,"PARACHUTE","PARA_steerR", 6.1, 1, 1, 1, 1, 0, 1);

	    Fly(playerid);

	    GameTextForPlayer(playerid, "~y~Fly mode~n~~r~~k~~PED_FIREWEAPON~ ~w~- increase height~n~~r~RMB ~w~- reduce height~n~~r~~k~~PED_SPRINT~ ~w~- increase speed~n~~r~~k~~SNEAK_ABOUT~ ~w~- reduce speed", 5000, 3);
	}
	else {
        stop playerVars[playerid][var_flytimer]; 
        ClearAnimations(playerid);
    }
    return 1;
}
 
SetPlayerLookAt(const playerid, Float:x, Float:y) {
    new 
    	Float:Px, Float:Py, Float: Pa;

    GetPlayerPos(playerid, Px, Py, Pa);

    Pa = floatabs(atan((y-Py)/(x-Px)));

    if(x <= Px && y >= Py)         
    	Pa = floatsub(180.0, Pa);

    else if(x < Px && y < Py)      
    	Pa = floatadd(Pa, 180.0);

    else if(x >= Px && y <= Py)    
    	Pa = floatsub(360.0, Pa);

    Pa = floatsub(Pa, 90.0);

    if(Pa >= 360.0) 
        Pa = floatsub(Pa, 360.0);

    return SetPlayerFacingAngle(playerid, Pa);
}

timer Fly[100](const playerid) {
    if(!IsPlayerConnected(playerid)) {
        stop playerVars[playerid][var_flytimer];
        return 0;
    }

    new 
        k, ud, lr, 
        Float:v_x, Float:v_y, Float:v_z,
        Float:x, Float:y, Float:z;

    GetPlayerKeys(playerid, k, ud, lr);

    if(ud < 0) {
        GetPlayerCameraFrontVector(playerid, x, y, z);
        
        v_x = x + 0.1; 
        v_y = y + 0.1;
    }

    if(k & 128)
        v_z = -0.2;

    else if(k & KEY_FIRE)  
        v_z = 0.2;

    if(k & KEY_WALK)   
        v_x /= 5.0, v_y /= 5.0, v_z /= 5.0;

    if(k & KEY_SPRINT) 
        v_x *= 4.0, v_y *= 4.0, v_z *= 4.0;

    if(v_z == 0.0) 
        v_z = 0.025;

    SetPlayerVelocity(playerid,v_x,v_y,v_z);

    if(v_x == 0.0 && v_y == 0.0) {   
        if(GetPlayerAnimationIndex(playerid) == 959)    
            ApplyAnimation(playerid,"PARACHUTE","PARA_steerR", 6.1, 1, 1, 1, 1, 0, 1);
    }
    else {
        GetPlayerCameraFrontVector(playerid, v_x, v_y, v_z); 
        GetPlayerCameraPos(playerid, x, y, z); 
        SetPlayerLookAt(playerid, v_x*500.0+x, v_y*500.0+y);

        if(GetPlayerAnimationIndex(playerid) != 959)
            ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel", 6.1, 1, 1, 1, 1, 0, 1);
    }

    if(playerVars[playerid][b_FLY_MODE])
        playerVars[playerid][var_flytimer] = defer Fly(playerid);

    return 1;
}