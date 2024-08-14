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
	PlayerInfo* p1_info = GetInfo(PLAYER1);
	PlayerInfo* p2_info = GetInfo(PLAYER2);

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

	if (p1)
	{
		if (TheMenu->m_bInfiniteHealthP1)	p1->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)		p1->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)	p1->SetLife(0.01f);

		if (TheMenu->m_bInfiniteMeterP1)
		{
			if (p1_info)
				p1_info->SetMeter(1000.0f);
		}

		if (TheMenu->m_bZeroMeterP1)
		{
			if (p1_info)
				p1_info->SetMeter(-1000.0f);
		}

		if (TheMenu->m_bFastUppercutsP1)
			p1->SetFastUppercutRecovery(true);

		if (TheMenu->m_bInfiniteXraysP1)
			p1->SetXRayInfinite(true);

		if (TheMenu->m_bXrayAlwaysP1)
			p1->SetXRayNoRequirement(true);

		if (TheMenu->m_bEasyBrutalitiesP1)
			p1->SetEasyBrutalities(true);

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p1_info)
				p1_info->SetDamageMult(1.0f);
		}
	}


	if (p2)
	{
		if (TheMenu->m_bInfiniteHealthP2)	p2->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP2)	p2->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP2)	p2->SetLife(0.01f);

		if (TheMenu->m_bInfiniteMeterP2)
		{
			if (p2_info)
				p2_info->SetMeter(1000.0f);
		}

		if (TheMenu->m_bZeroMeterP2)
		{
			if (p2_info)
				p2_info->SetMeter(-1000.0f);
		}


		if (TheMenu->m_bFastUppercutsP2)
			p2->SetFastUppercutRecovery(true);

		if (TheMenu->m_bInfiniteXraysP2)
			p2->SetXRayInfinite(true);

		if (TheMenu->m_bXrayAlwaysP2)
			p2->SetXRayNoRequirement(true);

		if (TheMenu->m_bEasyBrutalitiesP2)
			p2->SetEasyBrutalities(true);

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p2_info)
				p2_info->SetDamageMult(1.0f);
		}
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
