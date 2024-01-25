// ------------------------------------- //
//              Load Query Function      //
// ------------------------------------- //

query_function load_server_vehicles() {
    new const rows = cache_num_rows();

    if(!rows)
        return print("[MYSQL INFO] No server vehicles were found in the database.");

    for(new x = 0; x < rows; ++x) {
        resetVehicleVars(AddStaticVehicle(cache_get_field_content_int(x, "Model"), cache_get_field_content_float(x, "X"), cache_get_field_content_float(x, "Y"), cache_get_field_content_float(x, "Z"), cache_get_field_content_float(x, "Angle"), cache_get_field_content_int(x, "ColorOne"), cache_get_field_content_int(x, "ColorTwo")));
    }
    return printf("[MYSQL LOADED] Server vehicles loaded: %d", rows);
}

// ------------------------------------- //
//              Commands                 //
// ------------------------------------- //

YCMD:addservervehicle(playerid, params[], help) {
    if(playerInfo[playerid][pAdmin] < 7)
        return sendError(playerid, "Nu ai gradul administrativ necesar pentru a folosii aceasta comanda.");

    if(!IsPlayerInAnyVehicle(playerid))
        return sendError(playerid, "Nu esti intr-un vehicul.");

    new colorOne, colorTwo; if(sscanf(params, "dd", colorOne, colorTwo))
        return sendUsage(playerid, "/addservervehicle <colorone> <colortwo>");

    new 
        vehicleid = GetPlayerVehicleID(playerid),
        model = GetVehicleModel(vehicleid),
        Float:X, Float:Y, Float:Z, Float:Angle;

    GetVehiclePos(vehicleid, X, Y, Z); 
    GetVehicleZAngle(vehicleid, Angle);
    
    va_mysql_tquery("INSERT INTO `server_vehicles` (Model, X, Y, Z, Angle, ColorOne, ColorTwo) VALUES (%d, %f, %f, %f, %f, %d, %d)", model, X, Y, Z, Angle, colorOne, colorTwo);
    return SCMf(playerid, COLOR_GREY, "Vehicle %d (modelid: %d) was succesfully added in database.", vehicleid, model);
}