#include "MKObject.h"

void MKObject::SetPos(FVector* pos)
{

}

void MKObject::GetPos(FVector* dest)
{
	int64 obj = *(int64*)((int64)this + 312);
	*dest = *(FVector*)(obj + 284);
};
