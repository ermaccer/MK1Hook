#pragma once
#include "..\utils.h"
#include "Engine.h"
#include "..\unreal\FName.h"

#define CHARACTER_DEFINITION_SIZE 2336


struct CharacterInfo {
	int field0;
	int field4;
	int field8;
	int field12;
	FName path;
	int field20;
};

class CharacterDefinitionV2 {
public:
	char pad[0x90];
	FName path;
	char _pad[0x10];
	FName skin;
	FName extraMoveset;

	// TOOD: figure out info
	void Set(CharacterInfo* definition, int64 loadout);
	void LoadHook();
	void LoadKameoHook();
};
VALIDATE_OFFSET(CharacterDefinitionV2, path, 0x90);
VALIDATE_OFFSET(CharacterDefinitionV2, skin, 0xA8);
VALIDATE_OFFSET(CharacterDefinitionV2, extraMoveset, 0xB0);



void CharacterDefinition_Load(CharacterDefinitionV2* chr);
void CharacterDefinition_LoadKameo(CharacterDefinitionV2* chr);

extern void(*orgCharacterDefinition_Load)(CharacterDefinitionV2*);
extern void(*orgCharacterDefinition_LoadKameo)(CharacterDefinitionV2*);

void SetPartnerCharacter(int64 ptr, FString name, int plrNum, int flag);