#include "Hooks.h"

int64(*orgUObject_CreateDefaultSubobject)(int64, FName, int64, int64, bool, bool);


void PluginDispatch()
{
	TheMenu->Process();
	eMouse::UpdateMouse();
	Notifications->Update();

	FGGameInfo* GameInfo = GetGameInfo();
	MKCharacter* p1 = GetObj(PLAYER1);
	MKCharacter* p2 = GetObj(PLAYER2);



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
	FGGameInfo::OnJump();
	//TheMenu->m_bCustomCameras = false;
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


int64 CharacterDefinition_CreateObject(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_CreateObject);
	
	return ((int64(__fastcall*)(int64, int64, int64, wchar_t*, int64, int64, int64, int64))pat)(a1, a2, a3, name, a5, a6, a7, a8);
}

int64 CharacterDefinition_CreateObject_Hook(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8)
{
	int64 result = CharacterDefinition_CreateObject(a1, a2, a3, name, a5, a6, a7, a8);

	// geras clone doesnt have name
	if (name)
	{
		if (wcsstr(name, L"_P1000") && !wcsstr(name, L"Morph"))
			FGGameInfo::pPlayerObjs[PLAYER1] = result;
		else if (wcsstr(name, L"_P2000") && !wcsstr(name, L"Morph"))
			FGGameInfo::pPlayerObjs[PLAYER2] = result;
	}

	
	return result;
}
