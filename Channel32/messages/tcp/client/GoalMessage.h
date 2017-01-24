#ifndef __GOALMESSAGE_H__
#define __GOALMESSAGE_H__

#include <Message.h>

class GoalMessage : public Message
{
public:
	int goal;
	int unk2;
	int unk3;
	int unk4;
	int unk5;

    bool IsValid() const;
};

#endif // __GOALMESSAGE_H__
