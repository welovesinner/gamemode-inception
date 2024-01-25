/*
        *****************
        
	        beaZone
	         v1.0
    Gang Zone Numbers & Borders
    
		    by beaz
    
    
        *****************
*/


#include <a_samp>

#define NUMDIS 40.0
#define MAX_GANGZONES 68

enum zoneInfo
{
	bool:zexist,
	npart[5],
	npart2[5],
	border[4],
}
new zGangZones[1024][zoneInfo];


stock GangZoneCreateEx( Float:gzMinX,Float:gzMinY,Float:gzMaxX,Float:gzMaxY, gznumber , Float:numsize )
{
	new gid = GangZoneCreate(gzMinX,gzMinY,gzMaxX,gzMaxY);
	zGangZones[gid][zexist] = true;

	new Float:centposx,Float:centposy;
	centposx = (gzMinX+gzMaxX) / 2;
	centposy = (gzMinY+gzMaxY) / 2;

	// Borders

	zGangZones[gid][border][0] = GangZoneCreate( gzMinX-2.0, gzMinY, gzMinX+2.0, gzMaxY );
	zGangZones[gid][border][1] = GangZoneCreate( gzMinX-2.0, gzMaxY-2.0, gzMaxX, gzMaxY+2.0 );
	zGangZones[gid][border][2] = GangZoneCreate( gzMaxX-2.0, gzMinY, gzMaxX+2.0, gzMaxY );
	zGangZones[gid][border][3] = GangZoneCreate( gzMinX-2.0, gzMinY-2.0, gzMaxX, gzMinY+2.0 );

	// Numbers

	if(gznumber >= 0 && gznumber <= 9)
	{
	 GangZoneCreateNumber(gid,gznumber,centposx,centposy,numsize);
	}
	else if(gznumber > 9 && gznumber <= MAX_GANGZONES)
	{
	 new temp[3],gznum1[2],gznum2[2];
	 format(temp,sizeof temp,"%d",gznumber);
	 strmid(gznum1,temp,0,1);
	 strmid(gznum2,temp,1,2);

	 GangZoneCreateNumber(gid,strval(gznum1),centposx-(NUMDIS*numsize),centposy,numsize);
	 GangZoneCreateNumber2(gid,strval(gznum2),centposx+(NUMDIS*numsize),centposy,numsize);
	}
	else return gid;

	return gid;
}

stock GangZoneDestroyEx( gangzoneid )
{
  if(zGangZones[gangzoneid][zexist]) // Checking if gang zone was created with numbers and borders.
  {
   // Removing numbers and borders.
   for(new numpart;numpart < 5;numpart++)GangZoneDestroy(zGangZones[gangzoneid][npart][numpart]);
   for(new numpart;numpart < 5;numpart++)GangZoneDestroy(zGangZones[gangzoneid][npart][numpart]); 

   // Removing borders.
   for(new bord;bord < 4;bord++)GangZoneDestroy(zGangZones[ gangzoneid ][border][bord]);

   // Destroying main gang zone.
   GangZoneDestroy(gangzoneid);

   // Setting value to false, which means gang zone doesn't exist.
   zGangZones[gangzoneid][zexist] = false;
  }
}

GangZoneShowForPlayerEx(playerid,gangzoneid,color)
{
GangZoneShowForPlayer(playerid,gangzoneid,color); // showing main gangzone back
if(zGangZones[gangzoneid][zexist]) // if gangzone was created with boarders and numbers
{
	// showing borders
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][border][0],0x00000060);
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][border][1],0x00000060);
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][border][2],0x00000060);
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][border][3],0x00000060);

// showing numbers
for(new nump;nump<5;nump++)
{
if(zGangZones[gangzoneid][npart][nump] != -1)
{
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][npart][nump],0x00000080);
}
if(zGangZones[gangzoneid][npart2][nump] != -1)
{
GangZoneShowForPlayer(playerid,zGangZones[gangzoneid][npart2][nump],0x00000080);
}
}
}
}

GangZoneHideForPlayerEx(playerid,gangzoneid)
{
GangZoneHideForPlayer(playerid,gangzoneid); // showing main gangzone back
if(zGangZones[gangzoneid][zexist]) // if gangzone was created with boarders and numbers
{
	// showing borders
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][border][0]);
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][border][1]);
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][border][2]);
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][border][3]);

// showing numbers
for(new nump;nump<5;nump++)
{
if(zGangZones[gangzoneid][npart][nump] != -1)
{
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][npart][nump]);
}
if(zGangZones[gangzoneid][npart2][nump] != -1)
{
GangZoneHideForPlayer(playerid,zGangZones[gangzoneid][npart2][nump]);
}
}
}
}


stock GangZoneCreateNumber( gzid , gznum , Float:centposx , Float:centposy , Float:numsize )
{
	switch(gznum)
	{
	  case 0:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisx = 15.0*numsize;
		new Float:gsdisy = 20.0*numsize;
        zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy-gsdisy+gztk); // Down of 0
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up of 0
        zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy+gztk,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left of 0
        zGangZones[gzid][npart][3] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy+gztk,centposx+gsdisx+gztk,centposy+gsdisy-gztk); // Right of 0
	  }
	  case 1:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gztk,centposy-gsdisy-gztk,centposx+gztk,centposy+gsdisy+gztk);
	  }
	  case 2:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx+gsdisx-gztk-gztk,centposy+gztk,centposx+gsdisx,centposy+gsdisy-gztk); // Right Stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy+gztk,centposx-gsdisx+gztk+gztk,centposy-gztk); // Left Stick
        zGangZones[gzid][npart][4] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	  case 3:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy-gztk,centposx+gsdisx+gztk+gztk,centposy+gsdisy+gztk); // Stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	  case 4:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx,centposy+gztk,centposx-gsdisx+gztk+gztk,centposy+gsdisy); // Left
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk);// Middle
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy,centposx+gsdisx+gztk+gztk,centposy+gsdisy); // Stick
	  }
	  case 5:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gztk,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left Stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gztk,centposx+gsdisx+gztk,centposy+gztk); // Middle
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy+gztk,centposx+gsdisx+gztk,centposy-gztk); // Right Stick
		zGangZones[gzid][npart][4] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy-gsdisy+gztk); // Down
	  }
	  case 6:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx-gsdisx-gztk-gztk,centposy-gsdisy-gztk,centposx-gsdisx,centposy+gsdisy+gztk); // Main Left Stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
		zGangZones[gzid][npart][4] = GangZoneCreate(centposx+gsdisx-gztk-gztk,centposy-gsdisy+gztk,centposx+gsdisx,centposy-gztk); // Right small stick
	  }
	  case 7:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 15.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy-gztk); // Stick of 1
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up of 1
	  }
	  case 8:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx-gsdisx+gztk,centposy+gsdisy+gztk); // Left stick
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Right stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx+gztk,centposy+gsdisy-gztk,centposx+gsdisx-gztk,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx-gsdisx+gztk,centposy-gztk,centposx+gsdisx-gztk,centposy+gztk); // Center
		zGangZones[gzid][npart][4] = GangZoneCreate(centposx-gsdisx+gztk,centposy-gsdisy-gztk,centposx+gsdisx-gztk,centposy-gsdisy+gztk); // Down
	  }
	  case 9:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left Stick
		zGangZones[gzid][npart][1] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy-gztk,centposx+gsdisx+gztk+gztk,centposy+gsdisy+gztk); // Right Stick
		zGangZones[gzid][npart][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart][3] = GangZoneCreate(centposx-gsdisx+gztk,centposy,centposx+gsdisx,centposy+gztk+gztk); // Middle
		zGangZones[gzid][npart][4] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	}
}

stock GangZoneCreateNumber2( gzid , gznum , Float:centposx , Float:centposy , Float:numsize)
{
	switch(gznum)
	{
	  case 0:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisx = 15.0*numsize;
		new Float:gsdisy = 20.0*numsize;
        zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy-gsdisy+gztk); // Down of 0
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up of 0
        zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy+gztk,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left of 0
        zGangZones[gzid][npart2][3] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy+gztk,centposx+gsdisx+gztk,centposy+gsdisy-gztk); // Right of 0
	  }
	  case 1:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gztk,centposy-gsdisy-gztk,centposx+gztk,centposy+gsdisy+gztk);
	  }
	  case 2:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx+gsdisx-gztk-gztk,centposy+gztk,centposx+gsdisx,centposy+gsdisy-gztk); // Right Stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy+gztk,centposx-gsdisx+gztk+gztk,centposy-gztk); // Left Stick
        zGangZones[gzid][npart2][4] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	  case 3:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy-gztk,centposx+gsdisx+gztk+gztk,centposy+gsdisy+gztk); // Stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	  case 4:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx,centposy+gztk,centposx-gsdisx+gztk+gztk,centposy+gsdisy); // Left
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk);// Middle
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy,centposx+gsdisx+gztk+gztk,centposy+gsdisy); // Stick
	  }
	  case 5:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gztk,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left Stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gztk,centposx+gsdisx+gztk,centposy+gztk); // Middle
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy+gztk,centposx+gsdisx+gztk,centposy-gztk); // Right Stick
		zGangZones[gzid][npart2][4] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy-gsdisy+gztk); // Down
	  }
	  case 6:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx-gsdisx-gztk-gztk,centposy-gsdisy-gztk,centposx-gsdisx,centposy+gsdisy+gztk); // Main Left Stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx,centposy-gztk,centposx+gsdisx,centposy+gztk); // Middle
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx-gsdisx,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
		zGangZones[gzid][npart2][4] = GangZoneCreate(centposx+gsdisx-gztk-gztk,centposy-gsdisy+gztk,centposx+gsdisx,centposy-gztk); // Right small stick
	  }
	  case 7:
	  {
		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 15.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy-gztk); // Stick of 1
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx-gsdisx,centposy+gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Up of 1
	  }
	  case 8:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx-gsdisx+gztk,centposy+gsdisy+gztk); // Left stick
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx+gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx+gztk,centposy+gsdisy+gztk); // Right stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx+gztk,centposy+gsdisy-gztk,centposx+gsdisx-gztk,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx-gsdisx+gztk,centposy-gztk,centposx+gsdisx-gztk,centposy+gztk); // Center
		zGangZones[gzid][npart2][4] = GangZoneCreate(centposx-gsdisx+gztk,centposy-gsdisy-gztk,centposx+gsdisx-gztk,centposy-gsdisy+gztk); // Down
	  }
	  case 9:
	  {
  		new Float:gztk = 4.0*numsize;
		new Float:gsdisy = 20.0*numsize;
		new Float:gsdisx = 25.0*numsize;
		zGangZones[gzid][npart2][0] = GangZoneCreate(centposx-gsdisx-gztk,centposy,centposx-gsdisx+gztk,centposy+gsdisy-gztk); // Left Stick
		zGangZones[gzid][npart2][1] = GangZoneCreate(centposx+gsdisx,centposy-gsdisy-gztk,centposx+gsdisx+gztk+gztk,centposy+gsdisy+gztk); // Right Stick
		zGangZones[gzid][npart2][2] = GangZoneCreate(centposx-gsdisx-gztk,centposy+gsdisy-gztk,centposx+gsdisx,centposy+gsdisy+gztk); // Up
		zGangZones[gzid][npart2][3] = GangZoneCreate(centposx-gsdisx+gztk,centposy,centposx+gsdisx,centposy+gztk+gztk); // Middle
		zGangZones[gzid][npart2][4] = GangZoneCreate(centposx-gsdisx-gztk,centposy-gsdisy-gztk,centposx+gsdisx,centposy-gsdisy+gztk); // Down
	  }
	}
}
