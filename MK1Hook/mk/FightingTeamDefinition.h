#pragma once
#include "../utils.h"



class FightingTeamDefinition {
public:
	char pad[80];
	int  teamID; // 84
	char _pad[60];
	int64 primaryCharacter;
	char __pad[584];
	int64 partnerCharacter;

};

VALIDATE_OFFSET(FightingTeamDefinition, primaryCharacter, 0x90);
