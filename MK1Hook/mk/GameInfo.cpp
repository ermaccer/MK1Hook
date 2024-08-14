#include "GameInfo.h"
#include "FightingTeamDefinition.h"
#include "..\unreal\FName.h"
#include "..\plugin\Menu.h"

void(*orgFGGameInfo_SetBackground)(FGGameInfo*, int64);

uintptr_t FGGameInfo::pGameInfo = 0;

int64 FGGameInfo::pPlayerActorObjs[MAX_PLAYERS] = {};
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

	ptr = *(int64*)(missionInfo + 88);
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


void FGGameInfo::OnJump()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
		pPlayerActorObjs[i] = 0;
}

void FGGameInfo::LoadBackgroundHook(FGGameInfo* info, int64 backgroundInfo)
{
	FName* path = (FName*)(backgroundInfo + 24);
	FName* variant = (FName*)(backgroundInfo + 52);

	if (TheMenu->m_bStageModifier)
	{
		char* processString = TheMenu->szStageModifierStage + 5;
		char* variantName = strstr(processString, "_");
		if (variantName)
		{
			std::string mapStr(processString);
			mapStr = mapStr.substr(0, strlen(processString) - strlen(variantName));
			std::string variantStr(variantName + 1);

			char newMapPath[256] = {};
			snprintf(newMapPath, sizeof(newMapPath), "/Game/Disk/Env/%s/Map/%s.%s", mapStr.c_str(), mapStr.c_str(), mapStr.c_str());

			FName newMap(newMapPath, FNAME_Add, 1);
			FName newSkin(variantStr.c_str(), FNAME_Add, 1);

			*path = newMap;
			*variant = newSkin;
		}

	}

#ifdef _DEBUG
	FString str;
	path->ToString(&str);
	FString skinName;
	variant->ToString(&skinName);
	eLog::Message(__FUNCTION__, "Stage: %ws [%ws]", str.GetStr(), skinName.GetStr());
#endif // _DEBUG


	orgFGGameInfo_SetBackground(info, backgroundInfo);
}
