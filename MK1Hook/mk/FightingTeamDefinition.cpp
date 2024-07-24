#include "FightingTeamDefinition.h"

int64 FightingTeamDefinition::GetPrimaryAddress()
{
    return (int64)((int64)this + 0x98);
}

int64 FightingTeamDefinition::GetPartnerAddress()
{
    return (int64)((int64)this + 0x2E8);
}
