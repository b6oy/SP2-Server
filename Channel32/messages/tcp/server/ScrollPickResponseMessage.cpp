#include "ScrollPickResponseMessage.h"
#include <MessageTypes.h>

ScrollPickResponseMessage::ScrollPickResponseMessage(int scroll, int slot)
    : Message(sizeof(ScrollPickResponseMessage), MESSAGE_TYPE_PICK_SCROLL_RESPONSE), scroll(scroll), slot(slot)
{
	zero = 0;
}