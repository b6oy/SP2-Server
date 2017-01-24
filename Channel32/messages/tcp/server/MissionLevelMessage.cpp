#include "MissionLevelMessage.h"
#include <MessageTypes.h>

MissionLevelMessage::MissionLevelMessage(int MissionLevel)
    : Message(sizeof(MissionLevelMessage), MESSAGE_TYPE_MISSION_LEVEL),
      MissionLevel(MissionLevel)
{
	unk2 = 0;
}
