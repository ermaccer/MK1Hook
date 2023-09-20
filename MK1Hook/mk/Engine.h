#pragma once
#include "..\utils.h"
#include "GameInfo.h"
#include "MKCharacter.h"
#include "PlayerInfo.h"
#include "MKCamera.h"
#include "MissionInfo.h"

MKCharacter* GetObj(PLAYER_NUM plr);
PlayerInfo*  GetInfo(PLAYER_NUM plr);

unsigned int _hash(const char* input);
