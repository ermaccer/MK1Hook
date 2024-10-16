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

	// TODO: find actor in MKCharacter
	static int64 pPlayerActorObjs[MAX_PLAYERS];

	void Exec(char* line);
	void SetGameSpeed(float speed);

	PlayerInfo* GetInfo(PLAYER_NUM plr);
	int64		GetObj(PLAYER_NUM plr);

	int64		GetMissionInfo();
	int64		GetMissionInfo_ptr(int64 missionInfo);

	FightingTeamDefinition* GetTeam(TEAM_NUM id);
	static void OnJump();
	static void LoadBackgroundHook(FGGameInfo* info, int64 backgroundInfo);
};

FGGameInfo* GetGameInfo();


extern void(*orgFGGameInfo_SetBackground)(FGGameInfo*, int64);