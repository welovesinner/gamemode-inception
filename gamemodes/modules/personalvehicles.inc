// ------------------------------------- //
//   		    Includes 		  	     //
// ------------------------------------- //

#include <YSI_Coding\y_hooks>

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define MAX_PERSONAL_VEHICLES 100000

// ------------------------------------- //
//   		 Variables and enums         //
// ------------------------------------- //

enum e_pVehicleInfo {
	pv_ID, pv_OwnerPID, pv_ModelID, pv_ColorOne, pv_ColorTwo, pv_Days, pv_Insurance, pv_CarPlate[12],
	Float:pv_Odometer, Float:pv_Health, Float:pv_Fuel, 
	Float:pv_X, Float:pv_Y, Float:pv_Z, Float:pv_Angle, Float:pv_LastX, Float:pv_LastY, Float:pv_LastZ, Float:pv_LastAngle,
	pv_SpawnID, pv_DespawnTime
}

new	
	Vector:personalVehicles[MAX_PLAYERS],
	Iterator:personalVehiclesIDs<MAX_PERSONAL_VEHICLES>,
	Iterator:pVehiclesDespawn<MAX_VEHICLES>,
	personalVehiclesInfo[MAX_PERSONAL_VEHICLES][e_pVehicleInfo],
	dialogPersonalVehicles[MAX_PLAYERS][10],
	pageIndexPersonalVehicles[MAX_PLAYERS],
	personalVehiclesSpawned[MAX_PLAYERS];

// ------------------------------------- //
//   	   Query Functions      		 //
// ------------------------------------- //

query_function loadPlayerVehicles(const playerid, const dbid) {
    if(dbid != playerInfo[playerid][pSQLID])
        return 1;

	new const rows = cache_num_rows();

	if(!rows)
		return 1;

	for(new i = 0, id; i < rows; ++i) {
		id = Iter_Free(personalVehiclesIDs);

		personalVehiclesInfo[id][pv_ID] = cache_get_field_content_int(i, "ID");
		personalVehiclesInfo[id][pv_ModelID] = cache_get_field_content_int(i, "ModelID");
		personalVehiclesInfo[id][pv_ColorOne] = cache_get_field_content_int(i, "ColorOne");
		personalVehiclesInfo[id][pv_ColorTwo] = cache_get_field_content_int(i, "ColorTwo");
		personalVehiclesInfo[id][pv_Days] = cache_get_field_content_int(i, "Days");
		personalVehiclesInfo[id][pv_Insurance] = cache_get_field_content_int(i, "Insurance");

		personalVehiclesInfo[id][pv_Odometer] = cache_get_field_content_float(i, "Odometer");
		personalVehiclesInfo[id][pv_Fuel] = cache_get_field_content_float(i, "Fuel");
		personalVehiclesInfo[id][pv_Health] = cache_get_field_content_float(i, "HP");
		personalVehiclesInfo[id][pv_X] = cache_get_field_content_float(i, "X");
		personalVehiclesInfo[id][pv_Y] = cache_get_field_content_float(i, "Y");
		personalVehiclesInfo[id][pv_Z] = cache_get_field_content_float(i, "Z");
		personalVehiclesInfo[id][pv_Angle] = cache_get_field_content_float(i, "Angle");

		personalVehiclesInfo[id][pv_LastX] = 0.0;

		personalVehiclesInfo[id][pv_OwnerPID] = playerid;

		cache_get_field_content(i, "Plate", personalVehiclesInfo[id][pv_CarPlate], SQL, 16);

		Iter_Add(personalVehiclesIDs, id);
		VECTOR_push_back_val(personalVehicles[playerid], id);
	}
	return 1;
}

query_function insertPlayerPersonalVehicle(const playerid, const dbid, const id, const modelid, const days, const Float:x, const Float:y, const Float:z, const Float:angle) {
	if(dbid != playerInfo[playerid][pSQLID])
        return 1;

    personalVehiclesInfo[id][pv_ID] = cache_insert_id();
	personalVehiclesInfo[id][pv_ModelID] = modelid;
	personalVehiclesInfo[id][pv_ColorOne] = personalVehiclesInfo[id][pv_ColorTwo] = 1;
	personalVehiclesInfo[id][pv_Days] = days;
	personalVehiclesInfo[id][pv_Insurance] = 10;

	personalVehiclesInfo[id][pv_Odometer] = 0.0;
	personalVehiclesInfo[id][pv_Fuel] = 100.9;
	personalVehiclesInfo[id][pv_Health] = 1000.0;
	personalVehiclesInfo[id][pv_X] = x;
	personalVehiclesInfo[id][pv_Y] = y;
	personalVehiclesInfo[id][pv_Z] = z;
	personalVehiclesInfo[id][pv_Angle] = angle;

	personalVehiclesInfo[id][pv_LastX] = 0.0;

	personalVehiclesInfo[id][pv_OwnerPID] = playerid;

	strcpy(personalVehiclesInfo[id][pv_CarPlate], "New Car");

	Iter_Add(personalVehiclesIDs, id);
	VECTOR_push_back_val(personalVehicles[playerid], id);
	return 1;
}

// ------------------------------------- //
//   	   		Functions  		     	 //
// ------------------------------------- //

showPlayerPersonalVehicles(const playerid, &index_start) {
	gDialog = "Vehicle\tStatus\tID\tDespawn Time\n";

	new count;

	for(new Pointer:i, val; VECTOR_foreach_cmp(personalVehicles[playerid], index_start, i); ++index_start) {
		val = MEM_get_val(i);

		if(personalVehiclesInfo[val][pv_SpawnID]) {
			if(IsVehicleOccupied(personalVehiclesInfo[val][pv_SpawnID])) {
				format(gDialog, sizeof gDialog, "%s%s\t{FFFF00}occupied\t%d\t-\n", gDialog, aVehicleNames[personalVehiclesInfo[val][pv_ModelID] - 400], personalVehiclesInfo[val][pv_SpawnID]);
			}
			else {
				format(gDialog, sizeof gDialog, "%s%s\t{14AD11}spawned\t%d\t%s\n", gDialog, aVehicleNames[personalVehiclesInfo[val][pv_ModelID] - 400], personalVehiclesInfo[val][pv_SpawnID], personalVehiclesInfo[val][pv_DespawnTime] > gettime() ? CalculateTime(personalVehiclesInfo[val][pv_DespawnTime] - gettime()) : "now");
			}
		} 
		else {
			format(gDialog, sizeof gDialog, "%s%s\t{FF0000}despawned\tnone\t-\n", gDialog, aVehicleNames[personalVehiclesInfo[val][pv_ModelID] - 400]);
		}

		dialogPersonalVehicles[playerid][count++] = val;

		if(count == 10) {
			if(VECTOR_size(personalVehicles[playerid]) > index_start + 1) 
				strcat(gDialog, "> Next Page\n");
			
			break;
		}
	}

	if(index_start >= 10) 
		strcat(gDialog, "< Previous Page");

	gString[0] = EOS;
	format(gString, sizeof gString, "SERVER: Personal Vehicles (%d-%d)", ((index_start / 10) * 10) + 1, ((index_start / 10) * 10) + 10);

	return Dialog_Show(playerid, PERSONALVEHICLES, DIALOG_STYLE_TABLIST_HEADERS, gString, gDialog, "Select", "Exit");
}

lockPersonalVehicle(const playerid) {
	new const closestvehicleid = !GetPlayerVehicleID(playerid) ? GetClosestVehicle(playerid, 5.0) : GetPlayerVehicleID(playerid);

	if(closestvehicleid != -1 && getPersonalVehicleOwner(closestvehicleid) == playerid) {
		vehicleVars[closestvehicleid][var_carLocked] = !vehicleVars[closestvehicleid][var_carLocked];
		SetVehicleParamsEx(closestvehicleid, -1, -1, -1, vehicleVars[closestvehicleid][var_carLocked], -1, -1, -1);
		SetVehicleParamsForPlayer(closestvehicleid, playerid, 0, 0);

		va_GameTextForPlayer(playerid, "%s~N~%s", 3000, 4, aVehicleNames[personalVehiclesInfo[vehicleVars[closestvehicleid][var_carPersonal]][pv_ModelID] - 400], vehicleVars[closestvehicleid][var_carLocked] ? "~R~LOCKED" : "~G~UNLOCKED");
	}
	return 1;
}

getPersonalVehicleOwner(const vehicleid) {
	if(vehicleVars[vehicleid][var_carPersonal] == -1)
		return -1;

	return personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_OwnerPID];
}

calculateVehicleInsurance(const vehicleid) {
	return (((gettime() - personalVehiclesInfo[vehicleid][pv_Days]) / 86400) * 100) + 10000;
}

destroyPersonalVehicle(const vehicleid) {
	GetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);

	DestroyVehicle(personalVehiclesInfo[vehicleid][pv_SpawnID]);
	personalVehiclesInfo[vehicleid][pv_DespawnTime] = personalVehiclesInfo[vehicleid][pv_SpawnID] = 0;
	personalVehiclesSpawned[personalVehiclesInfo[vehicleid][pv_OwnerPID]] --;
	return 1;
}

setPersonalVehicleOwner(const vehicleid, const playerid) {
	if(personalVehiclesInfo[vehicleid][pv_SpawnID]) {
		personalVehiclesSpawned[personalVehiclesInfo[vehicleid][pv_OwnerPID]] --;
		personalVehiclesSpawned[playerid] ++;
	}

	VECTOR_remove_val(personalVehicles[personalVehiclesInfo[vehicleid][pv_OwnerPID]], vehicleid);
	VECTOR_push_back_val(personalVehicles[playerid], vehicleid);

	personalVehiclesInfo[vehicleid][pv_OwnerPID] = playerid;

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_personal_vehicles` SET `OwnerID` = %d WHERE `ID` = %d", playerInfo[playerid][pSQLID], personalVehiclesInfo[vehicleid][pv_ID]);
	mysql_tquery(SQL, gQuery, "", "");
	return 1;
}

// ------------------------------------- //
//   	   		Commands  		     	 //
// ------------------------------------- //

YCMD:vehicles(playerid, params[], help) {
	if(!VECTOR_size(personalVehicles[playerid]))
		return sendError(playerid, "Nu detii niciun vehicul personal.");

	pageIndexPersonalVehicles[playerid] = 0;
	return showPlayerPersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
}

YCMD:park(playerid, params[], help) {
	if(playerVars[playerid][var_car_spawn_delay] > gettime())
		return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a face asta.", playerVars[playerid][var_car_spawn_delay] - gettime());

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		return sendError(playerid, "Nu esti soferul unui vehicul.");

	new 
		vehicleid = GetPlayerVehicleID(playerid), 
		Float:vehicleHealth;

	if(getPersonalVehicleOwner(vehicleid) != playerid)
		return sendError(playerid, "Nu esti intr-un vehicul personal detinut de tine.");

	GetVehicleHealth(vehicleid, vehicleHealth);

	if(vehicleHealth < 600.0) 
		return sendError(playerid, "Vehiculul tau este avariat.");

	if(playerVars[playerid][var_insafezone])
		return sendError(playerid, "Nu poti parca vehiculul personal intr-o zona protejata.");

	new e_vehicleModelTypes:modeltype = getVehicleModelType(personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_ModelID]);

	if(getVehicleSpeed(vehicleid) || vehicleVars[vehicleid][var_carEngine] && modeltype != VEHICLE_MODEL_TYPE_BIKE)
		return sendError(playerid, "Nu poti parca vehiculul daca se afla in miscare sau motorul nu este oprit.");

	GetVehiclePos(vehicleid, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_X], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Y], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Z]);
	GetVehicleZAngle(vehicleid, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Angle]);

	Iter_Remove(pVehiclesDespawn, vehicleid);

	vehicleid = vehicleVars[vehicleid][var_carPersonal];

	destroyPersonalVehicle(vehicleid);

	personalVehiclesInfo[vehicleid][pv_SpawnID] = createVehicle(personalVehiclesInfo[vehicleid][pv_ModelID], personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle], personalVehiclesInfo[vehicleid][pv_ColorOne], personalVehiclesInfo[vehicleid][pv_ColorTwo], -1, 0, personalVehiclesInfo[vehicleid][pv_Fuel]);
	
	SetVehicleNumberPlate(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_CarPlate]);

	if(modeltype == VEHICLE_MODEL_TYPE_BIKE) {
		vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carEngine] = true;
		SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 1, 0, 0, 1, 0, 0, 0);
	}
	else 
		SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 0, 0, 0, 1, 0, 0, 0);

	SetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);

	vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carLocked] = true;
	vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carPersonal] = vehicleid;

	personalVehiclesInfo[vehicleid][pv_DespawnTime] = gettime() + (5 * 60);
	Iter_Add(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);

	personalVehiclesSpawned[playerid] ++;

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_personal_vehicles` SET `X` = %f, `Y` = %f, `Z` = %f, `Angle` = %f WHERE `ID` = %d", personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle], personalVehiclesInfo[vehicleid][pv_ID]);
	mysql_tquery(SQL, gQuery, "", "");

	playerVars[playerid][var_car_spawn_delay] = gettime() + 5;

	return SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}Your %s (ID: %d) was parked successfully.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID]);
}

YCMD:lock(playerid, params[], help) {
	if(playerVars[playerid][var_car_lock_delay] < GetTickCount()) {
		lockPersonalVehicle(playerid);

		playerVars[playerid][var_car_lock_delay] = GetTickCount() + 500;
	}
	return 1;
}

YCMD:checkv(playerid, params[], help) {
	if(playerInfo[playerid][pAdmin] < 6) 
		return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosi aceasta comanda.");

	new userID; if(sscanf(params, "u", userID))
		return sendUsage(playerid, "/checkv <playerid/name>");

	if(!IsPlayerLogged(userID))
		return sendError(playerid, "Acel player nu este logat.");

	if(userID == playerid)
		return sendError(playerid, "Nu poti folosi aceasta comanda asupra ta.");

	new count = VECTOR_size(personalVehicles[userID]);

	if(!count)
		return sendError(playerid, "Acel player nu are vehicule personale.");

	SCMf(playerid, COLOR_GREY, "%s's personal vehicles (%d vehicles, %d slots):", GetName(userID), count, playerInfo[userID][pVehiclesSlots]);

	count = 0;

	new val;

	VECTOR_foreach(i : personalVehicles[userID]) {
		val = MEM_get_val(i);

		SCMf(playerid, -1, "%d. %s (ID %d, %d days, %.0fkm, %d/%d colors)", ++count, aVehicleNames[personalVehiclesInfo[val][pv_ModelID] - 400], personalVehiclesInfo[val][pv_ID], (gettime() - personalVehiclesInfo[val][pv_Days]) / 86400, personalVehiclesInfo[val][pv_Odometer], personalVehiclesInfo[val][pv_ColorOne], personalVehiclesInfo[val][pv_ColorTwo]);
	}
	return 1;
}

// ------------------------------------- //
//   	   		Dialogs  		     	 //
// ------------------------------------- //

Dialog:PERSONALVEHICLES(playerid, response, listitem, inputtext[]) {
	if(!response)
		return 1;

	if(inputtext[0] == '>') {
		pageIndexPersonalVehicles[playerid] ++;
		return showPlayerPersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
	}
	else if(inputtext[0] == '<') { 
		pageIndexPersonalVehicles[playerid] = ((pageIndexPersonalVehicles[playerid] / 10) * 10) - 10;
		return showPlayerPersonalVehicles(playerid, pageIndexPersonalVehicles[playerid]);
	}

	SetPVarInt(playerid, "choosedListitem", listitem);

	return Dialog_Show(playerid, PERSONALVEHICLESMANAGE, DIALOG_STYLE_LIST, "SERVER: Personal Vehicles Manage", "Vehicle Info\nTow Vehicle (Park location)\nTow Vehicle (Last known location)\nFind Vehicle\nChange Vehicle Plate\nUnstuck Vehicle\nBuy Insurance\nSell Vehicle (to Dealership)\nDespawn Vehicle", "Select", "Exit");
}

Dialog:PERSONALVEHICLESMANAGE(playerid, response, listitem, inputtext[]) {
	if(!response)
		return 1;
	
	new 
		vehicleid = dialogPersonalVehicles[playerid][GetPVarInt(playerid, "choosedListitem")],
		e_vehicleModelTypes:vehicletype = getVehicleModelType(personalVehiclesInfo[vehicleid][pv_ModelID]);

	DeletePVar(playerid, "choosedListitem");

	switch(listitem) {
		case 0: {
			Dialog_Show(playerid, NULL, DIALOG_STYLE_MSGBOX, "SERVER: Vehicle Info", "Model: %s\nID: %d\nColors: %d/%d\nOdometer: %.0f km\nAge: %d days\nInsurance: $%s (%d/10 points)\nMax Speed: %d km/h", "Ok", "", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID], personalVehiclesInfo[vehicleid][pv_ColorOne], personalVehiclesInfo[vehicleid][pv_ColorTwo], personalVehiclesInfo[vehicleid][pv_Odometer], (gettime() - personalVehiclesInfo[vehicleid][pv_Days]) / 86400, formatNumber(calculateVehicleInsurance(vehicleid)), personalVehiclesInfo[vehicleid][pv_Insurance], aVehicleMaxSpeed[personalVehiclesInfo[vehicleid][pv_ModelID] - 400]);
		}
		case 1, 2: {
			if(playerVars[playerid][var_car_spawn_delay] > gettime())
				return sendError(playerid, "Trebuie sa astepti %d secunde inainte de a face asta.", playerVars[playerid][var_car_spawn_delay] - gettime());

			if(personalVehiclesInfo[vehicleid][pv_SpawnID]) {
				if(IsVehicleOccupied(personalVehiclesInfo[vehicleid][pv_SpawnID]))
					return sendError(playerid, "Vehiculul acesta este in uz.");

				GetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);

				if(personalVehiclesInfo[vehicleid][pv_Health] < 250.0) 
					return sendError(playerid, "Nu poti face asta acum.");

				SetVehicleToRespawn(personalVehiclesInfo[vehicleid][pv_SpawnID]);

				vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carFuel] = personalVehiclesInfo[vehicleid][pv_Fuel];
			}
			else {
				if(personalVehiclesSpawned[playerid] >= 5)
					return sendError(playerid, "Nu poti avea mai mult de 5 vehicule personale spawnate."); 

				personalVehiclesInfo[vehicleid][pv_SpawnID] = createVehicle(personalVehiclesInfo[vehicleid][pv_ModelID], personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle], personalVehiclesInfo[vehicleid][pv_ColorOne], personalVehiclesInfo[vehicleid][pv_ColorTwo], -1, 0, personalVehiclesInfo[vehicleid][pv_Fuel]);
				SetVehicleNumberPlate(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_CarPlate]);

				personalVehiclesInfo[vehicleid][pv_DespawnTime] = gettime() + (5 * 60);
				personalVehiclesSpawned[playerid] ++;
			}

			if(listitem == 2 && (personalVehiclesInfo[vehicleid][pv_LastX] != 0.0 && personalVehiclesInfo[vehicleid][pv_LastX] != FLOAT_INFINITY)) {
				SetVehiclePos(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_LastX], personalVehiclesInfo[vehicleid][pv_LastY], personalVehiclesInfo[vehicleid][pv_LastZ]);
				SetVehicleZAngle(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_LastAngle]);

				SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}Vehicle %s (ID: %d) was spawned on the last location found.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID]);
			}
			else 
				SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}Vehicle %s (ID: %d) was spawned on the park location.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID]);
		
			if(vehicletype == VEHICLE_MODEL_TYPE_BIKE) {
				vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carEngine] = true;
				SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 1, 0, 0, 1, 0, 0, 0);
			}
			else 
				SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 0, 0, 0, 1, 0, 0, 0);

			SetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);

			vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carLocked] = true;
			vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carPersonal] = vehicleid;

			Iter_Add(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);

			playerVars[playerid][var_car_spawn_delay] = gettime() + 10; 
		}
		case 3: {
			if(!personalVehiclesInfo[vehicleid][pv_SpawnID]) 
				return sendError(playerid, "Vehiculul acesta nu este spawnat.");

			CheckPlayerCheckpoint(playerid);

			new Float: X, Float: Y, Float: Z;
			GetVehiclePos(personalVehiclesInfo[vehicleid][pv_SpawnID], X, Y, Z);

			SetPlayerCheckpoint(playerid, X, Y, Z, 3.5);
			playerVars[playerid][var_checkpoint] = 1;

			SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}Vehicle %s (ID: %d) was found in location %s. Distance: %0.2fm.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_SpawnID], returnVehicleZoneName(personalVehiclesInfo[vehicleid][pv_SpawnID]), GetPlayerDistanceFromPoint(playerid, X, Y, Z));
		}
		case 4: {
			if(vehicletype == VEHICLE_MODEL_TYPE_BIKE || vehicletype == VEHICLE_MODEL_TYPE_BOAT || vehicletype == VEHICLE_MODEL_TYPE_PLANE)
				return sendError(playerid, "Nu poti face asta pe acest tip de vehicul.");

			SetPVarInt(playerid, "choosedListitem", vehicleid);

			Dialog_Show(playerid, PERSONALVEHICLESPLATE, DIALOG_STYLE_INPUT, "SERVER: Change Plate", "Type below the new number plate you want to set:", "Set", "Exit");
		}
		case 5: {
			if(playerVars[playerid][var_car_unstuck_delay] > gettime()) 
				return sendError(playerid, "Trebuie sa astepti %s inainte de a face asta din nou.", CalculateTime(playerVars[playerid][var_car_unstuck_delay] - gettime()));

			if(!personalVehiclesInfo[vehicleid][pv_SpawnID])
				return sendError(playerid, "Vehiculul nu este spawnat.");

			if(IsVehicleOccupied(personalVehiclesInfo[vehicleid][pv_SpawnID])) 
				return sendError(playerid, "Vehiculul acesta este in uz."); 

			Iter_Remove(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);
			
			GetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);
			
			DestroyVehicle(personalVehiclesInfo[vehicleid][pv_SpawnID]);

			switch(vehicletype) {
				case VEHICLE_MODEL_TYPE_PLANE: setRandomDealershipParkPos(e_dsVehicleTypes:0, personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle]);
				case VEHICLE_MODEL_TYPE_BOAT: setRandomDealershipParkPos(e_dsVehicleTypes:1, personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle]);
				default: setRandomDealershipParkPos(e_dsVehicleTypes:2, personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle]);
			}

			personalVehiclesInfo[vehicleid][pv_SpawnID] = createVehicle(personalVehiclesInfo[vehicleid][pv_ModelID], personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle], personalVehiclesInfo[vehicleid][pv_ColorOne], personalVehiclesInfo[vehicleid][pv_ColorTwo], -1, 0, personalVehiclesInfo[vehicleid][pv_Fuel]);
			SetVehicleNumberPlate(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_CarPlate]);

			if(vehicletype == VEHICLE_MODEL_TYPE_BIKE) {
				vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carEngine] = true;
				SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 1, 0, 0, 1, 0, 0, 0);
			}
			else 
				SetVehicleParamsEx(personalVehiclesInfo[vehicleid][pv_SpawnID], 0, 0, 0, 1, 0, 0, 0);

			SetVehicleHealth(personalVehiclesInfo[vehicleid][pv_SpawnID], personalVehiclesInfo[vehicleid][pv_Health]);

			personalVehiclesInfo[vehicleid][pv_DespawnTime] = gettime() + (5 * 60);
			Iter_Add(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);

			vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carLocked] = true;
			vehicleVars[personalVehiclesInfo[vehicleid][pv_SpawnID]][var_carPersonal] = vehicleid;

			gQuery[0] = EOS;
			mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_personal_vehicles` SET `X` = %f, `Y` = %f, `Z` = %f, `Angle` = %f WHERE `ID` = %d", personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], personalVehiclesInfo[vehicleid][pv_Angle], personalVehiclesInfo[vehicleid][pv_ID]);
			mysql_tquery(SQL, gQuery);

			playerVars[playerid][var_car_unstuck_delay] = gettime() + (5 * 60);

			playerVars[playerid][var_checkpoint] = 1;
			SetPlayerCheckpoint(playerid, personalVehiclesInfo[vehicleid][pv_X], personalVehiclesInfo[vehicleid][pv_Y], personalVehiclesInfo[vehicleid][pv_Z], 3.5);

			SCM(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}The parking positions of your vehicle were successfully resetted. An red marker has");
			SCM(playerid, -1, "... been placed on your vehicle's location.");
		}
		case 6: {
			if(personalVehiclesInfo[vehicleid][pv_Insurance] == 10) 
				return sendError(playerid, "Ai numarul maxim de puncte de asigurare.");

			SetPVarInt(playerid, "choosedListitem", vehicleid);

			Dialog_Show(playerid, PERSONALVEHICLEINSURANCE, DIALOG_STYLE_INPUT, "SERVER: Insurance", "Write below the number of insurance points you want to buy:\n\nYou have now %d/10 insurance points. (1 point = $%s)", "Buy", "Exit", personalVehiclesInfo[vehicleid][pv_Insurance], formatNumber(calculateVehicleInsurance(vehicleid)));
		}
		case 7: {
			SetPVarInt(playerid, "choosedListitem", vehicleid);

			Dialog_Show(playerid, PERSONALVEHICLESELL, DIALOG_STYLE_MSGBOX, "SERVER: Sell Vehicle", "You are sure that you want to sell your vehicle %s (ID %d, %.0f km, %d days) to dealership for $%s money?", "Yes", "No", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID], personalVehiclesInfo[vehicleid][pv_Odometer], (gettime() - personalVehiclesInfo[vehicleid][pv_Days]) / 86400, formatNumber(getPersonalVehicleDsSellPrice(vehicleid)));
		}
		case 8: {
			if(!personalVehiclesInfo[vehicleid][pv_SpawnID]) 
				return sendError(playerid, "Vehiculul acesta nu este spawnat.");

			if(IsVehicleOccupied(personalVehiclesInfo[vehicleid][pv_SpawnID]))
				return sendError(playerid, "Vehiculul acesta este in uz.");

			SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}Vehicle %s (ID: %d) was despawned successfully.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_SpawnID]);

			Iter_Remove(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);
			destroyPersonalVehicle(vehicleid);
		}
	}
	return 1;
}

Dialog:PERSONALVEHICLESPLATE(playerid, response, listitem, inputtext[]) {
	if(!response)
		return DeletePVar(playerid, "choosedListitem");

	if(isnull(inputtext) || strlen(inputtext) > 12) 
		return Dialog_Show(playerid, PERSONALVEHICLESPLATE, DIALOG_STYLE_INPUT, "SERVER: Change Plate", "Type below the new number plate you want to set:\n{FF0000}The length of the number plate needs to be between 1 and 12 characters.", "Set", "Exit");

	new const vehicleid = GetPVarInt(playerid, "choosedListitem"); 

	DeletePVar(playerid, "choosedListitem");

	strcpy(personalVehiclesInfo[vehicleid][pv_CarPlate], inputtext);
	SetVehicleNumberPlate(personalVehiclesInfo[vehicleid][pv_SpawnID], inputtext);

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_personal_vehicles` SET `Plate` = '%e' WHERE `ID` = %d", personalVehiclesInfo[vehicleid][pv_CarPlate], personalVehiclesInfo[vehicleid][pv_ID]);
	mysql_tquery(SQL, gQuery, "", "");

	return sendSplittedMessageToPlayer(playerid, COLOR_GREEN, COLOR_WHITE, "(Personal Vehicles): {FFFFFF}You changed the number plate successfully for vehicle %s. The change will be applied after vehicle respawn.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400]);
}

Dialog:PERSONALVEHICLEINSURANCE(playerid, response, listitem, inputtext[]) {
	if(!response)
		return DeletePVar(playerid, "choosedListitem");

	new 
		points = strval(inputtext),
		vehicleid = GetPVarInt(playerid, "choosedListitem"),
		price = points * calculateVehicleInsurance(vehicleid); 

	if(points < 1 || points > 10) 
		return Dialog_Show(playerid, PERSONALVEHICLEINSURANCE, DIALOG_STYLE_INPUT, "SERVER: Insurance", "Write below the number of insurance points you want to buy:\n\nYou have now %d/10 insurance points. (1 point = $%s)", "Buy", "Exit", personalVehiclesInfo[vehicleid][pv_Insurance], formatNumber(price / points));

	DeletePVar(playerid, "choosedListitem");

	if(points + personalVehiclesInfo[vehicleid][pv_Insurance] > 10) 
		return sendError(playerid, "Nu poti avea mai mult de 10 puncte de asigurare.");

	if(GetMoney(playerid) < price && GetMilliards(playerid) < 1)
		return sendError(playerid, "Nu ai destui bani. Ai nevoie de $%s.", formatNumber(price));

	personalVehiclesInfo[vehicleid][pv_Insurance] += points;

	substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price);

	return SCMf(playerid, COLOR_GREEN, "(Personal Vehicles): {FFFFFF}You bought %d insurance points with $%s money for vehicle %s.", points, formatNumber(price), aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400]);
}

Dialog:PERSONALVEHICLEENTERINS(playerid, response, listitem, inputtext[]) {
	if(!response) {
		DeletePVar(playerid, "choosedListitem");

		slapPlayer(playerid);
		return sendError(playerid, "Nu poti conduce acest vehicul cu asigurarea neplatita.");
	}

	new 
		vehicleid = GetPVarInt(playerid, "choosedListitem"),
		price = calculateVehicleInsurance(vehicleid);

	DeletePVar(playerid, "choosedListitem");

	if(GetMoney(playerid) < price && GetMilliards(playerid) < 1) {
		slapPlayer(playerid);
		return sendError(playerid, "Nu ai destui bani. Ai nevoie de $%s.", formatNumber(price));
	}

	personalVehiclesInfo[vehicleid][pv_Insurance] ++;

	substractMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price);
	return 1;
}

Dialog:PERSONALVEHICLESELL(playerid, response, listitem, inputtext[]) {
	if(!response) 
		return DeletePVar(playerid, "choosedListitem");

	new const vehicleid = GetPVarInt(playerid, "choosedListitem");

	DeletePVar(playerid, "choosedListitem");

	if(personalVehiclesInfo[vehicleid][pv_SpawnID]) {
		if(IsVehicleOccupied(personalVehiclesInfo[vehicleid][pv_SpawnID]))
			return sendError(playerid, "Vehiculul acesta este in uz.");

		Iter_Remove(pVehiclesDespawn, personalVehiclesInfo[vehicleid][pv_SpawnID]);
		destroyPersonalVehicle(vehicleid);
	}

	new const price = getPersonalVehicleDsSellPrice(vehicleid);

	addMoney(playerid, GetMilliards(playerid), GetMoney(playerid), 0, price);

	Iter_Remove(personalVehiclesIDs, vehicleid);
	VECTOR_remove_val(personalVehicles[playerid], vehicleid);

	gQuery[0] = EOS;
	mysql_format(SQL, gQuery, sizeof gQuery, "DELETE FROM `server_personal_vehicles` WHERE `ID` = %d", personalVehiclesInfo[vehicleid][pv_ID]);
	mysql_tquery(SQL, gQuery);

	return sendSplittedMessageToPlayer(playerid, COLOR_GREEN, -1, "(Personal Vehicles): {ffffff}You sold successfully your vehicle %s (ID %d, %.0f km, %d days) to dealership for $%s money.", aVehicleNames[personalVehiclesInfo[vehicleid][pv_ModelID] - 400], personalVehiclesInfo[vehicleid][pv_ID], personalVehiclesInfo[vehicleid][pv_Odometer], (gettime() - personalVehiclesInfo[vehicleid][pv_Days]) / 86400, formatNumber(price));
}

// ------------------------------------- //
//   	   		Callbacks 		     	 //
// ------------------------------------- //

function OnPlayerEnterPersonalVehicle(playerid, vehicleid, bool:passenger) {
	if(!passenger) {
		sendSplittedMessageToPlayer(playerid, -1, -1, "This %s (ID %d) is owned by %s | Age: %d days | Insurance: $%s (%d points) | Colors: %d/%d | Odometer: %.0f km", aVehicleNames[personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_ModelID] - 400], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_ID], GetName(personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_OwnerPID]), (gettime() - personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Days]) / 86400, formatNumber(calculateVehicleInsurance(vehicleVars[vehicleid][var_carPersonal])), personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Insurance], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_ColorOne], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_ColorTwo], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Odometer]);
		
		if(!personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Insurance]) {
			if(getPersonalVehicleOwner(vehicleVars[vehicleid][var_carPersonal]) == playerid) {
				SetPVarInt(playerid, "choosedListitem", vehicleVars[vehicleid][var_carPersonal]);

				Dialog_Show(playerid, PERSONALVEHICLEENTERINS, DIALOG_STYLE_MSGBOX, "SERVER: Insurance", "Your vehicle does not have insurance points anymore.\n\nDo you wish to buy one? (1 point costs $%s).", "Yes", "No", formatNumber(calculateVehicleInsurance(vehicleVars[vehicleid][var_carPersonal])));
			}
			else {
				slapPlayer(playerid);

				sendError(playerid, "Acest vehicul nu are asigurarea platita.");
			}
		}
	}

	if(personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_DespawnTime] != 0) {
		Iter_Remove(pVehiclesDespawn, vehicleid);
		personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_DespawnTime] = 0;
	}
	return 1;
}

function OnPlayerExitPersonalVehicle(playerid, vehicleid, bool:passenger) {
	if(!IsVehicleOccupied(vehicleid)) {
		personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_DespawnTime] = gettime() + (5 * 60);
		Iter_Add(pVehiclesDespawn, vehicleid);

		if(!passenger && personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastX] != FLOAT_INFINITY) {
			GetVehiclePos(vehicleid, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastX], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastY], personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastZ]);
			GetVehicleZAngle(vehicleid, personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastAngle]);
		}
	}
	return 1;
}

// ------------------------------------- //
//   	   		Timers 	 		     	 //
// ------------------------------------- //

task pVehiclesDespawnTimer[60000]() {
	foreach(new i : pVehiclesDespawn) {
		if(personalVehiclesInfo[vehicleVars[i][var_carPersonal]][pv_DespawnTime] < gettime()) {
			destroyPersonalVehicle(vehicleVars[i][var_carPersonal]);
			Iter_SafeRemove(pVehiclesDespawn, i, i);
		}
	}
	return 1;
}

// ------------------------------------- //
//   	   		Hooks 	 		     	 //
// ------------------------------------- //

hook OnPlayerDisconnect(playerid, reason) {
	VECTOR_foreach(i : personalVehicles[playerid]) {
		new const val = MEM_get_val(i);

		Iter_Remove(personalVehiclesIDs, val);

		if(personalVehiclesInfo[val][pv_SpawnID]) {
			Iter_Remove(pVehiclesDespawn, personalVehiclesInfo[val][pv_SpawnID]);

			destroyPersonalVehicle(val);
		}

		if(personalVehiclesInfo[val][pv_Health] < 250.0) 
			personalVehiclesInfo[val][pv_Health] = 1000.0;

		gQuery[0] = EOS;
		mysql_format(SQL, gQuery, sizeof gQuery, "UPDATE `server_personal_vehicles` SET `Odometer` = %f, `Fuel` = %f, `HP` = %f, `Insurance` = %d WHERE `ID` = %d", personalVehiclesInfo[val][pv_Odometer], personalVehiclesInfo[val][pv_Fuel], personalVehiclesInfo[val][pv_Health], personalVehiclesInfo[val][pv_Insurance], personalVehiclesInfo[val][pv_ID]);
		mysql_tquery(SQL, gQuery, "", "");
	}
    
	VECTOR_clear(personalVehicles[playerid]);
	return 1;
}

hook OnVehicleSpawn(vehicleid) {
	if(vehicleVars[vehicleid][var_carPersonal] != -1) 
		personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_DespawnTime] = gettime() + (5 * 60);
	
	return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
	if(vehicleVars[vehicleid][var_carPersonal] != -1) { 
		if(personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Insurance])
			personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_Insurance] --;

		personalVehiclesInfo[vehicleVars[vehicleid][var_carPersonal]][pv_LastX] = FLOAT_INFINITY;
	}
	return 1;
}