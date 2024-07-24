#pragma once
#include "../utils.h"



class FightingTeamDefinition {
public:
	char pad[80];
	int  teamID;

	int64 GetPrimaryAddress();
	int64 GetPartnerAddress();

};

