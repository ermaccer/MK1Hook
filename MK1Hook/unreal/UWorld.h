#pragma once
#include "..\utils.h"
#include "..\unreal\TArray.h"
#include "ULevel.h"


class UWorld {
public:
	char pad[48];
	ULevel* PersistentLevel;
	char _pad[88];
	TArray<ULevelStreaming*>  StreamingLevels;

	static UWorld** GWorld;
	static void FindWorld();
};
VALIDATE_OFFSET(UWorld, PersistentLevel, 0x30);
VALIDATE_OFFSET(UWorld, StreamingLevels, 0x90);




UWorld* GetWorld();