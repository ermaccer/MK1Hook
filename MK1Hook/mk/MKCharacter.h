#pragma once
#include "PlayerInfo.h"
#include "CharacterDefinition.h"
#include "GameInfo.h"
#include "MKScript.h"
#include "MKObject.h"

#include "..\unreal\SkeletalMesh.h"
#include "..\unreal\FRotator.h"
#include "..\unreal\FVector.h"
#include "..\utils.h"

#include "..\plugin\Hooks.h"

class MKCharacterActor : public MKObject {
public:
	USkeletalMeshComponent* GetSkeleton();
	USkeletalMeshComponent* GetHead();
};


class MKCharacter : public MKObject {
public:
	void ExecuteScript(MKScript* script, unsigned int function);
	void ExecutePowerAttack(int64 powerAttackDef);
	void SetScale(FVector* scale);
};


