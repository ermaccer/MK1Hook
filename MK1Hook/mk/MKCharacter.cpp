#include "MKCharacter.h"


USkeletalMeshComponent* MKCharacter::GetSkeleton()
{
    return *(USkeletalMeshComponent**)((int64)this + 0x2C0);
}

void MKCharacter::ExecuteScript(MKScript* script, unsigned int function)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScriptCharacterAction*, int, int64))pat)(this, Create_CharacterScriptAction(script, function), 1, 0);
}
