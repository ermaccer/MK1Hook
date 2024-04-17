#pragma once
#include "..\utils.h"
#include "Engine.h"
#include "..\unreal\FName.h"


struct CharacterContentDefinitionInfo {
	char pad[16];
	FName path;
	char _pad[16];
	FName skin;
	char __pad[1024];

	void Set(FString name, int type = 7);
};

class CharacterDefinitionV2 {
public:
	char pad[0xD0];
	char _pad[16];
	FName path;
	char __pad[16];
	FName skin;
	FName extraMoveset;

	void LoadHook();
	void LoadKameoHook();
};
VALIDATE_OFFSET(CharacterDefinitionV2, path, 0xE0);
VALIDATE_OFFSET(CharacterDefinitionV2, skin, 0xF8);
VALIDATE_OFFSET(CharacterDefinitionV2, extraMoveset, 0x100);



void CharacterDefinition_Load(CharacterDefinitionV2* chr);
void CharacterDefinition_LoadKameo(CharacterDefinitionV2* chr);

extern void(*orgCharacterDefinition_Load)(CharacterDefinitionV2*);
extern void(*orgCharacterDefinition_LoadKameo)(CharacterDefinitionV2*);

void SetPartnerCharacter(int64 ptr, FString name, int plrNum, int flag);