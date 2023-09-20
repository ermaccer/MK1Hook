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
    };

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
