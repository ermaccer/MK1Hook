#pragma once
#include "../utils.h"
#include "../unreal/FMatrix.h"
#include "Engine.h"


struct FMinimalViewInfo
{
	FVector Location;
	FVector Rotation;
	float FOV;

	float DesiredFOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float AspectRatio;
	unsigned __int32 bConstrainAspectRatio : 1;
	unsigned __int32 bUseFieldOfViewForLOD : 1;
};


struct FCameraCacheEntry {
	float TimeStamp;
	char pad[12];
	FMinimalViewInfo POV;
};



class MKCamera {
public:
	char pad[0x248];
	int64 PCOwner;
	int64 TransformComponent;
	int		 CameraStyle[2];
	float    DefaultFOV;
	float    LockedFOV;
	char     _pad[6328];
	FCameraCacheEntry CameraCache;
	void FillCameraCache(FMinimalViewInfo* NewInfo);
	void HookedFillCameraCache(FMinimalViewInfo* NewInfo);

	FMatrix GetMatrix();
};
VALIDATE_OFFSET(MKCamera, PCOwner, 0x248);
VALIDATE_OFFSET(MKCamera, CameraCache, 0x1B20);

extern MKCamera* TheCamera;