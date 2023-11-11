#pragma once
#include "..\utils.h"

class Scaleform {
public:
	char pad[64];
	bool m_bActive;
};


Scaleform* GetScaleform();