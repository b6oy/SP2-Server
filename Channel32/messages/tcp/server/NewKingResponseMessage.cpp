#include "NewKingResponseMessage.h"
#include <MessageTypes.h>

NewKingResponseMessage::NewKingResponseMessage(int slot)
    : Message(sizeof(NewKingResponseMessage), MESSAGE_TYPE_NEW_KING_RESPONSE), slot(slot)
{
}