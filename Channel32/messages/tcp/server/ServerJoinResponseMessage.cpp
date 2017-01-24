#include "ServerJoinResponseMessage.h"
#include <MessageTypes.h>

ServerJoinResponseMessage::ServerJoinResponseMessage()
    : Message(sizeof(ServerJoinResponseMessage), MESSAGE_TYPE_SERVER_JOIN_RESPONSE)
{
		unk2 = 0; //0x2CF
		unk3 = 0; //0x2CA
		unk4 = 0; //0
		unk5 = 0; //1
		unk6 = 0;
		unk7 = 0;
		unk8 = 0;
		unk9 = 0; //0x6D15D3
		unk10 = 0; //0
		unk11 = 0; //0
		unk12 = 0; //0x78020F00
}
