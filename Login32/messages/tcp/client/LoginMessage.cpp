#include <MessageTypes.h>
#include <FieldValidator.h>
#include "LoginMessage.h"

bool LoginMessage::IsValid() const
{
    return
        this->size == sizeof(LoginMessage) &&
        FieldValidator::GetInstance().IsValidUserId(this->userId) &&
        FieldValidator::GetInstance().IsValidPassword(this->password) &&
        (this->passwordHash[0] == '\0' || FieldValidator::GetInstance().IsValidPasswordHash(this->passwordHash)) &&
        FieldValidator::GetInstance().IsValidProcessId(this->processId);
}