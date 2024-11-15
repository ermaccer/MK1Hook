#pragma once
#include "..\utils.h"

// 0x81C3FA9 - makedrone

struct AIDroneInfo {
	unsigned char ScriptID;
	unsigned char Level;
	char pad[78];
};

class AIDrone {
public:
	// integer in mk12, previously float
	int GetDroneLevel();
	void Set(const char* script);

	static int ScriptToID(const char* script);
};

class PlayerInfo {
public:
	void AdjustMeter(float value);
	void SetMeter(float value);
	void SetDamageMult(float value);
	AIDrone* GetDrone();
};