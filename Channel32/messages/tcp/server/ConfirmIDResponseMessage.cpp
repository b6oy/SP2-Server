#include "ConfirmIDResponseMessage.h"
#include <MessageTypes.h>

ConfirmIDResponseMessage::ConfirmIDResponseMessage(int response)
    : Message(sizeof(ConfirmIDResponseMessage), MESSAGE_TYPE_CONFIRM_ID_RESPONSE), response(response)
{
}