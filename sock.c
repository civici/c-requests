#include "sock.h"


SOCKET OpenConnection(char* host, char* port) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct addrinfo hints, * result = NULL;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	int res = getaddrinfo(host, port, &hints, &result);

	SOCKET connection = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	connect(connection, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result);

	return connection;
}