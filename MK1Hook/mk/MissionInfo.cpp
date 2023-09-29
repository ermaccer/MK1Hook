#include "MissionInfo.h"
#include "..\plugin\Menu.h"
MissionInfo* MInfo;

void MissionInfo::BuildFightHUD()
{
	static uintptr_t pat = _pattern(PATID_MissionInfo_BuildFightHUD);
	if (!pat)
		return;
	if (TheMenu->m_bDisableFightHUD)
		HideFightHUD = true;

	if (!HideFightHUD)
		((void(__thiscall*)(int64, MissionInfo*))pat)(*(int64*)((int64)this + 928), this);
}

void MissionInfo::FindObjects()
{
	 
}
