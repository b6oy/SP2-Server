#include "FindUserResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

FindUserResponseMessage::FindUserResponseMessage(char *username, int room)
    : Message(sizeof(FindUserResponseMessage), MESSAGE_TYPE_FIND_USER_RESPONSE), room(room)
{
	strcpy(this->username,username);
	for(int i = 0; i < 7; i++)zeros[i] = 0;
	unk2 = unk3 = -1;
}