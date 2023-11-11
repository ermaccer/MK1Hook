#include "SteamAPI.h"
#include "..\gui\log.h"
#include "..\steam\Steamworks.h"

CSteamAPILoader*		SteamLoader = nullptr;
HSteamPipe				hSteamPipe = NULL;
HSteamUser				hSteamUser = NULL;
ISteamClient012*		pSteamClient = nullptr;
ISteamFriends014*		pSteamFriends = nullptr;
ISteamUtils007*			pSteamUtils = nullptr;
ISteamApps006*			pSteamApps = nullptr;

bool					ms_bSteamAPIOk = false;

bool SteamAPI_Initialize()
{
	eLog::Message(__FUNCTION__, "Init");

    SteamLoader = new CSteamAPILoader(CSteamAPILoader::k_ESearchOrderSteamInstallFirst);
	CreateInterfaceFn	factory = SteamLoader->GetSteam3Factory();

	if (!factory)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to find SteamAPI factory! Steam functions will not be available.");
		return false;
	}

	pSteamClient = (ISteamClient012*)factory(STEAMCLIENT_INTERFACE_VERSION_012, nullptr);

	if (!pSteamClient)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create SteamAPI client! Steam functions will not be available.");
		return false;
	}


	hSteamPipe = pSteamClient->CreateSteamPipe();

	if (!hSteamPipe)
	{
		pSteamClient->BShutdownIfAllPipesClosed();
		eLog::Message(__FUNCTION__, "ERROR: Failed to create SteamAPI pipe! Steam functions will not be available.");
		return false;
	}

	hSteamUser = pSteamClient->ConnectToGlobalUser(hSteamPipe);

	if (!hSteamUser)
	{
		pSteamClient->BReleaseSteamPipe(hSteamPipe);
		pSteamClient->BShutdownIfAllPipesClosed();
		eLog::Message(__FUNCTION__, "ERROR: Failed to create SteamAPI user! Steam functions will not be available.");
		return false;
	}

	pSteamFriends = (ISteamFriends014*)pSteamClient->GetISteamFriends(hSteamUser, hSteamPipe, STEAMFRIENDS_INTERFACE_VERSION_014);
	pSteamUtils = (ISteamUtils007*)pSteamClient->GetISteamUtils(hSteamPipe, STEAMUTILS_INTERFACE_VERSION_007);
	pSteamApps = (ISteamApps006*)pSteamClient->GetISteamApps(hSteamUser, hSteamPipe, STEAMAPPS_INTERFACE_VERSION_006);

	ms_bSteamAPIOk = true;
	eLog::Message(__FUNCTION__, "INFO: Init OK");
    return true;
}

void SteamAPI_Destroy()
{
	if (pSteamClient && hSteamPipe)
	{
		if (hSteamUser)
			pSteamClient->ReleaseUser(hSteamPipe, hSteamUser);
		pSteamClient->BReleaseSteamPipe(hSteamPipe);
		pSteamClient->BShutdownIfAllPipesClosed();

		pSteamFriends = nullptr;
		pSteamUtils = nullptr;
	}
	if (SteamLoader)
		delete SteamLoader;
}

unsigned int SteamAPI::GetApplicationID()
{
	if (pSteamUtils)
		return pSteamUtils->GetAppID();

	return -1;
}

const char* SteamAPI::GetUsername()
{
	if (pSteamFriends)
		return pSteamFriends->GetPersonaName();
	return "N/A";
}

bool SteamAPI::IsAppInstalled(unsigned int appID)
{
	if (pSteamApps)
		return pSteamApps->BIsDlcInstalled(appID);
	return false;
}
