#include "MKCharacter.h"

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

USkeletalMeshComponent* MKCharacterActor::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x2D0);
}

USkeletalMeshComponent* MKCharacterActor::GetHead()
{
	return nullptr;
}
