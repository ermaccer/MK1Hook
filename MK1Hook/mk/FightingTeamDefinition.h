#pragma once
#include "../utils.h"


class FightingTeamDefinition {
public:
	char pad[80];
	int  teamID; // 84
	char _pad[44];
	int64 primaryCharacter;
	char __pad[408];
	int64 partnerCharacter;

};

VALIDATE_OFFSET(FightingTeamDefinition, primaryCharacter, 0x80);
VALIDATE_OFFSET(FightingTeamDefinition, partnerCharacter, 0x220);