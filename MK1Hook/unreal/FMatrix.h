#pragma once
#include "FRotator.h"
#include "FVector.h"
#include "..\utils.h"

class FMatrix {
public:
	float M[4][4] = {};

	FMatrix();
	FMatrix(FRotator*);

	void MakeFromX(FVector* XAxis);
	void Rotator(FVector* result);

	FVector GetRight();
	FVector GetForward();
	FVector GetUp();
	FVector GetPos();
};

FVector FindLookAtRotation(FVector* start, FVector* target);