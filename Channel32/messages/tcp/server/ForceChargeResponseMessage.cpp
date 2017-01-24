#include "ForceChargeResponseMessage.h"
#include <MessageTypes.h>

ForceChargeResponseMessage::ForceChargeResponseMessage(int success, int item_slot, int item_type, int gf_slot)
    : Message(sizeof(ForceChargeResponseMessage), MESSAGE_TYPE_FORCE_CHARGE_RESPONSE), success(success), item_slot(item_slot), item_type(item_type), gf_slot(gf_slot)
{
}