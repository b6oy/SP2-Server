#include <MessageTypes.h>
#include <FieldValidator.h>
#include "GuildMarkMessage.h"

bool GuildMarkMessage::IsValid() const
{
    return
        this->size == sizeof(GuildMarkMessage);
}