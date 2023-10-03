#pragma once
#include "TArray.h"
#include "FVector.h"
#include "FQuat.h"
#include "FName.h"
#include "FMatrix.h"
#include "..\utils.h"

class USkeletalMesh {
public:
	int GetNumBones();
};

class USkeletalMeshComponent {
public:
	char pad[0x5A8];
	USkeletalMesh* SkeletalMesh;
	void GetBoneMatrix(FMatrix* result, int id);
	void GetBoneMatrix(const wchar_t* name, FMatrix* result);
	void GetBoneLocation(const wchar_t* name, FVector* result);
	void GetBoneRotation(const wchar_t* name, FVector* result);

	void GetBoneName(FName* result, int id);

	int GetBoneIndexFromString(const wchar_t* BoneName);
};