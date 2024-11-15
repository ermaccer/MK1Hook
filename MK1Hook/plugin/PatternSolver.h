#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_FEngineLoop_Tick,
	PATID_FEngineLoop_Tick_Hook,

	PATID_MKCamera_FillCameraCache,
	PATID_MKCamera_FillCameraCache_Hook,
	
	PATID_SlowGameTimeForXTicks,

	PATID_FGGameInfo_FindGameInfo,
	PATID_FGGameInfo_Exec,
	PATID_FGGameInfo_GetCurrentMission,
	PATID_FGGameInfo_GetPlayerInfo,
	PATID_FGGameInfo_GetTeamDefinition,
	PATID_FGGameInfo_SetStage,

	PATID_CharacterContentDefinition_Get,

	PATID_CharacterDefinition_Set,
	PATID_CharacterDefinition_SetPartner,

	PATID_MKCharacter_SetScale,
	PATID_MKCharacter_SetSpeed,
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

	PATID_HideHUD,
	PATID_PlayerInfo_GetObject,
	PATID_PlayerInfo_AdjustMeter,

	PATID_GetScaleform,
	PATID_GetScript,
	PATID_MKScript_GetFunctionID,
	PATID_MKScript_GetVariable,
	PATID_MKScript_CharacterScriptAction,
	PATID_MKScript_CharacterScriptAttackAction,
	PATID_MKScript_DataFunctionConstructor,
	PATID_MKScript_RegisterSpecialMove,
	PATID_MKScript_RegisterSpecialMove2,

	PATID_ScriptAlloc,

	PATID_ContentDefinition_Load,
	PATID_KameoContentDefinition_Load,

	PATID_PlayerInfo_GetDrone,
	PATID_MKCharacter_GetDrone,
	PATID_AIDrone_GetLevel,
	PATID_AIDrone_Set,

	PATID_USceneComponent_SetRelativeScale3D,
	PATID_UWorld_GWorld,

	PATID_ProcessPostProcessSettings,
	PATID_TeamInfo_SetKameo,
	PATID_TeamInfo_SetTag,
	PATID_TeamInfo_SetSingle,
	PATID_TeamInfo_GetDefinitions,
	PATID_TeamInfo_KameoClass,
	PATID_TeamInfo_TagClass,

	PATID_FightStartup,
	PATID_LoadMainMenuBGND,

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