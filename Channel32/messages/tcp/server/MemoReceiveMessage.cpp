#include "MemoReceiveMessage.h"
#include <MessageTypes.h>
#include <cstring>

MemoReceiveMessage::MemoReceiveMessage(char username[16], int unk3, char msg[120])
    : Message(sizeof(MemoReceiveMessage), MESSAGE_TYPE_RCV_MEMO_RESPONSE), unk3(unk3)
{
	unk2 = 5;
	zero = 0;
	time = 0;
	unk4 = 0;
	strcpy(this->username,username);
	for(int i = 0; i < 120; i++)
		this->msg[i] = msg[i];
}