#include "GameInfo.h"
#include "FightingTeamDefinition.h"
#include "..\unreal\FName.h"
#include "..\plugin\Menu.h"

uintptr_t FGGameInfo::pGameInfo = 0;

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)FGGameInfo::pGameInfo;
}

void FGGameInfo::FindGameInfo()
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_FindGameInfo);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		FGGameInfo::pGameInfo = (pat + offset + 4);
	}
}

void FGGameInfo::Exec(char* line)
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_Exec);
	if (pat)
	{
		((void(__thiscall*)(FGGameInfo*, char*))pat)(this, line);
	}
}

void FGGameInfo::SetGameSpeed(float speed)
{
	//fGameSpeed = speed;
	char cmd[128];
	sprintf(cmd, "slomo %f", speed);
	Exec(cmd);
}


FightingTeamDefinition* FGGameInfo::GetTeam(TEAM_NUM id)
{
	FightingTeamDefinition* teamInfo = nullptr;

	int64 missionInfo = GetMissionInfo();
	if (missionInfo)
	{
		int64 ptr = GetMissionInfo_ptr(missionInfo);
		if (ptr)
		{
			static uintptr_t pat = _pattern(PATID_FGGameInfo_GetTeamDefinition);
			if (pat)
			{
				teamInfo = ((FightingTeamDefinition* (__thiscall*)(int64, int))pat)(ptr, id);
			}
		}
	}

	return teamInfo;
}

void FGGameInfo::SetStage(int64 backgroundInfo, char* name)
{
	char* processString = name + 5;
	char* variantName = strstr(processString, "_");
	
	std::string mapStr(processString);
	mapStr = mapStr.substr(0, strlen(processString) - strlen(variantName));
	std::string variantStr(variantName + 1);
	
	
	static char stageName[128] = {};
	snprintf(stageName, sizeof(stageName), "%s.%s", mapStr.c_str(), variantStr.c_str());


	FName fName(stageName, FNAME_Add, 1);
	FString stageStr;
	fName.ToString(&stageStr);

	static uintptr_t pat = _pattern(PATID_FGGameInfo_SetStage);
	if (pat)
		((void(__thiscall*)(int64, FString))pat)(backgroundInfo, stageStr);
}

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	PlayerInfo* plrInfo = nullptr;

	int64 missionInfo = GetMissionInfo();
	if (missionInfo)
	{
		int64 ptr = GetMissionInfo_ptr(missionInfo);
		if (ptr)
		{
			static uintptr_t pat = _pattern(PATID_FGGameInfo_GetPlayerInfo);
			if (pat)
			{
				plrInfo = ((PlayerInfo*(__thiscall*)(int64, int))pat)(ptr, plr);
			}
		}
	}

	return plrInfo;
}


int64 FGGameInfo::GetObj(PLAYER_NUM plr)
{
	PlayerInfo* info = GetInfo(plr);
	if (info)
	{
		static uintptr_t pat = _pattern(PATID_PlayerInfo_GetObject);
		if (pat)
		{
			return ((int64(__thiscall*)(PlayerInfo*))pat)(info);
		}
	}
	return 0;
}

int64 FGGameInfo::GetMissionInfo_ptr(int64 missionInfo)
{
	int64 ptr = 0;

	ptr = *(int64*)(missionInfo + 96);
	if (ptr)
		return *(int64*)(ptr + 16);
	return ptr;
}

int64 FGGameInfo::GetMissionInfo()
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_GetCurrentMission);
	if (pat)
	{
		return ((int64(__fastcall*)(int64))pat)(0);
	}
	return 0;
}