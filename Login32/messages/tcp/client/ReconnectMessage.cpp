#include <MessageTypes.h>
#include <FieldValidator.h>
#include "ReconnectMessage.h"

bool ReconnectMessage::IsValid() const
{
    return
        this->size == sizeof(ReconnectMessage) &&
        FieldValidator::GetInstance().IsValidUserId(this->userId);
}