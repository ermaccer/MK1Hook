#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_FEngineLoop_Tick,
	PATID_FEngineLoop_Tick_Hook,
	PATID_MKCamera_FillCameraCache,
	PATID_MKCamera_FillCameraCache_Hook,
	PATID_MissionInfo_BuildFightHUD,
	PATID_MissionInfo_BuildFightHUD_Hook,
	PATID_FGGameInfo_FindGameInfo,
	PATID_Total_Patterns
};


class PatternSolver {
public:
	static uintptr_t ms_patterns[PATID_Total_Patterns];

	static uintptr_t GetPattern(const char* szPattern, int offset);

	static void			Initialize();
	static int			GetNumPatternsOK();
	static bool			CheckMissingPatterns();
	static const char*	GetPatternName(int id);

};


uintptr_t _pattern(EPatternID id);