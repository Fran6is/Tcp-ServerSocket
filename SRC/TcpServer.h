#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

class TcpServer {
private:
	const char* ipAddress;
	const int PORT;
	
protected:
	fd_set main_set;

	int listening;

	virtual void onConnect(const int& socket);

	virtual void onDisconnect(const int& socket);

	virtual void onMessageReceived(const int& clientSocket, const char* msg);

	//show info
	void showInfo(struct sockaddr_in& client);
public:
	~TcpServer() { std::cout << "TcpServer destructor called! \n"; }
	TcpServer(const char* IP, const int& port);
	int init();
	int run();
};

#endif //TcpServer.h