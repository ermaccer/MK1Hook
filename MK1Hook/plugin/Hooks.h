#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "..\mk\MKModifier.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "..\helper\eGamepadManager.h"
#include "PluginInterface.h"

extern void(__fastcall* pProcessPostProcessSettings)(int64, int64, float);
extern void(__fastcall* orgFightStartup)(int64);
extern void(*orgLoadMainMenuBGND)(int64 bgndInfo, FName name);
extern void(*pSetPartnerCharacter)(int64, FString, int, int);



void ProcessPostProcessSettings(int64 settings, int64 newSettings, float a3);

void PluginDispatch();
void PluginFightStartup(int64 ptr);
void PluginFightStartupSkipDialogue(int64 ptr);
void PluginFightStartupAddModifiers(int64 ptr);
void PluginFightStartupTeamModeChange();
void PluginFightStartupCacheLoadedCharacters();
void PluginOnJump(char* mkoName);

void USceneComponent_SetRelativeScale3D(int64 obj, FVector* scale);

void FightStartup_Hook(int64 ptr);
void LoadMainMenuBGND_Hook(int64 bgndInfo, FName name);
void SetPartnerCharacter_Hook(int64 ptr, FString name, int plrNum, int flag);

extern void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);