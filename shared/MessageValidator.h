#ifndef __MESSAGEVALIDATOR_H__
#define __MESSAGEVALIDATOR_H__

#include <stdexcept>

#include "Message.h"

typedef int (__thiscall * MakeDigestPtr)(Message*);

class MessageValidationException : public std::exception
{
public:
	MessageValidationException(const Message* message);
	MessageValidationException(const Message* message, const char* description);
	virtual const char* what() const throw();
	const Message* GetMessage() const;

private:
	const char* description;
	const Message* message;
	void Init(const Message* message, const char* description);
};

class MessageValidator
{
public:
	static const int MAX_BUFFER_SIZE = 8192;
    static const MessageValidator& GetInstance();

    void EncryptMessage(Message* message) const;

    void DecryptMessage(Message* message) const;

	bool IsValidMessageSize(int size) const;

private:
    char* iosocketdll;
    static MessageValidator instance;

    MessageValidator();
    MessageValidator(const MessageValidator&); // intentionally undefined
    MessageValidator& operator=(const MessageValidator&); // intentionally undefined

	void SetChecksum(Message* message) const;
	bool HasValidChecksum(Message* message) const;
	bool HasValidSize(const Message* message) const;
	MakeDigestPtr ComputeChecksum;
};

#endif // __MESSAGEVALIDATOR_H__
