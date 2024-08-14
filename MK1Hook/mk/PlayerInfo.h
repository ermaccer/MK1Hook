#pragma once
#include "..\utils.h"


class AIDrone {
public:
	// integer in mk12, previously float
	int GetDroneLevel();
};

class PlayerInfo {
public:
	void AdjustMeter(float value);
	void SetMeter(float value);
	void SetDamageMult(float value);
	AIDrone* GetDrone();
};