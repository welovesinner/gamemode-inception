// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>

// ------------------------------------- //
//                Variables              //
// ------------------------------------- //

new
	serverLSPDbar;

// ------------------------------------- //
//                Hooks                  //
// ------------------------------------- //

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	switch(newkeys)
	{
		case KEY_CTRL_BACK:
		{
			if(IsPlayerInRangeOfPoint(playerid, 15.0, 1544.7007, -1630.7527, 13.2983) && playerInfo[playerid][pGroup] == 1) 
			{
				MoveDynamicObject(serverLSPDbar, 1544.7007, -1630.7527, 13.2983, 1, 0.0000, 0.0000, 90.0000);
				defer CloseLSPDBar();
				return 1;
			}
		}
	}
	return 1;
}

// ------------------------------------- //
//               Commands                //
// ------------------------------------- //

YCMD:gate(playerid, params[], help)
{
	if(IsPlayerInRangeOfPoint(playerid, 15.0, 1544.7007, -1630.7527, 13.2983) && playerInfo[playerid][pGroup] == 1)
	{
		MoveDynamicObject(serverLSPDbar, 1544.7007, -1630.7527, 13.2983, 1, 0.0000, 0.0000, 90.0000);
		defer CloseLSPDBar();
	}
	return 1;
}

// ------------------------------------- //
//               Timers                  //
// ------------------------------------- //

timer CloseLSPDBar[10000]() {
	MoveDynamicObject(serverLSPDbar, 1544.7007, -1630.7527, 13.2983, 1.5,0.0000, 90.0200, 90.0000);
	return 1;
}