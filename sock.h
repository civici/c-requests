#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET connection;

SOCKET OpenConnection(char* host, char* port);