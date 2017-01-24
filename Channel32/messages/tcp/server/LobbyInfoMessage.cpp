#include "LobbyInfoMessage.h"
#include <MessageTypes.h>
#include <cstring>

LobbyInfoMessage::LobbyInfoMessage(char* username, int level, bool gender, int missionlevel, bool b)
    : Message(sizeof(LobbyInfoMessage), MESSAGE_TYPE_LOBBY_USERINFO_RESPONSE),
      level(level), gender(gender), missionlevel(missionlevel)
{
    strcpy(this->username, username);
	unk01 = 0;
    unk02 = 0;
    b2 = b;
    b3 = 0;
    b4 = 0;
    b5 = b;
    b6 = b;
    b7 = 0;
    b8 = 0;
}
