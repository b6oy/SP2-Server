#include "KssnVerificationRequestMessage.h"

bool KssnVerificationRequestMessage::IsValid() const
{
    return
        this->size == sizeof(KssnVerificationRequestMessage);
}
