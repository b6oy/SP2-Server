#include "MissionPassageCrossResponseMessage.h"
#include <MessageTypes.h>

MissionPassageCrossResponseMessage::MissionPassageCrossResponseMessage(int timestamp, int time)
    : Message(sizeof(MissionPassageCrossResponseMessage), MESSAGE_TYPE_START_COUNT_DOWN_RESPONSE), timestamp(timestamp),time(time)
{
	zero1 = 0;
	zero2 = 0;
}