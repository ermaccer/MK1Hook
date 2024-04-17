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
