#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

extern void(__fastcall* pProcessPostProcessSettings)(int64, int64, float);
extern void(__fastcall* orgFightStartup)(int64);
extern void(*orgLoadMainMenuBGND)(int64 bgndInfo, FName name);


void ProcessPostProcessSettings(int64 settings, int64 newSettings, float a3);

void PluginDispatch();
void PluginFightStartup(int64 ptr);
void PluginFightStartupTeamModeChange();
void PluginOnJump(char* mkoName);

void USceneComponent_SetRelativeScale3D(int64 obj, FVector* scale);

void FightStartup_Hook(int64 ptr);
void LoadMainMenuBGND_Hook(int64 bgndInfo, FName name);

extern void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);