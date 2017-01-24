#include "FriendListResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

FriendListResponseMessage::FriendListResponseMessage(char names[24][13], int online[24], int unks[24])
    : Message(sizeof(FriendListResponseMessage), MESSAGE_TYPE_FRIEND_LIST_RESPONSE)
{
	for(int i = 0; i < 24; i++){
		for(int j = 0; j < 13; j++)
			this->names[i][j] = names[i][j];
		this->online[i] = online[i];
		this->unks[i] = unks[i];
	}
}