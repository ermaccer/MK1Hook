#pragma once
#include "PlayerInfo.h"
#include "FightingTeamDefinition.h"

#include "..\utils.h"


enum TEAM_NUM
{
	TEAM1,
	TEAM2
};

enum PLAYER_NUM
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
};

enum eCharacterClass {
	Base,
	Kameo,
	Kitbash,
	TOTAL_CHARACTER_CLASSES
};


class FGGameInfo {
public:
	char pad[0x48C];
	float fGameSpeed;

	static void FindGameInfo();
	static uintptr_t pGameInfo;

	static FightingTeamDefinition* pTeamP1;
	static FightingTeamDefinition* pTeamP2;

	void Exec(char* line);
	void SetGameSpeed(float speed);

	static FightingTeamDefinition* GetTeam(TEAM_NUM id);
};

FGGameInfo* GetGameInfo();