// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "gui/dx12hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "plugin/Menu.h"
#include "plugin/Settings.h"
#include "plugin/Hooks.h"
#include "plugin/PatternSolver.h"
#include "plugin/PluginInterface.h"

#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "minhook/include/MinHook.h"
#include "mk/Engine.h"

#include "helper/eGamepadManager.h"

#include "unreal/FEngineLoop.h"
#include "unreal/UObject.h"
#include "unreal/UWorld.h"

#include <iostream>

using namespace Memory::VP;
int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }


static void (*orgSetFrameSkipping)(int status, int flags);
void SetFrameSkipping(int mode, int flags)
{
	if (TheMenu->m_b60FPSAllowed)
		mode = 1;

	orgSetFrameSkipping(mode, flags);
}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	eLog::Message(__FUNCTION__, "INFO: MK1Hook Begin!");

	FGGameInfo::FindGameInfo();
	UWorld::FindWorld();

	if (SettingsMgr->bEnableGamepadSupport)
		eGamepadManager::Initialize();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_pattern(PATID_FEngineLoop_Tick_Hook), tramp->Jump(&FEngineLoop::Tick));
	InjectHook(_pattern(PATID_MKCamera_FillCameraCache_Hook), tramp->Jump(&MKCamera::HookedFillCameraCache));
	InjectHook(_pattern(PATID_SetPartnerCharacter_Hook), tramp->Jump(SetPartnerCharacter));

	MH_CreateHook((void*)_pattern(PATID_CharacterDefinition_LoadCharacter), &CharacterDefinition_Load, (void**)&orgCharacterDefinition_Load);
	MH_EnableHook((void*)_pattern(PATID_CharacterDefinition_LoadCharacter));

	MH_CreateHook((void*)_pattern(PATID_CharacterDefinition_LoadCharacterKameo), &CharacterDefinition_LoadKameo, (void**)&orgCharacterDefinition_LoadKameo);
	MH_EnableHook((void*)_pattern(PATID_CharacterDefinition_LoadCharacterKameo));

	MH_CreateHook((void*)_pattern(PATID_SetCharacterDefinitions), &SetCharacterDefinitions, (void**)&orgSetCharacterDefinitions);
	MH_EnableHook((void*)_pattern(PATID_SetCharacterDefinitions));

	MH_CreateHook((void*)_pattern(PATID_ContentDefinition_Load), &ContentDefinition_Load, (void**)&orgContentDefinition_Load);
	MH_EnableHook((void*)_pattern(PATID_ContentDefinition_Load));

	MH_CreateHook((void*)_pattern(PATID_KameoContentDefinition_Load), &KameoContentDefinition_Load, (void**)&orgKameoContentDefinition_Load);
	MH_EnableHook((void*)_pattern(PATID_KameoContentDefinition_Load));


	MH_CreateHook((void*)_pattern(PATID_USceneComponent_SetRelativeScale3D), &USceneComponent_SetRelativeScale3D, (void**)&orgUSceneComponent_SetWorldScale3D);
	MH_EnableHook((void*)_pattern(PATID_USceneComponent_SetRelativeScale3D));

	MH_CreateHook((void*)_pattern(PATID_GamelogicJump), &GamelogicJump, (void**)&orgGamelogicJump);
	MH_EnableHook((void*)_pattern(PATID_GamelogicJump));

	MH_CreateHook((void*)_pattern(PATID_MKScript_PowerAttackObjDef), &PowerAttackCtor_Hook, (void**)&orgPowerAttackCtor_Hook);
	MH_EnableHook((void*)_pattern(PATID_MKScript_PowerAttackObjDef));

	if (SettingsMgr->bEnable60FPSPatch)
	{
		MH_CreateHook((void*)_pattern(PATID_SetFrameSkipping), &SetFrameSkipping, (void**)&orgSetFrameSkipping);
		MH_EnableHook((void*)_pattern(PATID_SetFrameSkipping));
	}

	HANDLE h = 0;
	
	h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX12Hook_Thread), 0, NULL, 0);
	
	if (!(h == nullptr)) CloseHandle(h);

}

bool ValidateGameVersion()
{
	if (PatternSolver::CheckMissingPatterns())
	{
		const wchar_t* message = L"Could not start MK1Hook!\n\n"
			L"One or more code patterns could not be found, this might indicate"
			L" that game version is not supported or the plugin has not been updated.\n\n"
			L"MK1Hook officially is only tested with latest Steam version.\n"
			L"Check log for more details.\n\n"
			L"Do you want to try to run the game anyway? It might crash or have missing features!\n";

		int answer = MessageBoxW(0, message, L"MK1Hook", MB_ICONWARNING | MB_YESNO);

		if (answer == IDOK)
			return true;
		else if (answer == IDNO)
			exit(0);
	}
	return true;
}

void Init()
{
	MH_Initialize();
	eLog::Initialize();
	PatternSolver::Initialize();
	PluginInterface::LoadPlugins();

	if (ValidateGameVersion())
		OnInitializeHook();

}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		break;
	case DLL_PROCESS_DETACH:
		eGamepadManager::Shutdown();
		GUIImplementation::Shutdown();
		PluginInterface::UnloadPlugins();
		SteamAPI_Destroy();
		break;
	}
	return TRUE;
}
