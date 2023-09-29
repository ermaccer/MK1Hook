#pragma once
#include "../utils.h"


class MissionInfo {
public:
	char pad[0x570];
	bool HideFightHUD;

	void BuildFightHUD();
	void FindObjects();

};

extern MissionInfo* MInfo;

VALIDATE_OFFSET(MissionInfo, HideFightHUD, 0x570);