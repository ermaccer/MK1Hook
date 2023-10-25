#pragma once
#include "PlayerInfo.h"
#include "FightingTeamDefinition.h"
#include "MissionInfo.h"
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
	
	static int64 pPlayerObjs[MAX_PLAYERS];

	void Exec(char* line);
	void SetGameSpeed(float speed);

	PlayerInfo* GetInfo(PLAYER_NUM plr);
	int64		GetObj(PLAYER_NUM plr);

	int64		GetMissionInfo();
	int64		GetMissionInfo_ptr(int64 missionInfo);

	static FightingTeamDefinition* GetTeam(TEAM_NUM id);
	static void OnJump();
};

FGGameInfo* GetGameInfo();