#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

void PluginDispatch();
void PluginFightStartup();
void PluginOnJump(char* mkoName);

int64 CharacterDefinition_CreateObject(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8);
int64 CharacterDefinition_CreateObject_Hook(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8);
void USceneComponent_SetRelativeScale3D(int64 obj, FVector* scale);


extern void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);