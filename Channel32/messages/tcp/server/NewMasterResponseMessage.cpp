#include "NewMasterResponseMessage.h"
#include <MessageTypes.h>

NewMasterResponseMessage::NewMasterResponseMessage(int Slot)
    : Message(sizeof(NewMasterResponseMessage), MESSAGE_TYPE_NEW_MASTER_RESPONSE), Slot(Slot)
{
	unk2 = 1;
}