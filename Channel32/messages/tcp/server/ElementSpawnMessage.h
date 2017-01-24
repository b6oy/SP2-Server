#ifndef __ELEMENTSPAWNMESSAGE_H__
#define __ELEMENTSPAWNMESSAGE_H__

#include <Message.h>

class ElementSpawnMessage : public Message
{
public:
	int unk01; //0x0839E404
	int ele_type; //3
	int x; //237
	int y; //795
	int angle; //190

    ElementSpawnMessage();
};

#endif // __ELEMENTSPAWNMESSAGE_H__
