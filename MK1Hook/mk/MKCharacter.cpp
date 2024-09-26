#include "MKCharacter.h"


/*
FLAG NOTES

singular 4 byte flags moved into seperate booleans BUT commands exactly the same as mk11 so:

HASH
0xA960173A - MKCharacter->flags?, inlined everywhere
0x700CC6D2 - MKCharacter->IsQuickUppercutRecoveryEnabled, any attack d2 in .mko, off 0x83 (update)
0x1F23F5F0 - MKCharacter->IsSupermoveAllowed, off 0x9D (update)


flags + 8 = health data
0x2c = health


*/

void MKCharacter::ExecuteScript(MKScript* script, unsigned int function)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScriptCharacterAction*, int, int64))pat)(this, Create_CharacterScriptAction(script, function), 1, 0);
}

void MKCharacter::ExecutePowerAttack(int64 powerAttackDef)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScriptCharacterAttackAction*, int, int64))pat)(this, Create_CharacterScriptAttackAction(powerAttackDef, (int64)this, 0), 1, 0);
}



void MKCharacter::SetLife(float life)
{
	int offset = GetFlagsOffset();
	if (offset > 0)
	{
		offset += 8;
		int64 healthInfo = *(int64*)((int64)this + offset);
		*(float*)(healthInfo + 0x28) = life;
		*(float*)(healthInfo + 0x2C) = life;
	}
}

void MKCharacter::SetScale(FVector* scale)
{
	PLAYER_NUM myID = PLAYER1;
	if (this == GetObj(PLAYER2))
		myID = PLAYER2;

	MKCharacterActor* actor = GetObjActor(myID);
	if (actor && actor->GetSkeleton())
	{
		USceneComponent_SetRelativeScale3D((int64)actor->GetSkeleton(), scale);
	}
}

void MKCharacter::SetFlag(int offset, bool status)
{
	int64 flags = GetFlags();
	if (flags)
	{
		*(bool*)(flags + offset) = status;
	}
}

void MKCharacter::SetFastUppercutRecovery(bool enable)
{
	SetFlag(0x83, enable);
}

void MKCharacter::SetXRayInfinite(bool enable)
{
	SetFlag(0x47, enable);
}

void MKCharacter::SetXRayNoRequirement(bool enable)
{
	SetFlag(0x9D, enable);
}

void MKCharacter::SetEasyBrutalities(bool enable)
{
	SetFlag(0x2D, enable);
}

int64 MKCharacter::GetFlags()
{
	int offset = GetFlagsOffset();
	if (offset > 0)
	{
		return *(int64*)((int64)this + offset);
	}
	return 0;
}

int MKCharacter::GetFlagsOffset()
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_FlagsOffset);
	if (pat)
	{
		unsigned int offset = *(int*)(pat);
		return offset;
	}

	return 0;
}

USkeletalMeshComponent* MKCharacterActor::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x2D0);
}

USkeletalMeshComponent* MKCharacterActor::GetHead()
{
	return nullptr;
}
