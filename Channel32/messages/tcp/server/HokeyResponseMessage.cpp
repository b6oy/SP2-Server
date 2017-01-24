#include "HokeyResponseMessage.h"
#include <MessageTypes.h>

HokeyResponseMessage::HokeyResponseMessage(int round, int bluewins, int redwins)
    : Message(sizeof(HokeyResponseMessage), MESSAGE_TYPE_HOKEY_GOAL_RESPONSE), round(round), bluewins(bluewins), redwins(redwins)
{
	zero = 0;
}