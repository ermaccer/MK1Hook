#include "CharacterDefinition.h"
#include "..\plugin\Menu.h"

void(*orgCharacterDefinition_Load)(CharacterDefinitionV2*);
void(*orgCharacterDefinition_LoadKameo)(CharacterDefinitionV2*);

void CharacterDefinitionV2::LoadHook()
{
	int chrID = -1;

	FString charName;
	path.ToString(&charName);

	FString skinName;
	skin.ToString(&skinName);

	FString movesetName;
	extraMoveset.ToString(&movesetName);


	if (TheMenu->m_nCurrentCharModifier == MODIFIER_CHARSWAP && TheMenu->m_bPlayer1Modifier)
	{
		int newIndex = TheMenu->ConvertCharacterNameToInternalString(0, Base);
		if (path.Index == newIndex)
		{
			path.Index = TheMenu->ConvertCharacterNameToInternalString(1, Base);
			if (TheMenu->m_bPlayer1SkinModifier)
			{
				newIndex = TheMenu->ConvertSkinToInternalString(0);
				if (newIndex > 0)
					skin.Index = newIndex;
			}

		}
			
	}

	FightingTeamDefinition* team = GetGameInfo()->GetTeam(TEAM1);
	FightingTeamDefinition* team2 = GetGameInfo()->GetTeam(TEAM2);

	if (!team)
		return;
	if (!team2)
		return;


	if ((int64)&team->primaryCharacter == (int64)this)
		chrID = 0;
	if ((int64)&team2->primaryCharacter == (int64)this)
		chrID = 1;

	eLog::Message(__FUNCTION__, "Setting P%d as %ws [Skin: %ws] [Extra Moveset: %ws]",chrID + 1, charName.GetStr(), skinName.GetStr(), movesetName.GetStr());

	if (chrID == -1)
		return;

	if (TheMenu->m_nCurrentCharModifier == MODIFIER_NORMAL)
	{
		if (TheMenu->m_bPlayer1Modifier && chrID == 0)
		{
			int newIndex = TheMenu->ConvertCharacterNameToInternalString(0, Base);
			if (newIndex > 0)
				path.Index = newIndex;
		}

		if (TheMenu->m_bPlayer2Modifier && chrID == 1)
		{
			int newIndex = TheMenu->ConvertCharacterNameToInternalString(1, Base);
			if (newIndex > 0)
				path.Index = newIndex;
		}
		if (TheMenu->m_bPlayer1SkinModifier && chrID == 0)
		{
			int newIndex = TheMenu->ConvertSkinToInternalString(0);
			if (newIndex > 0)
				skin.Index = newIndex;
		}
		if (TheMenu->m_bPlayer2SkinModifier && chrID == 1)
		{
			int newIndex = TheMenu->ConvertSkinToInternalString(1);
			if (newIndex > 0)
				skin.Index = newIndex;
		}
	}
}

void CharacterDefinitionV2::LoadKameoHook()
{
	int chrID = -1;

	FString charName;
	path.ToString(&charName);

	FString skinName;
	skin.ToString(&skinName);

	FightingTeamDefinition* team = GetGameInfo()->GetTeam(TEAM1);
	FightingTeamDefinition* team2 = GetGameInfo()->GetTeam(TEAM2);


	if (TheMenu->m_bKameoReplace)
	{
		CharacterContentDefinitionInfo def;
		CharacterContentDefinitionInfo def2;

		FName characterName(TheMenu->szPlayerKameoSource + 5, FNAME_Add, 1);
		FString characterString;
		characterName.ToString(&characterString);
		def.Set(characterString, 7);

		FName characterNameSwap(TheMenu->szPlayerKameoSwap + 5, FNAME_Add, 1);
		FString characterStringSwap;
		characterNameSwap.ToString(&characterStringSwap);
		def2.Set(characterStringSwap, 7);

		if (TheMenu->m_bKameoForceReplace)
		{
			path.Index = def2.path.Index;
		}
		else
		{
			if (path.Index == def.path.Index)
			{
				path.Index = def2.path.Index;
			}
		}

	}

	if (!team)
		return;
	if (!team2)
		return;

	if ((int64)&team->partnerCharacter == (int64)this)
		chrID = 0;
	if ((int64)&team2->partnerCharacter == (int64)this)
		chrID = 1;

	eLog::Message(__FUNCTION__, "Setting KAM%d as %ws [Skin: %ws]", chrID + 1, charName.GetStr(), skinName.GetStr());

	if (chrID == -1)
		return;

	if (TheMenu->m_bPlayer1KameoSkinModifier && chrID == 0)
	{
		int newIndex = TheMenu->ConvertKameoSkinToInternalString(0);
		if (newIndex > 0)
			skin.Index = newIndex;
	}
	if (TheMenu->m_bPlayer2KameoSkinModifier && chrID == 1)
	{
		int newIndex = TheMenu->ConvertKameoSkinToInternalString(1);
		if (newIndex > 0)
			skin.Index = newIndex;
	}
}

void CharacterDefinition_Load(CharacterDefinitionV2* chr)
{
	chr->LoadHook();
	orgCharacterDefinition_Load(chr);
}

void CharacterDefinition_LoadKameo(CharacterDefinitionV2* chr)
{
	chr->LoadKameoHook();
	orgCharacterDefinition_LoadKameo(chr);
}

void SetPartnerCharacter(int64 ptr, FString name, int plrNum, int flag)
{
	if (TheMenu->m_bEnableTagMode)
	{
		FString str;
		if (plrNum == 0)
		{
			FName newChar(TheMenu->szPlayer1TagCharacter, FNAME_Add, 1);
			newChar.ToString(&str);
		}
		else if (plrNum == 1)
		{
			FName newChar(TheMenu->szPlayer2TagCharacter, FNAME_Add, 1);
			newChar.ToString(&str);
		}
		name = str;
	}
	static uintptr_t pat = _pattern(PATID_SetPartnerCharacter);
	if (pat)
		((void(__thiscall*)(int64, FString, int, int))pat)(ptr, name, plrNum, flag);

}

void CharacterContentDefinitionInfo::Set(FString name, int type)
{
	static uintptr_t pat = _pattern(PATID_CharacterContentDefinition_Get);
	if (pat)
		((void(__thiscall*)(CharacterContentDefinitionInfo*, FString, int))pat)(this, name, type);
}
