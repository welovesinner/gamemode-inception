// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <YSI\y_hooks>

// -------------------------------------  //
//             Variables                 //
// -------------------------------------//

new factioncar[MAX_PLAYERS] = -1, vehicleSelected[MAX_PLAYERS][3], 
    factioncargroup[MAX_VEHICLES], vehicleColor[MAX_PLAYERS][2], siren[MAX_PLAYERS],
    objectcar[MAX_VEHICLES], FactionVehicleStock[MAX_GROUPS][3], 
    choosedList[MAX_PLAYERS];

new Float:SfvPos[][] = {
    {-1.0, -1.0, -1.0},
    {1564.4664,-1628.5497,13.3828},
    {617.3942, -588.4787, 17.2330},
    {1189.4696,-1310.5649,13.5625},
    {642.9942,-1348.9720,13.5544},
    {1082.4116,-325.0321,73.9922},
    {2503.4619,-1676.6868,13.3688},
    {2236.6267,-1316.6946,23.9844},
    {1882.5403,-2025.1862,13.3906}
};

//----------------------------------------//
//             Enumerations              //
//--------------------------------------//

enum vehInfo { 
    vehModel, vehColor1, vehColor2, 
    vehGroup, vehRank, vehJob, 
    vehCarID, vehCarIDD, Float:vehPosX, 
    Float:vehPosY, Float:vehPosZ, Float:vehRotation 
};
new VehicleInfo[1000][vehInfo];
new policecar;
//----------------------------------------//
//                Hooks                  //
//--------------------------------------//
hook OnGameModeInit() {
    for(new i; i < sizeof(SfvPos); i++) {
        new ftexst[40];
        switch(i) {
            case 1: ftexst = "Los Santos Police Department";
            case 2: ftexst = "Federal Bureau of Investigations";
            case 3: ftexst = "Paramedic Department";
            case 4: ftexst = "News Reporters";
            case 5: ftexst = "Hitman Agency";
            case 6: ftexst = "Groove Street";
            case 7: ftexst = "Ballas Family";
            case 8: ftexst = "Varrios Los Aztecas";
        }
        gString[0] = EOS;   
        format(gString, sizeof(gString), "{1C8A15}Faction:{ffffff} %s\nType {1C8A15}/sfv{ffffff} to spawn a faction vehicle!", ftexst);
        CreateDynamic3DTextLabel(gString, -1, SfvPos[i][0], SfvPos[i][1], SfvPos[i][2], 40.0); 
        CreateDynamicPickup(19134, 0, SfvPos[i][0], SfvPos[i][1], SfvPos[i][2], 0, 0);
        FactionVehicleStock[i][0] = 5; FactionVehicleStock[i][1] = 5; FactionVehicleStock[i][2] = 5;
    }
    return true; 
}

hook OnPlayerDisconnect(playerid, reason) { 
    DestroySpawnedVehicle(playerid); 
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    new vehicleid = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER) {
        foreach(new i : Player) {
            if(vehicleid == factioncar[i] && playerInfo[playerid][pGroup] != factioncargroup[factioncar[i]] && factioncargroup[factioncar[i]] != 0) {
                SCMf(playerid, -1, "Acasta masina poate fi condusa doar de membrii %s.", NumeFactiune(factioncargroup[factioncar[i]]));
                ClearAnimations(playerid);
            }
        }       
    }
    return true; 
}

hook OnPlayerConnect(playerid) { 
    factioncar[playerid] = -1; choosedList[playerid] = -1; 
    return true; 
}

hook OnVehicleSpawn(vehicleid) {
    foreach(new i : Player) if(factioncar[i] == vehicleid) DestroySpawnedVehicle(i);
    return true; 
}

// ---------------------------------------//
//               Functions               //
// -------------------------------------//

function DestroySpawnedVehicle(playerid) {
    if(factioncar[playerid] != -1) {
        factioncargroup[factioncar[playerid]] = 0; DestroyObject(policecar); DestroyObject(objectcar[factioncar[playerid]]); DestroyObject(objectcar[factioncar[playerid]]); objectcar[factioncar[playerid]] = INVALID_OBJECT_ID; VehicleInfo[factioncar[playerid]][vehGroup] = 0;
        DestroyVehicle(factioncar[playerid]); factioncar[playerid] = -1; vehicleColor[playerid][0] = -1; vehicleColor[playerid][1] = -1; FactionVehicleStock[playerInfo[playerid][pGroup]][choosedList[playerid]]++; choosedList[playerid] = -1;
    }
    return true; 
}

function IsACopCar(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 1) return true;
    } 
    return false; 
}

function Copcar2(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && (VehicleInfo[i][vehGroup] == 1)) return true;
    } 
    return false; 
}

function IsAFbiCar(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 2) return true;
    } 
    return false; 
}

function IsAnAmbulance(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 3) return true;
    } 
    return false; 
}

function IsANewsCar(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 4) return true;
    } 
    return false;
}

function IsAGangCar(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 6 && VehicleInfo[i][vehGroup] == 7 && VehicleInfo[i][vehGroup] == 8) return true;
    } 
    return false;
}
/*function IsAnTaxi(carid) {
    for(new i = 0; i < sizeof VehicleInfo; i++) {
        if(VehicleInfo[i][vehCarID] == carid && VehicleInfo[i][vehGroup] == 13) return true;
    } 
    return false; 
}*/

// ----------------------------------------//
//                 Stocks                 //
// --------------------------------------//

stock factionVehicleModel(member, vehid) {
    foreach(new i : Player) {
        new playerid = i;
        switch(member) {
            case 1: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 411;
                    case 1: vehicleSelected[i][1] = 523;
                    case 2: vehicleSelected[i][2] = 497;
                }
                vehicleColor[playerid][0] = 1; vehicleColor[playerid][1] = 0;
            }
            case 2: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 411;
                    case 1: vehicleSelected[i][1] = 597;
                    case 2: vehicleSelected[i][2] = 490;
                }
                vehicleColor[playerid][0] = 125; vehicleColor[playerid][1] = 125;
            }
            case 3: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 416;
                    case 1: vehicleSelected[i][1] = 416;
                    case 2: vehicleSelected[i][2] = 487;
                }
                vehicleColor[playerid][0] = 176; vehicleColor[playerid][1] = 176;
            }
            case 4: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 582;
                    case 1: vehicleSelected[i][1] = 582;
                    case 2: vehicleSelected[i][2] = 488;
                }
                vehicleColor[playerid][0] = 185; vehicleColor[playerid][1] = 185;
            }
            case 5: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 487;
                    case 1: vehicleSelected[i][1] = 560;
                    case 2: vehicleSelected[i][2] = 579;
                }
                vehicleColor[playerid][0] = 162; vehicleColor[playerid][1] = 162;
            }
            //
            case 6: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 560;
                    case 1: vehicleSelected[i][1] = 567;
                    case 2: vehicleSelected[i][2] = 505;
                }
                vehicleColor[playerid][0] = 252; vehicleColor[playerid][1] = 252;
            }
            //
            case 7: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 560;
                    case 1: vehicleSelected[i][1] = 567;
                    case 2: vehicleSelected[i][2] = 505;
                }
                vehicleColor[playerid][0] = 173; vehicleColor[playerid][1] = 173;
            }
            // 
            case 8: {
                switch(vehid) {
                    case 0: vehicleSelected[i][0] = 560;
                    case 1: vehicleSelected[i][1] = 567;
                    case 2: vehicleSelected[i][2] = 505;
                }
                vehicleColor[playerid][0] = 155; vehicleColor[playerid][1] = 155;
            }
        }
    }   
    return true; 
}

stock factionVehicles(member, veh) {
    new string[20];
    switch(member) {
        case 1: {
            switch(veh) {
                case 0: string = "Infernus";
                case 1: string = "HPV1000";
                case 2: string = "PD Maverick";
            }
        }
        case 2: {
            switch(veh) {
                case 0: string = "Infernus";
                case 1: string = "Police Car";
                case 2: string = "FBI Ranger";
            }
        }
        case 3: {
            switch(veh) {
                case 0: string = "Ambulance";
                case 1: string = "Ambulance";
                case 2: string = "Maverick";
            }
        }
        case 4: {
            switch(veh) {
                case 0: string = "News Van";
                case 1: string = "News Van";
                case 2: string = "News Chopper";
            }
        }
        case 5: {
            switch(veh) {
                case 0: string = "Maverick";
                case 1: string = "Sultan";
                case 2: string = "Huntley";
            }
        }
        case 6: {
            switch(veh) {
                case 0: string = "Sultan";
                case 1: string = "Savanna";
                case 2: string = "Rancher Lure";
            }
        }
        case 7: {
            switch(veh) {
                case 0: string = "Sultan";
                case 1: string = "Savanna";
                case 2: string = "Rancher Lure";
            }
        }
        case 8: {
            switch(veh) {
                case 0: string = "Sultan";
                case 1: string = "Savanna";
                case 2: string = "Rancher Lure";
            }
        }
    }
    return string; 
}

// ----------------------------------------//
//               Commands                 //
// --------------------------------------//

YCMD:sfv(playerid, params[], help) {
    if(playerInfo[playerid][pGroup] == 0/* || playerInfo[playerid][pGroup] == 6 || playerInfo[playerid][pGroup] == 7 || playerInfo[playerid][pGroup] == 8*/) return SCMf(playerid, -1, "Nu esti intr-o factiune sau factiunea ta nu beneficeaza de aceasta functie.");
    if(!Iter_Contains(DutyMember, playerid)) return SCMf(playerid, -1, "Trebuie sa fii la datorie pentru a folosi aceasta comanda.");
    if(IsPlayerInAnyVehicle(playerid)) return SCMf(playerid, -1, "Nu poti folosi aceasta comanda dintr-un vehicul.");
    if(factioncar[playerid] != -1) return SCMf(playerid, -1, "Nu poti avea mai multe vehicule ale factiunii spawnate, foloseste comanda /dfv.");
    if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SCMf(playerid, -1, "Nu poti folosi aceasta comanda dintr-un interior sau din virtual world.");
    new z = playerInfo[playerid][pGroup];
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, SfvPos[z][0], SfvPos[z][1], SfvPos[z][2])) return SCMf(playerid, -1, "Nu esti in locul potrivit pentru a folosi aceasta comanda (in apropierea pickup-ului de la hq).");
    new szDialog[40], szDialog2[200];
    strcat(szDialog2, "#\tVehicle\tRank\tStock\n");
    for(new i = 0; i < 3; i++) {
        factionVehicleModel(playerInfo[playerid][pGroup], i);
        format(szDialog, sizeof(szDialog), "%d.\t%s\t1\t%d in stock\n", i+1, factionVehicles(playerInfo[playerid][pGroup], i), FactionVehicleStock[playerInfo[playerid][pGroup]][i]);
        strcat(szDialog2, szDialog);
    }
    Dialog_Show(playerid, DIALOG_SFV, DIALOG_STYLE_TABLIST_HEADERS, "Vehicles:", szDialog2, "spawn", "back");
    return true; 
}      

YCMD:dfv(playerid, params[], help) {
    if(playerInfo[playerid][pGroup] == 0) return SCMf(playerid, -1, "Nu faci parte dintr-o factiune.");
    if(!Iter_Contains(DutyMember, playerid)) return SCMf(playerid, -1, "Trebuie sa fii la datorie pentru a folosi aceasta comanda.");
    if(factioncar[playerid] == -1) return SCMf(playerid, -1, "Nu ai un vehicul al factiunii spawnat!");
    DestroySpawnedVehicle(playerid); SCMf(playerid, COLOR_RED, "Vehiculul tau de factiune a fost distrus!");
    return true;
}

// -------------------------------------  //
//               Dialogs                 //
// -------------------------------------//

Dialog:DIALOG_SFV(playerid, response, listitem, inputtext[]) {
    if(!response) return true;
    if(FactionVehicleStock[playerInfo[playerid][pGroup]][listitem] == 0) return SCMf(playerid, -1, "Acest vehicul nu mai este in stock-ul factiunii.");

    new Float:X, Float:Y, Float:Z, string[144];
    GetPlayerPos(playerid, X, Y, Z);
    factionVehicleModel(playerInfo[playerid][pGroup], listitem);
    factioncar[playerid] = createVehicle(vehicleSelected[playerid][listitem], X,Y,Z, 0.0, vehicleColor[playerid][0], vehicleColor[playerid][1], 0);
    FactionVehicleStock[playerInfo[playerid][pGroup]][listitem]--;
    PutPlayerInVehicle(playerid, factioncar[playerid], 0);
    factioncargroup[factioncar[playerid]] = playerInfo[playerid][pGroup];
    format(string, sizeof(string), "Faction:{ffffff} You spawned an %s (vehicleId: %d | vehicleModel: %d | vehicleGroup: %d | vehicleRank: 1).", factionVehicles(playerInfo[playerid][pGroup], listitem), factioncar[playerid], vehicleSelected[playerid][listitem], factioncargroup[factioncar[playerid]] );
    SCMf(playerid, COLOR_GREEN, string); choosedList[playerid] = listitem;
    SCMf(playerid, COLOR_LIGHTRED, "Daca nu merge sa deschizi poarta pe tasta H, foloseste comanda /gate.");
    format(string, 50, "{ff0000}Faction #%d", playerInfo[playerid][pGroup]);
    SetVehicleNumberPlate(factioncar[playerid], string);
    SetVehicleHealth(factioncar[playerid], 1500);
    VehicleInfo[factioncar[playerid]][vehGroup] = playerInfo[playerid][pGroup];
    VehicleInfo[factioncar[playerid]][vehCarID] = factioncar[playerid];
    switch(vehicleSelected[playerid][listitem]) {
        case 411: {
            if(factioncargroup[factioncar[playerid]] == 1 || factioncargroup[factioncar[playerid]] == 2 || factioncargroup[factioncar[playerid]] == 3 || factioncargroup[factioncar[playerid]] == 8) {
                objectcar[GetPlayerVehicleID(playerid)] = CreateObject(19419, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0);
                AttachObjectToVehicle(objectcar[GetPlayerVehicleID(playerid)], factioncar[playerid],  0.010000, -0.060000, 0.689999, 0.000000, 0.000000, 0.000000);
                policecar = CreateObject(19327, -2597.0762, -2638.4270, -5.3536, -87.6999, 90.4001, -87.1805);
                SetObjectMaterialText(policecar, "POLICE", 0, OBJECT_MATERIAL_SIZE_256x128, "Arial", 40, 1, -16777216, 0, 1);
                AttachObjectToVehicle(policecar, VehicleInfo[playerid][vehCarID], 0.000000, -1.984998, 0.229999, -85.424964, 0.000000, 0.000000);
            }       
        }
        case 560: {
            if(factioncargroup[factioncar[playerid]] == 13) {
                objectcar[GetPlayerVehicleID(playerid)] = CreateObject(19308, 0.00000, 0.00000, 0.00000,0.00000, 0.00000, 0.00000);
                AttachObjectToVehicle(objectcar[GetPlayerVehicleID(playerid)], factioncar[playerid], 0.000000, -0.249999, 0.949999, 0.000000, 0.000001, 90.449951); 
            }   
        }
    }
    return 1;
}