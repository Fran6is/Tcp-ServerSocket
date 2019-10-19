#include"TcpServer.h"

TcpServer::TcpServer(const char* IP, const int& port)
	:ipAddress{ IP }, PORT(port), listening{}
{
	FD_ZERO(&main_set);
}

int TcpServer::init()
{
	WSADATA winsockData;
	WORD ver = MAKEWORD(2, 2);

	int status = WSAStartup(ver, &winsockData);
	if (status != 0)
	{
		std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
		return -1;
	}

	// Create a socket
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "couldn't create a socket! Quitting" << std::endl;
		return -1;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	inet_pton(AF_INET, ipAddress, &hint.sin_addr); // Could also use INADDR_ANY

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) != 0)
	{
		int err = WSAGetLastError(); WSACleanup(); closesocket(listening);
		return err;
	}

	// Tell Winsock the socket is for listening 
	if (listen(listening, SOMAXCONN) != 0)
	{
		int err = WSAGetLastError(); WSACleanup(); closesocket(listening);
		return err;
	}

	// Add first socket (our listening socket)
	FD_SET(listening, &main_set);

	return 0;

}

int TcpServer::run()
{
	//Incase 'run' was called before 'init'
	if (main_set.fd_count == 0) return -1;

	//Running loop
	bool running = true;
	while (running)
	{
		
		fd_set copy = main_set;

		//The select function determines the status of one or more sockets, waiting if necessary, to perform synchronous I / O.
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all connections ( new and old )
		for (int i = 0; i < socketCount; i++)
		{
			const int& sock = copy.fd_array[i];

			// A new request for the listening socket
			if (sock == listening)
			{
				//For Client information
				struct sockaddr_in client_info;
				int len = sizeof client_info;
				char host[NI_MAXHOST]{};

				// Accept a new connection
				int client = accept(listening, (sockaddr*)&client_info, &len);
				if (client == INVALID_SOCKET)
				{
					std::cerr << "client socket error#" << WSAGetLastError() << std::endl;
					continue;
				}

				// Add new connection to set
				FD_SET(client, &main_set);

				//Connection details
				showInfo(client_info);

				//(1)what to do when a client connects
				onConnect(client);
			}
			else // A message from other sockets
			{
				char buf[4000];
				ZeroMemory(buf, 4000);

				// Receive message
				int bytesRecd = recv(sock, buf, 4000, 0);
				if (bytesRecd <= 0)
				{
					//(2)what to do when a client disconnects
					closesocket(sock);
					FD_CLR(sock, &main_set);

					onDisconnect(sock);
				}
				else
				{
					//(3) what to do when we actually receive a message
					onMessageReceived(sock, buf);

				}
			}
		}

	}


	// Remove listening socket from the main set and close it
	FD_CLR(listening, &main_set);
	closesocket(listening);

	//remove other sockets
	while (main_set.fd_count > 0)
	{
		const int& sock = main_set.fd_array[0];
		send(sock, "Bye!", 5, 0);

		FD_CLR(sock, &main_set); //decreases as each socket is been removed
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	return 0;
}


void TcpServer::onConnect(const int& socket)
{
	//When a client connects

}


void TcpServer::onDisconnect(const int& socket)
{
	//When a client disconnects
}


void TcpServer::onMessageReceived(const int& clientSocket, const char* msg)
{
	//When a message is received

}


void TcpServer::showInfo(struct sockaddr_in& client)
{
	//Option 1: getnameinfo()

	//Option 2: inet_ntop(), ntohs()
	char buf[NI_MAXHOST]{};
	inet_ntop(AF_INET, &client.sin_addr.S_un.S_addr, buf, NI_MAXHOST);
	std::cout << buf << " connected on port: " << ntohs(client.sin_port) << std::endl;
}
