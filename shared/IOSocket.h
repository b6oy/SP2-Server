#ifndef __IOSOCKET_H__
#define __IOSOCKET_H__

#include "typedefs.h"
#include <Windows.h>

typedef int (__fastcall *fCall)(uint8 *);
class IOSocket
{
private:
    HMODULE hModule;

public:
    IOSocket();
    ~IOSocket();

    fCall MakeDigest;
};


#endif
