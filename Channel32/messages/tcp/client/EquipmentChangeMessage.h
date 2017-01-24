#ifndef __EQUIPMENTCHANGEMESSAGE_H__
#define __EQUIPMENTCHANGEMESSAGE_H__

#include <Message.h>

class EquipmentChangeMessage : public Message
{
public:
    int mag;
    int wpn;
    int arm;
    int pet;
    int foot;
    int body;
    int hand1;
    int hand2;
    int face;
    int hair;
    int head;

    bool IsValid() const;
};

#endif // __EQUIPMENTCHANGEMESSAGE_H__
