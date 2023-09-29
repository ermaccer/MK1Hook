#include "Hooks.h"

int64(*orgUObject_CreateDefaultSubobject)(int64, FName, int64, int64, bool, bool);


void PluginDispatch()
{
	TheMenu->Process();
	eMouse::UpdateMouse();
	Notifications->Update();

	FGGameInfo* GameInfo = GetGameInfo();

	if (!GameInfo)
		return;

	if (TheMenu->m_bSlowMotion)
	{
		GameInfo->SetGameSpeed(TheMenu->m_fSlowMotionSpeed);
	}

	if (TheMenu->m_bFreezeWorld)
	{
		GameInfo->SetGameSpeed(0.001f);
	}


	PluginInterface::OnFrameTick();
}

void PluginFightStartup()
{
	printf("MK12Hook::Info() | Starting a new fight!\n");

}

void PluginOnJump(char* mkoName)
{
	FGGameInfo::pTeamP1 = nullptr;
	FGGameInfo::pTeamP2 = nullptr;
}

int64 UObject_CreateDefaultSubobject(int64 ptr, FName name, int64 a3, int64 a4, bool a5, bool a6)
{
	int64 result = orgUObject_CreateDefaultSubobject(ptr, name, a3, a4, a5, a6);

	if (name.Index > 0)
	{
		FString str;
		name.ToString(&str);

		if (wcscmp(str.GetStr(), L"Team1Definition") == 0)
		{
			FGGameInfo::pTeamP1 = (FightingTeamDefinition*)result;
		}

		if (wcscmp(str.GetStr(), L"Team2Definition") == 0)
		{
			FGGameInfo::pTeamP2 = (FightingTeamDefinition*)result;
		}
	}

	return result;
}
