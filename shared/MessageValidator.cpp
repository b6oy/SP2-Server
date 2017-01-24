#include <iostream>
#include <fstream>
#include <exception>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

#include "MessageValidator.h"

using namespace std;

MessageValidationException::MessageValidationException(const Message* message)
{
	this->Init(message, "Invalid message.");
}

MessageValidationException::MessageValidationException(const Message* message, const char* description)
{
	this->Init(message, description);
}

void MessageValidationException::Init(const Message* message, const char* description)
{
	this->message = message;
	this->description = description;
}

const char* MessageValidationException::what() const
{
	return this->description;
}

const Message* MessageValidationException::GetMessage() const
{
	return this->message;
}

MessageValidator MessageValidator::instance;

MessageValidator::MessageValidator()
{
	ifstream iosocketdllFile("iosocketdll.bin", ios::in | ios::binary | ios::ate);

    if (iosocketdllFile.is_open()) {
        ifstream::pos_type size = iosocketdllFile.tellg();
        iosocketdll = new char[(unsigned int)size];
        iosocketdllFile.seekg(0, ios::beg);
        iosocketdllFile.read(iosocketdll, size);
        iosocketdllFile.close();

        ComputeChecksum = (MakeDigestPtr)(iosocketdll + 0x13C0);

    #ifdef _WIN32
        DWORD oldProtection;
	    if (VirtualProtect(iosocketdll, 15079, PAGE_EXECUTE_READWRITE, &oldProtection) == 0)
		    throw exception("Could not change memory access protection.");
    #else
        if (mprotect(iosocketdll, 15079, PROT_EXEC | PROT_READ | PROT_WRITE) != 0)
            throw exception("Could not change memory access protection.");
    #endif
    }
    else
    {
        throw exception("Could not open iosocketdll.bin.");
    }
}
 
const MessageValidator& MessageValidator::GetInstance()
{
    return instance;
}

void MessageValidator::EncryptMessage(Message* message) const
{
	this->SetChecksum(message);

	for (int i = 4; i < message->size; i++)
	{
		unsigned char b = reinterpret_cast<unsigned char*>(message)[i];
		b = b ^ 0x74;
		b = b - (i - 4);
		reinterpret_cast<unsigned char*>(message)[i] = ~((b << 3) | (b >> 5));
	}
}

void MessageValidator::DecryptMessage(Message* message) const
{
	if (!HasValidSize(message))
		throw MessageValidationException(message, "The size of the message is invalid.");

	for (int i = 4; i < message->size; i++)
	{
		unsigned char b = reinterpret_cast<unsigned char*>(message)[i];
		b = b ^ 0x3C;
		b = b - (i - 4);
		//b = b - 2;
		reinterpret_cast<unsigned char*>(message)[i] = ~((b >> 3) | (b << 5));
	}

	if (!HasValidChecksum(message))
		throw MessageValidationException(message, "The checksum of the message is invalid.");
}

void MessageValidator::SetChecksum(Message* message) const
{
	message->checksum = 0;
	message->checksum = ComputeChecksum(message);
}

bool MessageValidator::HasValidChecksum(Message* message) const
{
	int checksum = message->checksum;
	message->checksum = 0;
	bool result = (checksum == ComputeChecksum(message));
	message->checksum = checksum;
	return result;
}

bool MessageValidator::IsValidMessageSize(int size) const
{
	return 
		size >= sizeof(Message) &&
		size <= MAX_BUFFER_SIZE &&
		size % 4 == 0 &&
		size > 0;
}

bool MessageValidator::HasValidSize(const Message* message) const
{
	return IsValidMessageSize(message->size);
}
