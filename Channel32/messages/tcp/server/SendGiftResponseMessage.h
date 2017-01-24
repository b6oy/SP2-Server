#ifndef __SENDGIFTMESSAGE_H__
#define __SENDGIFTMESSAGE_H__

#include <Message.h>

class SendGiftResponseMessage : public Message
{
public:
	int sent; //1
	char username[16];
	int gift_type;
	int unk2; //0xFFFF764C
	int slot;
	int unk;

    SendGiftResponseMessage(int sent, char username[16], int gift_type, int slot);
};

#endif // __SENDGIFTMESSAGE_H__
