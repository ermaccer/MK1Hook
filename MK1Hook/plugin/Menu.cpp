#include "Menu.h"
#include "Settings.h"
#include "../helper/eKeyboardMan.h"
#include "../helper/eMouse.h"

#include "../gui/notifications.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl.h"

#include <math.h>
#include <iostream>
#include <algorithm>
#include <Windows.h>


using namespace Memory::VP;

const char* szCharacters[] = {
	// place npcs first for easy access
	"CHAR_Ermac_NPC",
	"CHAR_JanetCage",
	"CHAR_QuanChi_NPC",
	"CH15_CyberSmoke",
	"CH15_FemErmac",
	"CH15_FemReptile",
	"CH15_FemScorpion",
	"CH15_FemSubZero",

	// rest of the cast
	"CHAR_Ashrah",
	"CHAR_Baraka",
	"CHAR_Geras",
	"CHAR_Havik",
	"CHAR_JohnnyCage",
	"CHAR_Kenshi",
	"CHAR_Kitana",
	"CHAR_KungLao",
	"CHAR_LiMei",
	"CHAR_LiuKang",
	"CHAR_Mileena",
	"CHAR_Nitara",
	"CHAR_Raiden",
	"CHAR_RainMage",
	"CHAR_Reiko",
	"CHAR_Reptile",
	"CHAR_Scorpion",
	"CHAR_ShaoKahn",
	"CHAR_Sindel",
	"CHAR_Smoke",
	"CHAR_SubZero",
	"CHAR_Tanya",
	"CHAR_Tarkatan_Clone",
	"CHAR_Tarkatan_SuperClone",

	// kitbash

	"CH15_Ashrah",
	"CH15_Baraka",
	"CH15_Ermac",
	"CH15_Geras",
	"CH15_Havik",
	"CH15_JohnnyCage",
	"CH15_Kenshi",
	"CH15_Kitana",
	"CH15_KungLao",
	"CH15_LiMei",
	"CH15_LiuKang",
	"CH15_Mileena",
	"CH15_Nitara",
	"CH15_QuanChi",
	"CH15_Raiden",
	"CH15_RainMage",
	"CH15_Reiko",
	"CH15_Reptile",
	"CH15_Scorpion",
	"CH15_ShaoKahn",
	"CH15_Sindel",
	"CH15_Smoke",
	"CH15_SubZero",
	"CH15_Tanya",

};

const char* szTagCharacters[] = {
	"Ashrah",
	"Baraka",
	"Geras",
	"Havik",
	"JohnnyCage",
	"Kenshi",
	"Kitana",
	"KungLao",
	"LiMei",
	"LiuKang",
	"Mileena",
	"Nitara",
	"Raiden",
	"RainMage",
	"Reiko",
	"Reptile",
	"Scorpion",
	"ShangTsung",
	"ShaoKahn",
	"Sindel",
	"Smoke",
	"SubZero",
	"Tanya",
};

const char* szKameos[] = {
	"KHAR_AdamKAM",
	"KHAR_BarakaKAM",
	"KHAR_CyraxKAM",
	"KHAR_DarriusKAM",
	"KHAR_ErmacKAM",
	"KHAR_FireElementalKAM",
	"KHAR_FrostKAM",
	"KHAR_GoroKAM",
	"KHAR_HavikKAM",
	"KHAR_IceElementalKAM",
	"KHAR_JaxKAM",
	"KHAR_JohnnyCageKAM_NPC",
	"KHAR_KanoKAM",
	"KHAR_KenshiKAM",
	"KHAR_KhameleonKAM_NPC",
	"KHAR_KitanaKAM",
	"KHAR_KungJinKAM",
	"KHAR_KungLaoKAM",
	"KHAR_LightningElementalKAM",
	"KHAR_LiMeiKAM",
	"KHAR_LiuKangKAM",
	"KHAR_MileenaKAM",
	"KHAR_MotaroKAM",
	"KHAR_NitaraKAM",
	"KHAR_QuanChiKAM",
	"KHAR_RaidenKAM",
	"KHAR_RainMageKAM",
	"KHAR_ReikoKAM",
	"KHAR_ReptileKAM",
	"KHAR_SareenaKAM",
	"KHAR_ScorpionKAM",
	"KHAR_SektorKAM",
	"KHAR_ShangTsungKAM",
	"KHAR_ShaoKahnKAM",
	"KHAR_ShujinkoKAM",
	"KHAR_SindelKAM",
	"KHAR_SmokeKAM",
	"KHAR_SonyaKAM",
	"KHAR_StrykerKAM",
	"KHAR_SubZeroKAM",
	"KHAR_TanyaKAM",
	"KHAR_TarkatanCloneKAM",
};

const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Head Perspective"
};

int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}

MK12Menu* TheMenu = new MK12Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

MK12Menu::MK12Menu()
{
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer1KameoCharacter, szKameos[0]);
	sprintf(szPlayer2KameoCharacter, szKameos[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szPlayer1TagCharacter, szTagCharacters[0]);
	sprintf(szPlayer2TagCharacter, szTagCharacters[0]);
}

void MK12Menu::OnActivate()
{
	m_bIsActive ^= 1;
}

void MK12Menu::OnToggleSlowMotion()
{
	if (m_bIsActive)
		return;

	m_bSlowMotion ^= 1;

	if (FGGameInfo* GameInfo = GetGameInfo())
	{
		if (m_bSlowMotion) GameInfo->SetGameSpeed(m_fSlowMotionSpeed);
		else GameInfo->SetGameSpeed(1.0f);
	}
}

void MK12Menu::OnToggleFreezeWorld()
{
	if (m_bIsActive)
		return;

	m_bFreezeWorld ^= 1;

	if (FGGameInfo* GameInfo = GetGameInfo())
	{
		if (m_bFreezeWorld) GameInfo->SetGameSpeed(0.001f);
		else GameInfo->SetGameSpeed(1.0f);
	}
}

void MK12Menu::OnToggleFreeCamera()
{
	if (m_bIsActive)
		return;

	m_bFreeCam ^= 1;
}

void MK12Menu::OnToggleHUD()
{
	if (m_bIsActive)
		return;

	m_bDisableFightHUD ^= 1;

	if (m_bDisableFightHUD)
		HideHUD();
	else
		ShowHUD();
}

void MK12Menu::Draw()
{
	if (!m_bIsActive)
		return;

	ImGui::GetIO().MouseDrawCursor = true;

	ImGui::Begin("MK1Hook by ermaccer", &m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::BeginMenu("About"))
			{
				ImGui::MenuItem("Version: " MK12HOOK_VERSION);
				ImGui::MenuItem("Date: " __DATE__);
				ImGui::EndMenu();
			}

			if (PluginInterface::GetNumPlugins() > 0)
			{
				if (ImGui::BeginMenu("Loaded plugins"))
				{
					for (int i = 0; i < PluginInterface::GetNumPlugins(); i++)
					{
						ImGui::MenuItem(PluginInterface::plugins[i].GetPluginName());
					}


					ImGui::EndMenu();
				}
			}


			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character"))
		{
			DrawCharacterTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Tag"))
		{
			DrawTagTab();
			ImGui::EndTabItem();
		}
#ifdef _DEBUG
		if (ImGui::BeginTabItem("Player"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
#endif
		if (ImGui::BeginTabItem("Speed"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		PluginInterface::ProcessPluginTabs();
		ImGui::EndTabBar();
	}
	ImGui::End();


	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();

}

void MK12Menu::Process()
{
	UpdateControls();
}

void MK12Menu::UpdateControls()
{
	UpdateFreecam();
}

void MK12Menu::UpdateFreecam()
{
	if (TheMenu->m_bFreeCam)
	{
		if (TheMenu->m_bMouseControl && !TheMenu->m_bIsActive)
			ShowCursor(FALSE);

		if (TheCamera)
		{
			FVector fwd = TheCamera->GetMatrix().GetForward();
			FVector strafe = TheCamera->GetMatrix().GetRight();
			FVector up = TheCamera->GetMatrix().GetUp();

			float speed = m_fFreeCameraSpeed;
			float rotSpeed = m_fFreeCameraRotationSpeed;

			if (TheMenu->m_bMouseControl)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
					speed *= 5.0f;
				if (GetAsyncKeyState(VK_RBUTTON))
					speed *= 15.0f;
			}


			// forward

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
				TheMenu->camPos += fwd * speed * 1;


			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBackward))
				TheMenu->camPos += fwd * speed * -1;

			// strafe

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
				TheMenu->camPos += strafe * speed * -1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
				TheMenu->camPos += strafe * speed * 1;

			// up

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
				TheMenu->camPos += up * speed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
				TheMenu->camPos += up * speed * -1;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
				TheMenu->camRot.Y -= rotSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
				TheMenu->camRot.Y += rotSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
				TheMenu->camRot.Y -= rotSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
				TheMenu->camRot.Y += rotSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
				TheMenu->camRot.X -= rotSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
				TheMenu->camRot.X += rotSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
				TheMenu->camFov -= 1.0f;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
				TheMenu->camFov += 1.0f;

			// mouse
			{
				if (!TheMenu->m_bIsActive && TheMenu->m_bMouseControl)
				{
					TheMenu->camRot.X += (eMouse::GetDeltaY() * 180.0f) / 32767.0f;
					TheMenu->camRot.Y += (eMouse::GetDeltaX() * 180.0f) / 32767.0f;

				}
			}
		}
	}
}

void MK12Menu::DrawCharacterTab()
{
	ImGui::TextWrapped("To replace character in arcade/versus, set the options during an existing match then reload. Setting character on versus select will make"
		" swapped character use old model until reload is used. Arcade mode will crash when character is set on player select.");
	ImGui::Separator();

	ImGui::TextWrapped("Swap Method");
	ImGui::Separator();
	ImGui::RadioButton("Normal", &m_nCurrentCharModifier, MODIFIER_NORMAL);
	ImGui::SameLine();
	ShowHelpMarker("Replaces characters during loading for P1 or P2.");
	ImGui::SameLine();
	ImGui::RadioButton("Character Swap", &m_nCurrentCharModifier, MODIFIER_CHARSWAP);
	ImGui::SameLine();
	ShowHelpMarker("Replaces character based on used ID, Player 1 becomes source character and Player 2 becomes replacement, use this method to swap in story or modes where normal doesn't work!");
	ImGui::Separator();
	ImGui::Checkbox((m_nCurrentCharModifier == MODIFIER_NORMAL ? "Change Player 1 Character" : "Change P1 Source Character"), &m_bPlayer1Modifier);

	if (!m_bManualInput)
	{
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##p1chr", szPlayer1ModifierCharacter))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
			{
				bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
				if (ImGui::Selectable(szCharacters[n], is_selected))
					sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
	else
	{
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p1chrm", szPlayer1ModifierCharacter, sizeof(szPlayer1ModifierCharacter));
		ImGui::PopItemWidth();
	}



	ImGui::Checkbox((m_nCurrentCharModifier == MODIFIER_NORMAL ? "Change Player 2 Character" : "Change P1 Swap Character"), &m_bPlayer2Modifier);

	if (!m_bManualInput)
	{
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##p2chr", szPlayer2ModifierCharacter))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
			{
				bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
				if (ImGui::Selectable(szCharacters[n], is_selected))
					sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
	else
	{
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p2chrm", szPlayer2ModifierCharacter, sizeof(szPlayer2ModifierCharacter));
		ImGui::PopItemWidth();
	}

	if (ImGui::CollapsingHeader("Extras"))
	{
		ImGui::TextWrapped("Look up the log/console window for possible skin names, most however use a simple pattern, eg. \"BP_Scorpion_Skin001_A_Char\". Skins apply only to characters they're designed for.");
		ImGui::Checkbox("Change Player 1 Skin", &m_bPlayer1SkinModifier);
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p1skin", szPlayer1Skin, sizeof(szPlayer1Skin));
		ImGui::PopItemWidth();

		ImGui::Checkbox("Change Player 2 Skin", &m_bPlayer2SkinModifier);
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p2skin", szPlayer2Skin, sizeof(szPlayer2Skin));
		ImGui::PopItemWidth();
#ifdef _DEBUG
		ImGui::Checkbox("Manual Input", &m_bManualInput);
		ImGui::SameLine(); ShowHelpMarker("Write full path instead of selection.");
#endif
	}
}

void MK12Menu::DrawKameoTab()
{
	// TODO
}

void MK12Menu::DrawTagTab()
{
	ImGui::TextWrapped("Replaces Kameo selections with normal characters which makes the game play in actual tag mode. Enable the checkbox then choose anyone in Kameo select and they will be replaced with normal characters.");
	ImGui::TextWrapped("Versus/Practice only. NOTE: As of 24 October 2023 update, it is no longer possible to tag in with kameo button. First character needs to be defeated for next to pop in.");
	ImGui::Separator();
	ImGui::Checkbox("Tag Mode", &m_bEnableTagMode);
	
	ImGui::Text("Player 1 Tag Character");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##p1tag", szPlayer1TagCharacter))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szTagCharacters); n++)
		{
			bool is_selected = (szPlayer1TagCharacter == szTagCharacters[n]);
			if (ImGui::Selectable(szTagCharacters[n], is_selected))
				sprintf(szPlayer1TagCharacter, szTagCharacters[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	ImGui::Text("Player 2 Tag Character");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##p2tag", szPlayer2TagCharacter))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szTagCharacters); n++)
		{
			bool is_selected = (szPlayer2TagCharacter == szTagCharacters[n]);
			if (ImGui::Selectable(szTagCharacters[n], is_selected))
				sprintf(szPlayer2TagCharacter, szTagCharacters[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
}

void MK12Menu::DrawPlayerTab()
{
	// TODO
	ImGui::Text("P1: %p", GetObj(PLAYER1));
	ImGui::Text("P2: %p", GetObj(PLAYER2));
	ImGui::Separator();
	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		GetCharacterPosition(&plrPos, PLAYER1);
		ImGui::InputFloat3("X | Y | Z", &plrPos.X);
		GetCharacterPosition(&plrPos2, PLAYER2);
		ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
	}
	else
		ImGui::Text("Player options are only available in-game!");
}

void MK12Menu::DrawSpeedTab()
{
	ImGui::Text("Gamespeed");
	ImGui::InputFloat("##speed", &m_fSlowMotionSpeed, 0.1f);

	if (m_fSlowMotionSpeed > 2.0f) m_fSlowMotionSpeed = 2.0f;
	if (m_fSlowMotionSpeed < 0.0f) m_fSlowMotionSpeed = 0.0f;
	if (ImGui::Checkbox("Enable", &m_bSlowMotion))
	{
		if (FGGameInfo* GameInfo = GetGameInfo())
		{
			if (m_bSlowMotion) GameInfo->SetGameSpeed(m_fSlowMotionSpeed);
			else GameInfo->SetGameSpeed(1.0f);
		}

	}
	
	ImGui::SameLine();
	ShowHelpMarker(eKeyboardMan::KeyToString(SettingsMgr->iToggleSlowMoKey));

	if (ImGui::Checkbox("Freeze World", &m_bFreezeWorld))
	{
		if (FGGameInfo* GameInfo = GetGameInfo())
		{
			if (m_bFreezeWorld) GameInfo->SetGameSpeed(0.001f);
			else GameInfo->SetGameSpeed(1.0f);
		}

	}
	ImGui::SameLine();
	ShowHelpMarker(eKeyboardMan::KeyToString(SettingsMgr->iToggleFreezeWorldKey));
}

void MK12Menu::DrawCameraTab()
{
	ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
	ImGui::InputFloat3("X | Y | Z", &camPos.X);
	ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
	ImGui::InputFloat3("Pitch | Yaw | Roll", &camRot.X);

	ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
	ImGui::InputFloat("FOV", &camFov);

	ImGui::Separator();
	ImGui::Checkbox("Enable Free Camera", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with keyboard.Keys can be changed in the Settings menu or in the .ini file.");

	if (m_bFreeCam)
	{
		ImGui::InputFloat("Free Camera Speed", &m_fFreeCameraSpeed);
		ImGui::InputFloat("Free Camera Rotation Speed", &m_fFreeCameraRotationSpeed);
		ImGui::Checkbox("Mouse Control", &m_bMouseControl);
	}

	ImGui::Separator();
	ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);

	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
			{
				bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
				if (ImGui::Selectable(szCameraModes[n], is_selected))
					sprintf(szCurrentCameraOption, szCameraModes[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);

		if (m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING)
		{
			ImGui::InputFloat("Forward Offset", &m_fAdjustCustomHeadCameraX);
			ImGui::InputFloat("Left/Right Offset", &m_fAdjustCustomHeadCameraY);
			ImGui::InputFloat("Up/Down Offset", &m_fAdjustCustomHeadCameraZ);
			ImGui::InputFloat("Distance LookAt Offset", &m_fAdjustCustomHeadCameraDistanceOffset);
			ImGui::InputFloat("Distance LookAt Height", &m_fAdjustCustomHeadCameraDistanceHeight);

			ImGui::Checkbox("Use Player Two As Source", &m_bUsePlayerTwoAsTracker);

			ImGui::TextWrapped("Recommended FOV: 110+");
		}
	}
	else
		ImGui::Text("Custom cameras will appear once in-game!");


}

void MK12Menu::DrawMiscTab()
{
	if (ImGui::Button("Hide FightHUD"))
		HideHUD();
	ImGui::SameLine();
	if (ImGui::Button("Show FightHUD"))
		ShowHUD();
	ImGui::SameLine();
	ShowHelpMarker("Hotkey can be set in the Settings menu");

	if (ImGui::CollapsingHeader("Console"))
	{
		static char consoleText[2048] = {};
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##console", consoleText, sizeof(consoleText));
		ImGui::PopItemWidth();
		if (ImGui::Button("Execute", { -FLT_MIN, 0 }))
		{
			FGGameInfo* info = GetGameInfo();
			if (info)
			{
				info->Exec(consoleText);
			}
		}
	}
}

void MK12Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 35 * ImGui::GetFontSize(), 35 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",	
		"Keys",
		"Mouse"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
		MOUSE
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to mk1hook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("##", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:            
		ImGui::TextWrapped("These settings control MK1Hook.ini options. Any changes require game restart to take effect.");
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		ImGui::Checkbox("Gamepad Support", &SettingsMgr->bEnableGamepadSupport);
		ImGui::Checkbox("Disable System Log", &SettingsMgr->bDisableSystemLog);
		ImGui::Checkbox("60 FPS Patch", &SettingsMgr->bEnable60FPSPatch);
		if (SettingsMgr->bEnable60FPSPatch)
			ImGui::Checkbox("Restrict 60 FPS Patch to Invasions only", &SettingsMgr->b60FPSPatchInvasionsOnly);
		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Keys reset! Remember to save.");

		}
		ImGui::Separator();
		ImGui::LabelText("##", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iToggleSlowMoKey, "Toggle Gamespeed/Slow Motion", "slomo");
		KeyBind(&SettingsMgr->iToggleFreezeWorldKey, "Freeze World", "freeze");
		ImGui::Separator();
		ImGui::LabelText("##","Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyForward, "Forwards", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyBackward, "Backwards", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyLeft, "Left", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRight, "Right", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyUp, "Up", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyDown, "Down", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("##", "Misc");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleFreeCameraKey, "Toggle Free Camera", "fcam");
		KeyBind(&SettingsMgr->iToggleHUDKey, "Toggle FightHUD", "thud");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	case MOUSE:
		ImGui::TextWrapped("All user settings are saved to mk1hook_user.ini.");
		ImGui::Text("Sensitivity");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::SliderInt("##", &SettingsMgr->mouse.sens, 1, 50);
		ImGui::PopItemWidth();
		ImGui::Checkbox("Invert X", &SettingsMgr->mouse.invert_x);
		ImGui::Checkbox("Invert Y", &SettingsMgr->mouse.invert_y);
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to MK1Hook.ini and mk1hook_user.ini!");
		GUIImplementation::RequestFontReload();
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

int MK12Menu::ConvertCharacterNameToInternalString(int player, int classType)
{
	static wchar_t wideBuffer[1024] = {};

	int characterClass = -1;
	char* characterName = szPlayer1ModifierCharacter;
	if (player == 0 && classType == Kameo)
		characterName = szPlayer1KameoCharacter;

	if (player == 1 && classType == Base)
		characterName = szPlayer2ModifierCharacter;
	if (player == 1 && classType == Kameo)
		characterName = szPlayer2KameoCharacter;


	if (m_bManualInput)
	{
		std::string str = characterName;

		std::wstring wideString;
		wideString.resize(str.length());
		std::copy(str.begin(), str.end(), wideString.begin());
		wsprintfW(wideBuffer, L"%s", wideString.c_str());
	}
	else
	{
		if (strstr(characterName, "CHAR_"))
			characterClass = Base;
		else if (strstr(characterName, "KHAR_"))
			characterClass = Kameo;
		else if (strstr(characterName, "CH15_"))
			characterClass = Kitbash;

		if (characterClass == -1)
			return -1;

		std::string str = characterName;
		str = str.substr(5);

		std::wstring wideString;
		wideString.resize(str.length());
		std::copy(str.begin(), str.end(), wideString.begin());


		switch (characterClass)
		{
		case Base:
			wsprintfW(wideBuffer, L"/Game/Disk/Char/%s/Game/%s.%s", wideString.c_str(), wideString.c_str(), wideString.c_str());
			break;
		case Kameo:
			wsprintfW(wideBuffer, L"/Game/Disk/Kameo/%s/Game/%s.%s", wideString.c_str(), wideString.c_str(), wideString.c_str());
			break;
		case Kitbash:
			wsprintfW(wideBuffer, L"/Game/Disk/Kitbash/%sKIT/%sCH15.%sCH15", wideString.c_str(), wideString.c_str(), wideString.c_str());
			break;
		default:
			break;
		}

	}
	
	FName name(wideBuffer, FNAME_Add, 1);

	return name.Index;
}

int MK12Menu::ConvertSkinToInternalString(int player)
{
	static wchar_t wideBuffer[1024] = {};

	int characterClass = -1;
	char* skinName = szPlayer1Skin;
	if (player == 1)
		skinName = szPlayer2Skin;

	std::string str = skinName;

	std::wstring wideString;
	wideString.resize(str.length());
	std::copy(str.begin(), str.end(), wideString.begin());
	wsprintfW(wideBuffer, L"%s", wideString.c_str());

	FName name(wideBuffer, FNAME_Add, 1);

	return name.Index;
}

int MK12Menu::ConvertKameoSkinToInternalString(int player)
{
	static wchar_t wideBuffer[1024] = {};

	int characterClass = -1;
	char* skinName = szPlayer1KameoSkin;
	if (player == 1)
		skinName = szPlayer2KameoSkin;

	std::string str = skinName;

	std::wstring wideString;
	wideString.resize(str.length());
	std::copy(str.begin(), str.end(), wideString.begin());
	wsprintfW(wideBuffer, L"%s", wideString.c_str());

	FName name(wideBuffer, FNAME_Add, 1);

	return name.Index;
}

void MK12Menu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}

}

void MK12Menu::KeyBind(int* var, char * bindName, char * name)
{
	ImGui::LabelText("##", bindName);
	DrawKeyBind(name, var);
}
