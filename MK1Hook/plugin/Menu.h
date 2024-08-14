#pragma once
#include <vector>
#include "../mk/CharacterDefinition.h"
#include "../mk/MKCharacter.h"
#include "../mk/MKCamera.h"
#include "PluginInterface.h"

#include "../helper/eKeyboardMan.h"
#include "../utils.h"


#define MK12HOOK_VERSION "0.5.4"

enum eCustomCameras {
	CAMERA_HEAD_TRACKING,
	//CAMERA_THIRD_PERSON,
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
struct PowerAttackCache {
	int64 defPtr;
	char name[260];
	char scriptSource[260];
};


struct eScriptKeyBind {
	eScriptExecuteType type;
	eVKKeyCode key;
	bool isPowerAttack;
	PowerAttackCache powerAttackCache;
	char scriptName[128] = {};
	unsigned int functionHash;
};



enum eCHRModifierModes {
	MODIFIER_NORMAL,
	MODIFIER_CHARSWAP,
	TOTAL_MODES
};



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

	bool	m_bChangePlayerSpeed = false;
	bool	m_bChangePlayerScale = false;

	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;
	bool	m_bPlayer1SkinModifier = false;
	bool	m_bPlayer2SkinModifier = false;

	bool	m_bPlayer1KameoModifier = false;
	bool	m_bPlayer2KameoModifier = false;
	bool	m_bPlayer1KameoSkinModifier = false;
	bool	m_bPlayer2KameoSkinModifier = false;
	bool	m_bKameoReplace = false;
	bool	m_bKameoForceReplace = false;
	bool    m_bEnableTagMode = false;
	bool    m_bDefinitionSwap = false;
	bool    m_bDefinitionSwapLog = false;
	bool    m_bDefinitionExtraSwap = false;

	bool	m_bManualInput = false;
	bool    m_bDisableComboScaling = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomCameraX = -10.0f;
	float	 m_fAdjustCustomCameraY = 0.0f;
	float	 m_fAdjustCustomCameraZ = 161.0f;
	float	 m_fAdjustCustomCameraCrouch = 120.0f;
	float	 m_fAdjustCustomCameraThirdPersonX = 10.0f;
	float	 m_fAdjustCustomCameraThirdPersonY = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraX = 10.0f;
	float	 m_fAdjustCustomHeadCameraY = 0.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraDistanceOffset = 4.0f;
	float	 m_fAdjustCustomHeadCameraDistanceHeight = 1.0f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float	 m_fFreeCameraRotationSpeed = 1.25f;

	int  m_nScriptExecuteType = 0;
	int  m_nMovesetToUse = 0;
	unsigned int m_nHash = 0;
	PowerAttackCache m_paCache = {};
	MKScript* m_pScript;

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };

	int  m_nCurrentCustomCamera = CAMERA_HEAD_TRACKING;
	int  m_nCurrentCharModifier = MODIFIER_NORMAL;


	int* m_pCurrentVarToChange = nullptr;


	char szPlayer1ModifierCharacter[1024] = {};
	char szPlayer2ModifierCharacter[1024] = {};
	char szPlayer1Skin[1024] = {};
	char szPlayer2Skin[1024] = {};

	char szPlayer1KameoCharacter[1024] = {};
	char szPlayer2KameoCharacter[1024] = {};

	char szPlayerKameoSource[1024] = {};
	char szPlayerKameoSwap[1024] = {};

	char szPlayer1KameoSkin[1024] = {};
	char szPlayer2KameoSkin[1024] = {};
	char szPlayer1TagCharacter[1024] = {};
	char szPlayer2TagCharacter[1024] = {};
	char szCurrentCameraOption[128] = {};
	char szStageModifierStage[128] = {};
	char szLastJumpScript[128] = {};
	char szDefinitionSwap_Source[1024] = {};
	char szDefinitionSwap_Swap[1024] = {};

	char szDefinitionExtraSwap_Source[1024] = {};
	char szDefinitionExtraSwap_Swap[1024] = {};

	char szPlayer1Bone[128] = {};
	char szPlayer2Bone[128] = {};

	std::vector<std::string> m_CharacterList;
	std::vector<std::string> m_KameoList;
	std::vector<std::string> m_TagList;

	std::vector<PowerAttackCache> m_PowerAttacksList;

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
	void	 DrawTagTab();
	void	 DrawModifiersTab();
	void	 DrawPlayerTab();
	void	 DrawSpeedTab();
	void	 DrawCameraTab();
	void	 DrawCheatsTab();
	void	 DrawMiscTab();
	void	 DrawScriptTab();
	void	 DrawWorldTab();


	void	 DrawSettings();
	void	 DrawDefinitionSwapReference();

	void	 RunLastScript(bool powerAttack = false);
	void	 ProcessScriptHotkeys();

	bool	 IsFunctionSafeToCall(std::vector<std::string>& args);
	bool	 IsSpecialMoveInList(char* script, char* name);

	int		 ConvertSkinToInternalString(int player);
	int		 ConvertKameoSkinToInternalString(int player);

	void	 DrawKeyBind(char* name, int* var);
	void	 KeyBind(int* var, char* bindName, char* name);


};

extern MK12Menu* TheMenu;

