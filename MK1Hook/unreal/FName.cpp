#include "FName.h"

FName::FName()
{
	Index = -1;
	Number = 0;
}

FName::FName(const char * Name, EFindName FindType, int formal)
{

}

TArray<FNameEntry*>* GetNames()
{
	return nullptr;
}

char* GetName(int index)
{
	if (GetNames())
	{
		if (GetNames()->Data[index])
			return GetNames()->Data[index]->name;
	}
		return "n/a";
}