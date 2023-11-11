#include "Scaleform.h"

Scaleform* GetScaleform()
{
	static uintptr_t pat = _pattern(PATID_GetScaleform);
	if (pat)
		return ((Scaleform*(__fastcall*)())pat)();
	
	return nullptr;
}
