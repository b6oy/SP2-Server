#ifndef __FRIENDLISTRESPONSEMESSAGE_H__
#define __FRIENDLISTRESPONSEMESSAGE_H__

#include <Message.h>

class FriendListResponseMessage : public Message
{
public:
	char names[24][13];
	int online[24]; //-1
	int unks[24]; //-1

    FriendListResponseMessage(char names[24][13], int online[24], int unks[24]);
};

#endif // __FRIENDLISTRESPONSEMESSAGE_H__
