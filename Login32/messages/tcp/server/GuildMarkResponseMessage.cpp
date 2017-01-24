#include <cstring>
#include "GuildMarkResponseMessage.h"
#include <MessageTypes.h>

GuildMarkResponseMessage::GuildMarkResponseMessage(const char guildname[16])
	: Message(sizeof(GuildMarkResponseMessage), MESSAGE_TYPE_GUILD_MARK_RESPONSE)
{
	for(int i = 0; i < 16; i++)
		this->guildname[i] = guildname[i];
	for(int i = 0; i < 79; i++)
		zeros[i] = 0;
}
