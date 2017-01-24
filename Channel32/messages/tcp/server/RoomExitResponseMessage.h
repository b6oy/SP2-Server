#ifndef __ROOMEXITRESPONSEMESSAGE_H__
#define __ROOMEXITRESPONSEMESSAGE_H__

#include <Message.h>

class RoomExitResponseMessage : public Message
{
public:
    int slot; //0
    char username[16];

    RoomExitResponseMessage(int slot, char username[16]);
};

#endif // __ROOMEXITRESPONSEMESSAGE_H__
