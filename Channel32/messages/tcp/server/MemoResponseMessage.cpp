#include "MemoResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

MemoResponseMessage::MemoResponseMessage(int unk2, char username[16])
    : Message(sizeof(MemoResponseMessage), MESSAGE_TYPE_SEND_MEMO_RESPONSE), unk2(unk2)
{
	strcpy(this->username,username);
}