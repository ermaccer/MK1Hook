#include "MKScript.h"
#include "..\plugin\Menu.h"
#include <string>
#include <algorithm>

int64(*orgPowerAttackCtor_Hook)(int64 a1, char* name, int a3, int* a4, int64 a5, int a6);

// currently isnt inlined unlike mk11
MKScript* GetScript(const char* name)
{
	static uintptr_t pat = _pattern(PATID_GetScript);
	if (pat)
	{
		return ((MKScript*(__fastcall*)(const char*, int , int))pat)(name, 0, 0);
	}
	return nullptr;
}

MKScriptCharacterAction* Create_CharacterScriptAction(MKScript* script, unsigned int function)
{
	static MKScriptCharacterAction* defaultCharacterScriptAction = nullptr;

	if (!defaultCharacterScriptAction)
		defaultCharacterScriptAction = Alloc_ScriptCharacterAction(512);

	static uintptr_t pat = _pattern(PATID_MKScript_CharacterScriptAction);
	if (pat)
		((void(__thiscall*)(MKScriptCharacterAction*, MKScript*, unsigned int))pat)(defaultCharacterScriptAction, script, function);

	return defaultCharacterScriptAction;
}

MKScriptCharacterAttackAction* Create_CharacterScriptAttackAction(int64 powerAttackDef, int64 characterObj, int unkNum)
{
	static MKScriptCharacterAttackAction* defaultCharacterScriptAttackAction = nullptr;

	if (!defaultCharacterScriptAttackAction)	
		defaultCharacterScriptAttackAction = (MKScriptCharacterAttackAction*)Alloc_ScriptCharacterAction(512);

	static uintptr_t pat = _pattern(PATID_MKScript_CharacterScriptAttackAction);
	if (pat)
		((void(__thiscall*)(MKScriptCharacterAttackAction*, int64, int64, bool, int64, int64, char))pat)(defaultCharacterScriptAttackAction, characterObj, powerAttackDef, false, 0, characterObj, unkNum);

	return defaultCharacterScriptAttackAction;
}


MKScriptCharacterAction* Alloc_ScriptCharacterAction(int size)
{
	static uintptr_t pat = _pattern(PATID_ScriptAlloc);
	if (pat)
		return ((MKScriptCharacterAction * (__fastcall*)(int))pat)(size);

	return nullptr;
}

int MKScript::GetFunctionID(unsigned int hash)
{
	static uintptr_t pat = _pattern(PATID_MKScript_GetFunctionID);
	if (pat)
	{
		return ((int(__fastcall*)(MKScript*, unsigned int))pat)(this ,hash);
	}
	return 0;
}

int64 MKScript::GetVariable(unsigned int hash)
{
	static uintptr_t pat = _pattern(PATID_MKScript_GetVariable);
	if (pat)
	{
		return ((int64(__fastcall*)(MKScript*, unsigned int))pat)(this, hash);
	}
	return 0;
}

// it is no longer possible to call power attacks on their own due to kameos, so this caches all registered definitions for power attacks
// to use in script tab
int64 PowerAttackCtor_Hook(int64 a1, char* name, int a3, int* a4, int64 a5, int a6)
{
	int64 result = orgPowerAttackCtor_Hook(a1, name, a3, a4, a5, a6);
	int64 info = *(int64*)(result + 88);
	if (info)
	{
		int64 names = *(int64*)(info + 24);
		if (names)
		{
			wchar_t* scriptName = *(wchar_t**)(names + 16);
			if (scriptName)
			{	
				PowerAttackCache cache = {};
				cache.defPtr = result;
				sprintf(cache.name, name);

				std::wstring wstr(scriptName);
				std::string str("", wstr.length());
				std::copy(wstr.begin(), wstr.end(), str.begin());
				std::transform(str.begin(), str.end(), str.begin(), tolower);
				sprintf(cache.scriptSource, str.c_str());
				TheMenu->m_PowerAttacksList.push_back(cache);
#ifdef _DEBUG
				printf("PowerAttack [%p] - %s from %ws\n", a1, name, scriptName);
#endif // _DEBUG
			}

		}
	}
	return result;
}