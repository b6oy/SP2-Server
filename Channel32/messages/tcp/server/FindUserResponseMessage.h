#ifndef __FINDUSERRESPONSEMESSAGE_H__
#define __FINDUSERRESPONSEMESSAGE_H__

#include <Message.h>

class FindUserResponseMessage : public Message
{
public:
	char username[16];
	int zeros[7];
	int room;
	int unk2; //-1
	int unk3; //-1

    FindUserResponseMessage(char *username, int room);
};

#endif // __FINDUSERRESPONSEMESSAGE_H__
