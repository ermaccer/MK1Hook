#include "ContentDefinition.h"
#include "..\plugin\Menu.h"


void(*orgContentDefinition_Load)(ContentDefinition*, int64);
void(*orgKameoContentDefinition_Load)(KameoContentDefinition*, int64);

void ContentDefinition_Log(ContentDefinition* chr)
{
	eLog::Message(__FUNCTION__, "Definition [%p] - Skins %d", chr, chr->skins.Count);

	for (int i = 0; i < chr->skins.Count; i++)
	{
		MKSkeletalObjSoftPtr& skin = chr->skins.Get(i);
		FString str;
		skin.path.ToString(&str);
		eLog::Message(__FUNCTION__, "%03d - %ws", i, str.GetStr());
	}

	eLog::Message(__FUNCTION__, "============================", chr, chr->skins.Count);
}

void ContentDefinition_CacheForEasySwap(ContentDefinition* chr)
{
	for (int i = 0; i < chr->skins.Count; i++)
	{
		MKSkeletalObjSoftPtr& skin = chr->skins.Get(i);
		FString str;
		skin.path.ToString(&str);
		
		std::wstring wstr = str.GetStr();
		std::string newStr("", wstr.length());
		std::copy(wstr.begin(), wstr.end(), newStr.begin());

		std::vector<std::string>::iterator it;
		it = std::find(TheMenu->m_LoadedCharacterSkins.begin(), TheMenu->m_LoadedCharacterSkins.end(), newStr);
		if (!(it != TheMenu->m_LoadedCharacterSkins.end()))
			TheMenu->m_LoadedCharacterSkins.push_back(newStr);
	}
}

void ContentDefinition_LoadHook(ContentDefinition* chr)
{
	if (TheMenu->m_bDefinitionSwapLog)
		ContentDefinition_Log(chr);

	ContentDefinition_CacheForEasySwap(chr);
	
	if (!TheMenu->m_bDefinitionSwap)
		return;

	if (strlen(TheMenu->szDefinitionSwap_Source) == 0)
		return;
	if (strlen(TheMenu->szDefinitionSwap_Swap) == 0)
		return;

	{
		std::string str = TheMenu->szDefinitionSwap_Source;
		std::wstring wstr;
		wstr.resize(str.length());
		std::copy(str.begin(), str.end(), wstr.begin());

		FString firstSkinName;
		chr->skins.Get(0).path.ToString(&firstSkinName);

		if (wcsstr(firstSkinName.GetStr(), wstr.c_str()))
		{
			FName newSkin(TheMenu->szDefinitionSwap_Swap, FNAME_Add, 1);
			chr->skins.Get(0).path = newSkin;
		}
	}
	if (TheMenu->m_bDefinitionExtraSwap)
	{
		if (strlen(TheMenu->szDefinitionExtraSwap_Source) == 0)
			return;
		if (strlen(TheMenu->szDefinitionExtraSwap_Swap) == 0)
			return;

		std::string str = TheMenu->szDefinitionExtraSwap_Source;
		std::wstring wstr;
		wstr.resize(str.length());
		std::copy(str.begin(), str.end(), wstr.begin());

		FString firstSkinName;
		chr->skins.Get(0).path.ToString(&firstSkinName);

		if (wcsstr(firstSkinName.GetStr(), wstr.c_str()))
		{
			FName newSkin(TheMenu->szDefinitionExtraSwap_Swap, FNAME_Add, 1);
			chr->skins.Get(0).path = newSkin;
		}
	}
}

void ContentDefinition_Load(ContentDefinition* chr, int64 a2)
{
	FName cachedSkin;

	if (TheMenu->m_bDefinitionSwap)
		cachedSkin = chr->skins.Get(0).path;

	ContentDefinition_LoadHook(chr);
	orgContentDefinition_Load(chr, a2);

	if (TheMenu->m_bDefinitionSwap)
		chr->skins.Get(0).path = cachedSkin;
}

void KameoContentDefinition_Load(KameoContentDefinition* chr, int64 a2)
{
	FName cachedSkin;

	if (TheMenu->m_bDefinitionSwap)
		cachedSkin = chr->skins.Get(0).path;
	ContentDefinition_LoadHook((ContentDefinition*)chr);

	orgKameoContentDefinition_Load(chr, a2);

	if (TheMenu->m_bDefinitionSwap)
		chr->skins.Get(0).path = cachedSkin;
}
