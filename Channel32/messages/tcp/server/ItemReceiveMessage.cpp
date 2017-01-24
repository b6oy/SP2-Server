#include "ItemReceiveMessage.h"
#include <MessageTypes.h>
#include <cstring>

ItemReceiveMessage::ItemReceiveMessage(char sender[15], int level, int slot)
    : Message(sizeof(ItemReceiveMessage), MESSAGE_TYPE_ITEM_RECEIVE), level(level), lvl(level), slot(slot)
{

	strcpy(this->sender,sender);
	for(int i = 0; i < 30; i++)
		zeros[i] = 0;
}