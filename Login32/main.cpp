#include <WinSock2.h> // boost starts complaining if this is not included beforehand
#include <Windows.h>
#include <mysql.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <Log.h>
#include "ini.h"
#include "LoginServer.h"

#define IO_THREADS 150

CIni config(".\\config.ini", "CONFIG");
boost::asio::io_service ioService;

void DoIoWork()
{
    //Log::out() << "An I/O thread has started." << endl;

    mysql_thread_init();

    ioService.run();

    Log::out(LOG_TYPE_WARNING) << "An I/O thread has returned from io_service::run()." << endl;
}

void Keepalive()
{
	int i = 0;
	while(1)
	{
		try {

			static CHAR hdrs[] = "Content-Type: application/x-www-form-urlencoded";
			static CHAR frmdata[1000];
			sprintf(frmdata, "id=1&players=0");
			static LPCSTR accept[2] = { "*/*", NULL };
			HINTERNET hSession = InternetOpenA("spserver", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hConnect = InternetConnectA(hSession, "spgame.net", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
			HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/status2.php", NULL, NULL, accept, INTERNET_FLAG_SECURE, 1);

			HttpSendRequestA(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));

			Sleep(200);

			InternetCloseHandle(hSession);
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hRequest);

			i++;

			if (i % 6 == 0)
			{
				MySQL MySql;
				string data = MySql.GetSyncData();
				if (data.length() > 10)
				{
					string req = "r=update&data=";
					req.append(data);
					HINTERNET hSession = InternetOpenA("spserver", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
					HINTERNET hConnect = InternetConnectA(hSession, "spgame.net", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
					HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/sp.php", NULL, NULL, accept, INTERNET_FLAG_SECURE, 1);

					HttpSendRequestA(hRequest, hdrs, strlen(hdrs), (LPVOID)req.c_str(), req.length());

					Sleep(500);

					InternetCloseHandle(hSession);
					InternetCloseHandle(hConnect);
					InternetCloseHandle(hRequest);
				}
			}

			Sleep(10000);


		}
		catch (...) {
			
		}
		
	}

}


int main()
{
    mysql_library_init(0, 0, 0);

	boost::asio::io_service::work work(ioService);
    boost::thread* ioThreads[IO_THREADS];

	LoginServer *loginServer;
	try {
    loginServer = new LoginServer(ioService, 33001, 33001);
	}catch(...)
	{
		return 0;
	}
	ioThreads[0] = new boost::thread(&Keepalive);
	for (int i = 1; i < IO_THREADS; i++)
            ioThreads[i] = new boost::thread(&DoIoWork);

    loginServer->Start();

	Log::out() << "----- Server Started -----" << endl;

	for (int i = 0; i < IO_THREADS; i++)
            ioThreads[i]->join();

    Log::out() << "Server closed?" << endl;

    return 0;
}
