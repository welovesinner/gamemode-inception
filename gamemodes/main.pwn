// ------------------------------------- //
//             Includes                  //
// ------------------------------------- //

#include <a_samp>
#include <a_mysql> 

#include <omp>

#define YSI_MALLOC_SECURE

#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Visual\y_commands>
#include <YSI_Core\y_utils>
#include <YSI_Coding\y_stringhash>

#include <streamer>
#include <easyDialog>
#include <sscanf2> 
#include <map-zones>
#include <bcrypt>
#include <map>
#include <vector>
#include <queue>
#include <sort-array>
#include <colandreas>
#include <crashdetect>
#include <beaZone>

// ------------------------------------- //
//               Macros                  //
// ------------------------------------- //

DEFINE_HOOK_REPLACEMENT(OnPlayer, OP_);

#define CheckPlayerCheckpoint(%0) \
    if(playerVars[playerid][var_checkpoint] != -1) \
        return Dialog_Show(%0, CHECKPOINT, DIALOG_STYLE_MSGBOX, "SERVER: Checkpoint", "You have an active checkpoint. If you want to remove it press 'Ok'.", "Ok", "Cancel")

#if defined stop 
    #undef stop
#endif 
    
#define stop%0; \
    if(%0 != Timer: 0) { \
        KillTimer(_:%0); \
        %0 = Timer: 0; \
    }


#if defined INITIALISE_GAMEMODE_DELAY 
    #warning "OnGameModeInit initialise delay is activated."
#endif
#define DEBUG
#if defined DEBUG 
    #warning "Debug mode is activated."
#endif

#define PRESSED(%0) (newkeys & %0)
#define RELEASED(%0) (oldkeys & %0)

#define function%0(%1)                  forward %0(%1); public %0(%1)
#define query_function                  function

#define SCMf                            va_SendClientMessage
#define SCM                             SendClientMessage
#define SCMTAf                          va_SendClientMessageToAll
#define SCMTA                           SendClientMessageToAll

#define strsame(%0,%1,%2)               (!strcmp(%0, %1, %2))
#define GetName(%0)                     playerInfo[%0][pName]
#define GetPlayerIP(%0)                 playerInfo[%0][pIPAddress]
#define GetMoney(%0)                    playerInfo[%0][pMoney]
#define GetMilliards(%0)                playerInfo[%0][pMoneyStore]

#define getPlayerLastVehicle(%0)        anticheatInfo[%0][ac_lastvehicle]

#define GetVehicleName(%0)              aVehicleNames[GetVehicleModel(%0) - 400]
#define HOST
#if defined LOCALHOST
    #define MYSQL_HOST                  "localhost"
    #define MYSQL_USER                  "root"
    #define MYSQL_PASSWORD              ""
    #define MYSQL_DATABASE              "inception"
    #define SERVER_HOSTNAME             "lurk.ro - working"
#elseif defined HOST 
    #define MYSQL_HOST                  "5.9.8.124"
    #define MYSQL_USER                  "u2094707_zqOpFLKiPV"
    #define MYSQL_PASSWORD              "g3M^vDHwX!4r^7JGq7J7bEqv"
    #define MYSQL_DATABASE              "s2094707_db1704286925767"
    #define SERVER_HOSTNAME             "lurk.ro - working"
#endif

#define SERVER_PASSWORD                 "1234"
#define SERVER_VERSION                  "0.10.278 alpha"
#define SERVER_LANGUAGE                 "RO/EN"
#define SERVER_WEBURL                   "lurk.ro"

#define REPORT_TYPE_DELETED             -1
#define REPORT_TYPE_MESSAGE             1
#define REPORT_TYPE_DM                  2
#define REPORT_TYPE_STUCK               4

#define MAX_QUESTIONS                   20
#define MAX_REPORTS                     20
#define MAX_SKINS                       5

#define COLOR_ANNOUNCE                  0xA9C4E4FF
#define COLOR_TEAL                      0x67AAB1FF
#define COLOR_GREY                      0xAFAFAFFF
#define COLOR_ERROR                     0xFFFFCCFF
#define COLOR_SERVER                    0x996600FF
#define COLOR_GREEN                     0x1C8A15FF
#define COLOR_DARKGREEN                 0x256E20FF
#define COLOR_RED                       0xFF0000FF
#define COLOR_YELLOW                    0xFFFF00AA
#define COLOR_WHITE                     0xFFFFFFAA
#define COLOR_BLUE                      0x0000BBAA
#define COLOR_LIGHTBLUE                 0x33CCFFAA
#define COLOR_ORANGE                    0xFF9900AA
#define COLOR_DARKRED                   0x990000FF
#define COLOR_PURPLE                    0xC2A2DAAA
#define COLOR_BLACK                     0x000000AA
#define COLOR_BROWN                     0xC17532FF
#define COLOR_CORAL                     0xFF7F50AA
#define COLOR_GOLD                      0xB8860BAA
#define COLOR_GREENYELLOW               0xADFF2FAA
#define COLOR_LAWNGREEN                 0x7CFC00AA
#define COLOR_LIMEGREEN                 0x32CD32AA 
#define COLOR_MIDNIGHTBLUE              0X191970AA
#define COLOR_ADMINCHAT                 0xFFC266AA
#define COLOR_HELPERCHAT                0xF2A35EFF
#define COLOR_PINK                      0xFFC0CBAA 
#define COLOR_LIGHTRED                  0xFF6347FF
#define COLOR_LOGS                      0xE6833CFF
#define COLOR_CLIENT                    0xA9C4E4FF
#define COLOR_LGREEN                    0xD7FFB3FF
#define COLOR_GREENTWO                  0x00D900FF
#define COLOR_RADIO                     0x8D8DFFFF
#define COLOR_D                         0xff353535
#define COLOR_GENANNOUNCE               0xA9C4E4FF

#define INDEX_HELMET                    1
#define INDEX_PHONE                     2
#define INDEX_JOB                       3
 
#define BODY_PART_HEAD                  9
#define BODY_PART_RIGHT_LEG             8
#define BODY_PART_LEFT_LEG              7
#define BODY_PART_RIGHT_ARM             6
#define BODY_PART_LEFT_ARM              5
#define BODY_PART_GROIN                 4
#define BODY_PART_TORSO                 3

#define FEMALE_GENDER                   1
#define MALE_GENDER                     2

// ------------------------------------- //
//                Enums                  //
// ------------------------------------- //

enum e_pInfo {
    Cache:pSQLLoginCache, pSQLID, pName[MAX_PLAYER_NAME], pIntIP, pIPAddress[16], pPassword[65], pEMail[128], pReferral[MAX_PLAYER_NAME], pReferralSQLID, pReferralRespectPoints, pReferralCash, bool:pTutorial, pGender, pSkin, pAdmin, pHelper, pRespectPoints, pLevel, pMoney, pMoneyStore, pBank, pBankStore, 
    Float:pHours, Float:pSeconds, pDrivingLicense, pWeaponLicense, pFlyLicense, pBoatLicense, pMute, pWarn, pLoginTries, pAFKSeconds, pPlayersHelped, 
    pHouse, pBusiness, pRent, e_pSpawnTypes:pSpawnType, pAge, pHelperWarns, pAdminWarns, bool:pPhoneBook, pPhoneNumber, pPhoneCredit, pGroup, pGroupRank,
    pGroupJoin, pFactionWarns, pFactionPunish, pFactionRaport1, pFactionRaport2, pFactionRaport3, pRaportPlaying,
    pFrequency, bool:pWalkieTalkie, pFightingStyle, pJob, pFarmerSkill, pFishermanSkill, pFiremanSkill, pBusDriverSkill, pHunterSkill, pCourierSkill, pDrugs, pDrugsDealerSkill, pMaterials, pArmsDealerSkill, 
    pTruckerSkill, pRepairKits, pDayQuest, pQuestProgress[3], pQuestType[3], pReportMute, pQuestionMute, pPin, pVehiclesSlots, bool:pHUDFps, bool:pHUDAdminStats, bool:pHUDShowAHp, bool:pHUDDMG, bool:pHUDSpeedometer, bool:pTOGFind, bool:pTOGSurf, bool:pTOGPay,
    pPremiumPoints, pWantedLevel, pCrime1[48], pCrime2[48], pCrime3[48], pJailTime, pWantedExpire, pHeadValue,

    Timer:pLoginTimer,

    Float:pLastPosX, Float:pLastPosY, Float:pLastPosZ
}

enum e_rInfo {
    rReportText[128], rReportType, rReportConversation, rReportedPlayer, rReported, rReportedBy
}

enum e_pVars {
    var_chat_last[144], var_SpectatePlayer, var_FPS, var_drunklevel, var_inhouse, var_spectateMe, var_warningtimer,
    var_inbizz, var_precedentskin, var_precedentweapon, var_objectweapon, Timer:var_flytimer, bool:var_insafezone, bool:var_delay, bool:var_death, bool:var_usingAnimation, bool:var_loopingAnimation, var_QuestionText[128],
    var_incall, var_calls, var_callfrom, var_placed_ad[144], Timer:var_ad_timer, var_dice_invited, var_dice_money, var_checkpoint, bool:var_freezed, var_rentedcar, var_rentlistitem, var_rentedcarbusiness, var_rentedcartime, var_findon, var_fishkg,
    bool:var_working, var_jobvehicle, var_jobseconds, var_jobtime, var_jobexitvehicletime, var_busdrivercheckpoint, var_jobobject, var_courierstuff, bool:var_have_seeds, var_planted_seeds_time,
    var_sell_drugs, var_sell_drugs_money, var_sell_drugs_value, var_arms_dealer_materials, var_arms_dealer_money, var_sell_mats, var_sell_mats_money, var_sell_mats_value, var_cigarettes, var_cigarettes_delay, Timer:var_spectatetimer, Timer:var_drugs_dealer_timer, Timer:var_jobtimer,
    Timer:var_find_timer, Timer:var_renttimer, var_trucker_trailer, var_trucker_cash_bonus, var_trucker_chat_delay, var_spectateseconds, bool:var_gascan, var_repair_invited, var_repair_price, var_courierhouse, Timer:var_healtharmourhudtimer,
    Timer:var_jobtimerchecks, Timer:var_speedometertimer, Timer:var_damageinformer_timer,

    //booleans
    bool:b_FLY_MODE, bool:b_ADMIN_DUTY, bool:b_HELPER_DUTY, bool:b_HELMET_ON, bool:b_IS_SLEEPING, bool:b_CLOTHES_SHOW, bool:b_GUNSHOP_SHOW, bool:b_PHONE_TURN, bool:b_SPEED_BOOST, bool:b_PHONE_SPEAKER, bool:b_FISHING, bool:b_ACTIVE_TIMER, bool:b_ARMS_DEALER_WORKING,

    //delay vars
    var_engine_delay, var_kick_delay, var_me_delay, var_shout_delay, var_time_delay, var_changepass_delay, var_ban_delay, var_buy_delay, var_wt_delay,
    var_house_delay, var_ph_delay, var_chat_delay, var_sleep_delay, var_pay_delay, var_heal_delay, var_radio_delay, var_bank_delay, var_bizz_delay, var_atm_delay,
    var_gunshop_delay, var_warn_delay, var_unwarn_delay, var_mute_delay, var_report_delay, var_nmute_delay, var_hduty_delay, var_rmute_delay, var_aduty_delay, var_call_delay, var_sms_delay, var_dice_delay,
    var_pns_delay, var_incall_delay, var_addfriend_delay, var_repair_delay, var_gunshopopened_delay, var_work_delay, var_car_lock_delay, var_car_spawn_delay,
    var_car_unstuck_delay
}

enum e_vVars {
    bool:var_carEngine, bool:var_carLights, bool:var_carBoot, bool:var_carBoonet, bool:var_carLocked,
    var_carRadio, Float:var_carFuel, var_carPersonal
}

enum e_sStuff {
    houses, business, sVars, safeZones, jobs, dealershipVehiclesModels
}

enum e_pTD {
    PlayerText:NameTD, PlayerText:SpecTD, PlayerText:FpsTD, PlayerText:SpeedTD, PlayerText:SpeedometerTD, PlayerText:kmTD,
    PlayerText:HealthTD, PlayerText:ArmourTD, PlayerText:ClothesTD[8], PlayerText:GunShopTD[8], PlayerText:FindTD[2], PlayerText:DMG,
    PlayerText:JobTD, PlayerText:FriendsTD, PlayerText:LoginQueuePositionTD, PlayerText:PinTD[19], PlayerText:dealerShipTD[9]
}

enum e_pLabels {
    Text3D:l_death, Text3D:l_drugs_dealer
}   

enum e_pkInfo {
    pk_Job, pk_House, pk_Bizz, pk_Rent
}

enum e_pSpawnTypes {
    SPAWN_TYPE_NORMAL = 1,
    SPAWN_TYPE_HOUSE
}

enum e_vehicleModelTypes {
    VEHICLE_MODEL_TYPE_CAR,
    VEHICLE_MODEL_TYPE_BIKE,
    VEHICLE_MODEL_TYPE_PLANE,
    VEHICLE_MODEL_TYPE_BOAT,
    VEHICLE_MODEL_TYPE_MOTOR_BIKE
}

// ------------------------------------- //
//                 Variables             //
// ------------------------------------- //

new SQL = -1, gQuery[2056], gString[512], gDialog[2056],

    Iterator:serverAdmins<MAX_PLAYERS>,
    Iterator:serverHelpers<MAX_PLAYERS>,
    Iterator:spawnedCars<MAX_VEHICLES>,
    Iterator:serverStaff<MAX_PLAYERS>,
    Iterator:serverReports<MAX_PLAYERS>,
    Iterator:serverQuestions<MAX_PLAYERS>,
    Iterator:serverPlayers<MAX_PLAYERS>,
    Iterator:serverFrequency[201]<MAX_PLAYERS>,
    Iterator:playersStreamed[MAX_PLAYERS]<MAX_PLAYERS>,
    Iterator:vehiclesStreamed[MAX_PLAYERS]<MAX_VEHICLES>,
    Iterator:playerSkins[MAX_PLAYERS]<50>,
    Iterator:truckersChat<MAX_PLAYERS>,
    Iterator:playersInVehicles<MAX_PLAYERS>,
    
    Queue:loginQueue<MAX_PLAYERS>,

    SortedArray:playersIPs<MAX_PLAYERS>,

    Map:playersNames,
    Map:playersSQLID,
    Map:phoneNumbers,

    bool:racTimerActive,

    playerDeathKillerID = INVALID_PLAYER_ID,
    playerDeathReason,

    serverRestartTime = -1,
    serverPayday = -1,
    Timer:serverRestartTimerVar,
    serverStartTime,
    staffQuestionsInfoDelay,

    bool:serverTeleportEvent,
    Float:serverTeleportEventLocation[3],

    serverStuff[e_sStuff],

    playerTextdraws[MAX_PLAYERS][e_pTD],
    playerLabels[MAX_PLAYERS][e_pLabels],

    playerVars[MAX_PLAYERS + 1][e_pVars], 
    vehicleVars[MAX_VEHICLES][e_vVars],

    playerInfo[MAX_PLAYERS + 1][e_pInfo],
    reportInfo[MAX_PLAYERS][e_rInfo],
    pickupInfo[2000][e_pkInfo],

    raceCheckThreads[MAX_PLAYERS],

    Text:serverDateTD,
    Text:serverClockTD,
    Text:AStatsTD,
    Text:LogoTD[3],
    Text:ReportsTD, 
    Text:SafezoneTD,
    Text:LoginQueueTD[3];

// ------------------------------------- //
//               Modules                 //
// ------------------------------------- //

#include <fly>

#include "server/globalarrays"
#include "server/utils"
#include "server/animations"

#include "modules/ly"
#include "modules/svars"
#include "modules/houses"
#include "modules/dmv"
#include "modules/anticheat"
#include "modules/safezone"
#include "modules/business"
#include "modules/jobs"
#include "modules/emails"
#include "modules/friends"
#include "modules/quests"
#include "modules/atm"  
#include "modules/anticollision"
#include "modules/servervehicles"
#include "modules/rentvehicles"
#include "modules/vendingmachines"
#include "modules/personalvehicles"
#include "modules/dealership"
#include "modules/pin"
#include "modules/trade"
#include "modules/lotto"

#include "modules/groups/groups"
#include "modules/groups/doors"
#include "modules/groups/groupgates"
#include "modules/groups/cops"
#include "modules/groups/newsreporters"
#include "modules/groups/paramedics"
#include "modules/groups/hitman"

#include "modules/groups/gangs/death_loot"
#include "modules/groups/gangs/turfs"
#include "modules/groups/gangs/gangs"
#include "modules/groups/gangs/wars"
#include "modules/groups/groupcars"
#include "server/callbacks"
#include "server/dialogs"
#include "server/timers"
#include "server/functions"
#include "server/playercommands"
#include "server/helpercommands"
#include "server/admincommands"

#pragma warning disable 239, 203, 219, 217