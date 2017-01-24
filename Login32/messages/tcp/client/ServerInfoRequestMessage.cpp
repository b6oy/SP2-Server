#include <FieldValidator.h>
#include "ServerInfoRequestMessage.h"

bool ServerInfoRequestMessage::IsValid() const
{
    return
        this->size == sizeof(ServerInfoRequestMessage);
}