#ifndef __GOALRESPONSEMESSAGE_H__
#define __GOALRESPONSEMESSAGE_H__

#include <Message.h>

class GoalResponseMessage : public Message
{
public:
	int team;
	int bluewins;
	int redwins;
	int unk4;
	int unk5;

    GoalResponseMessage(int team, int bluewins, int redwins);
};

#endif // __GOALRESPONSEMESSAGE_H__
