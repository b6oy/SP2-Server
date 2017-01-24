#ifndef __FIELDSCROLLPICKMESSAGE_H__
#define __FIELDSCROLLPICKMESSAGE_H__

#include <Message.h>

class FieldScrollPickMessage : public Message
{
public:
    int zero;
    int scroll;
    int slot;

    bool IsValid() const;
};

#endif // __FIELDSCROLLPICKMESSAGE_H__
