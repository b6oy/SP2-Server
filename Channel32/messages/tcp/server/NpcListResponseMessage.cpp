#include "NpcListResponseMessage.h"
#include <MessageTypes.h>

NpcListResponseMessage::NpcListResponseMessage(short *NpcLevels)
    : Message(sizeof(NpcListResponseMessage), MESSAGE_TYPE_NPC_LIST_RESPONSE)
{
	for(int i = 0; i < 33; i++)
			levels[i] = NpcLevels[i];
	levels[34] = levels[35] = 0;
}
