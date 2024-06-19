#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_FEngineLoop_Tick,
	PATID_FEngineLoop_Tick_Hook,

	PATID_MKCamera_FillCameraCache,
	PATID_MKCamera_FillCameraCache_Hook,

	PATID_FGGameInfo_FindGameInfo,
	PATID_FGGameInfo_Exec,
	PATID_FGGameInfo_GetCurrentMission,
	PATID_FGGameInfo_GetPlayerInfo,
	PATID_FGGameInfo_GetTeamDefinition,

	PATID_CharacterContentDefinition_Get,

	PATID_CharacterDefinition_LoadCharacter,
	PATID_CharacterDefinition_LoadCharacterKameo,

	PATID_MKCharacter_SetScale,
	PATID_MKCharacter_ExecuteScript,
	PATID_MKCharacter_FlagsOffset,

	PATID_USkeletalMeshComponent_GetBoneMatrix,
	PATID_USkeletalMeshComponent_GetBoneName,

	PATID_FName_FNameChar,
	PATID_FName_FName,
	PATID_FName_ToString,
	PATID_GamelogicJump,

	PATID_FMatrix_Rotator,
	PATID_FMatrix_MakeFromX,

	PATID_SetPartnerCharacter,
	PATID_SetPartnerCharacter_Hook,

	PATID_HideHUD,
	PATID_PlayerInfo_GetObject,
	PATID_PlayerInfo_AdjustMeter,
	PATID_SetCharacterDefinitions,
	PATID_GetScaleform,
	PATID_GetScript,
	PATID_MKScript_GetFunctionID,
	PATID_MKScript_GetVariable,
	PATID_MKScript_CharacterScriptAction,
	PATID_MKScript_CharacterScriptAttackAction,
	PATID_MKScript_PowerAttackObjDef,

	PATID_ScriptAlloc,

	PATID_ContentDefinition_Load,
	PATID_KameoContentDefinition_Load,

	PATID_PlayerInfo_GetDrone,
	PATID_AIDrone_GetLevel,

	PATID_USceneComponent_SetRelativeScale3D,
	PATID_UWorld_GWorld,

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