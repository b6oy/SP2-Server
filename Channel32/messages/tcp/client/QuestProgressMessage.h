#ifndef __QUESTPROGRESSMESSAGE_H__
#define __QUESTPROGRESSMESSAGE_H__

#include <Message.h>

class QuestProgressMessage : public Message
{
public:
    int unk2; //1
    int progress; //0~100

    bool IsValid() const;
};

#endif // __QUESTPROGRESSMESSAGE_H__
