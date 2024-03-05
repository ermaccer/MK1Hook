#include "UWorld.h"
UWorld** UWorld::GWorld = nullptr;
void UWorld::FindWorld()
{
	static uintptr_t pat = _pattern(PATID_UWorld_GWorld);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		UWorld::GWorld = (UWorld**)(pat + offset + 4);
	}
}

UWorld* GetWorld()
{
	if (UWorld::GWorld)
		return *UWorld::GWorld;

	return nullptr;
}

