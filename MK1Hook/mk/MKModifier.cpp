#include "MKModifier.h"
#include "../unreal/FName.h"
#include "Engine.h"

void(*pGlobalModifier_Constructor)(GlobalModifier*, wchar_t*, float) = nullptr;
void(*pTeamModifier_Constructor)(TeamModifier*, wchar_t*, float) = nullptr;

GlobalModifier::GlobalModifier()
{
}

GlobalModifier::GlobalModifier(FString name, float level)
{
	if (pGlobalModifier_Constructor)
		pGlobalModifier_Constructor(this, name.GetStr(), level);
}

void MKModifier::ActivateModifier(int64 fightObject, const char* name)
{
	TArray<GlobalModifier>& list = *(TArray<GlobalModifier>*)(fightObject + 0x158);

	int currentNum = list.Count;
	currentNum++;

	static uintptr_t pat = _pattern(PATID_TArray_Resize);
	if (pat)
		((void(__fastcall*)(int64, int, int))pat)((int64)&list.Data, currentNum, sizeof(GlobalModifier));

	FName modifierPath(name, FNAME_Add, 1);
	FString str;
	modifierPath.ToString(&str);

	GlobalModifier modifier(str, 1.0f);
	list.Add(modifier);
}

void MKModifier::ActivateModifier(const char* name, PLAYER_NUM player)
{
	TEAM_NUM teamNum = TEAM1;
	if (player == PLAYER2)
		teamNum = TEAM2;

	FightingTeamDefinition* team = GetGameInfo()->GetTeam(teamNum);
	
	if (!team)
		return;

	static int teamModifierListOffset = 0;

	if (teamModifierListOffset == 0)
	{
		int64 pat = _pattern(PATID_TeamModifiersOffset);
		if (pat)
			teamModifierListOffset = *(int*)(pat) + sizeof(int64);
	}

	if (!teamModifierListOffset)
		return;

	TArray<TeamModifier>& list = *(TArray<TeamModifier>*)((int64)team + teamModifierListOffset);

	int currentNum = list.Count;
	currentNum++;

	static uintptr_t pat = _pattern(PATID_TArray_Resize);
	if (pat)
		((void(__fastcall*)(int64, int, int))pat)((int64)&list.Data, currentNum, sizeof(GlobalModifier));

	FName modifierPath(name, FNAME_Add, 1);
	FString str;
	modifierPath.ToString(&str);

	TeamModifier modifier(str, 1.0f);
	list.Add(modifier);
}

TeamModifier::TeamModifier()
{
}

TeamModifier::TeamModifier(FString name, float level)
{
	if (pTeamModifier_Constructor)
		pTeamModifier_Constructor(this, name.GetStr(), level);
}
