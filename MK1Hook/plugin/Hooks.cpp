#include "Hooks.h"
#include "..\unreal\UWorld.h"

void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);

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

	if (TheMenu->m_bChangePlayerScale)
	{
		if (p1) p1->SetScale(&TheMenu->m_vP1Scale);
		if (p2) p2->SetScale(&TheMenu->m_vP2Scale);
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
	TheMenu->OnJump();
	//TheMenu->m_bCustomCameras = false;
}

int64 CharacterDefinition_CreateObject(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_CreateObject);
	
	return ((int64(__fastcall*)(int64, int64, int64, wchar_t*, int64, int64, int64, int64))pat)(a1, a2, a3, name, a5, a6, a7, a8);
}

int64 CharacterDefinition_CreateObject_Hook(int64 a1, int64 a2, int64 a3, wchar_t* name, int64 a5, int64 a6, int64 a7, int64 a8)
{
	// TODO: replace with level scanner
	// seems like mkcharacter no longer has actor ptr, or its id

	int64 result = CharacterDefinition_CreateObject(a1, a2, a3, name, a5, a6, a7, a8);

	// geras clone doesnt have name
	if (name)
	{
		if (wcsstr(name, L"_P1000") && !wcsstr(name, L"Morph"))
			FGGameInfo::pPlayerActorObjs[PLAYER1] = result;
		else if (wcsstr(name, L"_P2000") && !wcsstr(name, L"Morph"))
			FGGameInfo::pPlayerActorObjs[PLAYER2] = result;
	}

	
	return result;
}

void USceneComponent_SetRelativeScale3D(int64 obj, FVector* scale)
{
	USkeletalMeshComponent* curComponent = (USkeletalMeshComponent*)obj;
	if (TheMenu->m_bChangePlayerScale)
	{
		MKCharacterActor* p1Actor = GetObjActor(PLAYER1);
		MKCharacterActor* p2Actor = GetObjActor(PLAYER2);

		if (p1Actor)
		{
			if (curComponent == p1Actor->GetSkeleton())
					*scale = TheMenu->m_vP1Scale;
		}
		if (p2Actor)
		{
			if (curComponent == p2Actor->GetSkeleton())
				*scale = TheMenu->m_vP2Scale;
		}
	}
	

	orgUSceneComponent_SetWorldScale3D(obj, scale);
}
