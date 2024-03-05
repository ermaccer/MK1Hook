#include "PlayerInfo.h"

AIDrone* PlayerInfo::GetDrone()
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_GetDrone);
	if (pat)
		return	((AIDrone * (__fastcall*)(PlayerInfo*))pat)(this);
	return nullptr;
}

int AIDrone::GetDroneLevel()
{
	static uintptr_t pat = _pattern(PATID_AIDrone_GetLevel);
	if (pat)
		return	((int(__fastcall*)(AIDrone*))pat)(this);
	return 0;
}
