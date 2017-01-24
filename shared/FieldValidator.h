#ifndef __FIELDVALIDATOR_H__
#define __FIELDVALIDATOR_H__

class FieldValidator
{
public:
	static const int USER_ID_MIN_LENGTH = 4;
    static const int USER_ID_MAX_LENGTH = 12;
    static const int PASSWORD_MIN_LENGTH = 4;
    static const int PASSWORD_MAX_LENGTH = 12;
    static const int PASSWORD_HASH_MIN_LENGTH = 8;
    static const int PASSWORD_HASH_MAX_LENGTH = 24;

	static const FieldValidator& GetInstance();
    bool IsValidUserId(const char* userId) const;
    bool IsValidPassword(const char* password) const;
    bool IsValidPasswordHash(const char* passwordHash) const;
    bool IsValidProcessId(int processId) const;

private:
    static FieldValidator instance;
    FieldValidator() { };
    FieldValidator(const FieldValidator&); // intentionally undefined
    FieldValidator& operator=(const FieldValidator&); // intentionally undefined
};

#endif // __FIELDVALIDATOR_H__
