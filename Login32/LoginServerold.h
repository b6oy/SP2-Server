#ifndef __LOGINSERVER_H__
#define __LOGINSERVER_H__

#define BUFFER_SIZE     1000

#include "main.h"
#include "PacketHandler.h"

class cLoginServer
{
public:
    cLoginServer();
    ~cLoginServer();
    bool Start();
    bool CommLoop();
    void outBuffer();

private:
	//unsigned char buffer[BUFFER_SIZE];
	WSADATA wsaData;
	struct sockaddr_in server, client;
	int serverlen, clientlen;
	SOCKET listen_socket, msg_socket;
};


#endif
