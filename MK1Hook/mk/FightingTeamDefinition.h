#pragma once
#include "../utils.h"


#define TEAM_MAIN_OFFSET 8
#define TEAM_PARTNER_OFFSET 600


enum TEAM_INFO_MODE {
	MODE_SINGLE,
	MODE_KAMEO,
	MODE_TAG,
	TOTAL_TEAM_MODES
};


class FightingTeamDefinition {
public:
	char pad[80];
	int  teamID;

	void SetMode(TEAM_INFO_MODE mode);	
	bool IsPartnerMode();

	int64 GetDefinitions();
	int64 GetClass();

	static int64 GetKameoClass();
	static int64 GetTagClass();
};


extern int64(*pTeamInfo_SetKameoMode)(FightingTeamDefinition*, bool);
extern int64(*pTeamInfo_SetTagMode)(FightingTeamDefinition*, bool);
extern int64(*pTeamInfo_SetSingleMode)(FightingTeamDefinition*, bool);


extern int64(*pTeamInfo_GetKameoClass)();
extern int64(*pTeamInfo_GetTagClass)();