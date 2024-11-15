#include "Engine.h"
#include "..\plugin\Hooks.h"
#include "..\plugin\Settings.h"
#include "..\unreal\UWorld.h"

int64(*orgGamelogicJump)(int64, char*, unsigned int, int, int, int, int, int, int);

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

void SlowGameTimeForXTicks(float speed, int ticks)
{
	// FightEngine.mko -> DefaultSlowWorldCallback has 0x60667ECC call which seems to be slowdownforxticks
	static uintptr_t pat = _pattern(PATID_SlowGameTimeForXTicks);
	if (pat)
		((void(__fastcall*)(float, int, int, int))pat)(speed, 7, ticks, 10);
}

int64 GamelogicJump(int64 gameInfoPtr, char* mkoName, unsigned int functionHash, int a3, int a4, int a5, int a6, int a7, int a8)
{
	PluginOnJump(mkoName);
	return orgGamelogicJump(gameInfoPtr,mkoName, functionHash, a3, a4, a5, a6, a7, a8);
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

char* GetCharacterName(PLAYER_NUM plr)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return nullptr;

	static char characterName[128] = {};

	FString charPath;
	chr->path.ToString(&charPath);

	std::wstring name(charPath.GetStr());
	name = name.substr(name.find_last_of(L".") + 1);

	char* type = "CHAR_";

	if (wcsstr(charPath.GetStr(), L"KAM") || wcsstr(charPath.GetStr(), L"Kameo"))
		type = "KHAR_";
	if (wcsstr(charPath.GetStr(), L"CH15") || wcsstr(charPath.GetStr(), L"Kitbash"))
		type = "CH15_";
	if (wcsstr(charPath.GetStr(), L"EnemyAI"))
		type = "BOSS_";

	snprintf(characterName,sizeof(characterName), "%s%ws", type, name.c_str());

	return characterName;
}

char* GetCharacterSkinName(PLAYER_NUM plr)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return nullptr;

	static char skin[256] = {};

	FString skinName;

	chr->skin.ToString(&skinName);
	snprintf(skin, sizeof(skin), "%ws", skinName.GetStr());

	return skin;
}

void SetTeamMode(TEAM_NUM plr, TEAM_INFO_MODE mode)
{
	FightingTeamDefinition* team = GetGameInfo()->GetTeam(plr);

	if (!team)
		return;

	team->SetMode(mode);
}

bool IsPartnerTeam(TEAM_NUM plr)
{
	FightingTeamDefinition* team = GetGameInfo()->GetTeam(plr);

	if (!team)
		return false;

	return team->IsPartnerMode();
}

void SetCharacterMKX(PLAYER_NUM plr, char* name, bool tag)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return;

	FName nameContentInfo(name + 5, FNAME_Add, 1);
	FString stringContentInfo;
	nameContentInfo.ToString(&stringContentInfo);

	static CharacterContentDefinitionInfo contentInfo;
	contentInfo.Set(stringContentInfo);

	bool partner = IsCharacterPartner(plr);

	// ai is now stored in definition so have to cache it first
	AIDroneInfo ai = *(AIDroneInfo*)((int64)chr + AI_DATA_OFFSET);

	if (partner && !tag)
		chr->SetPartner(&contentInfo);
	else
		chr->Set(&contentInfo);
	*(AIDroneInfo*)((int64)chr + AI_DATA_OFFSET) = ai;

}

void SetCharacterSkin(PLAYER_NUM plr, char* name)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return;

	FName skinName(name, FNAME_Add, 1);
	chr->skin.Index = skinName.Index;
}

void SetCharacterExtraMoveset(PLAYER_NUM plr, char* name)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return;

	FName skinName(name, FNAME_Add, 1);
	chr->extraMoveset.Index = skinName.Index;
}

void SetCharacterAI(PLAYER_NUM plr, char* script, int level)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return;
	int scriptID = AIDrone::ScriptToID(script);
	
	chr->SetAIDrone(scriptID, level);
}

void SetCharacterAI(PLAYER_NUM plr, int scriptID, int level)
{
	CharacterDefinitionV2* chr = GetCharacterDefinition(plr);

	if (!chr)
		return;

	chr->SetAIDrone(scriptID, level);
}

CharacterDefinitionV2* GetCharacterDefinition(PLAYER_NUM plr)
{
	TEAM_NUM teamNum = TEAM1;

	if (plr == PLAYER2 || plr == PLAYER4)
		teamNum = TEAM2;

	bool partner = IsCharacterPartner(plr);

	FightingTeamDefinition* team = GetGameInfo()->GetTeam(teamNum);

	if (!team)
		return nullptr;

	int64 definitionPtr = team->GetDefinitions();

	if (!definitionPtr)
		return nullptr;

	int offset = TEAM_MAIN_OFFSET;
	if (partner)
		offset = TEAM_PARTNER_OFFSET;

	CharacterDefinitionV2* chr = (CharacterDefinitionV2*)(definitionPtr + offset);
	return chr;
}

bool IsCharacterPartner(PLAYER_NUM plr)
{
	if (plr == PLAYER3 || plr == PLAYER4)
		 return true;
	return false;
}

