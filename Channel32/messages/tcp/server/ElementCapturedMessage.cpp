#include "ElementCapturedMessage.h"
#include <MessageTypes.h>
#include <cstring>

ElementCapturedMessage::ElementCapturedMessage(int slot, int eleType, int eleBase, int eleMul)
    : Message(sizeof(ElementCapturedMessage), MESSAGE_TYPE_ELEMENT_CAPTURED_RESPONSE), slot(slot), eleType(eleType), eleBase(eleBase), eleMul(eleMul)
{
	unk2 = 4;
}