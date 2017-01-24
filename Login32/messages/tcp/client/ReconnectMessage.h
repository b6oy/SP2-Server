#ifndef __RECONNECTMESSAGE_H__
#define __RECONNECTMESSAGE_H__

#include <Message.h>

using namespace std;

class ReconnectMessage : public Message
{
public:
	char userId[13];
	short zero;
	int unk01;
    int unk02;
	int unk03;
	bool IsValid() const;

};

#endif // __RECONNECTMESSAGE_H__
