#include "GiftVerifyIDMessage.h"
#include <MessageTypes.h>

GiftVerifyIDMessage::GiftVerifyIDMessage(int id)
    : Message(sizeof(GiftVerifyIDMessage), MESSAGE_TYPE_GIFT_VERIFY_ID_RESPONSE), id(id)
{
}