#include "SendGiftResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

SendGiftResponseMessage::SendGiftResponseMessage(int sent, char username[16], int gift_type, int slot)
    : Message(sizeof(SendGiftResponseMessage), MESSAGE_TYPE_SEND_GIFT_RESPONSE), sent(sent), gift_type(gift_type), slot(slot)
{
	strcpy(this->username,username);
	unk2 = 0xFFFF764C;
	unk = 0;
}