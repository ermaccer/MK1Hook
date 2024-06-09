#include "Menu.h"
#include "Settings.h"
#include "../helper/eKeyboardMan.h"
#include "../helper/eMouse.h"
#include "../mk/Scaleform.h"

#include "../gui/notifications.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl.h"

#include "../unreal/UWorld.h"

#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>


using namespace Memory::VP;

static const char* szCharacters[] = {
	// place npcs first for easy access
	"CHAR_Ermac_NPC",
	"CHAR_JanetCageCH15",
	"CHAR_QuanChi_NPC",
	"CH15_CyberSmokeCH15",
	"CH15_FemErmacCH15",
	"CH15_FemReptileCH15",
	"CH15_FemScorpionCH15",
	"CH15_FemSubZeroCH15",

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

	"CH15_AshrahCH15",
	"CH15_BarakaCH15",
	"CH15_ErmacCH15",
	"CH15_GerasCH15",
	"CH15_HavikCH15",
	"CH15_JohnnyCageCH15",
	"CH15_KenshiCH15",
	"CH15_KitanaCH15",
	"CH15_KungLaoCH15",
	"CH15_LiMeiCH15",
	"CH15_LiuKangCH15",
	"CH15_MileenaCH15",
	"CH15_NitaraCH15",
	"CH15_QuanChiCH15",
	"CH15_RaidenCH15",
	"CH15_RainMageCH15",
	"CH15_ReikoCH15",
	"CH15_ReptileCH15",
	"CH15_ScorpionCH15",
	"CH15_ShaoKahnCH15",
	"CH15_SindelCH15",
	"CH15_SmokeCH15",
	"CH15_SubZeroCH15",
	"CH15_TanyaCH15",


	// invasions
	"BOSS_Grunt_Ashrah_A",
	"BOSS_Grunt_Baraka_A",
	"BOSS_Grunt_Geras_A",
	"BOSS_Grunt_Havik_A",
	"BOSS_Grunt_JohnnyCage_A",
	"BOSS_Grunt_Kenshi_A",
	"BOSS_Grunt_Kitana_A",
	"BOSS_Grunt_KungLao_A",
	"BOSS_Grunt_LiMei_A",
	"BOSS_Grunt_LiuKang_A",
	"BOSS_Grunt_Mileena_A",
	"BOSS_Grunt_Nitara_A",
	"BOSS_Grunt_Raiden_A",
	"BOSS_Grunt_RainMage_A",
	"BOSS_Grunt_Reiko_A",
	"BOSS_Grunt_Reptile_A",
	"BOSS_Grunt_Scorpion_A",
	"BOSS_Grunt_ShaoKahn_A",
	"BOSS_Grunt_Sindel_A",
	"BOSS_Grunt_Smoke_A",
	"BOSS_Grunt_SubZero_A",
	"BOSS_Grunt_Tanya_A",
};

static const char* szKameos[] = {
	"KHAR_AdamKAM",
	"KHAR_BarakaKAM_NPC",
	"KHAR_CyraxKAM",
	"KHAR_DarriusKAM",
	"KHAR_ErmacKAM_NPC",
	"KHAR_FireElementalKAM",
	"KHAR_FrostKAM",
	"KHAR_GoroKAM",
	"KHAR_HavikKAM_NPC",
	"KHAR_IceElementalKAM",
	"KHAR_JaxKAM",
	"KHAR_JohnnyCageKAM_NPC",
	"KHAR_KanoKAM",
	"KHAR_KenshiKAM_NPC",
	"KHAR_KhameleonKAM_NPC",
	"KHAR_KitanaKAM_NPC",
	"KHAR_KungLaoKAM",
	"KHAR_KungLaoKAM_NPC",
	"KHAR_LightningElementalKAM_NPC",
	"KHAR_LiMeiKAM_NPC",
	"KHAR_LiuKangKAM_NPC",
	"KHAR_MileenaKAM_NPC",
	"KHAR_MotaroKAM",
	"KHAR_NitaraKAM_NPC",
	"KHAR_QuanChiKAM_NPC",
	"KHAR_RaidenKAM_NPC",
	"KHAR_RainMageKAM_NPC",
	"KHAR_ReikoKAM_NPC",
	"KHAR_ReptileKAM_NPC",
	"KHAR_SareenaKAM",
	"KHAR_ScorpionKAM",
	"KHAR_ScorpionKAM_NPC",
	"KHAR_SektorKAM",
	"KHAR_ShangTsungKAM_NPC",
	"KHAR_ShaoKahnKAM_NPC",
	"KHAR_ShujinkoKAM",
	"KHAR_SindelKAM_NPC",
	"KHAR_SmokeKAM_NPC",
	"KHAR_SonyaKAM",
	"KHAR_StrykerKAM",
	"KHAR_SubZeroKAM",
	"KHAR_SubZeroKAM_NPC",
	"KHAR_TanyaKAM_NPC",
	"KHAR_TarkatanCloneKAM",
};
const char* szBones[] = {
	"Head",
	"Hips",
	"Jaw",
	"LeftArm",
	"LeftFoot",
	"LeftForeArm",
	"LeftHand",
	"LeftLeg",
	"Neck",
	"Neck1",
	"Reference",
	"RightArm",
	"RightFoot",
	"RightHand",
	"RightLeg",
	"Spine",
	"Spine1",
	"Spine2",
	"Spine3",
};
const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Head Perspective",
//	"Third Person",
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
	sprintf(szPlayer1TagCharacter, szCharacters[0]);
	sprintf(szPlayer2TagCharacter, szCharacters[0]);
	sprintf(szPlayerKameoSource, szKameos[0]);
	sprintf(szPlayerKameoSwap, szKameos[0]);
}

void MK12Menu::SetupCharacterLists()
{
	m_CharacterList.clear();
	m_KameoList.clear();

	for (int i = 0; i < IM_ARRAYSIZE(szCharacters); i++)
	{
		m_CharacterList.push_back(szCharacters[i]);
	}

	for (int i = 0; i < IM_ARRAYSIZE(szKameos); i++)
	{
		m_KameoList.push_back(szKameos[i]);
	}

	// check if all files for extra chars are there

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2576800))
	{
		m_CharacterList.push_back("CHAR_ShangTsung");
		m_CharacterList.push_back("CHAR_Boss_ShangTsung_Tower");
		m_CharacterList.push_back("BOSS_Grunt_ShangTsung_A");
	}

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2636080))
		m_CharacterList.push_back("CHAR_OmniMan");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2636090))
		m_KameoList.push_back("KHAR_TremorKAM");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2695680))
		m_CharacterList.push_back("CHAR_QuanChi");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2695690))
		m_KameoList.push_back("KHAR_KhameleonKAM");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2777460))
		m_CharacterList.push_back("CHAR_Peacemaker");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2777480))
		m_KameoList.push_back("KHAR_JanetCageKAM");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2880670))
		m_CharacterList.push_back("CHAR_Ermac");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2968440))
		m_CharacterList.push_back("CHAR_Homelander");

	if (SteamAPI::IsAppInstalled(2576780) || SteamAPI::IsAppInstalled(2880680))
		m_KameoList.push_back("KHAR_MavadoKAM");


	for (auto& chr : m_CharacterList)
		m_TagList.push_back(chr);
	for (auto& kam : m_KameoList)
		m_TagList.push_back(kam);

}

void MK12Menu::Initialize()
{
	SetupCharacterLists();
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

	m_bHideHUD ^= 1;

	if (GetScaleform())
	{
		if (m_bHideHUD)
			GetScaleform()->m_bActive = false;
		else
			GetScaleform()->m_bActive = true;	
	}
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

			if (ImGui::MenuItem("Defintion Swap Reference"))
				m_bSubmenuActive[SUBMENU_DEFSWAP] = true;

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
		if (ImGui::BeginTabItem("Kameo"))
		{
			DrawKameoTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Tag"))
		{
			DrawTagTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Modifiers"))
		{
			DrawModifiersTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
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
		if (ImGui::BeginTabItem("Cheats"))
		{
			DrawCheatsTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Script"))
		{
			DrawScriptTab();
			ImGui::EndTabItem();
		}
#ifdef _DEBUG
		if (ImGui::BeginTabItem("World"))
		{
			DrawWorldTab();
			ImGui::EndTabItem();
		}
#endif
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		PluginInterface::ProcessPluginTabs();
		ImGui::EndTabBar();
	}
	ImGui::End();


	if (m_bSubmenuActive[SUBMENU_DEFSWAP])
		DrawDefinitionSwapReference();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();

}

void MK12Menu::Process()
{
	UpdateControls();
}

void MK12Menu::UpdateControls()
{
	if (!m_bIsActive)
		ProcessScriptHotkeys();

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
				TheMenu->camRot.Z -= rotSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
				TheMenu->camRot.Z += rotSpeed;

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
	ImGui::TextWrapped("Swap Method");
	ImGui::Separator();
	ImGui::RadioButton("Normal", &m_nCurrentCharModifier, MODIFIER_NORMAL);
	ImGui::SameLine();
	ShowHelpMarker("Versus/Practice only.");
	ImGui::SameLine();
	ImGui::RadioButton("Character Swap", &m_nCurrentCharModifier, MODIFIER_CHARSWAP);
	ImGui::SameLine();
	ShowHelpMarker("Replaces character based on used ID, Player 1 becomes source character and Player 2 becomes replacement, use this method to swap in story or modes where normal doesn't work! Reload match after using this option");
	ImGui::Separator();
	ImGui::Checkbox((m_nCurrentCharModifier == MODIFIER_NORMAL ? "Change Player 1 Character" : "Change P1 Source Character"), &m_bPlayer1Modifier);

	if (!m_bManualInput)
	{
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##p1chr", szPlayer1ModifierCharacter))
		{
			for (unsigned int n = 0; n < m_CharacterList.size(); n++)
			{
				bool is_selected = (szPlayer1ModifierCharacter == m_CharacterList[n].c_str());
				if (ImGui::Selectable(m_CharacterList[n].c_str(), is_selected))
					sprintf(szPlayer1ModifierCharacter, m_CharacterList[n].c_str());
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
			for (unsigned int n = 0; n < m_CharacterList.size(); n++)
			{
				bool is_selected = (szPlayer2ModifierCharacter == m_CharacterList[n].c_str());
				if (ImGui::Selectable(m_CharacterList[n].c_str(), is_selected))
					sprintf(szPlayer2ModifierCharacter, m_CharacterList[n].c_str());
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
	ImGui::TextWrapped("Works in versus and practice only. Reset match or change kameo in practice to reload any missing assets (or skin).");
	ImGui::Separator();
	ImGui::Checkbox("Change Player 1 Kameo", &m_bPlayer1KameoModifier);
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##p1kameo", szPlayer1KameoCharacter))
	{
		for (unsigned int n = 0; n < m_KameoList.size(); n++)
		{
			bool is_selected = (szPlayer1KameoCharacter == m_KameoList[n].c_str());
			if (ImGui::Selectable(m_KameoList[n].c_str(), is_selected))
				sprintf(szPlayer1KameoCharacter, m_KameoList[n].c_str());
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	ImGui::Checkbox("Change Player 2 Kameo", &m_bPlayer2KameoModifier);
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##p2kameo", szPlayer2KameoCharacter))
	{
		for (unsigned int n = 0; n < m_KameoList.size(); n++)
		{
			bool is_selected = (szPlayer2KameoCharacter == m_KameoList[n].c_str());
			if (ImGui::Selectable(m_KameoList[n].c_str(), is_selected))
				sprintf(szPlayer2KameoCharacter, m_KameoList[n].c_str());
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	if (ImGui::CollapsingHeader("Extras"))
	{
		ImGui::TextWrapped("Look up the log/console window for possible skin names, most however use a simple pattern, eg. \"BP_ScorpionKAM_Skin001_A_Char\". Skins apply only to characters they're designed for. Khameleon (Story) skin is \"BP_KhameleonKAM_Story_Disk\"");
		ImGui::Checkbox("Change Player 1 Kameo Skin", &m_bPlayer1KameoSkinModifier);
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p1kskin", szPlayer1KameoSkin, sizeof(szPlayer1KameoSkin));
		ImGui::PopItemWidth();

		ImGui::Checkbox("Change Player 2 Kameo Skin", &m_bPlayer2KameoSkinModifier);
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##p2kskin", szPlayer2KameoSkin, sizeof(szPlayer2KameoSkin));
		ImGui::PopItemWidth();

		ImGui::Separator();
		ImGui::Checkbox("Kameo Swap On Load", &m_bKameoReplace);
		ImGui::SameLine(); ShowHelpMarker("Replaces kameo character similar to character swap modifier from Character tab, should work in story");
		ImGui::Separator();

		ImGui::TextWrapped("Kameo Source Character");
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##ksrc", szPlayerKameoSource))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szKameos); n++)
			{
				bool is_selected = (szPlayerKameoSource == szKameos[n]);
				if (ImGui::Selectable(szKameos[n], is_selected))
					sprintf(szPlayerKameoSource, szKameos[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::TextWrapped("Kameo Swap Character");
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##kswp", szPlayerKameoSwap))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szKameos); n++)
			{
				bool is_selected = (szPlayerKameoSwap == szKameos[n]);
				if (ImGui::Selectable(szKameos[n], is_selected))
					sprintf(szPlayerKameoSwap, szKameos[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

	}
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
		for (unsigned int n = 0; n < m_TagList.size(); n++)
		{
			bool is_selected = (szPlayer1TagCharacter == m_TagList[n].c_str());
			if (ImGui::Selectable(m_TagList[n].c_str(), is_selected))
				sprintf(szPlayer1TagCharacter, m_TagList[n].c_str());
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
		for (unsigned int n = 0; n < m_TagList.size(); n++)
		{
			bool is_selected = (szPlayer2TagCharacter == m_TagList[n].c_str());
			if (ImGui::Selectable(m_TagList[n].c_str(), is_selected))
				sprintf(szPlayer2TagCharacter, m_TagList[n].c_str());
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
}

void MK12Menu::DrawPlayerTab()
{
	if (GetObjActor(PLAYER1) && GetObjActor(PLAYER2))
	{
		ImGui::Checkbox("Change Player Scale", &m_bChangePlayerScale);
		ImGui::InputFloat3("Player 1 ", &m_vP1Scale.X);
		ImGui::InputFloat3("Player 2 ", &m_vP2Scale.X);

		if (ImGui::Button("Reset Scale"))
		{
			m_vP1Scale = { 1.0f,1.0f,1.0f };
			m_vP2Scale = { 1.0f,1.0f,1.0f };
			if (GetObj(PLAYER1))
				GetObj(PLAYER1)->SetScale(&m_vP1Scale);
			if (GetObj(PLAYER2))
				GetObj(PLAYER2)->SetScale(&m_vP2Scale);
		}
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SameLine(); ShowHelpMarker("Read only!");
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

	if (GetObjActor(PLAYER1) && GetObjActor(PLAYER2))
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
		/*else if (m_nCurrentCustomCamera == CAMERA_THIRD_PERSON)
		{
			ImGui::InputFloat("X Offset", &m_fAdjustCustomCameraThirdPersonX);
			ImGui::InputFloat("Y Offset", &m_fAdjustCustomCameraThirdPersonY);
			ImGui::InputFloat("Z Offset", &m_fAdjustCustomCameraThirdPersonZ);

			ImGui::Checkbox("Use Player Two As Source", &m_bUsePlayerTwoAsTracker);
		}
		*/
	}
	else
		ImGui::Text("Custom cameras will appear once in-game!");


}

void MK12Menu::DrawCheatsTab()
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 14 * ImGui::GetFontSize());

	ImGui::Text("Infinite Health");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
	ImGui::NextColumn();


	ImGui::Text("Zero Health\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
	ImGui::NextColumn();


	ImGui::Text("1 Health\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##1health", &m_bOneHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##1health", &m_bOneHealthP2);
	ImGui::NextColumn();


	ImGui::Text("Infinite Supermeter\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##met", &m_bInfiniteMeterP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##met", &m_bInfiniteMeterP2);
	ImGui::NextColumn();

	ImGui::Text("Zero Supermeter\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##zmet", &m_bZeroMeterP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##zmet", &m_bZeroMeterP2);
	ImGui::NextColumn();


	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		ImGui::Text("Quick Uppercut Recovery\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##ups", &m_bFastUppercutsP1))
		{
			if (m_bFastUppercutsP1)
				GetObj(PLAYER1)->SetFastUppercutRecovery(true);
			else
				GetObj(PLAYER1)->SetFastUppercutRecovery(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##ups", &m_bFastUppercutsP2))
		{
			if (m_bFastUppercutsP2)
				GetObj(PLAYER2)->SetFastUppercutRecovery(true);
			else
				GetObj(PLAYER2)->SetFastUppercutRecovery(false);
		}
		ImGui::NextColumn();

		ImGui::Text("Infinite Fatal Blows\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##ixr", &m_bInfiniteXraysP1))
		{
			if (m_bInfiniteXraysP1)
				GetObj(PLAYER1)->SetXRayInfinite(true);
			else
				GetObj(PLAYER1)->SetXRayInfinite(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##ixr", &m_bInfiniteXraysP2))
		{
			if (m_bInfiniteXraysP2)
				GetObj(PLAYER2)->SetXRayInfinite(true);
			else
				GetObj(PLAYER2)->SetXRayInfinite(false);
		}
		ImGui::NextColumn();

		ImGui::Text("Fatal Blow Always Active\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##uxr", &m_bXrayAlwaysP1))
		{
			if (m_bXrayAlwaysP1)
				GetObj(PLAYER1)->SetXRayNoRequirement(true);
			else
				GetObj(PLAYER1)->SetXRayNoRequirement(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##uxr", &m_bXrayAlwaysP2))
		{
			if (m_bXrayAlwaysP2)
				GetObj(PLAYER2)->SetXRayNoRequirement(true);
			else
				GetObj(PLAYER2)->SetXRayNoRequirement(false);
		}
		ImGui::NextColumn();

		ImGui::Text("Easy Brutalities\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##bru", &m_bEasyBrutalitiesP1))
		{
			if (m_bEasyBrutalitiesP1)
				GetObj(PLAYER1)->SetEasyBrutalities(true);
			else
				GetObj(PLAYER1)->SetEasyBrutalities(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##bru", &m_bEasyBrutalitiesP2))
		{
			if (m_bEasyBrutalitiesP2)
				GetObj(PLAYER2)->SetEasyBrutalities(true);
			else
				GetObj(PLAYER2)->SetEasyBrutalities(false);
		}
		ImGui::NextColumn();
	}




	ImGui::Columns(1);
	ImGui::Separator();

}

void MK12Menu::DrawMiscTab()
{
	if (ImGui::Button("Hide FightHUD"))
		HideHUD();
	ImGui::SameLine();
	if (ImGui::Button("Show FightHUD"))
		ShowHUD();

	if (ImGui::Checkbox("Disable HUD", &m_bHideHUD))
	{
		if (GetScaleform())
		{
			if (m_bHideHUD)
				GetScaleform()->m_bActive = false;
			else
				GetScaleform()->m_bActive = true;
		}
	}
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

#ifdef _DEBUG
	ImGui::Text("GameInfo: %p", GetGameInfo());
	ImGui::Text("PlayerInfo[0]: %p", GetGameInfo()->GetInfo(PLAYER1));
	ImGui::Text("PlayerInfo[1]: %p", GetGameInfo()->GetInfo(PLAYER2));
	ImGui::Text("MKCharacter P1: %p", GetGameInfo()->GetObj(PLAYER1));
	ImGui::Text("MKCharacter P2: %p", GetGameInfo()->GetObj(PLAYER2));
	ImGui::Text("MKCharacter P1.obj: %p", GetObjActor(PLAYER1));
	ImGui::Text("MKCharacter P2.obj: %p", GetObjActor(PLAYER2));
	if (GetGameInfo()->GetInfo(PLAYER1))
	{
		MKCharacter* p1 = (MKCharacter*)GetGameInfo()->GetObj(PLAYER1);
		ImGui::Text("MKCharacter P1.flags: %p %d", p1->GetFlags(), p1->GetFlagsOffset());
	}

	if (ImGui::CollapsingHeader("FName test"))
	{
		static int FNameID = 0;
		ImGui::InputInt("FnameID", &FNameID);
		if (ImGui::Button("test", { -FLT_MIN, 0 }))
		{
			FName name;
			name.Index = FNameID;
			FString str;
			name.ToString(&str);
			printf("FName[%05d] - %p [%ws]\n", FNameID, str.GetStr(), str.GetStr());
		}
		static char FNameAdd[512] = {};
		ImGui::InputText("FName add", FNameAdd, sizeof(FNameAdd));
		if (ImGui::Button("add", { -FLT_MIN, 0 }))
		{
			FName newName(FNameAdd, FNAME_Add, 1);
			printf("Added FName %05d [%s]\n", newName.Index, FNameAdd);
		}
		if (ImGui::Button("find", { -FLT_MIN, 0 }))
		{
			FName newName(FNameAdd, FNAME_Find, 1);
			printf("Find FName %05d [%s]\n", newName.Index, FNameAdd);
		}
	}
#endif
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
		KeyBind(&SettingsMgr->iToggleHUDKey, "Toggle HUD", "thud");
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

void MK12Menu::DrawScriptTab()
{
	static int functionIndex = 0;
	static char szFunction[256] = {};
	static int hash = 0;
	static unsigned int voidArgHash = _hash("void");
	static unsigned int mkCharacterArgHash = _hash("MKCharacterObj&");
	static std::vector<std::string> lastArgs;
	static PowerAttackCache lastCache;
	static char szScriptSource[256] = {};

	enum EScriptTabMode {
		ScriptTab_Basic = 1,
		ScriptTab_SpecialMoves,
	};
	static int scriptMode = ScriptTab_Basic;


	ImGui::TextWrapped("Execution Type");
	ImGui::Separator();
	ImGui::RadioButton("On Player1", &m_nScriptExecuteType, SCRIPT_P1); ImGui::SameLine();
	ImGui::RadioButton("On Player2", &m_nScriptExecuteType, SCRIPT_P2);
	ImGui::Separator();
	ImGui::TextWrapped("Script Calling Type");
	ImGui::Separator();
	if (ImGui::RadioButton("Default", &scriptMode, ScriptTab_Basic))
		szFunction[0] = 0x00;
	ImGui::SameLine();
	if (ImGui::RadioButton("Special Moves", &scriptMode, ScriptTab_SpecialMoves))
		szFunction[0] = 0x00;
	ImGui::SameLine();
	ShowHelpMarker("Unlike previous MKs, introduction of kameos has changed the way special moves can be executed, use this mode to call only all available special moves from all players.");
	ImGui::Separator();

	ImGui::TextWrapped("Script Source (.MKO)");
	ImGui::SameLine();
	ShowHelpMarker(".MKO file names can be found in MKScript folder. Alternatively add .mko to names from Character and Kameo tabs.");
	ImGui::PushItemWidth(-FLT_MIN);
	ImGui::InputText("##scriptsrc", szScriptSource, sizeof(szScriptSource));
	ImGui::PopItemWidth();

	m_pScript = GetScript(szScriptSource);
	if (m_pScript)
	{
		if (scriptMode == ScriptTab_Basic)
		{
			ImGui::Text("Function List");
			static ImGuiTextFilter filter;
			ImGui::Text("Search");
			ImGui::PushItemWidth(-FLT_MIN);
			filter.Draw("##fnlist");
			ImGui::PopItemWidth();
			static int selectID = 0;
			ImGui::BeginChild("##list", { 0, 125.0f }, true);
			{
				for (int i = 0; i < m_pScript->functions.Count; i++)
				{
					mko_function_header_mk12& function = m_pScript->functions.Get(i);

					if (function.functionName)
					{
						if (filter.PassFilter(function.functionName))
						{
							bool is_selected = (selectID == i);
							if (ImGui::Selectable(function.functionName, is_selected))
							{
								lastArgs.clear();
								selectID = i;
								sprintf(szFunction, "%s", function.functionName);

								for (int a = 0; a < m_pScript->functions.Get(i).functionInfo->args.Count; a++)
								{
									int offset = m_pScript->functions.Get(i).functionInfo->args.Get(a);
									if (offset > 0)
									{
										std::string arg = (char*)((int64)&m_pScript->scriptData->script_string.Data[0] + (offset - 1));
										lastArgs.push_back(arg);
									}
									
								}
							}
						}
					}


				}
			}
			ImGui::EndChild();
			if (strlen(szFunction) > 0)
			{
				ImGui::TextWrapped("Selected function: %s", szFunction);
				if (IsFunctionSafeToCall(lastArgs))
					ImGui::TextColored(ImVec4(0.6, 1.0, 0.6, 1.0), "This function (probably) can be called.");
				else
					ImGui::TextColored(ImVec4(1.0, 0.6, 0.6, 1.0), "This function will probably crash the game.");

#ifdef _DEBUG
				std::string functionDef;
				ImGui::TextWrapped("Selected function definition %d/%d", selectID, m_pScript->functions.Count);
				if (lastArgs.size() == 1)
				{
					functionDef += lastArgs[0];
					functionDef += " ";
					functionDef += szFunction;
				}
				else
				{
					functionDef += lastArgs[0];
					functionDef += " ";
					functionDef += szFunction;
					functionDef += "(";

					for (unsigned int i = 1; i < lastArgs.size(); i++)
					{
						functionDef += lastArgs[i];
						if (!(i == lastArgs.size() - 1))
						functionDef += " ,";
					}
					functionDef += ")";
				}

				ImGui::Text(functionDef.c_str());
#endif
			}
		}
		else if (scriptMode == ScriptTab_SpecialMoves)
		{
			ImGui::Text("Special Moves Function List");
			static ImGuiTextFilter filter;
			ImGui::Text("Search");
			ImGui::PushItemWidth(-FLT_MIN);
			filter.Draw("##palist");
			ImGui::PopItemWidth();	
			static int selectID = 0;

			ImGui::BeginChild("##paolist", { 0, 125.0f }, true);
			{
				for (int i = 0; i < m_PowerAttacksList.size(); i++)
				{
					PowerAttackCache cache = m_PowerAttacksList[i];

					std::string scriptName = szScriptSource;
					std::transform(scriptName.begin(), scriptName.end(), scriptName.begin(), tolower);

					if (strcmp(scriptName.c_str(), cache.scriptSource) == 0)
					{
						if (filter.PassFilter(cache.name))
						{
							bool is_selected = (selectID == i);
							if (ImGui::Selectable(cache.name, is_selected))
							{
								selectID = i;
								lastCache = cache;
								sprintf(szFunction, "%s", cache.name);
							}
						}
					}


				}
			}
			ImGui::EndChild();
			if (strlen(szFunction) > 0)
			{
				ImGui::TextWrapped("Selected function: %s", szFunction);
			}
		}
			
		static eScriptKeyBind bind = {};
		if (ImGui::Button("Add Hotkey"))
		{
			if (scriptMode == ScriptTab_SpecialMoves)
				bind.isPowerAttack = true;
			else
				bind.isPowerAttack = false;

			if (!bind.isPowerAttack)
			{
				m_nHash = _hash(szFunction);
				functionIndex = m_pScript->GetFunctionID(m_nHash);

				bind.functionHash = m_nHash;
				sprintf(bind.scriptName, "%s", szScriptSource);
				bind.type = (eScriptExecuteType)m_nScriptExecuteType;
			}
			else
			{
				bind.powerAttackCache = lastCache;
			}


			m_bPressingKey = true;
		}

		if (m_bPressingKey)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				bind.key = result;
				if (scriptMode == ScriptTab_SpecialMoves)
					bind.isPowerAttack = true;
				else
					bind.isPowerAttack = false;

				m_vKeyBinds.push_back(bind);
				m_bPressingKey = false;
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Run"))
		{
			m_nHash = _hash(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			// todo: more types
			if (scriptMode == ScriptTab_SpecialMoves)
			{
				TheMenu->m_paCache = lastCache;
				RunLastScript(true);
			}
			else
				RunLastScript(false);

		}
	}
	else
	{
		if (strlen(szScriptSource) > 0)
			ImGui::TextWrapped("Cannot load %s!", szScriptSource);
	}

	ImGui::Separator();
	ImGui::TextWrapped("Registered hotkeys:");
	for (unsigned int i = 0; i < m_vKeyBinds.size(); i++)
	{
		if (m_vKeyBinds[i].isPowerAttack)
			ImGui::TextWrapped("%s - Run [0x%X] from %s", eKeyboardMan::KeyToString(m_vKeyBinds[i].key), _hash(m_vKeyBinds[i].powerAttackCache.name), m_vKeyBinds[i].powerAttackCache.scriptSource);
		else
			ImGui::TextWrapped("%s - Run [0x%X] from %s", eKeyboardMan::KeyToString(m_vKeyBinds[i].key), m_vKeyBinds[i].functionHash, m_vKeyBinds[i].scriptName);
	}

	if (ImGui::Button("Clear All"))
		m_vKeyBinds.clear();


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

void MK12Menu::DrawModifiersTab()
{
	if (ImGui::BeginTabBar("##modifiers"))
	{
		if (ImGui::BeginTabItem("Skin Definition Swap"))
		{
			ImGui::TextWrapped("Check help for information on how to use this tab.");
			ImGui::Checkbox("Enable Skin Definition Log", &m_bDefinitionSwapLog);
			ImGui::SameLine(); ShowHelpMarker("Will print all skin definitions to console and log.");
			ImGui::Checkbox("Enable Definition Swap", &m_bDefinitionSwap);
			ImGui::Separator();

			ImGui::TextWrapped("Definition Source");
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("##defsrc", szDefinitionSwap_Source, sizeof(szDefinitionSwap_Source));
			ImGui::PopItemWidth();

			ImGui::TextWrapped("Definition Swap");
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("##defswp", szDefinitionSwap_Swap, sizeof(szDefinitionSwap_Swap));
			ImGui::PopItemWidth();
			ImGui::Separator();

			ImGui::Checkbox("Enable Extra Definition Swap", &m_bDefinitionExtraSwap);
			ImGui::Separator();

			ImGui::TextWrapped("Definition Extra Source");
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("##edefsrc", szDefinitionExtraSwap_Source, sizeof(szDefinitionExtraSwap_Source));
			ImGui::PopItemWidth();

			ImGui::TextWrapped("Definition Extra Swap");
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("##edefswp", szDefinitionExtraSwap_Swap, sizeof(szDefinitionExtraSwap_Swap));
			ImGui::PopItemWidth();

			

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void MK12Menu::RunLastScript(bool powerAttack)
{
	if (powerAttack)
	{
		if (m_paCache.defPtr)
		{
			MKCharacter* obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER1);
			if (m_nScriptExecuteType == SCRIPT_P2)
				obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER2);

			if (obj)
				obj->ExecutePowerAttack(m_paCache.defPtr);
		}
		else
		{
			Notifications->SetNotificationTime(3500);
			Notifications->PushNotification("Special move does not exist!");
		}
	}
	else
	{
		if (m_pScript)
		{
			if (m_pScript->GetFunctionID(m_nHash))
			{
				MKCharacter* obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER1);
				if (m_nScriptExecuteType == SCRIPT_P2)
					obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER2);

				if (obj)
					obj->ExecuteScript(m_pScript, m_nHash);
			}
			else
			{
				Notifications->SetNotificationTime(3500);
				Notifications->PushNotification("Function %x does not exist!", m_nHash);
			}
		}
	}

}

void MK12Menu::ProcessScriptHotkeys()
{
	if (TheMenu->m_bIsActive)
		return;

	for (int i = 0; i < m_vKeyBinds.size(); i++)
	{
		if (GetAsyncKeyState(m_vKeyBinds[i].key) & 0x1)
		{
			if (m_vKeyBinds[i].isPowerAttack)
			{
				if (m_vKeyBinds[i].powerAttackCache.defPtr)
				{
					MKCharacter* obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER1);
					if (m_nScriptExecuteType == SCRIPT_P2)
						obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER2);

					if (obj)
						obj->ExecutePowerAttack(m_vKeyBinds[i].powerAttackCache.defPtr);
				}
				else
				{
					Notifications->SetNotificationTime(3500);
					Notifications->PushNotification("Special move does not exist!");
				}
			}
			else
			{
				MKScript* script = GetScript(m_vKeyBinds[i].scriptName);
				if (script)
				{
					if (script->GetFunctionID(m_vKeyBinds[i].functionHash))
					{
						MKCharacter* obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER1);
						if (m_vKeyBinds[i].type == SCRIPT_P2)
							obj = (MKCharacter*)GetGameInfo()->GetObj(PLAYER2);

						if (obj)
							obj->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					}
					else
					{
						Notifications->SetNotificationTime(3500);
						Notifications->PushNotification("Function %x does not exist!", m_vKeyBinds[i].functionHash);
					}
				}
				else
				{
					Notifications->SetNotificationTime(3500);
					Notifications->PushNotification("Script %s couldn't be loaded!", m_vKeyBinds[i].scriptName);
				}
			}
			

			
		}
	}
}

bool MK12Menu::IsFunctionSafeToCall(std::vector<std::string>& args)
{
	if (args[0] == "void" && args.size() == 1)
		return true;
	
	if (args[0] == "void" && args.size() >= 2)
	{
		if (strstr(args[1].c_str(), "NavigationAction") || strstr(args[1].c_str(), "ScriptAction") || strstr(args[1].c_str(), "MKCharacter")
			|| strstr(args[1].c_str(), "void") || strstr(args[1].c_str(), "EndOfRoundAction") || strstr(args[1].c_str(), "VictoryAction"))
			return true;
	}
	return false;
}

void MK12Menu::DrawWorldTab()
{
#ifdef _DEBUG
	UWorld* world = GetWorld();

	if (!world)
		return;

	if (!world->PersistentLevel)
		return;

	ULevel* p = world->PersistentLevel;

	ImGui::Text("%p", world);
	ImGui::Text("StreamingNum %d/%d", world->StreamingLevels.Count, world->StreamingLevels.Max);
	ImGui::Text("Persistent level: %p", p);
	ImGui::Text("Persistent level actors: %d/%d", p->Actors.Count, p->Actors.Max);

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Persistent Level"))
	{
		for (int i = 0; i < p->Actors.Count; i++)
		{
			UObject* a = p->Actors.Get(i);
			if (a)
			{
				FString str;
				a->Name.ToString(&str);

				FString classStr;

				if (a->Class)
				{
					a->Class->Name.ToString(&classStr);
				}

				ImGui::Text("%03d | 0x%p | [%ws] %ws", i + 1, a, classStr.GetStr(), str.GetStr());
			}
		}
	}

	for (int i = 0; i < world->StreamingLevels.Count; i++)
	{
		ULevelStreaming* ls = world->StreamingLevels.Get(i);
		if (ls)
		{
			static char nameTab[128] = {};
			sprintf_s(nameTab, "SLevel %d##l%d", i, i);
			if (ImGui::CollapsingHeader(nameTab))
			{
				ULevel* l = ls->LoadedLevel;
				if (l)
				{
					for (int k = 0; k < l->Actors.Count; k++)
					{
						UObject* a = l->Actors.Get(k);
						if (a)
						{
							FString str;
							a->Name.ToString(&str);

							FString classStr;

							if (a->Class)
							{
								a->Class->Name.ToString(&classStr);
							}

							ImGui::Text("%03d | 0x%p | [%ws] %ws", k + 1, a, classStr.GetStr(), str.GetStr());
						}
					}
				}
			}
		}
	}
#endif
	
}

void MK12Menu::OnJump()
{
	m_PowerAttacksList.clear();
	m_paCache = {};
	m_pScript = nullptr;
	m_nHash = 0;
}

void MK12Menu::DrawDefinitionSwapReference()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 35 * ImGui::GetFontSize(), 35 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Definition Swap", &m_bSubmenuActive[SUBMENU_DEFSWAP]);

	static int secID = 0;
	static const char* scriptSections[] = {
		"General",
	};

	enum eScriptRef {
		GEN,
	};

	ImGui::BeginChild("##info", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(scriptSections); n++)
	{
		bool is_selected = (secID == n);
		if (ImGui::Selectable(scriptSections[n], is_selected))
			secID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (secID)
	{
	case GEN:
		ImGui::TextWrapped("Definition swaps can only be done with already loaded models! It is not possible to load extra ones. This means it is not possible to swap to someone that is not in the fight, all models must be loaded during swap. For best results change P2 kameo to the character you want to swap.");
		ImGui::Separator();
		ImGui::TextWrapped("1. Enter any match, then enable definition log and restart the fight.\n"
			"2. Check the console or log to see loaded definition names.\n"
		"3. Look up first available skin for the character you want to swap, for Cage it is \"/Game/Disk/Char/JohnnyCage/Skin/002/Blueprint/BP_JohnnyCage_Skin002_A_Char.BP_JohnnyCage_Skin002_A_Char_C\"\n"
		"4. Copy only part of the definition into the definition source field, so in this case it would be \"BP_JohnnyCage_\"\n"
		"5. In definition swap field, enter the full new definition path, for example: \"/Game/Disk/Kameo/StrykerKAM/Skin/001/Blueprint/BP_StrykerKAM_Skin001_A_Char.BP_StrykerKAM_Skin001_A_Char_C\"\n"
		"6. Enable definition swap ONLY if both fields have data in them.\n"
		"7. Go to character tab and set P1 or P2 skin value to the new definition, so in this case it would be \"BP_StrykerKAM_Skin001_A_Char\"\n"
		"8. Restart the match (or change kameos to restart in practice)\n");
		break;
	default:
		break;
	}

	ImGui::EndChild();

	ImGui::End();
}
