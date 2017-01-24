#include "GoalResponseMessage.h"
#include <MessageTypes.h>
#include <time.h>
GoalResponseMessage::GoalResponseMessage(int team, int bluewins, int redwins)
    : Message(sizeof(GoalResponseMessage), MESSAGE_TYPE_SOCCER_GOAL_RESPONSE), team(team), bluewins(bluewins), redwins(redwins)
{
	unk4 = time(0);
	unk5 = clock();
}