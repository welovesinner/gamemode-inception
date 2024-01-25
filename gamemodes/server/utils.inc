bool:isInRectangleArea(const Float:x, const Float:y, const Float:minX, const Float:maxX, const Float:minY, const Float:maxY) 
    return (x >= minX && x <= maxX && y >= minY && y <= maxY);

bool:isPlayerInRectangleArea(const playerid, const Float:minX, const Float:maxX, const Float:minY, const Float:maxY) {
    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

stock Float:returnPercentage(const value, const max_value) 
    return (float(value) / float(max_value)) * 100.0; 

encryptIPAddress(const ip[]) {
    new 
        encryptedIP[17];

    strcpy(encryptedIP, ip);

    for(new i = 0; encryptedIP[i++];) {
        if(encryptedIP[i] != '.' && random(2)) {
            encryptedIP[i] = random('Z' - 'A' + 1) + 'A';
        }
    }
    return encryptedIP;
}

generateRandomString(dest[], length = sizeof dest, const type, const size = sizeof dest) {
    // Types
    // 0 = Upper Letters
    // 1 = Lower Letters
    // 2 = Upper Letters with Lower Letters
    // 3 = Upper/Lower Letters with Numbers

    if(length == size)
        length --; //empty space for null char

    switch(type) {
        case 0: {
            while(length--) 
                dest[length] = random('Z' - 'A' + 1) + 'A';
        }
        case 1: {
            while(length--) 
                dest[length] = random('z' - 'a' + 1) + 'a';
        }
        case 2: {
            while(length--) 
                dest[length] = !random(2) ? random('Z' - 'A' + 1) + 'A' : random('z' - 'a' + 1) + 'a';
        }
        case 3: {
            while(length--) {
                switch(random(3)) {
                    case 0: dest[length] = random('Z' - 'A' + 1) + 'A';
                    case 1: dest[length] = random('z' - 'a' + 1) + 'a';
                    case 2: dest[length] = random('9' - '0' + 1) + '0';
                }
            }
        }
    }
}

sendSplittedMessageToAll(const first_line_color, const last_line_color, const message[], va_args<>) {
    new 
        string[289];
    
    va_format(string, sizeof string, message, va_start<3>);

    SCMTAf(first_line_color, string);

    if(strlen(string) >= 144) 
        SCMTAf(last_line_color, "... %s", string[143]);

    return 1;
}

sendSplittedMessageToPlayer(const playerid, const first_line_color, const last_line_color, const message[], va_args<>) {
    new 
        string[289];
    
    va_format(string, sizeof string, message, va_start<4>);

    SCMf(playerid, first_line_color, string);

    if(strlen(string) >= 144) 
        SCMf(playerid, last_line_color, "... %s", string[143]);
    
    return 1;
}

returnPlayerZoneName(const playerid) {
    new 
        MapZone:zone_id = GetPlayerMapZone(playerid),
        zone_name[MAX_MAP_ZONE_NAME] = "Unknown";

    if(zone_id != INVALID_MAP_ZONE_ID)
        GetMapZoneName(zone_id, zone_name);

    return zone_name;
}

returnVehicleZoneName(const vehicleid) {
    new 
        MapZone:zone_id = GetVehicleMapZone(vehicleid),
        zone_name[MAX_MAP_ZONE_NAME] = "Unknown";

    if(zone_id != INVALID_MAP_ZONE_ID)
        GetMapZoneName(zone_id, zone_name);

    return zone_name;
}

bool:isPlayerFalling(const playerid) {
    switch(GetPlayerAnimationIndex(playerid)) {
        case 958..979, 1132, 1130, 1195: return true;
    }
    return false;
}

loadPlayerAnimations(const playerid) {
    ApplyAnimation(playerid, "BOMBER", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "RAPPING", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "SHOP", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "BEACH", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "SMOKING", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "FOOD", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "ON_LOOKERS", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "DEALER", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "MISC", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "SWEET", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "RIOT", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "PED", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "POLICE", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "CRACK", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "CARRY", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "COP_AMBIENT", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "PARK", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "FOOD", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "INT_HOUSE", "NULL", 0.0, 0, 0, 0, 0, 0);
    return 1;
}

bool:findAdvert(const text[]) {
    return 
        strfind(text, "bugged", true) != -1 || strfind(text, "nephrite", true) != -1 || strfind(text, "b-hood", true) != -1 || strfind(text, "brotherhood", true) != -1 || strfind(text, "brother-hood", true) != -1 
        || strfind(text, "og-times", true) != -1 || strfind(text, ":7777", true) != -1 || strfind(text, "b-zone", true) != -1 || strfind(text, "crowland", true) != -1;
}

bool:isnumeric(const string[]) 
    return !sscanf(string, "{i}");

stock bool:isalpha(const string[]) {
    for(new i = 0; string[i++];) {
        if(!('A' <= string[i] <= 'Z' || 'a' <= string[i] <= 'z'))
            return false;
    }
    return true;
}

getVehicleOccupantsCount(const vehicleid) {
    new 
        count, modelid = GetVehicleModel(vehicleid) - 400;

    foreach(new i : playersInVehicles) {
        if(GetPlayerVehicleID(i) != vehicleid) 
            continue;

        if(++count == aVehicleSeatsCount[modelid]) 
            break;
    }
    return count;
}

getVehicleSpeed(const vehicleid, const type = 0) {
    new 
        Float:vX, Float:vY, Float:vZ;

    GetVehicleVelocity(vehicleid, vX, vY, vZ);
    return floatround(VectorSize(vX, vY, 0.0) * (!type ? 170.0 : 111.84681456));
}

GetPlayerSpeed(const playerid) {
    new 
        Float: X, Float: Y, Float: Z; 

    GetPlayerVelocity(playerid, X,Y,Z); 
    return floatround(VectorSize(X, Y, Z) * 200.0); 
}

slapPlayer(const playerid) {
    new 
        Float: X, Float: Y, Float: Z;
        
    GetPlayerPos(playerid, X,Y,Z);
    return SetPlayerPos(playerid, X,Y,Z+3);
}

formatNumber(const number) {
    new 
        str[32],
        length;

    format(str, sizeof(str), "%d", number);

    if((length = strlen(str)) < 4)
        return str;

    for(length -= 3; length > 0; length -= 3) 
        strins(str, ".", length);

    return str;
}

sendNearbyMessage(playerid, color, Float:distance, const text[], va_args<>) {
    new 
        str[144], 
        Float:x, Float:y, Float:z;

    va_format(str, sizeof(str), text, va_start<4>);

    GetPlayerPos(playerid, x, y, z);

    foreach(new i : playersStreamed[playerid]) {
        if(IsPlayerInRangeOfPoint(i, distance, x, y, z)) {
            SCM(i, color, str); 
        }
    }
    SCM(playerid, color, str);
    return 1;
}

FixWorldWeather(const hour) {
    SetWorldTime(hour); 
    SetWeather(random(6)); 
    return 1;
}

va_mysql_tquery(const text[], va_args<>) {
    new query[1024];
    mysql_format(SQL, query, sizeof query, text, va_start<1>);
    return mysql_tquery(SQL, query);
}

bool:IsValidEmail(const email[]) {
    new const length = strlen(email);

    if(length < 8 || length > 128)
        return false;

    new const at_pos = strfind(email, "@", true);
    
    return (at_pos >= 1 && strfind(email, ".", true, at_pos+1) > at_pos+1);
}

bool:IsValidPassword(const pass[]) {
    if(isnumeric(pass))
        return false;

    new 
        bool: have_upper_letters,
        bool: have_lower_letters,
        bool: have_numbers;

    for(new i = 0; pass[i]; ++i) {
        if(have_upper_letters && have_lower_letters && have_numbers) 
            return true;

        else if(!have_upper_letters && ('A' <= pass[i] <= 'Z'))
            have_upper_letters = true;

        else if(!have_lower_letters && ('a' <= pass[i] <= 'z'))
            have_lower_letters = true;

        else if(!have_numbers && ('0' <= pass[i] <= '9'))
            have_numbers = true;
    }
    return (have_upper_letters && have_lower_letters && have_numbers);
}

clearChat(playerid, const lines = 20) {
    for(new i; i < lines; i++) 
        SCM(playerid, -1, "");

    return 1;
}

getDateTime() {
    new 
        hour, minute, second,
        year, month, day,
        str[24];

    gettime(hour, minute, second); 
    getdate(year, month, day);
    format(str, sizeof str, "%02d:%02d:%02d %02d/%02d/%d", hour, minute, second, day, month, year);
    return str;
}

CalculateTime(seconds) {
    new time[12];

    if(seconds < 3600) 
        format(time, sizeof time, "%02d:%02d", (seconds / 60) % 60, seconds % 60);
    
    else 
        format(time, sizeof time, "%02d:%02d:%02d", (seconds / 3600), (seconds / 60) % 60, seconds % 60);

    return time;
}

Float:GetDistanceBetweenPlayers(const playerOne, const playerTwo) {
    new 
        Float: X, Float: Y, Float: Z;

    GetPlayerPos(playerTwo, X, Y, Z);
    return GetPlayerDistanceFromPoint(playerOne, X, Y, Z);
}

stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) 
    return VectorSize(x1-x2, y1-y2, z1-z2);

findFunction(playerid, userID)
{
    playerTextdraws[playerid][FindTD][0] = CreatePlayerTextDraw(playerid, 87.000000, 272.755615, "...");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][FindTD][0], 0.170000, 1.058666);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][FindTD][0], 2);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][FindTD][0], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][FindTD][0], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][FindTD][0], 1);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][FindTD][0], 255);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][FindTD][0], 2);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][FindTD][0], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][FindTD][0], 0);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][FindTD][0]);

    playerTextdraws[playerid][FindTD][1] = CreatePlayerTextDraw(playerid, 49.299987, 199.633117, "");
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][FindTD][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, playerTextdraws[playerid][FindTD][1], 73.000000, 70.000000);
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][FindTD][1], 1);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][FindTD][1], -1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][FindTD][1], 0);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][FindTD][1], 0);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][FindTD][1], 0);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][FindTD][1], 5);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][FindTD][1], 0);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][FindTD][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, playerTextdraws[playerid][FindTD][1], GetPlayerSkin(userID));
    PlayerTextDrawSetPreviewRot(playerid, playerTextdraws[playerid][FindTD][1], 0.000000, 0.000000, 0.000000, 1.000000);
    PlayerTextDrawShow(playerid, playerTextdraws[playerid][FindTD][1]);

    playerVars[playerid][var_findon] = userID;
    playerVars[playerid][var_checkpoint] = 1;

    playerVars[playerid][var_find_timer] = repeat findPlayer(playerid);

    SCMf(playerid, COLOR_GREEN, "(Info): {FFFFFF}A red marker has been placed on player %s (%d). Distance: %0.2fkm.", GetName(userID), userID, GetDistanceBetweenPlayers(playerid, userID)/1000);
    return 1;
}

GetClosestVehicle(const playerid, Float:range) {
    if(!Iter_Count(vehiclesStreamed[playerid]))
        return -1;

    new 
        Float: vX, Float: vY, Float: vZ, 
        Float: distance, vehid = -1;

    foreach(new vehicleid : vehiclesStreamed[playerid]) {
        GetVehiclePos(vehicleid, vX, vY, vZ);   

        distance = GetPlayerDistanceFromPoint(playerid, vX, vY, vZ);

        if(distance < range) {
            range = distance;
            vehid = vehicleid;
        }
    }
    return vehid;
}

bool:IsPlayerInRangeOfPlayer(const playerOne, const playerTwo, Float:range) {
    new 
        Float:X, Float:Y, Float:Z;

    GetPlayerPos(playerTwo, X, Y, Z);
    return bool:IsPlayerInRangeOfPoint(playerOne, range, X, Y, Z);
}

e_vehicleModelTypes:getVehicleModelType(const modelid) {
    switch(modelid) {
        case 417, 425, 447, 460, 469, 476, 487, 488, 497, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593: return VEHICLE_MODEL_TYPE_PLANE;
        case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return VEHICLE_MODEL_TYPE_BOAT;
        case 481, 509, 510: return VEHICLE_MODEL_TYPE_BIKE;
        case 448, 461, 462, 463, 468, 471, 521, 522, 523, 581, 586: return VEHICLE_MODEL_TYPE_MOTOR_BIKE;
    }
    return VEHICLE_MODEL_TYPE_CAR;
}

stock ConvertToHours(seconds) {
	new time = seconds, ore, minute, secunde;

	ore = time / 3600; 
	time = time % 3600; 
	minute = time / 60; 
	time = time % 60; 
	secunde = time;

	gString[ 0 ] = (EOS); format(gString, sizeof gString, "%02d:%02d:%02d", ore, minute, secunde);
	return gString; 
}

stock ConvertToMinutes(time) {
    new string[10], minutes, seconds;
    if(time > 59)
    {
        minutes = floatround(time / 60);
        seconds = floatround(time - minutes * 60);
        format(string, sizeof(string), "%02d:%02d", minutes, seconds);
    }
    else
    {
        seconds = floatround(time);
        format(string, sizeof(string), "00:%02d", seconds);
    }
    return string;
}
bool:IsValidWeapon(const weaponid) 
    return !(weaponid < 1 || weaponid > 46 || weaponid == 19 || weaponid == 20 || weaponid == 21 || weaponid == 45);
