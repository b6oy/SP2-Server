#ifndef __CONFIRMIDRESPONSEMESSAGE_H__
#define __CONFIRMIDRESPONSEMESSAGE_H__

#include <Message.h>

class ConfirmIDResponseMessage : public Message
{
public:
	int response; //1 = OK, 0 = Not found

    ConfirmIDResponseMessage(int response);
};

#endif // __CONFIRMIDRESPONSEMESSAGE_H__
