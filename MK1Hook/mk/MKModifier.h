#pragma once
#include "../utils.h"
#include "../unreal/FName.h"
#include "../unreal/TArray.h"
#include "../unreal/FString.h"
#include "GameInfo.h"


class BaseModifier {
public:
	char _pad[104] = {};
};
VALIDATE_SIZE(BaseModifier, 104);

class GlobalModifier : public BaseModifier {
public:
	GlobalModifier();
	GlobalModifier(FString name, float level = 1.0f);
};

class TeamModifier : public BaseModifier {
public:
	TeamModifier();
	TeamModifier(FString name, float level = 1.0f);
};



class MKModifier {
public:
	static void ActivateModifier(int64 fightObject, const char* name);
	static void ActivateModifier(const char* name, PLAYER_NUM player);
};

extern void(*pGlobalModifier_Constructor)(GlobalModifier*, wchar_t*, float);
extern void(*pTeamModifier_Constructor)(TeamModifier*, wchar_t*, float);