#include "Hooks.h"

void PluginDispatch()
{
	TheMenu->Process();
	eMouse::UpdateMouse();
	Notifications->Update();

	FGGameInfo* GameInfo = GetGameInfo();

	if (!GameInfo)
		return;

	if (TheMenu->m_bSlowMotion)
		GameInfo->SetGameSpeed(TheMenu->m_fSlowMotionSpeed);

	PluginInterface::OnFrameTick();
}

void PluginFightStartup()
{
	printf("MK12Hook::Info() | Starting a new fight!\n");

}
