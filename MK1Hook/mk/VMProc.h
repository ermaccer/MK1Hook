#pragma once
#include "..\unreal\TArray.h"
class VMProc {
public:
	char pad[0x68];
	TArray<void*> args;

	void PushArg();

	unsigned int GetCurrentFunction();
};