#pragma once
#include "..\utils.h"
#include "..\unreal\FName.h"

struct MKSkeletalObjSoftPtr {
	char pad[16];
	FName path;
	char _pad[16];
};
VALIDATE_SIZE(MKSkeletalObjSoftPtr, 40);

class ContentDefinition {
public:
	char _pad[0xA8];
	TArray<MKSkeletalObjSoftPtr> skins;
};


class KameoContentDefinition {
public:
	char _pad[0xA8];
	TArray<MKSkeletalObjSoftPtr> skins;
};


// 
void ContentDefinition_Log(ContentDefinition* chr);
void ContentDefinition_LoadHook(ContentDefinition* chr);

void ContentDefinition_Load(ContentDefinition* chr, int64 a2);
void KameoContentDefinition_Load(KameoContentDefinition* chr, int64 a2);


extern void(*orgContentDefinition_Load)(ContentDefinition*, int64);
extern void(*orgKameoContentDefinition_Load)(KameoContentDefinition*, int64);