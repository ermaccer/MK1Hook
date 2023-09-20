#include "Engine.h"

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return nullptr;	
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return nullptr;
	//return GetGameInfo()->GetInfo(plr);
}


unsigned int _hash(const char* input)
{
	unsigned int result;
	int stringLength;
	int character;

	if (!input)
		return 0;
	stringLength = -1;

	do
		++stringLength;
	while (input[stringLength]);

	for (result = 0x811C9DC5; stringLength; --stringLength)
	{
		character = *(unsigned char*)input++;
		result = character ^ (unsigned int)(0x1000193 * result);
	}
	return result;
}