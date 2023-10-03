#include "GameInfo.h"

uintptr_t FGGameInfo::pGameInfo = 0;
FightingTeamDefinition* FGGameInfo::pTeamP1 = nullptr;
FightingTeamDefinition* FGGameInfo::pTeamP2 = nullptr;
int64 FGGameInfo::pPlayerObjs[MAX_PLAYERS] = {};
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
	if (id == TEAM2)
		return pTeamP2;
	else
		return pTeamP1;
}

void FGGameInfo::OnJump()
{
	FGGameInfo::pTeamP1 = nullptr;
	FGGameInfo::pTeamP2 = nullptr;

	for (int i = 0; i < MAX_PLAYERS; i++)
		pPlayerObjs[i] = 0;
}
