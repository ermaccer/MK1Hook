#pragma once
#include "..\utils.h"
#include "Engine.h"
#include "..\unreal\FName.h"

// 560 bytes
struct CharacterContentDefinitionInfo {
	char pad[16];
	FName path;
	char _pad[16];
	FName skin;
	char __pad[512];

	void Set(FString name, int type = 7);
};
VALIDATE_SIZE(CharacterContentDefinitionInfo, 560);


class CharacterDefinitionV2 {
public:
	char pad[0xB0];
	char _pad[16];
	FName path;
	char __pad[16];
	FName skin;
	FName extraMoveset;

	void LoadHook();
	void LoadKameoHook();
};
VALIDATE_OFFSET(CharacterDefinitionV2, path, 0xC0);
VALIDATE_OFFSET(CharacterDefinitionV2, skin, 0xD8);
VALIDATE_OFFSET(CharacterDefinitionV2, extraMoveset, 0xE0);



void CharacterDefinition_Load(CharacterDefinitionV2* chr);
void CharacterDefinition_LoadKameo(CharacterDefinitionV2* chr);

extern void(*orgCharacterDefinition_Load)(CharacterDefinitionV2*);
extern void(*orgCharacterDefinition_LoadKameo)(CharacterDefinitionV2*);

void SetPartnerCharacter(int64 ptr, FString name, int plrNum, int flag);