#include "ChatMessageArrivalMessage.h"
#include <MessageTypes.h>
#include <cstring>

ChatMessageArrivalMessage::ChatMessageArrivalMessage(int chatType, char* senderId, char* recieverId, char* msg)
    : Message(sizeof(ChatMessageArrivalMessage), MESSAGE_TYPE_CHAT_MESSAGE_ARRIVAL),
      chatType(chatType)
{
    strcpy(this->senderId, senderId);
    strcpy(this->recieverId, recieverId);
    strcpy(this->msg, msg);
}
