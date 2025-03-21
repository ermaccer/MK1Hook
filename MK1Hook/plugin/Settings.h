#pragma once
#include <Windows.h>

struct eMouseSettings {
	int sens;
	bool invert_y;
	bool invert_x;
};

class eSettingsManager {
public:
	eSettingsManager();

	bool bEnableConsoleWindow;
	bool bUseInvasionsCH15Characters;

	bool bEnableGamepadSupport;


	// generic
	int iHookMenuOpenKey;
	int iToggleCustomCamKey;
	int iToggleSlowMoKey = VK_F5;
	int iToggleFreezeWorldKey = VK_F2;
	int iToggleFreeCameraKey;
	int iToggleHUDKey;
	// free camera keys
	int iFreeCameraKeyForward;
	int iFreeCameraKeyBackward;
	int iFreeCameraKeyLeft;
	int iFreeCameraKeyRight;
	int iFreeCameraKeyUp;
	int iFreeCameraKeyDown;

	
	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;

	int iFreeCameraKeyPitchPlus;
	int iFreeCameraKeyPitchMinus;

	int iFreeCameraKeyRollMinus;
	int iFreeCameraKeyRollPlus;



	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	eMouseSettings mouse;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();
};

extern eSettingsManager* SettingsMgr;