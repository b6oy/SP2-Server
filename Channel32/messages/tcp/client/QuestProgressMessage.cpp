#include "QuestProgressMessage.h"

bool QuestProgressMessage::IsValid() const
{
    return
        this->size == sizeof(QuestProgressMessage);
}
