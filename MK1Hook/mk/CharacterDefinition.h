#pragma once
#include "..\utils.h"
#include "Engine.h"
#include "..\unreal\FName.h"

#define CHARACTER_DEFINITION_SIZE 2336


// 536 bytes
struct CharacterContentDefinition {
	int field0;
	int field4;
	int field8;
	int field12;
	FName path;
	int field24;
	int field28;
	int field32;
	int field36;
	FName skin;
	char pad[488];

	void Set(FString name, int type);
};
VALIDATE_SIZE(CharacterContentDefinition, 536);


class CharacterDefinitionV2 {
public:
	char pad[0xC0];
	FName path;
	char _pad[0x10];
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