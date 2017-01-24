#include "ServerJoinMessage.h"

bool ServerJoinMessage::IsValid() const
{
    return
        this->size == sizeof(ServerJoinMessage);
}
