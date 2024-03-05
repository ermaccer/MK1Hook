#include "Engine.h"
#include "..\plugin\Hooks.h"
#include "..\plugin\Settings.h"
#include "..\unreal\UWorld.h"

int64(*orgGamelogicJump)(int64, char*, unsigned int, int, int, int, int, int, int);
int64(*orgSetCharacterDefinitions)(int64, FightingTeamDefinition*, int);

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return (MKCharacter*)GetGameInfo()->GetObj(plr);
}

MKCharacterActor* GetObjActor(PLAYER_NUM plr)
{
	UWorld* w = GetWorld();

	if (!w)
		return nullptr;

	if (!w->PersistentLevel)
		return nullptr;

	ULevel* p = w->PersistentLevel;

	const wchar_t* actorName = L"P1000";
	if (plr == PLAYER2)
		actorName = L"P2000";

	for (int i = 0; i < p->Actors.Count; i++)
	{
		UObject* a = p->Actors.Get(i);
		if (a)
		{
			FString objName;
			a->Name.ToString(&objName);

			wchar_t* wstrName = objName.GetStr();
			if (wcsstr(wstrName, actorName) && !(wcsstr(wstrName, L"Morph")) && !(wcsstr(wstrName, L"Clone")))
				return (MKCharacterActor*)a;
		}
	}
	return nullptr;
	//return (MKCharacterActor*)FGGameInfo::pPlayerActorObjs[plr];
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return GetGameInfo()->GetInfo(plr);
}

void HideHUD()
{
	static uintptr_t pat = _pattern(PATID_HideHUD);
	if (pat)
		((void(__thiscall*)(int64, int))pat)(GetGameInfo()->GetMissionInfo(), 0);
}

void ShowHUD()
{
	static uintptr_t pat = _pattern(PATID_HideHUD);
	if (pat)
		((void(__thiscall*)(int64, int))pat)(GetGameInfo()->GetMissionInfo(), 1);
}

int64 GamelogicJump(int64 gameInfoPtr, char* mkoName, unsigned int functionHash, int a3, int a4, int a5, int a6, int a7, int a8)
{
	PluginOnJump(mkoName);
	if (SettingsMgr->bEnable60FPSPatch)
	{
		if (SettingsMgr->b60FPSPatchInvasionsOnly)
		{
			if (strcmp(mkoName, "MapMode.mko") == 0)
			{
				// enter/return/start
				if (functionHash == 0xA1A4DF6C || functionHash == 0x44A477CC || functionHash == 0x4CA174CC || functionHash == 0x7DED6222)
					TheMenu->m_b60FPSAllowed = true;
				else
					TheMenu->m_b60FPSAllowed = false;
			}
			else
			{
				TheMenu->m_b60FPSAllowed = false;
			}
		}
		else
		{
				TheMenu->m_b60FPSAllowed = true;
		}
	}

	return orgGamelogicJump(gameInfoPtr,mkoName, functionHash, a3, a4, a5, a6, a7, a8);
}

void SetCharacterDefinitions(int64 data, FightingTeamDefinition* team, int unk)
{
	int64 contentDefs = *(int64*)(data + 8);
	CharacterContentDefinitionInfo* mainInfo = (CharacterContentDefinitionInfo*)(contentDefs);
	CharacterContentDefinitionInfo* partnerInfo = (CharacterContentDefinitionInfo*)(contentDefs + 560);

	if (team->teamID == 0)
	{
		if (TheMenu->m_nCurrentCharModifier == MODIFIER_NORMAL)
		{
			if (TheMenu->m_bPlayer1Modifier)
			{
				FName newMain(TheMenu->szPlayer1ModifierCharacter + 5, FNAME_Add, 1);
				FString strMain;
				newMain.ToString(&strMain);
				mainInfo->Set(strMain, 7);
			}

			if (TheMenu->m_bPlayer1SkinModifier)
			{
				FName newSkin(TheMenu->szPlayer1Skin, FNAME_Add, 1);
				mainInfo->skin.Index = newSkin.Index;
			}
		}


		if (TheMenu->m_bPlayer1KameoModifier)
		{
			FName newPartner(TheMenu->szPlayer1KameoCharacter + 5, FNAME_Add, 1);
			FString strPartner;
			newPartner.ToString(&strPartner);
			partnerInfo->Set(strPartner, 7);
		}

		if (TheMenu->m_bPlayer1KameoSkinModifier)
		{
			FName newSkin(TheMenu->szPlayer1KameoSkin, FNAME_Add, 1);
			partnerInfo->skin.Index = newSkin.Index;
		}
	}
	if (team->teamID == 1)
	{
		if (TheMenu->m_nCurrentCharModifier == MODIFIER_NORMAL)
		{
			if (TheMenu->m_bPlayer2Modifier)
			{
				FName newMain(TheMenu->szPlayer2ModifierCharacter + 5, FNAME_Add, 1);
				FString strMain;
				newMain.ToString(&strMain);
				mainInfo->Set(strMain, 7);
			}

			if (TheMenu->m_bPlayer2SkinModifier)
			{
				FName newSkin(TheMenu->szPlayer2Skin, FNAME_Add, 1);
				mainInfo->skin.Index = newSkin.Index;
			}
		}


		if (TheMenu->m_bPlayer2KameoModifier)
		{
			FName newPartner(TheMenu->szPlayer2KameoCharacter + 5, FNAME_Add, 1);
			FString strPartner;
			newPartner.ToString(&strPartner);
			partnerInfo->Set(strPartner, 7);
		}

		if (TheMenu->m_bPlayer2KameoSkinModifier)
		{
			FName newSkin(TheMenu->szPlayer2KameoSkin, FNAME_Add, 1);
			partnerInfo->skin.Index = newSkin.Index;
		}
	}
	orgSetCharacterDefinitions(data, team, unk);
}


unsigned int _hash(const char* input)
{
	unsigned int result;
	int stringLength;
	int character;

	if (!input)
		return 0;
	stringLength = -1;

	do
		++stringLength;
	while (input[stringLength]);

	for (result = 0x811C9DC5; stringLength; --stringLength)
	{
		character = *(unsigned char*)input++;
		result = character ^ (unsigned int)(0x1000193 * result);
	}
	return result;
}

void GetCharacterPosition(FVector* vec, PLAYER_NUM plr)
{
	MKCharacterActor* obj = GetObjActor(plr);
	if (obj)
		obj->GetPos(vec);
}
