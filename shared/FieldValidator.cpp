#include <cstring>

#include "FieldValidator.h"

FieldValidator FieldValidator::instance;

const FieldValidator& FieldValidator::GetInstance()
{
    return instance;
}

bool FieldValidator::IsValidUserId(const char* userId) const
{
    int len = strlen(userId);
    int i;
    if (len < USER_ID_MIN_LENGTH || len > USER_ID_MAX_LENGTH)
        return false;

    for (i = 0; i < len; i++) {
        char c = userId[i];
        if (c != '-' &&
            !((c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'z') &&
              (c >= 'A' && c <= 'Z')))
            return false;
    }
    return true;
}

bool FieldValidator::IsValidPassword(const char* password) const
{
    int len = strlen(password);
    int i;
    if (len < PASSWORD_MIN_LENGTH || len > PASSWORD_MAX_LENGTH)
        return false;

    for (i = 0; i < len; i++) {
        char c = password[i];
        if (c != '-' &&
            !((c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'z') &&
              (c >= 'A' && c <= 'Z')))
            return false;
    }
    return true;
}

bool FieldValidator::IsValidPasswordHash(const char* passwordHash) const
{
    int len = strlen(passwordHash);
    int i;
    if ((len < PASSWORD_HASH_MIN_LENGTH || len > PASSWORD_HASH_MAX_LENGTH) ||
         len % 2 != 0)
        return false;

    for (i = 0; i < len; i++) {
        char c = passwordHash[i];
        if (c != '-' &&
            !((c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'f') &&
              (c >= 'A' && c <= 'F')))
            return false;
    }
    return true;
}

bool FieldValidator::IsValidProcessId(int processId) const
{
    return processId > 0;
}
