#include "ElementSpawnMessage.h"
#include <MessageTypes.h>
#include <cstring>
#include <cstdlib>

ElementSpawnMessage::ElementSpawnMessage()
    : Message(sizeof(ElementSpawnMessage), MESSAGE_TYPE_ELEMENT_SPAWN)
{
	unk01 = 0x0839E404;
	ele_type = 3;
	x = 537;
	y = 595;
	angle = rand()%360;
}