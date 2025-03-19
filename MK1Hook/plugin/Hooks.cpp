#include "Hooks.h"
#include "..\unreal\UWorld.h"

void (*orgUSceneComponent_SetWorldScale3D)(int64 obj, FVector* scale);
void(__fastcall* pProcessPostProcessSettings)(int64, int64, float) = nullptr;
void(__fastcall* orgFightStartup)(int64) = nullptr;
void(*orgLoadMainMenuBGND)(int64 bgndInfo, FName name) = nullptr;
void(*pSetPartnerCharacter)(int64, FString, int, int) = nullptr;

void ProcessPostProcessSettings(int64 settings, int64 newSettings, float a3)
{
	if (TheMenu->m_bDisableDOF)
		*(int*)(newSettings + 1208) = 0;

	pProcessPostProcessSettings(settings, newSettings, a3);
}

void PluginDispatch()
{
	GUIImplementation::Gamepad_Process();
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

		if (TheMenu->m_bChangePlayer1Speed)
			p1->SetSpeed(TheMenu->m_fP1Speed);
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

		if (TheMenu->m_bChangePlayer2Speed)
			p2->SetSpeed(TheMenu->m_fP2Speed);
	}

	if (TheMenu->m_bChangePlayerScale)
	{
		if (p1) p1->SetScale(&TheMenu->m_vP1Scale);
		if (p2) p2->SetScale(&TheMenu->m_vP2Scale);
	}

	PluginInterface::OnFrameTick();
	GUIImplementation::Gamepad_Reset();
}

void PluginFightStartup(int64 ptr)
{
	eLog::Message("MK1Hook::Info()", "Starting a new fight!");
	TheMenu->ClearFunctionLists();

	if (TheMenu->m_bStageModifier)
		GetGameInfo()->SetStage(ptr + 0x608, TheMenu->szStageModifierStage);

	PluginFightStartupTeamModeChange();
	PluginFightStartupSkipDialogue(ptr);
	PluginFightStartupAddModifiers(ptr);
	PluginFightStartupCacheLoadedCharacters();

	if (TheMenu->m_bPlayer1Modifier)
		SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

	if (TheMenu->m_bPlayer1SkinModifier)
		SetCharacterSkin(PLAYER1, TheMenu->szPlayer1Skin);
	if (TheMenu->m_bPlayer2SkinModifier)
		SetCharacterSkin(PLAYER2, TheMenu->szPlayer2Skin);

	if (TheMenu->m_bPlayer1MovesetModifier)
		SetCharacterExtraMoveset(PLAYER1, TheMenu->szPlayer1Moveset);
	if (TheMenu->m_bPlayer2MovesetModifier)
		SetCharacterExtraMoveset(PLAYER2, TheMenu->szPlayer2Moveset);

	if (TheMenu->m_bPlayer1KameoModifier)
		SetCharacterMKX(PLAYER3, TheMenu->szPlayer1KameoCharacter);
	if (TheMenu->m_bPlayer2KameoModifier)
		SetCharacterMKX(PLAYER4, TheMenu->szPlayer2KameoCharacter);

	if (TheMenu->m_bPlayer1KameoSkinModifier)
		SetCharacterSkin(PLAYER3, TheMenu->szPlayer1KameoSkin);
	if (TheMenu->m_bPlayer2KameoSkinModifier)
		SetCharacterSkin(PLAYER4, TheMenu->szPlayer2KameoSkin);

	if (TheMenu->m_bAIDroneModifierP1)
		SetCharacterAI(PLAYER1, TheMenu->szPlayer1AI, TheMenu->m_nAIDroneLevelP1);
	if (TheMenu->m_bAIDroneModifierP2)
		SetCharacterAI(PLAYER2, TheMenu->szPlayer2AI, TheMenu->m_nAIDroneLevelP2);

	eLog::Message("MK1Hook::Info()", "Team1");
	eLog::Message("MK1Hook::Info()", "P1: %s Skin: %s", GetCharacterName(PLAYER1), GetCharacterSkinName(PLAYER1));
	if (IsPartnerTeam(TEAM1))
		eLog::Message("MK1Hook::Info()", "P3: %s Skin: %s", GetCharacterName(PLAYER3), GetCharacterSkinName(PLAYER3));

	eLog::Message("MK1Hook::Info()", "Team2");
	eLog::Message("MK1Hook::Info()", "P2: %s Skin: %s", GetCharacterName(PLAYER2), GetCharacterSkinName(PLAYER2));
	if (IsPartnerTeam(TEAM2))
		eLog::Message("MK1Hook::Info()", "P4: %s Skin: %s", GetCharacterName(PLAYER4), GetCharacterSkinName(PLAYER4));

	PluginInterface::OnFightStartup();
}

void PluginFightStartupSkipDialogue(int64 ptr)
{
	if (!TheMenu->m_bDisableDialogueIntro)
		return;

	int64 vTable = *(int64*)(ptr);
	int64 func_0x2B0 = *(int64*)(vTable + 0x2B0);

	int64 missionInfo = ((int64(__thiscall*)(int64))func_0x2B0)(ptr);
	if (missionInfo)
		*(bool*)(missionInfo + 0x98) = false;
}

void PluginFightStartupAddModifiers(int64 ptr)
{
	if (!TheMenu->m_bAddGlobalModifiers)
		return;

	static int fightObjectOffset = 0;

	if (fightObjectOffset == 0)
	{
		int64 pat = _pattern(PATID_FightObjectOffset);
		fightObjectOffset = *(int*)(pat);
	}

	if (!fightObjectOffset)
		return;

	int64 fightObject = *(int64*)(ptr + fightObjectOffset);

	if (!fightObject)
		return;

	unsigned int numModifiers = TheMenu->m_ModifiersList.size();

	std::string modifiersNames = "";
	for (int i = 0; i < numModifiers; i++)
	{
		ModifierEntry& modifier = TheMenu->m_ModifiersList[i];

		modifiersNames += modifier.name.c_str();
		modifiersNames += "(";
		if (modifier.flag & ModifierEntryFlag_P1)
			modifiersNames += "P1";
		if (modifier.flag & ModifierEntryFlag_P2)
			modifiersNames += "P2";
		modifiersNames += ")";
		if (!(i == numModifiers - 1))
			modifiersNames += ",";
	}

	eLog::Message("MK1Hook::Info()", "Used modifiers: %s", modifiersNames.c_str());

	for (int i = 0; i < numModifiers; i++)
	{
		ModifierEntry& modifier = TheMenu->m_ModifiersList[i];

		if (modifier.bothPlayers)
			MKModifier::ActivateModifier(fightObject, TheMenu->m_ModifiersList[i].name.c_str());

		if (modifier.flag & ModifierEntryFlag_P1)
			MKModifier::ActivateModifier(TheMenu->m_ModifiersList[i].name.c_str(), PLAYER1);
		if (modifier.flag & ModifierEntryFlag_P2)
			MKModifier::ActivateModifier(TheMenu->m_ModifiersList[i].name.c_str(), PLAYER2);

	}
}

void PluginFightStartupTeamModeChange()
{
	if (!TheMenu->m_bChangeGameMode)
		return;

	if (TheMenu->m_nCurrentTeamMode == TEAM_INFO_MODE::MODE_TAG && TheMenu->m_bOldTagSwap)
		return;

	// cache stuff to restore after mode reload
	char p1_name[128] = {};
	char p2_name[128] = {};
	char p1_skin[128] = {};
	char p2_skin[128] = {};

	AIDroneInfo p1_ai = {};
	AIDroneInfo p2_ai = {};

	CharacterDefinitionV2* p1_chr = GetCharacterDefinition(PLAYER1);
	CharacterDefinitionV2* p2_chr = GetCharacterDefinition(PLAYER2);

	int p1_level = 0;
	int p1_script = 0;

	int p2_level = 0;
	int p2_script = 0;

	p1_level = p1_chr->GetAIDroneLevel();
	p2_level = p2_chr->GetAIDroneLevel();

	p1_script = p1_chr->GetAIDroneScript();
	p2_script = p2_chr->GetAIDroneScript();


	if (p1_chr && p2_chr)
	{
		p1_ai = *(AIDroneInfo*)((int64)p1_chr + AI_DATA_OFFSET);
		p2_ai = *(AIDroneInfo*)((int64)p2_chr + AI_DATA_OFFSET);
	}

	snprintf(p1_name, sizeof(p1_name), GetCharacterName(PLAYER1));
	snprintf(p2_name, sizeof(p2_name), GetCharacterName(PLAYER2));

	snprintf(p1_skin, sizeof(p1_skin), GetCharacterSkinName(PLAYER1));
	snprintf(p2_skin, sizeof(p2_skin), GetCharacterSkinName(PLAYER2));

	SetTeamMode(TEAM1, (TEAM_INFO_MODE)TheMenu->m_nCurrentTeamMode);
	SetTeamMode(TEAM2, (TEAM_INFO_MODE)TheMenu->m_nCurrentTeamMode);

	SetCharacterMKX(PLAYER1, p1_name);
	SetCharacterMKX(PLAYER2, p2_name);
	SetCharacterSkin(PLAYER1, p1_skin);
	SetCharacterSkin(PLAYER2, p2_skin);

	if (TheMenu->m_nCurrentTeamMode == MODE_TAG)
	{
		SetCharacterMKX(PLAYER3, TheMenu->szPlayer1TagCharacter, true);
		SetCharacterMKX(PLAYER4, TheMenu->szPlayer2TagCharacter, true);
	}

	*(AIDroneInfo*)((int64)p1_chr + AI_DATA_OFFSET) = p1_ai;
	*(AIDroneInfo*)((int64)p2_chr + AI_DATA_OFFSET) = p2_ai;

	SetCharacterAI(PLAYER1, p1_script, p1_level);
	SetCharacterAI(PLAYER2, p2_script, p2_level);

	if (TheMenu->m_nCurrentTeamMode == MODE_TAG)
	{
		SetCharacterAI(PLAYER3, p1_script, p1_level);
		SetCharacterAI(PLAYER4, p2_script, p2_level);
	}
}

void PluginFightStartupCacheLoadedCharacters()
{
	TheMenu->m_LoadedCharacterSkins.clear();
}

void PluginOnJump(char* mkoName)
{
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


void FightStartup_Hook(int64 ptr)
{
	PluginFightStartup(ptr);
	orgFightStartup(ptr);
}

void LoadMainMenuBGND_Hook(int64 bgndInfo, FName name)
{
	if (TheMenu->m_bStageModifierMainMenu)
	{
		GetGameInfo()->SetStage(bgndInfo, TheMenu->szStageModifierStage);
		return;
	}

	if (orgLoadMainMenuBGND)
		orgLoadMainMenuBGND(bgndInfo, name);
}

void SetPartnerCharacter_Hook(int64 ptr, FString name, int plrNum, int flag)
{
	if (TheMenu->m_bOldTagSwap)
	{
		FString str;
		if (plrNum == 0)
		{
			FName newChar(TheMenu->szPlayer1TagCharacter + 5, FNAME_Add, 1);
			newChar.ToString(&str);
		}
		else if (plrNum == 1)
		{
			FName newChar(TheMenu->szPlayer2TagCharacter + 5, FNAME_Add, 1);
			newChar.ToString(&str);
		}
		name = str;
	}
	if (pSetPartnerCharacter)
		pSetPartnerCharacter(ptr, name, plrNum, flag);
}