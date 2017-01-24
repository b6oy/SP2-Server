#include "Message.h"

Message::Message(int size, int type)
	: size(size), type(type), thirdField(THIRD_FIELD), checksum(0), state(-1)
{
}

