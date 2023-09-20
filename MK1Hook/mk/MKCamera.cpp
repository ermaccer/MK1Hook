#include "MKCamera.h"
#include "../plugin/Menu.h"
#include <iostream>
#include <Windows.h>
#include "MKCharacter.h"

MKCamera* TheCamera;

void MKCamera::FillCameraCache(FMinimalViewInfo* NewInfo)
{
	TheCamera = this;
	static uintptr_t pat = _pattern(PATID_MKCamera_FillCameraCache);
	if (pat)
		((void(__thiscall*)(MKCamera*, FMinimalViewInfo*))pat)(this, NewInfo);
}

void MKCamera::HookedFillCameraCache(FMinimalViewInfo* NewInfo)
{
	FillCameraCache(NewInfo);

	if (!TheMenu->m_bCustomCameraFOV && !TheMenu->m_bFreeCam)
		TheMenu->camFov = CameraCache.POV.FOV;
	else
		CameraCache.POV.FOV = TheMenu->camFov;

	if (!TheMenu->m_bCustomCameraPos && !TheMenu->m_bFreeCam)
		TheMenu->camPos = CameraCache.POV.Location;
	else
		CameraCache.POV.Location = TheMenu->camPos;
	
	if (!TheMenu->m_bCustomCameraRot && !TheMenu->m_bFreeCam)
		TheMenu->camRot = CameraCache.POV.Rotation;
	else
		CameraCache.POV.Rotation = TheMenu->camRot;
}

FMatrix MKCamera::GetMatrix()
{
	FRotator rot;
	float Pitch = CameraCache.POV.Rotation.X;
	float Yaw = CameraCache.POV.Rotation.Y;
	float Roll = CameraCache.POV.Rotation.Z;

	rot.Pitch = (int)(float)((float)(Pitch * 32767.0) / 180.0);
	rot.Yaw = (int)(float)((float)(Yaw * 32767.0) / 180.0);
	rot.Roll = (int)(float)((float)(Roll * 32767.0) / 180.0);

	FMatrix mat(&rot);
	return mat;
}
