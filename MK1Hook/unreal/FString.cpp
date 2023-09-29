#include "FString.h"

wchar_t* FString::GetStr()
{
    return (wchar_t*)(&Data[0]);
}
