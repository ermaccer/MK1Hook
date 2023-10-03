#pragma once
#include <vector>
#include "../mk/CharacterDefinition.h"
#include "../mk/MKCharacter.h"
#include "../mk/MKCamera.h"
#include "PluginInterface.h"

#include "../helper/eKeyboardMan.h"
#include "../utils.h"


#define MK12HOOK_VERSION "0.3"

enum eCustomCameras {
	CAMERA_HEAD_TRACKING,
	TOTAL_CUSTOM_CAMERAS
};


enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	TOTAL_SUBMENUS
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
	bool	 m_bDisableFightHUD = false;
	bool	 m_bAutoHideHUD = false;
	bool	 m_bMouseControl = false;


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


	bool	m_bManualInput = false;
	bool	m_b60FPSAllowed = true;

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
	char szPlayer1KameoSkin[1024] = {};
	char szPlayer2KameoSkin[1024] = {};
	char szCurrentCameraOption[128] = {};
	char szStageModifierStage[128] = {};
	char szLastJumpScript[128] = {};


	// camera

	FVector  camPos = {};
	FVector  camRot = {};
	float	 camFov = 0;

	// player 
	FVector plrPos;
	FVector plrPos2;

	MK12Menu();

	void	 OnActivate();
	void	 OnToggleSlowMotion();
	void	 OnToggleFreezeWorld();
	void	 OnToggleFreeCamera();

	void	 Draw();
	void	 Process();
	void	 UpdateControls();
	void	 UpdateFreecam();

	void	 DrawCharacterTab();
	void	 DrawKameoTab();
	void	 DrawPlayerTab();
	void	 DrawSpeedTab();
	void	 DrawCameraTab();
	void	 DrawMiscTab();


	void	 DrawSettings();

	int		 ConvertCharacterNameToInternalString(int player, int classType);
	int		 ConvertSkinToInternalString(int player);
	int		 ConvertKameoSkinToInternalString(int player);

	void	 DrawKeyBind(char* name, int* var);
	void	 KeyBind(int* var, char* bindName, char* name);


};

extern MK12Menu* TheMenu;

