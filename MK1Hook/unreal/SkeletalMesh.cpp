#include "SkeletalMesh.h"

void USkeletalMeshComponent::GetBoneMatrix(FMatrix* result, int id)
{
	static uintptr_t pat = _pattern(PATID_USkeletalMeshComponent_GetBoneMatrix);
	if (pat)
		((void(__fastcall*)(USkeletalMeshComponent*, FMatrix*, int))pat)(this, result, id);
}

void USkeletalMeshComponent::GetBoneMatrix(const wchar_t* name, FMatrix* result)
{
	int boneID = GetBoneIndexFromString(name);
	if (boneID < 0)
		return;
	GetBoneMatrix(result, boneID);
}

void USkeletalMeshComponent::GetBoneLocation(const wchar_t* name, FVector* result)
{
	int boneID = GetBoneIndexFromString(name);
	if (boneID < 0)
		*result = { 0.0f, 0.0f, 0.0f };

	FMatrix mat = {};
	GetBoneMatrix(&mat, boneID);
	*result = mat.GetPos();
}

void USkeletalMeshComponent::GetBoneRotation(const wchar_t* name, FVector* result)
{
	int boneID = GetBoneIndexFromString(name);
	if (boneID < 0)
		*result = { 0.0f, 0.0f, 0.0f };

	FMatrix mat = {};
	GetBoneMatrix(&mat, boneID);

	mat.Rotator(result);
}

void USkeletalMeshComponent::GetBoneName(FName* result, int id)
{
	static uintptr_t pat = _pattern(PATID_USkeletalMeshComponent_GetBoneName);
	if (pat)
		((void(__fastcall*)(USkeletalMeshComponent*, FName*, int))pat)(this, result, id);
}

int USkeletalMeshComponent::GetBoneIndexFromString(const wchar_t* BoneName)
{
	for (int i = 0; i < SkeletalMesh->GetNumBones(); i++)
	{
		FName name;
		GetBoneName(&name, i);

		if (name.Index > 0)
		{
			FString boneName;
			name.ToString(&boneName);
			if (wcscmp(boneName.GetStr(), BoneName) == 0)
			{
				return i;
			}
		}
	}

	return -1;
}

int USkeletalMesh::GetNumBones()
{
	return *(int*)(this + 0x238);
}
