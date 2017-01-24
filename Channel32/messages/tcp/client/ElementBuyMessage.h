#ifndef __ELEMENTBUYMESSAGE_H__
#define __ELEMENTBUYMESSAGE_H__

#include <Message.h>

class ElementBuyMessage : public Message
{
public:
    int item_id;
	int amount;

    bool IsValid() const;
};

#endif // __ELEMENTBUYMESSAGE_H__
