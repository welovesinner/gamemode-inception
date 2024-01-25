//what to do

#include <YSI\y_hooks>

native GetCursorPos(&x, &y);
native IsKeyToggled(key);
native IsLocalKeyDown(key);
native GetSAMPWindowPos(&x, &y);
native GetSAMPWindowSize(&size_x, &size_y);

new PlayerText:paintTextdraw[MAX_PLAYERS][9] = {PlayerText: -1, ...}, 
	PlayerText:paintArtTextdraw[MAX_PLAYERS][4000] = {PlayerText: -1, ...}, 
	Timer:paint[MAX_PLAYERS] = {Timer: -1, ...}, 
	countPaintArt[MAX_PLAYERS] = {-1, ...},
	paintArtColors[] = {-16776961, 16777215, -65281, 16711935, -16711681, 255, 65535}, 
	paintArtColorSelected[MAX_PLAYERS];

YCMD:paint(playerid, params[], help) 
{
	createPaintTextdraws(playerid);
	showPlayerPaintTextdraws(playerid);
	SelectTextDraw(playerid, -1);
	paintArtColorSelected[playerid] = paintArtColors[0];
	paint[playerid] = repeat paintTimer(playerid);
	return 1;
}

YCMD:exitpaint(playerid, params[], help) 
{
	destroyPlayerPaintTextdraws(playerid);
	stop paint[playerid];
	return 1;
}

YCMD:clear(playerid, params[], help) 
{
	while(countPaintArt[playerid] > -1) 
	{
		if(paintArtTextdraw[playerid][countPaintArt[playerid]] == PlayerText: -1)
		{
			continue;
		}
		playerTextDrawDestroy(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]--]);	
	}
	return 1;
}

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid) 
{
	if(playertextid >= paintTextdraw[playerid][2] && playertextid <= paintTextdraw[playerid][8]) 
	{
		SCM(playerid, -1, "clicked");
		paintArtColorSelected[playerid] = paintArtColors[_:playertextid-_:paintTextdraw[playerid][2]];
	}
	return 1;
}

hook OnGameModeInit() {
	print("\n\n\nPaint loaded...\nCreated by Sancky\n\n\n");
}

timer paintTimer[100](const playerid) 
{
	if(countPaintArt[playerid]+1 > sizeof paintArtTextdraw[])
	{
		return 0;
	}

	new 
		_:x, _:y;

	if(IsLocalKeyDown(0x59))
	{
		GetCursorPos(x, y);
		paintArtTextdraw[playerid][++countPaintArt[playerid]] = CreatePlayerTextDraw(playerid, x, y, "astai_ala_pt_desen");
		PlayerTextDrawLetterSize(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 0.000000, 0.064499);
		PlayerTextDrawTextSize(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], x, 0.000000);
		PlayerTextDrawAlignment(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 1);
		PlayerTextDrawColor(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], -1);
		PlayerTextDrawUseBox(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 1);
		PlayerTextDrawBoxColor(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], paintArtColorSelected[playerid]);
		PlayerTextDrawSetShadow(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 0);
		PlayerTextDrawSetOutline(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 0);
		PlayerTextDrawBackgroundColor(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 255);
		PlayerTextDrawFont(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 1);
		PlayerTextDrawSetProportional(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 1);
		PlayerTextDrawSetShadow(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]], 0);
		PlayerTextDrawShow(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]]);
		printf("called");
	}
	printf("%d", IsLocalKeyDown(0x59), IsKeyToggled(0x59));
	printf("%f, %f", x, y);
	return 1;
}

showPlayerPaintTextdraws(const playerid) 
{
	for(new i = 0; i < sizeof paintTextdraw[]; ++i) PlayerTextDrawShow(playerid, paintTextdraw[playerid][i]); 
	return 1;
}

destroyPlayerPaintTextdraws(const playerid) 
{
	for(new i = 0; i < sizeof paintTextdraw[]; ++i) playerTextDrawDestroy(playerid, paintTextdraw[playerid][i]);
	while(countPaintArt[playerid]-- > -1) playerTextDrawDestroy(playerid, paintArtTextdraw[playerid][countPaintArt[playerid]]); 
	return 1;
}

createPaintTextdraws(const playerid) 
{
	paintTextdraw[playerid][0] = CreatePlayerTextDraw(playerid, 185.051223, 86.750022, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][0], 0.000000, 23.352851);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][0], 457.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][0], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][0], -1);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][0], 0);

	paintTextdraw[playerid][1] = CreatePlayerTextDraw(playerid, 188.730895, 90.833335, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][1], 0.000000, 22.415809);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][1], 453.400024, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][1], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][1], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][1], 0);

	paintTextdraw[playerid][2] = CreatePlayerTextDraw(playerid, 186.925323, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][2], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][2], 211.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][2], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][2], -16776961);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][2], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][2], true);

	paintTextdraw[playerid][3] = CreatePlayerTextDraw(playerid, 227.127777, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][3], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][3], 251.202453, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][3], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][3], 16777215);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][3], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][3], true);

	paintTextdraw[playerid][4] = CreatePlayerTextDraw(playerid, 268.730316, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][4], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][4], 292.804992, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][4], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][4], -65281);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][4], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][4], true);

	paintTextdraw[playerid][5] = CreatePlayerTextDraw(playerid, 308.532745, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][5], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][5], 332.607421, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][5], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][5], 16711935);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][5], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][5], true);

	paintTextdraw[playerid][6] = CreatePlayerTextDraw(playerid, 347.835144, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][6], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][6], 371.909820, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][6], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][6], -16711681);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][6], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][6], true);

	paintTextdraw[playerid][7] = CreatePlayerTextDraw(playerid, 388.337615, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][7], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][7], 412.412292, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][7], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][7], 255);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][7], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][7], true);

	paintTextdraw[playerid][8] = CreatePlayerTextDraw(playerid, 428.040039, 310.749908, "box");
	PlayerTextDrawLetterSize(playerid, paintTextdraw[playerid][8], 0.000000, 2.363105);
	PlayerTextDrawTextSize(playerid, paintTextdraw[playerid][8], 452.114715, 0.000000);
	PlayerTextDrawAlignment(playerid, paintTextdraw[playerid][8], 1);
	PlayerTextDrawColor(playerid, paintTextdraw[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, paintTextdraw[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, paintTextdraw[playerid][8], 65535);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, paintTextdraw[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, paintTextdraw[playerid][8], 255);
	PlayerTextDrawFont(playerid, paintTextdraw[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, paintTextdraw[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, paintTextdraw[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, paintTextdraw[playerid][8], true);
	return 1;
}