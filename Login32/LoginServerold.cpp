#if 0

#include "LoginServer.h"
#include "console.h"
#include "ini.h"

extern CIni config;

cLoginServer::cLoginServer()
{
    //for (int i = 0; i < BUFFER_SIZE; i++)
      //  buffer[i] = 0;

    serverlen = sizeof(server);
    clientlen = sizeof(client);
}

cLoginServer::~cLoginServer()
{
    WSACleanup();
}

bool cLoginServer::Start()
{
    if (WSAStartup(514, &wsaData))
    {
        MakeMeFocused("WSAStartup Error",0);
        return false;
    }
    else
        MakeMeFocused("WSAStartup success",1);

    server.sin_family = 2;
	uint16 port = config.ReadInteger("port", 21000, "LOGIN");
    server.sin_port = htons( port );
    server.sin_addr.s_addr = 0;

    listen_socket = socket(2,1,0);

    if (listen_socket == INVALID_SOCKET)
    {
        MakeMeFocused("Login Server: listen_socket Error",0);
        return false;
    }
    else MakeMeFocused("Login Server: listen_socket success",1);

    if (bind(listen_socket,(struct sockaddr*)&server, serverlen) == SOCKET_ERROR)
    {
        MakeMeFocused("Login Server: bind Error",0);
        return false;
    }
    else 
		printf("Login Server: listening on port %u\n", port);


    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        MakeMeFocused("Login Server: listen Error",0);
        return false;
    }
    else MakeMeFocused("Login Server: listen success",1);

    return true;
}

void Comm(void *msg_sock)
{
    SOCKET msg_socket = (SOCKET)msg_sock;
    unsigned char buffer[2000];
    int retbufsize = 0;
	{PacketHandler PackHandle(msg_socket);
	while(msg_sock)
	{
		retbufsize = recv(msg_socket, (char*)buffer, sizeof(buffer), 0);

		if (!retbufsize)
		{
			MakeMeFocused("Login Server: Connection closed by client",0);
			closesocket(msg_socket);
			break;
		}

		if (retbufsize == SOCKET_ERROR)
		{
			MakeMeFocused("Login Server: Client socket closed",0);
			closesocket(msg_socket);
			break;
		}
		else printf("recv %d bytes success\n",retbufsize);

		//outBuffer();
		PackHandle.Handler(buffer);
		if(PackHandle.nOfPackets)
		{
			MakeMeFocused("Login Server: Sending Response",1);
			retbufsize = send(msg_socket,(char*)buffer,PackHandle.ServerResponse(buffer)*buffer[0], 0);
		}
		else MakeMeFocused("Login Server: Server have no response",0);

	}
	}
    _endthread();
}

bool cLoginServer::CommLoop()
{
    bool bExit = false;
    int retbufsize = 0;

    while (!bExit)
    {
            if ((msg_socket = accept(listen_socket, (struct sockaddr*)&client, &clientlen)) == INVALID_SOCKET)
            {
                MakeMeFocused("Login Server: Accept Error",0);
                return false;
            }
            else printf("Login Server: Accept Client with IP:%s\n",inet_ntoa(client.sin_addr));
            _beginthread(Comm,0,(void *)msg_socket);
    }

    return true;
}

void cLoginServer::outBuffer()
{
    /*
    printf("---- Recieved Data From %s  ----\n",inet_ntoa(client.sin_addr));

    for (int i = 0; i < buffer[0]; i++)
    {
        if (i && i%16 == 0)printf("\n");
        if (*(BYTE*)(buffer+i) < 0x10)printf("0");
        printf("%x ",(int)*(BYTE*)(buffer+i));
    }
    printf("\n");
    */
}

#endif