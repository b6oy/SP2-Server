#include "ReviveResponseMessage.h"
#include <MessageTypes.h>

ReviveResponseMessage::ReviveResponseMessage(int Slot, int unk2, int unk3)
    : Message(sizeof(ReviveResponseMessage), MESSAGE_TYPE_REVIVE_RESPONSE), Slot(Slot),unk2(unk2),unk3(unk3)
{
}