#pragma once
#include "PlayerInfo.h"
#include "..\utils.h"


// + 1000 in mk12
enum PLAYER_NUM
{
	PLAYER1 = 1000,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
};



class FGGameInfo {
public:
	char pad[0x48C];
	float fGameSpeed;

	static void FindGameInfo();
	static uintptr_t pGameInfo;

	void SetGameSpeed(float speed);
};

FGGameInfo* GetGameInfo();