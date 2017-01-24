#include "AddFriendResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

AddFriendResponseMessage::AddFriendResponseMessage(char* username,int unk2)
    : Message(sizeof(AddFriendResponseMessage), MESSAGE_TYPE_ADD_FRIEND_RESPONSE), unk2(unk2)
{
	strcpy(this->username,username);
}