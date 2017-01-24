#ifndef __SERVERINFOREQUESTMESSAGE_H__
#define __SERVERINFOREQUESTMESSAGE_H__

#include <Message.h>

class ServerInfoRequestMessage : public Message
{
public:
	int unknown1; // always 0xFAF
    int channel;
	
	bool IsValid() const;

};

#endif // __SERVERINFOREQUESTMESSAGE_H__
