/*
	easyDialog.inc - Dialogs made easier!

	With this useful include, scripters can easily create
	dialogs and show them to players.

	This include will prevent dialog spoofing, ID collision
	and a lot more.

	Created by Emmet on Friday, January 24, 2014.

	Updated by Southclaws 2017-10-13 to add include guard.

	Updated by Sancky 2022-07-31 to improve it.
*/

#if defined _easyDialog_included
	#endinput
#endif
#define _easyDialog_included

#include <YSI_Coding\y_va>
#include <YSI_Coding\y_hooks>

#define Dialog:%0(%1) \
	forward dialog_%0(%1); public dialog_%0(%1)

#define Dialog_Show(%0,%1, \
	Dialog_Open(%0, #%1,

static
	s_DialogName[MAX_PLAYERS][32],
	bool: s_DialogOpened[MAX_PLAYERS]
;

forward OnDialogPerformed(playerid, const dialog[], response, success);

forward Dialog_IsOpened(playerid);
public Dialog_IsOpened(playerid)
{
	return (s_DialogOpened[playerid]);
}

stock Dialog_Close(playerid)
{
	s_DialogName[playerid][0] = EOS;
	s_DialogOpened[playerid] = false;

	#if !defined HidePlayerDialog
		return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, "", "", "", "");
	#else
		return HidePlayerDialog(playerid);
	#endif
}

stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[], va_args<>) 
{
	if(info[0] == EOS)
		return 0;
	
	if(numargs() > 7) {
		static 
			string[4096];

		va_format(string, sizeof string, info, va_start<7>);

		ShowPlayerDialog(playerid, 32700, style, caption, string, button1, button2);
	}
	else {
		ShowPlayerDialog(playerid, 32700, style, caption, info, button1, button2);
	}

	s_DialogOpened[playerid] = true;

	s_DialogName[playerid] = "dialog_";
	strcat(s_DialogName[playerid], function);
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{	
	if(dialogid == 32700 && strlen(s_DialogName[playerid]) > 7)
	{
		s_DialogOpened[playerid] = false;
		if((funcidx("OnDialogPerformed") == -1) || (CallLocalFunction("OnDialogPerformed", "dsdd", playerid, s_DialogName[playerid][7], response, funcidx(s_DialogName[playerid]) != -1)))
		{
	 		CallLocalFunction(s_DialogName[playerid], "ddds", playerid, response, listitem, (!inputtext[0]) ? ("\1") : (inputtext));
		}
	}
	return 1;
}