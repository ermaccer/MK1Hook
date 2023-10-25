#pragma once
#include "../utils.h"


class MissionInfo {
public:
	char pad[0x5E0];
	bool HideFightHUD;

	void BuildFightHUD();
	void FindObjects();

};

extern MissionInfo* MInfo;

VALIDATE_OFFSET(MissionInfo, HideFightHUD, 0x5E0);