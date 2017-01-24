#ifndef __ROOMTITLECHANGEMESSAGE_H__
#define __ROOMTITLECHANGEMESSAGE_H__

#include <Message.h>

class RoomTitleChangeMessage : public Message
{
public:
    int room;
    char title[32];

    bool IsValid() const;
};

#endif // __ROOMTITLECHANGEMESSAGE_H__
