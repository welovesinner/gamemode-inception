/*
    DEATH LOOTS
*/

#include <YSI_Coding\y_hooks>

enum E_DEATH_LOOTS
{
    loot_type,
    loot_amount,

    loot_pickup,
    loot_turf
}
new WeaponNames[47][] = {
    "punch","brass knuckles","golf club","nitestick","knife","baseball bat","shovel","pool cue","katana","chainsaw","purple dildo","small white vibrator","large white vibrator","silver vibrator",
    "bouquet of flowers","cane","grenade","tear gas grenade","molotov cocktail","jetpack"," "," ","Colt .45","silenced Colt .45","Deagle","12-gauge shotgun","sawn-off shotgun","Combat Shotgun",
    "Micro Uzi","MP5","AK47","M4","TEC-9","Rifle","sniper rifle","rocket launcher","heatseeker","flamethrower","minigun","satchel charge","detonator","spray can","fire extinguisher",
    "camera","nightvision goggles", "thermal goggles","parachute"
};
new deathLoots[100][E_DEATH_LOOTS],
    Iterator:death_loots<100>;

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
    foreach(new d : death_loots)
    {
        if(pickupid == deathLoots[d][loot_pickup])
        {
            if(deathLoots[d][loot_type] == 1240)
            {
                new Float:hp; 
                GetPlayerHealth(playerid, hp);

                SetPlayerHealth(playerid, hp + 25);

                if(hp > 100) SetPlayerHealth(playerid, 100);
            }

            else
            {
                GivePlayerWeapon(playerid, deathLoots[d][loot_type], deathLoots[d][loot_amount]);

                sendNearbyMessage(playerid, COLOR_PURPLE, 30.0, "* %s picked up a %s with %d ammo.", GetName(playerid), WeaponNames[deathLoots[d][loot_type]], deathLoots[d][loot_amount]);
            }

            DestroyDeathLoot(d);
            break;
        }
    }
}

stock CreateDeathLoot(turf, Float:x, Float:y, Float:z)
{
    new loot = Iter_Free(death_loots), pickup;
    Iter_Add(death_loots, loot);

    if(random(3) == 0)
    {
        pickup = 1240;
        deathLoots[loot][loot_type] = 1240;
        deathLoots[loot][loot_amount] = 25;
    }
    
    else
    {
        new rand_weapon;
        switch(random(4))
        {
            case 0: rand_weapon = 24;
            case 1: rand_weapon = 31;
            case 2: rand_weapon = 33;
            case 3: rand_weapon = 29;
        }

        deathLoots[loot][loot_type] = rand_weapon;
        deathLoots[loot][loot_amount] += random(100) + 50;

        pickup = WeaponObject(rand_weapon);
    }

    deathLoots[loot][loot_pickup] = CreateDynamicPickup(pickup, 23, x, y, z, turf + 50000, -1, -1, 100.0, -1, 0);
    deathLoots[loot][loot_turf] = turf;

    return deathLoots[loot][loot_pickup];
}

// furat de pe net idk
stock WeaponObject(wid) 
{
    if(wid == 1) return 331; 
    else if(wid == 2) return 332; 
    else if(wid == 3) return 333; 
    else if(wid == 5) return 334; 
    else if(wid == 6) return 335; 
    else if(wid == 7) return 336; 
    else if(wid == 10) return 321; 
    else if(wid == 11) return 322; 
    else if(wid == 12) return 323; 
    else if(wid == 13) return 324; 
    else if(wid == 14) return 325; 
    else if(wid == 15) return 326; 
    else if(wid == 23) return 347; 
    else if(wid == 24) return 348; 
    else if(wid == 25) return 349; 
    else if(wid == 26) return 350; 
    else if(wid == 27) return 351; 
    else if(wid == 28) return 352; 
    else if(wid == 29) return 353; 
    else if(wid == 30) return 355; 
    else if(wid == 31) return 356; 
    else if(wid == 32) return 372;
    else if(wid == 33) return 357; 
    else if(wid == 4) return 335; 
    else if(wid == 34) return 358; 
    else if(wid == 41) return 365; 
    else if(wid == 42) return 366; 
    else if(wid == 43) return 367; 
    return 0;
}

stock DestroyDeathLoot(loot)
{
    DestroyDynamicPickup(deathLoots[loot][loot_pickup]);
    Iter_Remove(death_loots, loot);

    deathLoots[loot][loot_type] = 0;
    deathLoots[loot][loot_amount] = 0;
    deathLoots[loot][loot_turf] = 0;
    deathLoots[loot][loot_pickup] = -1;
    return 1;
}

stock DestroyTurfLoots(turf)
{
    foreach(new loot : death_loots)
    {
        if(deathLoots[loot][loot_turf] == turf)
        {
            DestroyDeathLoot(loot);
        }
    }
}