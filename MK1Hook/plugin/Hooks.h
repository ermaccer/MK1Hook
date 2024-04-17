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

void USceneComponent_SetRelativeScale3D(int64 obj, FVector* scale);


extern void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);