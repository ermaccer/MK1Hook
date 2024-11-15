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

void AIDrone::Set(const char* script)
{
	static uintptr_t pat = _pattern(PATID_AIDrone_Set);
	if (pat)
		((void(__fastcall*)(AIDrone*, int))pat)(this, ScriptToID(script));
}
int AIDrone::ScriptToID(const char* script)
{
	if (strcmp(script, "AIButtonMasher.mko") == 0)
		return 1;
	if (strcmp(script, "AIDummy.mko") == 0)
		return 5;
	if (strcmp(script, "AINormal.mko") == 0)
		return 4;
	if (strcmp(script, "AIVerifier.mko") == 0)
		return 6;

	return 0;
}
