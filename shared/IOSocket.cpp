#include "IOSocket.h"
#include "console.h"

IOSocket::IOSocket()
{
    hModule = LoadLibraryA("iosocketdll.dll");
	if(!hModule)
	{
		MakeMeFocused("Failed to load iosocketdll.dll. Make sure you included iosocketdll.dll and logdll.dll.", 0);
		return;
	}

    MakeDigest = (fCall)GetProcAddress(hModule,"?MakeDigest@CGenericMessage@@IAEKXZ");
}

IOSocket::~IOSocket()
{
    FreeLibrary(hModule);
}
