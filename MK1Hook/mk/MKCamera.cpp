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

	if (TheMenu->m_bCustomCameras)
	{
		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING)
		{
			if (GetObjActor(PLAYER1) && GetObjActor(PLAYER2))
			{
				FVector p1;
				FVector p2;
				FVector headPos;
				FVector headRot;
				FVector headRight;
				FVector headForward;


				// characters are stuck in one place in fatalities
				GetObjActor(TheMenu->m_bUsePlayerTwoAsTracker ? PLAYER2 : PLAYER1)->GetSkeleton()->GetBoneLocation(L"Spine", &p1);
				GetObjActor(TheMenu->m_bUsePlayerTwoAsTracker ? PLAYER1 : PLAYER2)->GetSkeleton()->GetBoneLocation(L"Spine", &p2);

				GetObjActor(TheMenu->m_bUsePlayerTwoAsTracker ? PLAYER2 : PLAYER1)->GetSkeleton()->GetBoneLocation(L"Head", &headPos);

				FMatrix mat;
				GetObjActor(TheMenu->m_bUsePlayerTwoAsTracker ? PLAYER2 : PLAYER1)->GetSkeleton()->GetBoneMatrix(L"Head", &mat);

				// flipped for characters
				headRight = mat.GetRight();
				headForward = mat.GetUp();

				FVector finalPos = headPos;

				finalPos += headRight * TheMenu->m_fAdjustCustomHeadCameraY;
				finalPos += headForward * TheMenu->m_fAdjustCustomHeadCameraX;
				finalPos.Z += TheMenu->m_fAdjustCustomHeadCameraZ;

				CameraCache.POV.Location = finalPos;
				TheMenu->camPos = CameraCache.POV.Location;


				FVector lookDirection = finalPos;
				lookDirection += headForward * TheMenu->m_fAdjustCustomHeadCameraDistanceOffset;
				lookDirection.Z += TheMenu->m_fAdjustCustomHeadCameraDistanceHeight;


				FVector finalRot;
				finalRot = FindLookAtRotation(&finalPos, &lookDirection);

				CameraCache.POV.Rotation = finalRot;
				CameraCache.POV.FOV = TheMenu->camFov;
				TheMenu->camRot = finalRot;
			}
		}
		
	}
	else
	{

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
