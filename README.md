# Tcp-ServerSocket

Two classes:
    -A "TcpServer" base class
    -A publicly derived "TcpConsoleChat" class.
    
The "TcpConsoleChat" class allows for multisocket communcation. So two or more opened windows of "Tcp-client-socket" are needed to connect to this server

Language: C/C++
IDE used: Visual Studio 2019

DEPENDENCIES
Windows OS 
Headerfile: WS2tcpip.h
lib file: ws2_32.lib
Microsoft documentation for ws2tcpip.h: https://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/

Linux / other OS 
Header file: sys/types.h, sys/socket.h, netinet/in.h
