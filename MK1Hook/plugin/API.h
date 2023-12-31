#pragma once
#include "..\mk\Engine.h"

extern "C"  {
	__declspec(dllexport) bool MK12HOOK_GetMenuActive();
	__declspec(dllexport) MKCharacter* MK12HOOK_GetCharacterObject(PLAYER_NUM id);
	__declspec(dllexport) PlayerInfo* MK12HOOK_GetPlayerInfo(PLAYER_NUM id);
	__declspec(dllexport) FGGameInfo* MK12HOOK_GetGameInfo();
	__declspec(dllexport) void MK12HOOK_ImGui_Text(const char* text);
	__declspec(dllexport) bool MK12HOOK_ImGui_Checkbox(const char* text, bool* value);
	__declspec(dllexport) bool MK12HOOK_ImGui_Button(const char* text);
	__declspec(dllexport) bool MK12HOOK_ImGui_InputInt(const char* text, int* value);
	__declspec(dllexport) bool MK12HOOK_ImGui_InputFloat(const char* text, float* value);
	__declspec(dllexport) bool MK12HOOK_ImGui_InputText(const char* label, char* buff, size_t size);
	__declspec(dllexport) bool MK12HOOK_ImGui_BeginCombo(const char* label, const char* previewValue);
	__declspec(dllexport) void MK12HOOK_ImGui_EndCombo();
	__declspec(dllexport) bool MK12HOOK_ImGui_Selectable(const char* label, bool selected);
	__declspec(dllexport) void MK12HOOK_ImGui_SetItemDefaultFocus();
	__declspec(dllexport) void MK12HOOK_ImGui_Separator();
	__declspec(dllexport) bool MK12HOOK_ImGui_CollapsingHeader(const char* label);
	__declspec(dllexport) uintptr_t MK12HOOK_GetPattern(const char* pattern, int offset);
	__declspec(dllexport) bool MK12HOOK_ImGui_ColorEdit4(const char* label, float* col);
	__declspec(dllexport) int MK12HOOK_CreateHook(LPVOID, LPVOID, LPVOID*);
	__declspec(dllexport) void MK12HOOK_PushNotif(int time, const char* text);
	__declspec(dllexport) const char* MK12HOOK_GetVersion();
}