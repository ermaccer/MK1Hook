#pragma once
#include "..\utils.h"
#include "GameInfo.h"
#include "MKCharacter.h"
#include "PlayerInfo.h"
#include "MKCamera.h"
#include "ContentDefinition.h"
#include "CharacterDefinition.h"

class MKCharacter;
class MKCharacterActor;
class CharacterDefinitionV2;

extern int64(*orgGamelogicJump)(int64, char*, unsigned int, int, int, int, int, int, int);

MKCharacter* GetObj(PLAYER_NUM plr);
MKCharacterActor* GetObjActor(PLAYER_NUM plr);
PlayerInfo*  GetInfo(PLAYER_NUM plr);


void HideHUD();
void ShowHUD();

void SlowGameTimeForXTicks(float speed, int ticks);

int64 GamelogicJump(int64 gameInfoPtr,char* mkoName, unsigned int functionHash, int a3, int a4, int a5, int a6, int a7, int a8);

unsigned int _hash(const char* input);

// wrappers

void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);
char* GetCharacterName(PLAYER_NUM plr);
char* GetCharacterSkinName(PLAYER_NUM plr);

void SetTeamMode(TEAM_NUM plr, TEAM_INFO_MODE mode);
bool IsPartnerTeam(TEAM_NUM plr);

void SetCharacterMKX(PLAYER_NUM plr, char* name, bool tag = false);
void SetCharacterSkin(PLAYER_NUM plr, char* name);
void SetCharacterExtraMoveset(PLAYER_NUM plr, char* name);
void SetCharacterAI(PLAYER_NUM plr, char* script, int level);
void SetCharacterAI(PLAYER_NUM plr, int scriptID, int level);

CharacterDefinitionV2* GetCharacterDefinition(PLAYER_NUM plr);
bool IsCharacterPartner(PLAYER_NUM plr);
