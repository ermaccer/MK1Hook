#pragma once
#include <vector>
#include "../mk/CharacterDefinition.h"
#include "../mk/MKCharacter.h"
#include "../mk/MKCamera.h"
#include "PluginInterface.h"

#include "../helper/eKeyboardMan.h"
#include "../utils.h"


#define MK12HOOK_VERSION "0.1"



enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	TOTAL_SUBMENUS
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

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomCameraX = -10.0f;
	float	 m_fAdjustCustomCameraY = 0.0f;
	float	 m_fAdjustCustomCameraZ = 161.0f;
	float	 m_fAdjustCustomCameraCrouch = 120.0f;
	float	 m_fAdjustCustomCameraThirdPersonX = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonY = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraX = 0.0f;
	float	 m_fAdjustCustomHeadCameraY = 1600.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float	 m_fFreeCameraRotationSpeed = 1.25f;


	int* m_pCurrentVarToChange = nullptr;


	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[128];
	char szStageModifierStage[128] = {};


	// camera

	FVector  camPos = {};
	FVector  camRot = {};
	float	 camFov = 0;


	MK12Menu();

	void	 OnActivate();
	void	 OnToggleSlowMotion();
	void	 OnToggleFreeCamera();

	void	 Draw();
	void	 Process();
	void	 UpdateControls();
	void	 UpdateFreecam();

	void	 DrawSpeedTab();
	void	 DrawCameraTab();
	void	 DrawMiscTab();


	void	 DrawSettings();


	void	 DrawKeyBind(char* name, int* var);
	void	 KeyBind(int* var, char* bindName, char* name);
};

extern MK12Menu* TheMenu;

