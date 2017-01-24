#include <WinSock2.h> // boost starts complaining if this is not included beforehand
#include <Windows.h>
#include <mysql.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <Log.h>
#include "ini.h"
#include "GameServer.h"

#define IO_THREADS 50
int type = 3, port = 9332, id = 4;
char name[20];

CIni config(".\\config.ini", "CONFIG");
boost::asio::io_service ioService;
GameServer *gameserver;

void DoIoWork()
{
    //Log::out() << "An I/O thread has started." << endl;
	srand(time(0));
    mysql_thread_init();

    ioService.run();

    Log::out(LOG_TYPE_WARNING) << "An I/O thread has returned from io_service::run()." << endl;
}

void Keepalive()
{
	while (1)
	{
		try {

			static CHAR hdrs[] = "Content-Type: application/x-www-form-urlencoded";
			static CHAR frmdata[1000];
			sprintf(frmdata, "id=%d&players=%d", id, gameserver->GetTotalPlayers());
			static LPCSTR accept[2] = { "*/*", NULL };
			HINTERNET hSession = InternetOpenA("spserver", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hConnect = InternetConnectA(hSession, "spgame.net", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
			HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/status2.php", NULL, NULL, accept, INTERNET_FLAG_SECURE, 1);

			HttpSendRequestA(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));
			Sleep(200);
			InternetCloseHandle(hSession);
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hRequest);

			Sleep(10000);

			gameserver->UpdateActiveUsers();
		}
		catch (...) {

		}

	}

}

int main(int argc, char *argv[])
{
	strcpy(name, "Epic1");
	if(argc == 5){
		id = atoi(argv[1]);
		type = atoi(argv[2]);
		port = atoi(argv[3]);
		strcpy(name,argv[4]);
	}

    mysql_library_init(0, 0, 0);
	boost::asio::io_service::work work(ioService);
    boost::thread* ioThreads[IO_THREADS];

	try {
    //GameServer gameServer(ioService, port, port, type);
		gameserver = new GameServer(ioService, port, port, type);
	}catch(...)
	{
		return 0;
	}

	ioThreads[0] = new boost::thread(&Keepalive);
	for (int i = 1; i < IO_THREADS; i++)
            ioThreads[i] = new boost::thread(&DoIoWork);

	gameserver->Start();

	Log::out() << "-- Server ID: " << id << " Type:" << type << " Port:" << port << " Name:" << name << " --" << endl;

	for (int i = 0; i < IO_THREADS; i++)
            ioThreads[i]->join();

    Log::out() << "Server closed?" << endl;

    return 0;
}
