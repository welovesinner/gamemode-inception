//TODO: CreateGlobalProgressBar and SetGlobalProgressBarValue

const 
	MAX_GLOBAL_PROGRESS_BARS = 128,

	INVALID_PROGRESS_BAR = -1;

enum e_g_progress_data {
	Text:progress_bar_textdraws_id[7],

	Float:progress_bar_posX,
	Float:progress_bar_posY,
	Float:progress_bar_main_box_width,
	Float:progress_bar_main_box_height,

	Float:progress_bar_value,
	Float:progress_bar_max_value,

	progress_bar_background_colour,
	progress_bar_fill_colour,

	bool:progress_bar_active
}

static 
	g_progressBar_Data[MAX_GLOBAL_PROGRESS_BARS][e_g_progress_data],
	Iterator:g_progressBar_IDs<MAX_GLOBAL_PROGRESS_BARS>;

stock GlobalBar:CreateGlobalProgressBar(Float:x, Float:y, Float:height, Float:width, const background_colour = 0x000000FF, const fill_colour = 0xFFFF00FF, const Float:max_value = 100.0) {
	new const progress_bar_id = Iter_Free(g_progressBar_IDs);

	if(progress_bar_id == INVALID_ITERATOR_SLOT) 
		return GlobalBar:INVALID_PROGRESS_BAR; 

	Iter_Add(g_progressBar_IDs, progress_bar_id);

	g_progressBar_Data[progress_bar_id][progress_bar_posX] = x;
	g_progressBar_Data[progress_bar_id][progress_bar_posY] = y;
	g_progressBar_Data[progress_bar_id][progress_bar_main_box_width] = width;
	g_progressBar_Data[progress_bar_id][progress_bar_main_box_height] = height;

	g_progressBar_Data[progress_bar_id][progress_bar_value] = 0.0;
	g_progressBar_Data[progress_bar_id][progress_bar_max_value] = max_value;

	g_progressBar_Data[progress_bar_id][progress_bar_background_colour] = background_colour;
	g_progressBar_Data[progress_bar_id][progress_bar_fill_colour] = fill_colour;

	_g_ProgressBarCreateTextdraws(progress_bar_id);

	return GlobalBar:progress_bar_id;
}



static _g_ProgressBarCreateTextdraws(bar_id) 
{
	if(!IsValidProgressBar(_:bar_id))
		return 0;

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][0] = TextDrawCreate(g_progressBar_Data[bar_id][progress_bar_posX], g_progressBar_Data[bar_id][progress_bar_posY], "box");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 0.000000, g_progressBar_Data[bar_id][progress_bar_main_box_height]);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], g_progressBar_Data[bar_id][progress_bar_posX] + g_progressBar_Data[bar_id][progress_bar_main_box_width], 0.000000);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], g_progressBar_Data[bar_id][progress_bar_background_colour]);
	TextDrawUseBox(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 1);
	TextDrawBoxColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 255);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 1);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 1);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][0], 0);

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][1] = TextDrawCreate(g_progressBar_Data[bar_id][progress_bar_posX] - 11.0, g_progressBar_Data[bar_id][progress_bar_posY] - 5.0, "LD_BEAT:chit");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 0.000000, 0.000000);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], g_progressBar_Data[bar_id][progress_bar_main_box_width] + 17.0, g_progressBar_Data[bar_id][progress_bar_main_box_width] * 8 + 15.3);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], g_progressBar_Data[bar_id][progress_bar_background_colour]);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 4);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 0);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][1], 0);

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][2] = TextDrawCreate(g_progressBar_Data[bar_id][progress_bar_posX] + g_progressBar_Data[bar_id][progress_bar_main_box_width] - 4.86, g_progressBar_Data[bar_id][progress_bar_posY] - 5.0, "LD_BEAT:chit");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 0.000000, 0.000000);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], g_progressBar_Data[bar_id][progress_bar_main_box_width] + 17.0, g_progressBar_Data[bar_id][progress_bar_main_box_width] * 6.2 + 15.3);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], g_progressBar_Data[bar_id][progress_bar_background_colour]);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 4);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 0);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][2], 0);

	for(new i = 0; i <= 2; ++i) 
		TextDrawShowForAll(g_progressBar_Data[bar_id][progress_bar_textdraws_id][i]);

	/*g_progressBar_Data[bar_id][progress_bar_textdraws_id][3] = TextDrawCreate(246.563262, 277.000518, "LD_BEAT:chit");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 0.000000, 0.000000);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 12.529989, 11.689970);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 16711935);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 4);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 0);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][3], 0);

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][4] = TextDrawCreate(256.062042, 281.516754, "box");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 0.000000, 0.340000);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 379.823730, 7.180069);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 16711935);
	TextDrawUseBox(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 1);
	TextDrawBoxColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 16711935);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 1);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 1);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][4], 0);

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][5] = TextDrawCreate(376.599792, 277.000518, "LD_BEAT:chit");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 0.000000, 0.000000);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 12.529989, 11.689970);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 16711935);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 4);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 0);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][5], 0);

	g_progressBar_Data[bar_id][progress_bar_textdraws_id][6] = TextDrawCreate(250.561706, 280.916717, "box");
	TextDrawLetterSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 0.000000, 0.366999);
	TextDrawTextSize(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 385.311187, 7.180069);
	TextDrawAlignment(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 1);
	TextDrawColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 16711935);
	TextDrawUseBox(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 1);
	TextDrawBoxColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 255);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 0);
	TextDrawSetOutline(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 0);
	TextDrawBackgroundColor(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 255);
	TextDrawFont(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 1);
	TextDrawSetProportional(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 1);
	TextDrawSetShadow(g_progressBar_Data[bar_id][progress_bar_textdraws_id][6], 0);*/
	return 1;
}

IsValidProgressBar(bar_id) 
	return (bar_id != INVALID_PROGRESS_BAR && Iter_Contains(g_progressBar_IDs, bar_id));

YCMD:progress(playerid, params[], help) 
{
	CreateGlobalProgressBar(200.000000, 200.000000, 1.0, 120.000000);
	return 1;
}