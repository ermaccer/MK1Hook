#include "MKObject.h"

void MKObject::GetPos(FVector* dest)
{
	int64 obj = *(int64*)((int64)this + 312);
	*dest = *(FVector*)(obj + 292);
}