#include "PatternSolver.h"
#include "..\utils\Patterns.h"
#include "..\gui\log.h"
#include <chrono>

uintptr_t PatternSolver::ms_patterns[PATID_Total_Patterns];


uintptr_t PatternSolver::GetPattern(const char* szPattern, int offset)
{
    uintptr_t addr = 0;
    try {
        addr = (uintptr_t)hook::txn::get_pattern(szPattern, offset);
    }
    TXN_CATCH();

    return addr;
}

void PatternSolver::Initialize()
{
    eLog::Message(__FUNCTION__, "Starting pattern search");

    for (int i = 0; i < PATID_Total_Patterns; i++)
        ms_patterns[i] = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    ms_patterns[PATID_FEngineLoop_Tick] = GetPattern("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 C8", 0);
    ms_patterns[PATID_FEngineLoop_Tick_Hook] = GetPattern("48 8D 0D ? ? ? ? E8 ? ? ? ? 80 3D ? ? ? ? ? 74 EB 80", 7);

    ms_patterns[PATID_MKCamera_FillCameraCache] = GetPattern("48 8B C4 48 89 70 20 57 48 81 EC 40 06 00 00", 0);
    ms_patterns[PATID_MKCamera_FillCameraCache_Hook] = GetPattern("48 8D 54 24 20 48 8B CF E8 ? ? ? ? 48 8B 8C 24 ? ? ? ? 48 8B BC 24", 8);

    ms_patterns[PATID_SlowGameTimeForXTicks] = GetPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 50 0F 29 74 24 ? 41 8B D9 0F 28 F0 41 8B F8", 0);

    ms_patterns[PATID_FGGameInfo_FindGameInfo] = GetPattern("48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? 44 89 6C 24 ? 41 8B D5", 3);
    ms_patterns[PATID_FGGameInfo_Exec] = GetPattern("48 89 5C 24 18 48 89 6C 24 20 56 57 41 56 48 81 EC 80 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 84", 0);
    ms_patterns[PATID_FGGameInfo_GetCurrentMission] = GetPattern("48 83 EC 28 48 8B C1 48 85 C9 75 11 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0C 48 8B C8 48 83 C4 28 E9", 0);
    ms_patterns[PATID_FGGameInfo_GetPlayerInfo] = GetPattern("0F B6 C2 48 69 C0 ? ? ? ? 48 83 C0 48 48 03 C1 C3", 0);
    ms_patterns[PATID_FGGameInfo_GetTeamDefinition] = GetPattern("48 89 5C 24 ? 57 48 83 EC 30 0F B6 FA 48 8D 54 24 ? E8 ? ? ? ? 4C 8B 44 24 ? 48 63 4C 24 ? 4C 89 C0 4D 8D 0C C8 4D 39 C8 74 1A 0F 1F 00 48 8B 18 48 85 DB 74 06", 0);
    ms_patterns[PATID_FGGameInfo_SetStage] = GetPattern("40 55 53 56 57 41 54 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 63 5A 08 45 33 E4 48 8B 3A 48 8B F1 4C 89 65 EF", 0);
    ms_patterns[PATID_CharacterContentDefinition_Get] = GetPattern("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 18 33 FF 4C 8D 4C 24 ? 48 8B C2 48 89 7C 24 ? 4D 8B F0 48 89 7C 24 ? 48 8B F1 48 89 7C 24", 0);

    ms_patterns[PATID_CharacterDefinition_Set] = GetPattern("48 89 5C 24 ? 57 48 83 EC 40 48 8B FA 48 8B D9 E8 ? ? ? ? 48 8B 47 10 48 8D 57 18 48 8D 4C 24 ? 48 89 44 24 ? E8 ? ? ? ? 48 8B 44 24 ? 48 8D 8B ? ? ? ? C7 83 ? ? ? ? ? ? ? ? 48 8D 54 24 ? C7 83 ? ? ? ? ? ? ? ? 48 89 83 ? ? ? ? E8 ? ? ? ? 48 8B 4C 24 ? C7 83 ? ? ? ? ? ? ? ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B 47 28 48 8D 57 38 48 89 83 ? ? ? ? 48 8D 8B", 0);
    ms_patterns[PATID_CharacterDefinition_SetPartner] = GetPattern("48 89 5C 24 ? 57 48 83 EC 40 48 8B FA 48 8B D9 E8 ? ? ? ? 48 8B 47 10 48 8D 57 18 48 8D 4C 24 ? 48 89 44 24 ? E8", 0);

    ms_patterns[PATID_MKCharacter_SetScale] = GetPattern("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? F2 0F 10 02 48 8B F9", 0);
    ms_patterns[PATID_MKCharacter_SetSpeed] = GetPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 0F 29 74 24 ? 48 81 C1 ? ? ? ? 8B FA 41 8B D9 0F 28 F2 E8", 0);
    ms_patterns[PATID_MKCharacter_ExecuteScript] = GetPattern("48 8B C4 55 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 89 58 D8 48 8B D9 48 89 70 D0 48 81 C1 ? ? ? ? 48 89 78 C8", 0);
    ms_patterns[PATID_MKCharacter_FlagsOffset] = GetPattern("48 8B 81 ? ? ? ? 80 78 ? 00 74 77 80 78 ? 00", 3);

    ms_patterns[PATID_USkeletalMeshComponent_GetBoneMatrix] = GetPattern("48 8B C4 48 89 58 10 48 89 70 18 57 48 81 EC ? ? ? ? F6 81 ? ? ? ? ? 48 8B FA 0F 29 78 E8 48 8B D9", 0);
    ms_patterns[PATID_USkeletalMeshComponent_GetBoneName] = GetPattern("4C 8B 89 ? ? ? ? 4D 85 C9 74 27 45 85 C0 78 22 45 3B 81 ? ? ? ? 7D 19", 0);

    ms_patterns[PATID_FName_FNameChar] = GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 89 54 24 20 41 8B F8 4C 8B CA", 0);
    ms_patterns[PATID_FName_FName] = GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 8B D9 48 89 54 24 20 33 C9", 0);
    ms_patterns[PATID_FName_ToString] = GetPattern("48 89 5C 24 18 48 89 74 24 20 57 48 83 EC 20 8B 01", 0);

    ms_patterns[PATID_GamelogicJump] = GetPattern("4C 8B DC 48 83 EC 68 0F B6 84 24 ? ? ? ? 49 89 5B 18 41 8B D8 49 89 6B 20 48 8B EA 45 88 4B C8 48 8D 15 ? ? ? ? 88 44 24 31 0F B6 84 24 ? ? ? ? 49 89 73 F8 48 8D B1 ? ? ? ? 88 44 24 32 0F B6 84 24", 0);

    ms_patterns[PATID_FMatrix_Rotator] = GetPattern("48 8B C4 53 48 81 EC ? ? ? ? F3 0F 10 41 ? 48 8B DA 0F 29 70 E8 F3 0F 10 31 0F 29 78 D8 0F 28 CE F3 0F 10 79 ? 44 0F 29 40", 0);
    ms_patterns[PATID_FMatrix_MakeFromX] = GetPattern("48 8B C4 48 81 EC ? ? ? ? F3 0F 10 6A ? F3 0F 10 1A 0F 28 C5 F3 0F 10 62 ? 0F 28 D3 0F 29 70 E8", 0);

    ms_patterns[PATID_SetPartnerCharacter_Hook] = GetPattern("E8 ? ? ? ? 41 80 FE 02 41 0F 42 DE 0F B6 C3 48 83 C0 07 48 03 C0 48 8B 1C C6 48 81 C3 ? ? ? ? 48 8B CB", 0);

    ms_patterns[PATID_HideHUD] = GetPattern("48 8B 49 60 48 85 C9 74 17 48 83 79 ? ? 74 10 48 8B 49 10 48 8B 89 ? ? ? ? E9", 0);
    ms_patterns[PATID_PlayerInfo_GetObject] = GetPattern("48 83 EC 28 BA ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0E 33 D2 48 8B C8 48 83 C4 28 E9", 0);
    ms_patterns[PATID_PlayerInfo_AdjustMeter] = GetPattern("48 8B C4 44 88 40 18 53 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 B8 4C 8B F1 0F 29 78 A8 48 81 C1 ? ? ? ? 44 0F 29 50 ? 0F 28 F1 E8 ? ? ? ? 4C 8B F8 0F 57 FF", 0);

    ms_patterns[PATID_GetScaleform] = GetPattern("48 83 EC 68 48 8B 05 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 48 8D 0D ? ? ? ? 48 89 7C 24 ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? 33 FF", 0);

    ms_patterns[PATID_GetScript] = GetPattern("40 53 55 41 56 48 83 EC 30 41 0F B6 D8 4C 8B C1 0F B6 EA 48 85 C9 74 3E B9 ? ? ? ? 48 C7 C0", 0);
    ms_patterns[PATID_MKScript_GetFunctionID] = GetPattern("48 89 5C 24 ? 48 89 7C 24 ? 8B 81 ? ? ? ? 33 FF 4C 8B D1 4C 63 DA 3B 81 ? ? ? ? 74 57 48 63 81", 0);
    ms_patterns[PATID_MKScript_GetVariable] = GetPattern("4C 8B C2 4C 8B C9 48 85 D2 0F 84 ? ? ? ? BA ? ? ? ? 48 C7 C0 ? ? ? ? 0F 1F 44 00", 0);
    ms_patterns[PATID_MKScript_CharacterScriptAction] = GetPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8B D8 48 8B FA 48 8B F1 E8 ? ? ? ? 48 8D 05 ? ? ? ? 89 9E ? ? ? ? 8B D3 48 89 06 48 8B CF C6 86", 0);
    ms_patterns[PATID_MKScript_CharacterScriptAttackAction] = GetPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B EA 41 0F B6 F1 49 8B 50 58 49 8B F8 48 8B D9 E8 ? ? ? ? 48 8B 54 24 ? 48 8D 05", 0);
    ms_patterns[PATID_MKScript_DataFunctionConstructor] = GetPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 4D 8B E8 48 8B DA 45 33 C0 33 D2 49 8B F1 48 8B F9 E8 ? ? ? ? 4C 89 6F 30 48 8D 05", 0);
    ms_patterns[PATID_MKScript_RegisterSpecialMove] = GetPattern("FF 50 58 BA ? ? ? ? 48 8B CF E8 ? ? ? ? 83 BD ? ? ? ? ? 48 8B 9C 24 ? ? ? ? 74 23", 11);
    ms_patterns[PATID_MKScript_RegisterSpecialMove2] = GetPattern("FF 50 58 BA ? ? ? ? 48 8B CB E8 ? ? ? ? 83 BF ? ? ? ? ? 74 23 4C 8B C3", 11);
    ms_patterns[PATID_ScriptAlloc] = GetPattern("48 85 C9 B8 01 00 00 00 48 0F 45 C1", 0);


    ms_patterns[PATID_ContentDefinition_Load] = GetPattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F2 4C 8B E1 E8 ? ? ? ? 49 8B BC 24 ? ? ? ? 4D 63 BC 24 ? ? ? ? 49 C1 E7 07 4C 03 FF 49 3B FF", 0);
    ms_patterns[PATID_KameoContentDefinition_Load] = GetPattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 8B FA 48 8B D9 E8 ? ? ? ? 45 33 ED", 0);

    ms_patterns[PATID_PlayerInfo_GetDrone] = GetPattern("4C 8B 89 ? ? ? ? 4C 8D 15 ? ? ? ? 4C 8B C1 4D 85 C9 74 1B 8B 81 ? ? ? ? 3D ? ? ? ? 73 0E", 0);
    ms_patterns[PATID_MKCharacter_GetDrone] = GetPattern("48 8B 81 ? ? ? ? 48 8B 88 ? ? ? ? E9", 0);
    ms_patterns[PATID_AIDrone_GetLevel] = GetPattern("0F B6 81 ? ? ? ? 3C 14 75 07 0F B6 81", 0);
    ms_patterns[PATID_AIDrone_Set] = GetPattern("0F B6 81 ? ? ? ? 3C 14 75 07 0F B6 81", 0);

    ms_patterns[PATID_USceneComponent_SetRelativeScale3D] = GetPattern("48 89 5C 24 ? 57 48 83 EC 30 F2 0F 10 81 ? ? ? ? 48 8B FA F3 0F 10 0A 48 8B D9 0F 2E C8 8B 81 ? ? ? ? 89 44 24 28 F2 0F 11 44 24 ? 7A 22", 0);
    ms_patterns[PATID_UWorld_GWorld] = GetPattern("48 8B 05 ? ? ? ? 48 8B D9 48 8D 4D 20 48 8B 50 18 48 89 55 20", 3);

    ms_patterns[PATID_ProcessPostProcessSettings] = GetPattern("48 8B C4 55 53 41 55 48 8B EC 48 81 EC ? ? ? ? 44 0F 29 40 ? 48 8B DA 45 0F 57 C0 4C 8B E9 44 0F 2F C2 0F 83", 0);
    ms_patterns[PATID_TeamInfo_SetKameo] = GetPattern("E8 ? ? ? ? 33 D2 48 8B CD 48 8B F0 48 8B 78 08 E8 ? ? ? ? 48 8B D0", 0);
    ms_patterns[PATID_TeamInfo_SetTag] = GetPattern("E8 ? ? ? ? 33 D2 48 8B CD 48 8B F0 48 8B 78 08 E8 ? ? ? ? 48 8B D0 48 8D 4E 08 FF 97 ? ? ? ? 48 8B BE ? ? ? ? BA ? ? ? ? 48 8B CD E8 ? ? ? ? 48 8B D0 48 8D 8E ? ? ? ? 48 8B 87 ? ? ? ? 48 8B 7C 24 ? 48 83 C4 30 5E 5D 5B 48 FF E0 48 8B CD E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 4C 89 74 24", 0);
    ms_patterns[PATID_TeamInfo_SetSingle] = GetPattern("E8 ? ? ? ? 48 8B 78 08 33 D2 48 8B CD 48 8D 58 08 E8 ? ? ? ? 48 8B D0", 0);
    ms_patterns[PATID_TeamInfo_GetDefinitions] = GetPattern("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83 ? ? ? ? 48 83 C4 20 5B C3 E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83", 0);
    ms_patterns[PATID_TeamInfo_KameoClass] = GetPattern("E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83 ? ? ? ? 48 83 C4 20 5B C3", 0);
    ms_patterns[PATID_TeamInfo_TagClass] = GetPattern("E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83 ? ? ? ? 48 83 C4 20 5B C3 E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83 ? ? ? ? 48 83 C4 20 5B C3 E8 ? ? ? ? 48 39 83 ? ? ? ? 75 0D 48 8D 83 ? ? ? ? 48 83 C4 20 5B C3 33 C0", 0);

    ms_patterns[PATID_FightStartup] = GetPattern("4C 8B DC 55 53 41 56 49 8D 6B A1 48 81 EC ? ? ? ? 41 0F 29 73 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 17 4C 8B F1", 0);
    ms_patterns[PATID_LoadMainMenuBGND] = GetPattern("E8 ? ? ? ? E8 ? ? ? ? 48 8B C8 B2 02 E8 ? ? ? ? E8 ? ? ? ? 48 8B C8 B2 17", 0);

    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    auto timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    eLog::Message(__FUNCTION__, "Checked %d patterns in %dms (%ds)", PATID_Total_Patterns, time.count(), timeSeconds.count());

}

int PatternSolver::GetNumPatternsOK()
{
    int patternNum = 0;

    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i]) patternNum++;
    return patternNum;
}

bool PatternSolver::CheckMissingPatterns()
{
    int missingPatterns = 0;
    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i] == 0)
        {
            missingPatterns++;
            eLog::Message(__FUNCTION__, "ERROR: Could not find %s!", GetPatternName(i));
        }
    return missingPatterns > 0;
}

const char* PatternSolver::GetPatternName(int id)
{
    if (id >= PATID_Total_Patterns)
        return "UNKNOWN";

    static const char* szPatternNames[PATID_Total_Patterns] = {
            "FEngineLoop_Tick",
            "FEngineLoop_Tick_Hook",
            "MKCamera_FillCameraCache",
            "MKCamera_FillCameraCache_Hook",
            "SlowGameTimeForXTicks",
            "FGGameInfo_FindGameInfo",
            "FGGameInfo_Exec",
            "FGGameInfo_GetCurrentMission",
            "FGGameInfo_GetPlayerInfo",
            "FGGameInfo_GetTeamDefinition",
            "FGGameInfo_SetStage",
            "CharacterContentDefinition_Get",
            "CharacterDefinition_Set",
            "CharacterDefinition_SetPartner",
            "MKCharacter_SetScale",
            "MKCharacter_SetSpeed",
            "MKCharacter_ExecuteScript",
            "MKCharacter_FlagsOffset",
            "USkeletalMeshComponent_GetBoneMatrix",
            "USkeletalMeshComponent_GetBoneName",
            "FName_FNameChar",
            "FName_FName",
            "FName_ToString",
            "GamelogicJump",
            "FMatrix_Rotator",
            "FMatrix_MakeFromX",
            "SetPartnerCharacter_Hook",
            "HideHUD",
            "PlayerInfo_GetObject",
            "PlayerInfo_AdjustMeter",
            "GetScaleform",
            "GetScript",
            "MKScript_GetFunctionID",
            "MKScript_GetVariable",
            "MKScript_CharacterScriptAction",
            "MKScript_CharacterScriptAttackAction",
            "MKScript_DataFunctionConstructor",
            "MKScript_RegisterSpecialMove",
            "MKScript_RegisterSpecialMove2",
            "ScriptAlloc",
            "ContentDefinition_Load",
            "KameoContentDefinition_Load",
            "PlayerInfo_GetDrone",
            "MKCharacter_GetDrone",
            "AIDrone_GetLevel",
            "AIDrone_Set",
            "USceneComponent_SetRelativeScale3D",
            "UWorld_GWorld",
            "ProcessPostProcessSettings",
            "TeamInfo_SetKameo",
            "TeamInfo_SetTag",
            "TeamInfo_SetSingle",
            "TeamInfo_GetDefinitions",
            "TeamInfo_KameoClass",
            "TeamInfo_TagClass",
            "FightStartup",
            "LoadMainMenuBGND",
    };   

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
