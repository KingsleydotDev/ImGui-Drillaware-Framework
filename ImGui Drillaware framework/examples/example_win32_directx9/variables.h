#pragma once
namespace variables {
    bool bEnableDLC = true;
    bool bAntiLeave = false;
    bool bFFATeamFix = false;
    bool bDisableEquipment = false;

    const char* map_list[27] = { "Afghan", "Derail", "Estate", "Favela", "Highrise", "Invasion", "Karachi", "Quarry", "Rundown", "Rust", "Scrapyard", "Skidrow", "Sub Base", "Terminal", "Underpass", "Wasteland", "-----DLC MAPS-----", "Bailout", "Crash", "Salvage", "Overgrown", "Storm", "Carnival", "Fuel", "Strike", "Trailer Park", "Vacant" };
    int map_list_number = 0;


    char friend1[128] = "";
    char friend2[128] = "";
    char friend3[128] = "";
    char friend4[128] = "";


    float fLadderCap = 100.0f;
    float fProneCap = 85.0f;

    int iFPS = 125;
    float fFieldOfView = 65.0f;
    bool bThirdPerson = false;

    int iPrestige = 9;


}
