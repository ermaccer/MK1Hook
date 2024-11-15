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
	Base = 1,
	Kameo = 2,
	Kitbash = 4,
	TOTAL_CHARACTER_CLASSES = 3,
};


class FGGameInfo {
public:
	static void FindGameInfo();
	static uintptr_t pGameInfo;

	void Exec(char* line);
	void SetGameSpeed(float speed);

	PlayerInfo* GetInfo(PLAYER_NUM plr);
	int64		GetObj(PLAYER_NUM plr);

	int64		GetMissionInfo();
	int64		GetMissionInfo_ptr(int64 missionInfo);

	FightingTeamDefinition* GetTeam(TEAM_NUM id);

	static void SetStage(int64 backgroundInfo, char* name);
};

FGGameInfo* GetGameInfo();


