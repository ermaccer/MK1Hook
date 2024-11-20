#pragma once
#include "..\utils.h"
#include "Engine.h"
#include "..\unreal\FName.h"

#define AI_DATA_OFFSET 280

struct CharacterContentDefinitionInfo {
	char pad[16];
	FName path;
	char _pad[16];
	FName skin;
	char __pad[528];

	void Set(FString name, int type = 7);

};
VALIDATE_SIZE(CharacterContentDefinitionInfo, 576);

class CharacterDefinitionV2 {
public:
	char pad[0xD0];
	char _pad[16];
	FName path;
	char __pad[16];
	FName skin;
	FName extraMoveset;

	void Set(CharacterContentDefinitionInfo* info);
	void SetPartner(CharacterContentDefinitionInfo* info);

	void SetAIDrone(int mko, int level);
	int  GetAIDroneLevel();
	int  GetAIDroneScript();
};

VALIDATE_OFFSET(CharacterDefinitionV2, path, 0xE0);
VALIDATE_OFFSET(CharacterDefinitionV2, skin, 0xF8);
VALIDATE_OFFSET(CharacterDefinitionV2, extraMoveset, 0x100);