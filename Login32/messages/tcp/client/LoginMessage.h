#ifndef __LOGINMESSAGE_H__
#define __LOGINMESSAGE_H__

#include <Message.h>

using namespace std;

class LoginMessage : public Message
{
public:
	char versionHash[36]; // Version fields may have different values every time, and are used to check if the client has the latest version. Note that this hash includes random uninitialized garbage from the stack.
	int versionCode1;
	char userId[13];
	char password[15];
	int versionCode2;
	short screenResWidth; // Used to check if the client is running SP in a window.
	short screenResHeight;
	short windowWidth; // TODO: confirm if this is, in fact, the correct order (screen first, then window), because I don't remember.
	short windowHeight;
	char passwordHash[28]; // TODO: find out when this field is empty and when it isn't.
	int unknown1; // TODO: Seems to be always 0.
	int processId; // KSP doesn't seem to do anything with this, but it can be useful.
	
	bool IsValid() const;

};

#endif // __LOGIN_PACKET_H__
