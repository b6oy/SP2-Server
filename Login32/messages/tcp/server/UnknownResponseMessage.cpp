#include <cstring>

#include "UnknownResponseMessage.h"
#include <MessageTypes.h>

UnknownResponseMessage::UnknownResponseMessage()
	: Message(sizeof(UnknownResponseMessage), MESSAGE_TYPE_UNKNOWN10520_RESPONSE)
{
	zero = 0;
	one1 = 1;
	one2 = 1;
	two = 2;
}
