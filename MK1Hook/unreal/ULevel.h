#pragma once
#include "TArray.h"
#include "UObject.h"
#include "UWorld.h"

class UWorld;

class ULevel {
public:
	char pad[152];
	TArray<UObject*> Actors;
};
VALIDATE_OFFSET(ULevel, Actors, 0x98);

class ULevelStreaming {
public:
	char pad[296];
	ULevel* LoadedLevel;
};
VALIDATE_OFFSET(ULevelStreaming, LoadedLevel, 0x128);