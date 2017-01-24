#ifndef __ADDFRIENDRESPONSEMESSAGE_H__
#define __ADDFRIENDRESPONSEMESSAGE_H__

#include <Message.h>

class AddFriendResponseMessage : public Message
{
public:
	char username[16];
	int unk2; //1 = Add, 2 = Delete

    AddFriendResponseMessage(char* username, int unk2);
};

#endif // __ADDFRIENDRESPONSEMESSAGE_H__
