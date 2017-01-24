#ifndef __GUILDMARKSPONSEMESSAGE_H__
#define __GUILDMARKSPONSEMESSAGE_H__

#include <ServerEnum.h>
#include <Message.h>

class GuildMarkResponseMessage : public Message
{
public:
	char guildname[16];
	int zeros[79];
	GuildMarkResponseMessage(const char guildname[16]);
};

#endif // __GUILDMARKSPONSEMESSAGE_H__
