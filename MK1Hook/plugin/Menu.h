#pragma once
#include <vector>
#include "../mk/CharacterDefinition.h"
#include "../mk/MKCharacter.h"
#include "../mk/MKCamera.h"
#include "PluginInterface.h"

#include "../helper/eKeyboardMan.h"
#include "../helper/eGamepadManager.h"
#include "../utils.h"


class MKCamera;

#define NUM_MODIFIERS 515
#define NUM_TEAM_MODIFIERS 199

#define MK12HOOK_VERSION "0.5.9"

enum eCustomCameras {
	CAMERA_HEAD_TRACKING,
	CAMERA_THIRD_PERSON,
	CAMERA_INJUSTICE_2,
	CAMERA_9_16,
	TOTAL_CUSTOM_CAMERAS
};


enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	SUBMENU_DEFSWAP,
	TOTAL_SUBMENUS
};

enum eScriptExecuteType {
	SCRIPT_P1,
	SCRIPT_P2,
	SCRIPT_GLOBAL
};
struct ScriptDataFunction {
	int64 defPtr;
	char name[260];
	char scriptSource[260];
};

enum eScriptKeyBind_CallType {
	Keybind_Default = 1,
	Keybind_SpecialMove,
	Keybind_DataFunction,
};

enum eModifierEntryFlag {
	ModifierEntryFlag_P1 = 1,
	ModifierEntryFlag_P2 = 2,
};

enum eScriptKeyBind_HotkeyDevice {
	KeybindDevice_Keyboard,
	KeybindDevice_Pad
};

struct eScriptKeyBind {
	eScriptExecuteType type;
	eScriptKeyBind_HotkeyDevice deviceType;
	eVKKeyCode key;
	eGamepad_ButtonID gamepadButton;
	eScriptKeyBind_CallType callType;
	ScriptDataFunction scriptDataFunction;
	char scriptName[128] = {};
	unsigned int functionHash;
};

enum eDefinitionSwapMode {
	DefinitionSwap_Basic = 1,
	DefinitionSwap_Advanced,
};

struct ModifierEntry {
	std::string name;
	int flag;
	bool bothPlayers;
};

extern const char* szModifiers[NUM_MODIFIERS];
extern const char* szTeamModifiers[NUM_TEAM_MODIFIERS];

class MK12Menu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool     m_bFreezeWorld = false;
	bool	 m_bIsFocused = true;
	bool	 m_bHookDispatch = false;
	bool	 m_bForceCameraUpdate = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bDontFlipCamera = false;
	bool	 m_bDisableHeadTracking = false;
	bool	 m_bUsePlayerTwoAsTracker = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	bool	 m_bHideHUD = false;
	bool	 m_bDisableFightHUD = false;
	bool	 m_bAutoHideHUD = false;
	bool	 m_bMouseControl = false;
	bool	 m_bDisableDOF = false;
	bool	 m_bStageModifierMainMenu = false;

	// cheats
	bool	m_bInfiniteHealthP1 = false;
	bool	m_bInfiniteHealthP2 = false;
	bool	m_bNoHealthP1 = false;
	bool	m_bNoHealthP2 = false;
	bool	m_bInfiniteMeterP1 = false;
	bool	m_bInfiniteMeterP2 = false;
	bool	m_bZeroMeterP1 = false;
	bool	m_bZeroMeterP2 = false;
	bool	m_bOneHealthP1 = false;
	bool	m_bOneHealthP2 = false;
	bool    m_bFastUppercutsP1 = false;
	bool    m_bFastUppercutsP2 = false;
	bool	m_bInfiniteXraysP1 = false;
	bool	m_bInfiniteXraysP2 = false;
	bool	m_bXrayAlwaysP1 = false;
	bool	m_bXrayAlwaysP2 = false;
	bool    m_bEasyBrutalitiesP1 = false;
	bool    m_bEasyBrutalitiesP2 = false;

	bool	m_bChangePlayer1Speed = false;
	bool	m_bChangePlayer2Speed = false;
	bool	m_bChangePlayerScale = false;

	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;
	bool	m_bPlayer1SkinModifier = false;
	bool	m_bPlayer2SkinModifier = false;
	bool	m_bPlayer1MovesetModifier = false;
	bool	m_bPlayer2MovesetModifier = false;

	bool	m_bPlayer1KameoModifier = false;
	bool	m_bPlayer2KameoModifier = false;
	bool	m_bPlayer1KameoSkinModifier = false;
	bool	m_bPlayer2KameoSkinModifier = false;

	bool    m_bChangeGameMode = false;
	bool	m_bOldTagSwap = false;
	bool    m_bDefinitionSwap = false;
	bool    m_bDefinitionSwapLog = false;
	bool    m_bDefinitionExtraSwap = false;
	bool	m_bDisableDialogueIntro = false;
	bool	m_bAddGlobalModifiers = false;

	bool    m_bDisableComboScaling = false;
	bool	m_bAIDroneModifierP1 = false;
	bool	m_bAIDroneModifierP2 = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomCameraX = -10.0f;
	float	 m_fAdjustCustomCameraY = 0.0f;
	float	 m_fAdjustCustomCameraZ = 161.0f;
	float	 m_fAdjustCustomCameraCrouch = 120.0f;
	float	 m_fAdjustCustomCameraThirdPersonX = 25.0f;
	float	 m_fAdjustCustomCameraThirdPersonY = 400.0f;
	float	 m_fAdjustCustomCameraThirdPersonZ = 45.0f;
	float	 m_fAdjustCustomHeadCameraX = 10.0f;
	float	 m_fAdjustCustomHeadCameraY = 0.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraDistanceOffset = 4.0f;
	float	 m_fAdjustCustomHeadCameraDistanceHeight = 1.0f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float	 m_fFreeCameraRotationSpeed = 1.25f;

	int  m_nScriptExecuteType = 0;
	int  m_nDefinitionSwapType = DefinitionSwap_Basic;
	unsigned int m_nHash = 0;
	ScriptDataFunction m_paCache = {};
	MKScript* m_pScript;

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };

	int  m_nCurrentCustomCamera = CAMERA_HEAD_TRACKING;
	int  m_nCurrentTeamMode = MODE_SINGLE;

	int  m_nAIDroneLevelP1 = 0;
	int  m_nAIDroneLevelP2 = 0;


	int* m_pCurrentVarToChange = nullptr;


	char szPlayer1ModifierCharacter[1024] = {};
	char szPlayer2ModifierCharacter[1024] = {};
	char szPlayer1Skin[1024] = {};
	char szPlayer2Skin[1024] = {};
	char szPlayer1Moveset[1024] = {};
	char szPlayer2Moveset[1024] = {};

	char szPlayer1KameoCharacter[1024] = {};
	char szPlayer2KameoCharacter[1024] = {};

	char szPlayer1KameoSkin[1024] = {};
	char szPlayer2KameoSkin[1024] = {};
	char szPlayer1TagCharacter[1024] = {};
	char szPlayer2TagCharacter[1024] = {};
	char szCurrentCameraOption[128] = {};
	char szCurrentModeOption[128] = {};
	char szStageModifierStage[128] = {};
	char szLastJumpScript[128] = {};
	char szDefinitionSwap_Source[1024] = {};
	char szDefinitionSwap_Swap[1024] = {};

	char szDefinitionExtraSwap_Source[1024] = {};
	char szDefinitionExtraSwap_Swap[1024] = {};

	char szPlayer1Bone[128] = {};
	char szPlayer2Bone[128] = {};

	char szPlayer1AI[128] = {};
	char szPlayer2AI[128] = {};

	std::vector<std::string> m_CharacterList;
	std::vector<std::string> m_KameoList;
	std::vector<std::string> m_TagList;
	std::vector<std::string> m_LoadedCharacterSkins;
	std::vector<ModifierEntry> m_ModifiersList;

	std::vector<ScriptDataFunction> m_SpecialMoveList;
	std::vector<ScriptDataFunction> m_DataFunctionsList;

	// camera

	FVector  camPos = {};
	FVector  camRot = {};
	float	 camFov = 0;

	// player 
	FVector plrPos;
	FVector plrPos2;

	std::vector<eScriptKeyBind> m_vKeyBinds;

	MK12Menu();

	void	 Initialize();

	void	 SetupCharacterLists();

	void	 OnActivate();
	void	 OnToggleSlowMotion();
	void	 OnToggleFreezeWorld();
	void	 OnToggleFreeCamera();
	void	 OnToggleHUD();

	void	 OnJump();

	void	 Draw();
	void	 Process();
	void	 UpdateControls();
	void	 UpdateFreecam();

	void	 DrawCharacterTab();
	void	 DrawStageTab();
	void	 DrawKameoTab();
	void	 DrawModifiersTab();
	void	 DrawPlayerTab();
	void	 DrawSpeedTab();
	void	 DrawCameraTab();
	void	 DrawCheatsTab();
	void	 DrawMiscTab();
	void	 DrawScriptTab();
	void	 DrawWorldTab();
	
	void	 ProcessCustomCameras(MKCamera* camera);
	void	 ProcessCamera_HeadTracking(MKCamera* camera);
	void	 ProcessCamera_ThirdPerson(MKCamera* camera);
	void	 ProcessCamera_Injustice2(MKCamera* camera);
	void	 ProcessCamera_9_16(MKCamera* camera);

	void	 DrawSettings();
	void	 DrawDefinitionSwapReference();

	void	 RunLastScript(eScriptKeyBind_CallType callType = Keybind_Default);
	void	 ProcessScriptHotkeys();

	bool	 IsFunctionSafeToCall(std::vector<std::string>& args);

	void	 AddFunctionToList(ScriptDataFunction* func, bool isSpecialMove);
	int64	 FindScriptDefinition(char* scriptName, unsigned int functionHash, bool isSpecialMove);

	void	 ClearFunctionLists();

	void	 DrawKeyBind(char* name, int* var);
	void	 KeyBind(int* var, char* bindName, char* name);


};

extern MK12Menu* TheMenu;

