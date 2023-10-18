// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PluginInfo.h"
#include <iostream>
#include "SDK.h"

// Plugin name to use when loading and printing errors to log
extern "C" PLUGIN_API const char* GetPluginName()
{
    return "SamplePlugin";
}

// Hook project name that this plugin is compatible with
extern "C" PLUGIN_API const char* GetPluginProject()
{
    return "MK12HOOK";
}

// GUI tab name that will be used in the Plugins section
extern "C" PLUGIN_API const char* GetPluginTabName()
{
    return "Sample";
}

// Initialization
extern "C" PLUGIN_API void OnInitialize(HMODULE hMod)
{
    MK12HOOKSDK::Initialize(hMod);
}

// Shutdown
extern "C" PLUGIN_API void OnShutdown()
{

}

// Called every game tick
extern "C" PLUGIN_API void OnFrameTick()
{

}

// Called on match/fight start
extern "C" PLUGIN_API void OnFightStartup()
{
    // not implemented yet
}

// Tab data for menu, remove this if you don't want a plugin tab
extern "C" PLUGIN_API void TabFunction()
{
    if (!MK12HOOKSDK::IsOK())
        return;


    static int counter = 0;

    if (MK12HOOKSDK::ImGui_CollapsingHeader("Basic"))
    {
        MK12HOOKSDK::ImGui_Text("Text");

        static bool toggle = false;
        MK12HOOKSDK::ImGui_Checkbox("Toggle", &toggle);

        if (MK12HOOKSDK::ImGui_Button("button"))
            counter++;

        MK12HOOKSDK::ImGui_Text("Version");
        MK12HOOKSDK::ImGui_Text(MK12HOOKSDK::GetVersion());

    }
    if (MK12HOOKSDK::ImGui_CollapsingHeader("Input"))
    {
        MK12HOOKSDK::ImGui_InputInt("InputInt", &counter);


        static float flt = 1.0f;

        MK12HOOKSDK::ImGui_InputFloat("InputFloat", &flt);

        MK12HOOKSDK::ImGui_Separator();

        static char comboBuffer[256] = {};

        MK12HOOKSDK::ImGui_InputText("InputText", comboBuffer, sizeof(comboBuffer));

        static const char* comboContent[3] = {
            "One",
            "Two",
            "Three",
        };

        if (MK12HOOKSDK::ImGui_BeginCombo("Combo", comboBuffer))
        {
            for (int n = 0; n < 3; n++)
            {
                bool is_selected = (comboBuffer == comboContent[n]);
                if (MK12HOOKSDK::ImGui_Selectable(comboContent[n], is_selected))
                    sprintf_s(comboBuffer, comboContent[n]);
                if (is_selected)
                    MK12HOOKSDK::ImGui_SetItemDefaultFocus();

            }
            MK12HOOKSDK::ImGui_EndCombo();
        }
    }
    if (MK12HOOKSDK::ImGui_CollapsingHeader("Color"))
    {
        static float color[4] = {};
        MK12HOOKSDK::ImGui_ColorEdit4("RGB pick", color);
    }

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

