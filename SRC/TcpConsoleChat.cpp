#include "TcpConsoleChat.h"

//When a client connects
void TcpConsoleChat::onConnect(const int& socket)
{
	std::ostringstream oss{};
	oss << "Welcome socket#" << socket << "\r\n" << std::endl;
	std::string msg{ oss.str() };


	send(socket, msg.c_str(), msg.size() + 1, 0);
}

//When a client disconnects
void TcpConsoleChat::onDisconnect(const int& socket)
{
	std::cout << "#" << socket << " left the chat! \n";

}

//When a message is received
void TcpConsoleChat::onMessageReceived(const int& clientSocket, const char* msg)
{
	relayMessage(clientSocket, msg);
}


void TcpConsoleChat::relayMessage(const int& sock, const char* msg)
{
	// Send message to other clients except listening and sending socket
	for (unsigned i = 0; i < main_set.fd_count; i++)
	{
		int outSock = main_set.fd_array[i];

		if (outSock != listening && outSock != sock)
		{
			std::ostringstream ss;
			ss << "SOCKET #" << sock << ": " << msg << std::flush;
			std::string str = ss.str();

			send(outSock, str.c_str(), str.size(), 0);
		}

	}

}

