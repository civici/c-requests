#include <WinSock2.h>
#include <WS2tcpip.h>
#include <openssl/ssl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

SOCKET openConnection(char* host, char* port);

void socket_send(SOCKET s, char* buf);

char* socket_recv(SOCKET s);

void closeConnection(SOCKET s);


char* secure_recv(SSL* ssl);

void secure_send(SSL* ssl, char* input);

SSL* openSecConnection(SOCKET s);