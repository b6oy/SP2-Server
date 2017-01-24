#include "GiftReceiveMessage.h"
#include <MessageTypes.h>

GiftReceiveMessage::GiftReceiveMessage(int slot, int type, int gf, int level, int skill)
    : Message(sizeof(GiftReceiveMessage), MESSAGE_TYPE_GIFT_RECEIVE), slot(slot), type(type), gf(gf), level(level), skill(skill)
{
}