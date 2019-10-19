#pragma once
#include "TcpServer.h"

class TcpConsoleChat final: public TcpServer {
private:

	void relayMessage(const int& outSocket, const char* msg);

protected:
	//When a client connects
	virtual void onConnect(const int& socket) override;

	//When a client disconnects
	virtual void onDisconnect(const int& socket) override;

	virtual void onMessageReceived(const int& clientSocket, const char* msg) override;

public:
	TcpConsoleChat(const char* IP, const int& port)
		:TcpServer::TcpServer(IP, port){}
	~TcpConsoleChat() { std::cout << "MultiClient destructor called! \n"; }
	
};

