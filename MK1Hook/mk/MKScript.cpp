#include "MKScript.h"

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
		((void(__thiscall*)(MKScriptCharacterAction*, MKScript*, unsigned))pat)(defaultCharacterScriptAction, script, function);

	return defaultCharacterScriptAction;
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
