#include "MKCharacter.h"

void MKCharacter::ExecuteScript(MKScript* script, unsigned int function)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScriptCharacterAction*, int, int64))pat)(this, Create_CharacterScriptAction(script, function), 1, 0);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__thiscall*)(MKCharacter*, float))_addr(0x140FF26F0))(this, speed);
}

USkeletalMeshComponent* MKCharacterActor::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x2C0);
}