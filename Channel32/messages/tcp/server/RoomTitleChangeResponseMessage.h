#ifndef __ROOMTITLECHANGERESPONSEMESSAGE_H__
#define __ROOMTITLECHANGERESPONSEMESSAGE_H__

#include <Message.h>

class RoomTitleChangeResponseMessage : public Message
{
public:
    char title[32];

    RoomTitleChangeResponseMessage(char *title);
};

#endif // __ROOMTITLECHANGERESPONSEMESSAGE_H__
