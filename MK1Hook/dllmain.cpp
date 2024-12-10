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

#include <Commctrl.h>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")

using namespace Memory::VP;
int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	eLog::Message(__FUNCTION__, "INFO: MK1Hook (%s | %s) Begin!", MK12HOOK_VERSION, __DATE__);

	FGGameInfo::FindGameInfo();
	UWorld::FindWorld();

	if (SettingsMgr->bEnableGamepadSupport)
		eGamepadManager::Initialize();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_pattern(PATID_FEngineLoop_Tick_Hook), tramp->Jump(&FEngineLoop::Tick));
	InjectHook(_pattern(PATID_MKCamera_FillCameraCache_Hook), tramp->Jump(&MKCamera::HookedFillCameraCache));

	ReadCall(_pattern(PATID_MKScript_RegisterSpecialMove), orgRegisterSpecialMove);
	InjectHook(_pattern(PATID_MKScript_RegisterSpecialMove), tramp->Jump(RegisterSpecialMove_Hook));
	InjectHook(_pattern(PATID_MKScript_RegisterSpecialMove2), tramp->Jump(RegisterSpecialMove_Hook));

	ReadCall(_pattern(PATID_LoadMainMenuBGND), orgLoadMainMenuBGND);
	InjectHook(_pattern(PATID_LoadMainMenuBGND), tramp->Jump(LoadMainMenuBGND_Hook));

	ReadCall(_pattern(PATID_SetPartnerCharacter_Hook), pSetPartnerCharacter);
	InjectHook(_pattern(PATID_SetPartnerCharacter_Hook), tramp->Jump(SetPartnerCharacter_Hook));

	ReadCall(_pattern(PATID_TeamInfo_SetKameo), pTeamInfo_SetKameoMode);
	ReadCall(_pattern(PATID_TeamInfo_SetTag), pTeamInfo_SetTagMode);
	ReadCall(_pattern(PATID_TeamInfo_SetSingle), pTeamInfo_SetSingleMode);
	ReadCall(_pattern(PATID_TeamInfo_KameoClass), pTeamInfo_GetKameoClass);
	ReadCall(_pattern(PATID_TeamInfo_TagClass), pTeamInfo_GetTagClass);
	ReadCall(_pattern(PATID_MKModifier_GlobalConstructor), pGlobalModifier_Constructor);
	ReadCall(_pattern(PATID_MKModifier_TeamConstructor), pTeamModifier_Constructor);

	MH_CreateHook((void*)_pattern(PATID_ContentDefinition_Load), &ContentDefinition_Load, (void**)&orgContentDefinition_Load);
	MH_EnableHook((void*)_pattern(PATID_ContentDefinition_Load));

	MH_CreateHook((void*)_pattern(PATID_KameoContentDefinition_Load), &KameoContentDefinition_Load, (void**)&orgKameoContentDefinition_Load);
	MH_EnableHook((void*)_pattern(PATID_KameoContentDefinition_Load));

	MH_CreateHook((void*)_pattern(PATID_USceneComponent_SetRelativeScale3D), &USceneComponent_SetRelativeScale3D, (void**)&orgUSceneComponent_SetWorldScale3D);
	MH_EnableHook((void*)_pattern(PATID_USceneComponent_SetRelativeScale3D));

	MH_CreateHook((void*)_pattern(PATID_GamelogicJump), &GamelogicJump, (void**)&orgGamelogicJump);
	MH_EnableHook((void*)_pattern(PATID_GamelogicJump));

	MH_CreateHook((void*)_pattern(PATID_ProcessPostProcessSettings), &ProcessPostProcessSettings, (void**)&pProcessPostProcessSettings);
	MH_EnableHook((void*)_pattern(PATID_ProcessPostProcessSettings));

	MH_CreateHook((void*)_pattern(PATID_MKScript_DataFunctionConstructor), &DataFunctionConstructor_Hook, (void**)&orgDataFunctionConstructor);
	MH_EnableHook((void*)_pattern(PATID_MKScript_DataFunctionConstructor));

	MH_CreateHook((void*)_pattern(PATID_FightStartup), &FightStartup_Hook, (void**)&orgFightStartup);
	MH_EnableHook((void*)_pattern(PATID_FightStartup));

	HANDLE h = 0;
	
	h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX12Hook_Thread), 0, NULL, 0);
	
	if (!(h == nullptr)) CloseHandle(h);

}

bool ValidateGameVersion()
{
	if (PatternSolver::CheckMissingPatterns())
	{
		int nButtonPressed = 0;
		TASKDIALOGCONFIG config;
		ZeroMemory(&config, sizeof(TASKDIALOGCONFIG));

		const TASKDIALOG_BUTTON buttons[] = {
			{ IDOK, L"Launch anyway\nThe game might crash or have missing features!" },
			{ IDNO, L"Exit" }
		};
		config.cbSize = sizeof(config);

		config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_CAN_BE_MINIMIZED | TDF_USE_COMMAND_LINKS;
		config.pszMainIcon = TD_WARNING_ICON;

		config.pszWindowTitle = L"Warning";
		config.pszMainInstruction = L"MK1Hook";
		config.pszContent = L"Could not start MK1Hook!\n\n"
			L"One or more code patterns could not be found, this might indicate"
			L" that game version is not supported or the plugin has not been updated.\n\n"
			L"MK1Hook officially is only tested with latest Steam version.\n"
			L"Check log for more details.\n";


		config.pButtons = buttons;
		config.cButtons = ARRAYSIZE(buttons);

		if (SUCCEEDED(TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)))
		{
			switch (nButtonPressed)
			{
			case IDOK:
				return true;
				break;
			case IDNO:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void Init()
{
	MH_Initialize();
	eLog::Initialize();
	PatternSolver::Initialize();
	PluginInterface::LoadPlugins();
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (ValidateGameVersion())
		{
			OnInitializeHook();
		}
	}
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
