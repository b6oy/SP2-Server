#include "MissionAfterResponseMessage.h"
#include <MessageTypes.h>

MissionAfterResponseMessage::MissionAfterResponseMessage(int unk2, int unk3)
    : Message(sizeof(MissionAfterResponseMessage), MESSAGE_TYPE_MISSION_AFTER_RESPONSE), unk2(unk2),unk3(unk3)
{
}