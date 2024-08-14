#include "PlayerInfo.h"

void PlayerInfo::AdjustMeter(float value)
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_AdjustMeter);
	if (pat)
		((void(__fastcall*)(PlayerInfo*, float, bool))pat)(this, value, 1);
}

void PlayerInfo::SetMeter(float value)
{
	// wrapper cuz set meter is either inlined or gone
	AdjustMeter(value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)((int64)this + 216) = value;
}

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
