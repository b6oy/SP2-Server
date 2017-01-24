#ifndef __GUILDMARKMESSAGE_H__
#define __GUILDMARKMESSAGE_H__

#include <Message.h>

using namespace std;

class GuildMarkMessage : public Message
{
public:
	char guildname[16];
	int unk; //-1
	bool IsValid() const;

};

#endif // __GUILDMARKMESSAGE_H__
