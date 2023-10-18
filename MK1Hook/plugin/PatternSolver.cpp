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

    // check with numbers so when update changes offset, this breaks
    ms_patterns[PATID_MissionInfo_BuildFightHUD_Hook] = GetPattern("80 B9 70 05 00 00 00 75 0F 48 89 CA", 0);
    ms_patterns[PATID_MissionInfo_BuildFightHUD] = GetPattern("48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 55 41 54 41 55 41 56 41 57 48 8D 6C 24 90 48 81 EC 70 01 00 00 80 B9 29 18 00 00 00", 0);

    ms_patterns[PATID_FGGameInfo_FindGameInfo] = GetPattern("75 7A 48 8B 0D ? ? ? ? E8 ? ? ? ? 4C 8B C0 48 8D 54 24 38", 5);
    ms_patterns[PATID_FGGameInfo_Exec] = GetPattern("48 89 5C 24 18 48 89 6C 24 20 56 57 41 56 48 81 EC 80 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 84", 0);

    ms_patterns[PATID_ContentDefinition_Get] = GetPattern("48 89 5C 24 08 48 89 74 24 20 57 48 83 EC 40 48 63 42 08 48 8B FA", 0);
    ms_patterns[PATID_CharacterDefinition_Set] = GetPattern("48 89 5C 24 10 4C 89 44 24 18 55 56 57 48 83 EC 50", 0);

    ms_patterns[PATID_CharacterDefinition_LoadCharacter] = GetPattern("40 57 48 83 EC 40 48 83 79 ? ? 48 8B F9 75 1A 48 8B 01 FF 50 10 48 8B D0 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 10 48 89 57 38 48 83 7F ? ? 75 15 48 8B 07 48 8B CF FF 50 10 48 8B C8 E8 ? ? ? ? 48 89 47 48 48 83 7F ? ? 75 15 48 8B 07 48 8B CF FF 50 10 48 8B C8 E8 ? ? ? ? 48 89 47 40 48 83 7F ? ? 75 6D 48 8B 07 48 8D 54 24 ? 48 8B CF 48 89 5C 24 ? FF 50 30 48 8B 17 48 8B CF 48 8B D8 FF 52 10 4C 8B C3 48 8D 4C 24 ? 48 8B D0 E8 ? ? ? ? C7 47 ? ? ? ? ? C7 47 ? ? ? ? ? 48 8B 08 48 8D 58 08 48 89 4F 60 48 8B D3 48 8D 4F 68 E8 ? ? ? ? C7 47 ? ? ? ? ? 48 8B 0B 48 8B 5C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 80 BF ? ? ? ? ? 74 0D 48 8B CF 48 83 C4 40 5F E9 ? ? ? ? 48 83 C4 40 5F C3", 0);
    ms_patterns[PATID_CharacterDefinition_LoadCharacterKameo] = GetPattern("40 57 48 83 EC 40 48 83 79 ? ? 48 8B F9 75 1A 48 8B 01 FF 50 10 48 8B D0 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 10 48 89 57 38 48 83 7F ? ? 75 15 48 8B 07 48 8B CF FF 50 10 48 8B C8 E8 ? ? ? ? 48 89 47 48 48 83 7F ? ? 75 15 48 8B 07 48 8B CF FF 50 10 48 8B C8 E8 ? ? ? ? 48 89 47 40 48 83 7F ? ? 75 6D 48 8B 07 48 8D 54 24 ? 48 8B CF 48 89 5C 24 ? FF 50 30 48 8B 17 48 8B CF 48 8B D8 FF 52 10 4C 8B C3 48 8D 4C 24 ? 48 8B D0 E8 ? ? ? ? C7 47 ? ? ? ? ? C7 47 ? ? ? ? ? 48 8B 08 48 8D 58 08 48 89 4F 60 48 8B D3 48 8D 4F 68 E8 ? ? ? ? C7 47 ? ? ? ? ? 48 8B 0B 48 8B 5C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 83 C4 40 5F C3", 0);
    ms_patterns[PATID_CharacterDefinition_CreateObject] = GetPattern("4C 89 4C 24 ? 4C 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 8B FA", 0);
    ms_patterns[PATID_CharacterDefinition_CreateObject_Hook] = GetPattern("E8 ? ? ? ? 8B 6C 24 68 48 8B F0 85 ED 74 1F 48 8B 5C 24 ? 48 83 C3 18", 0);

    ms_patterns[PATID_MKCharacter_SetScale] = GetPattern("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? F2 0F 10 02 48 8B F9", 0);

    ms_patterns[PATID_USkeletalMeshComponent_GetBoneMatrix] = GetPattern("48 8B C4 55 53 56 57 41 54 41 56 41 57 48 8D 68 A1 48 81 EC ? ? ? ? 0F 29 70 B8", 0);
    ms_patterns[PATID_USkeletalMeshComponent_GetBoneName] = GetPattern("4C 8B 89 ? ? ? ? 4D 85 C9 74 27 45 85 C0 78 22 45 3B 81 ? ? ? ? 7D 19", 0);

    ms_patterns[PATID_FName_FNameChar] = GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 89 54 24 20 41 8B F8 4C 8B CA", 0);
    ms_patterns[PATID_FName_FName] = GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 8B D9 48 89 54 24 20 33 C9", 0);
    ms_patterns[PATID_FName_ToString] = GetPattern("48 89 5C 24 18 48 89 74 24 20 57 48 83 EC 20 8B 01", 0);

    ms_patterns[PATID_GamelogicJump] = GetPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 50 33 F6 45 33 FF 45 33 E4 48 89 74 24 ? 4C 89 7C 24", 0);
    ms_patterns[PATID_SetFrameSkipping] = GetPattern("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 0F B6 D9 8B FA 0F B6 0D ? ? ? ? 8D 41 FE", 0);

    ms_patterns[PATID_UObject_CreateDefaultSubobject] = GetPattern("48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 50 48 8D 44 24 70 C6 44 24 70 00", 0);
    ms_patterns[PATID_SystemLog] = GetPattern("40 53 55 56 57 41 54 41 55 B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4", 0);

    ms_patterns[PATID_FMatrix_Rotator] = GetPattern("48 8B C4 53 48 81 EC ? ? ? ? F3 0F 10 41 ? 48 8B DA 0F 29 70 E8 F3 0F 10 31 0F 29 78 D8 0F 28 CE F3 0F 10 79 ? 44 0F 29 40", 0);
    ms_patterns[PATID_FMatrix_MakeFromX] = GetPattern("48 8B C4 48 81 EC ? ? ? ? F3 0F 10 6A ? F3 0F 10 1A 0F 28 C5 F3 0F 10 62 ? 0F 28 D3 0F 29 70 E8", 0);

    ms_patterns[PATID_SetPartnerCharacter] = GetPattern("45 85 C9 0F 88 ? ? ? ? 53 55 56 57 41 56 48 81 EC", 0);
    ms_patterns[PATID_SetPartnerCharacter_Hook] = GetPattern("E8 ? ? ? ? 40 80 FD 02 B2 01 0F 42 F5 40 0F B6 C6 48 03 C0 49 8B 4C C6", 0);

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
        "MissionInfo_BuildFightHUD",
        "MissionInfo_BuildFightHUD_Hook",
        "FGGameInfo_FindGameInfo",
        "FGGameInfo_Exec",
        "ContentDefinition_Get",
        "CharacterDefinition_Set",
        "CharacterDefinition_LoadCharacter",
        "CharacterDefinition_LoadCharacterKameo",
        "CharacterDefinition_CreateObject",
        "CharacterDefinition_CreateObject_Hook",
        "MKCharacter_SetScale",
        "USkeletalMeshComponent_GetBoneMatrix",
        "USkeletalMeshComponent_GetBoneName",
        "FName_FNameChar",
        "FName_FName",
        "FName_ToString",
        "UObject_CreateDefaultSubobject",
        "GamelogicJump",
        "SetFrameSkipping",
        "SystemLog",
        "FMatrix_Rotator",
        "FMatrix_MakeFromX",
        "SetPartnerCharacter",
        "SetPartnerCharacter_Hook",
    };   

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
