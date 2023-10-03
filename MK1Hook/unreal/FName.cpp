#include "FName.h"

FString* FName::ToString(FString* str)
{
	static uintptr_t pat = _pattern(PATID_FName_ToString);
	if (pat)
		return 	((FString * (__thiscall*)(FName*, FString*))pat)(this, str);

	return nullptr;
}

FName::FName()
{
	Index = -1;
	Number = 0;
}

FName::FName(const char* Name, EFindName FindType, int formal)
{
	static uintptr_t pat = _pattern(PATID_FName_FNameChar);
	if (pat)
		((void(__fastcall*)(FName*, const char*, EFindName, int))pat)(this, Name, FindType, formal);
}

FName::FName(const wchar_t* Name, EFindName FindType, int formal)
{
	static uintptr_t pat = _pattern(PATID_FName_FName);
	if (pat)
		((void(__fastcall*)(FName*, const wchar_t*, EFindName, int))pat)(this, Name, FindType, formal);
}
