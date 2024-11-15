#include "FightingTeamDefinition.h"

int64(*pTeamInfo_SetKameoMode)(FightingTeamDefinition*, bool) = nullptr;
int64(*pTeamInfo_SetTagMode)(FightingTeamDefinition*, bool) = nullptr;
int64(*pTeamInfo_SetSingleMode)(FightingTeamDefinition*, bool) = nullptr;
int64(*pTeamInfo_GetKameoClass)() = nullptr;
int64(*pTeamInfo_GetTagClass)() = nullptr;

void FightingTeamDefinition::SetMode(TEAM_INFO_MODE mode)
{
	switch (mode)
	{
	case MODE_SINGLE:
		pTeamInfo_SetSingleMode(this, false);
		break;
	case MODE_KAMEO:
		pTeamInfo_SetKameoMode(this, false);
		break;
	case MODE_TAG:
		pTeamInfo_SetTagMode(this, false);
		break;
	default:
		break;
	}
}

bool FightingTeamDefinition::IsPartnerMode()
{
	int64 teamClass = GetClass();

	if (teamClass == GetKameoClass() || teamClass == GetTagClass())
		return true;

	return false;
}

int64 FightingTeamDefinition::GetDefinitions()
{
	static uintptr_t pat = _pattern(PATID_TeamInfo_GetDefinitions);
	if (pat)
		return ((int64(__thiscall*)(FightingTeamDefinition*))pat)(this);

	return 0;
}

int64 FightingTeamDefinition::GetClass()
{
	return *(int64*)((int64)this + 136);
}

int64 FightingTeamDefinition::GetKameoClass()
{
	return pTeamInfo_GetKameoClass();
}

int64 FightingTeamDefinition::GetTagClass()
{
	return pTeamInfo_GetTagClass();
}
