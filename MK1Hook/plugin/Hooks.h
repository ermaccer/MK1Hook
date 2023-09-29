#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

extern int64 (*orgUObject_CreateDefaultSubobject)(int64, FName, int64, int64, bool, bool);

void PluginDispatch();
void PluginFightStartup();
void PluginOnJump(char* mkoName);

int64 UObject_CreateDefaultSubobject(int64 ptr, FName name, int64 a3, int64 a4, bool a5, bool a6);