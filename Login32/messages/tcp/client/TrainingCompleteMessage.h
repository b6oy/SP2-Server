#ifndef __TRAININGCOMPLETEMESSAGE_H__
#define __TRAININGCOMPLETEMESSAGE_H__

#include <Message.h>

class TrainingCompleteMessage : public Message
{
public:
	bool IsValid() const;
};

#endif // __TRAININGCOMPLETEMESSAGE_H__
