#include "MKCharacter.h"

USkeletalMeshComponent* MKCharacter::GetSkeleton()
{
    return *(USkeletalMeshComponent**)((int64)this + 0x2C0);
}
