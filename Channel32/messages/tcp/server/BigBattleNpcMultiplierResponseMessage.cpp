#include "BigBattleNpcMultiplierResponseMessage.h"
#include <MessageTypes.h>

BigBattleNpcMultiplierResponseMessage::BigBattleNpcMultiplierResponseMessage(char x[36])
    : Message(sizeof(BigBattleNpcMultiplierResponseMessage), MESSAGE_TYPE_BIGBATTLE_NPC_X_RESPONSE)
{
	for(int i = 0; i < 36; i++)
		this->x[i] = x[i];
}