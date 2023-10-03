#include "Engine.h"
#include "..\plugin\Hooks.h"
#include "..\plugin\Settings.h"

int64(*orgGamelogicJump)(int64, char*, unsigned int, int, int, int, int, int, int);

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return (MKCharacter*)FGGameInfo::pPlayerObjs[plr];
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return nullptr;
	//return GetGameInfo()->GetInfo(plr);
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
				if (functionHash == 0xA1A4DF6C || functionHash == 0x44A477CC || functionHash == 0x4CA174CC)
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
	MKCharacter* obj = GetObj(plr);
	if (obj)
		obj->GetPos(vec);
}
