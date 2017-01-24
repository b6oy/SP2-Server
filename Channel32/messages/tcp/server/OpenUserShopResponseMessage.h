#ifndef __OPENUSERSHOPRESPONSEMESSAGE_H__
#define __OPENUSERSHOPRESPONSEMESSAGE_H__

#include <Message.h>

class OpenUserShopResponseMessage : public Message
{
public:
	char username[13];
	char shopname[15];
	int one; //1
	int zero;
	int zero1;
	int zero2;
    OpenUserShopResponseMessage(char username[13], char shopname[15]);
};

#endif // __OPENUSERSHOPRESPONSEMESSAGE_H__
