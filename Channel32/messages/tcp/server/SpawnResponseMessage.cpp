#include "SpawnResponseMessage.h"
#include <MessageTypes.h>

SpawnResponseMessage::SpawnResponseMessage(int *slots, int slot)
    : Message(sizeof(SpawnResponseMessage), MESSAGE_TYPE_SPAWN_RESPONSE), slot(slot)
{
	for(int i = 0; i < 8; i ++)
		this->slots[i] = slots[i];
}