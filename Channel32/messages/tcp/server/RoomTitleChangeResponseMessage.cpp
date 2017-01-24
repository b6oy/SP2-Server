#include "RoomTitleChangeResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomTitleChangeResponseMessage::RoomTitleChangeResponseMessage(char *title)
    : Message(sizeof(RoomTitleChangeResponseMessage), MESSAGE_TYPE_CHANGE_ROOMTITLE_RESPONSE)
{
	strcpy(this->title, title);
}
