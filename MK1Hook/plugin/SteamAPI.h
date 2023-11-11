#pragma once

// uses open steamworks

bool SteamAPI_Initialize();
void SteamAPI_Destroy();

namespace SteamAPI {
	unsigned int GetApplicationID();
	const char* GetUsername();
	bool		IsAppInstalled(unsigned int appID);
}