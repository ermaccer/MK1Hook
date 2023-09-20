#include "GameInfo.h"

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

void FGGameInfo::SetGameSpeed(float speed)
{
	fGameSpeed = speed;
}
