#include "API.h"
#include "Menu.h"
#include "..\gui\imgui\imgui.h"
#include "..\mk\PlayerInfo.h"
#include "..\minhook\include\MinHook.h"
#include "..\gui\notifications.h"

bool MK12HOOK_GetMenuActive()
{
    return TheMenu->m_bIsActive;
}

MKCharacter* MK12HOOK_GetCharacterObject(PLAYER_NUM id)
{
    return GetObj(id);
}

PlayerInfo* MK12HOOK_GetPlayerInfo(PLAYER_NUM id)
{
    return GetInfo(id);
}

FGGameInfo* MK12HOOK_GetGameInfo()
{
    return GetGameInfo();
}

void MK12HOOK_ImGui_Text(const char* text)
{
    ImGui::TextWrapped(text);
}

bool MK12HOOK_ImGui_Checkbox(const char* text, bool* value)
{
    return ImGui::Checkbox(text, value);
}

bool MK12HOOK_ImGui_Button(const char* text)
{
    return ImGui::Button(text);
}

bool MK12HOOK_ImGui_InputInt(const char* text, int* value)
{
    return ImGui::InputInt(text, value);
}

bool MK12HOOK_ImGui_InputFloat(const char* text, float* value)
{
    return ImGui::InputFloat(text, value);
}

bool MK12HOOK_ImGui_InputText(const char* label, char* buff, size_t size)
{
    return ImGui::InputText(label, buff, size);
}

bool MK12HOOK_ImGui_BeginCombo(const char* label, const char* previewValue)
{
    return ImGui::BeginCombo(label, previewValue);
}

void MK12HOOK_ImGui_EndCombo()
{
    ImGui::EndCombo();
}

bool MK12HOOK_ImGui_Selectable(const char* label, bool selected)
{
    return ImGui::Selectable(label, selected);
}

void MK12HOOK_ImGui_SetItemDefaultFocus()
{
    ImGui::SetItemDefaultFocus();
}

void MK12HOOK_ImGui_Separator()
{
    ImGui::Separator();
}

bool MK12HOOK_ImGui_CollapsingHeader(const char* label)
{
    return ImGui::CollapsingHeader(label);
}

uintptr_t MK12HOOK_GetPattern(const char* pattern, int offset)
{
    return PatternSolver::GetPattern(pattern, offset);
}

bool MK12HOOK_ImGui_ColorEdit4(const char* label, float* col)
{
    return ImGui::ColorEdit4(label, col);
}

int MK12HOOK_CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal)
{
    MH_STATUS s = MH_CreateHook(pTarget, pDetour, ppOriginal);
    if (s == MH_OK)
        s = MH_EnableHook(pTarget);
    return s;
}

void MK12HOOK_PushNotif(int time, const char* text)
{
    Notifications->SetNotificationTime(time);
    Notifications->PushNotification(text);
}

const char* MK12HOOK_GetVersion()
{
    return MK12HOOK_VERSION;
}

