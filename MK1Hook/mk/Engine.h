#pragma once
#include "..\utils.h"
#include "GameInfo.h"
#include "MKCharacter.h"
#include "PlayerInfo.h"
#include "MKCamera.h"
#include "MissionInfo.h"
#include "ContentDefinition.h"

class MKCharacter;

extern int64(*orgGamelogicJump)(int64, char*, unsigned int, int, int, int, int, int, int);
extern int64(*orgSetCharacterDefinitions)(int64,FightingTeamDefinition*, int);

MKCharacter* GetObj(PLAYER_NUM plr);
PlayerInfo*  GetInfo(PLAYER_NUM plr);


void HideHUD();
void ShowHUD();


int64 GamelogicJump(int64 gameInfoPtr,char* mkoName, unsigned int functionHash, int a3, int a4, int a5, int a6, int a7, int a8);

void SetCharacterDefinitions(int64 data, FightingTeamDefinition* team, int unk);

unsigned int _hash(const char* input);

void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);