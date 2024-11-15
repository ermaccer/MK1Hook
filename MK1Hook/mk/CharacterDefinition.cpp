#include "CharacterDefinition.h"
#include "..\plugin\Menu.h"

void CharacterDefinitionV2::Set(CharacterContentDefinitionInfo* info)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_Set);
	if (pat)
		((void(__fastcall*)(CharacterDefinitionV2*, CharacterContentDefinitionInfo*))pat)(this, info);
}

void CharacterDefinitionV2::SetPartner(CharacterContentDefinitionInfo* info)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_SetPartner);
	if (pat)
		((void(__fastcall*)(CharacterDefinitionV2*, CharacterContentDefinitionInfo*))pat)(this, info);
}

void CharacterDefinitionV2::SetAIDrone(int mko, int level)
{
	*(char*)((int64)this + AI_DATA_OFFSET) = mko;
	*(char*)((int64)this + AI_DATA_OFFSET + 1) = level;
}

int CharacterDefinitionV2::GetAIDroneLevel()
{
	return *(char*)((int64)this + AI_DATA_OFFSET + 1);
}

int CharacterDefinitionV2::GetAIDroneScript()
{
	return *(char*)((int64)this + AI_DATA_OFFSET);
}

void CharacterContentDefinitionInfo::Set(FString name, int type)
{
	static uintptr_t pat = _pattern(PATID_CharacterContentDefinition_Get);
	if (pat)
		((void(__thiscall*)(CharacterContentDefinitionInfo*, FString, int))pat)(this, name, type);
}