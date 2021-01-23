#include "conn.h"

SOCKET openConnection(char* host, char* port){
    
    int err = 0;
    struct addrinfo hints, *result = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
    
    err = getaddrinfo(host, port, &hints, &result);
    if (err != 0){
        puts("err at getaddrinfo");
    }

    SOCKET connection = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connection == INVALID_SOCKET){
        puts("err at socket()");
    }
    err = connect(connection, result->ai_addr, (int) result->ai_addrlen);
    if (err != 0){
        puts("err at connect");
        int test = WSAGetLastError();
        printf("%d\n", test);
    }
    freeaddrinfo(result);
    return connection;
}

void socket_send(SOCKET s, char* buf){
    int bytes = strlen(buf);

    int err = send(s, buf, bytes, 0);
}

char* socket_recv(SOCKET s){

    char* resp = calloc(8192, 1);
    int bytes = recv(s, resp, 8192, 0);
    if (bytes < 0){
        puts("error at recv");
        int err = WSAGetLastError();
        printf("err is %d\n", err);
    }
    char* buf = calloc(bytes + 1, 1);
    for (int i = 0; i < bytes; i++){
        buf[i] = resp[i];
    }

    buf[bytes] = 0;
    return buf;

}

char* secure_recv(SSL* ssl){
    char* buf = calloc(8192, 1);
    int bytes = SSL_read(ssl, buf, 8192);
    char* buffer = calloc(bytes, 1);
    for (int i = 0; i < bytes; i++){
        buffer[i] = buf[i];
    }
    return buffer;
}

void secure_send(SSL* ssl, char* input){
    SSL_write(ssl, input, strlen(input));
}

SSL* openSecConnection(SOCKET s){
    SSL_CTX* tlsctx = SSL_CTX_new(TLSv1_2_client_method());

    SSL* ssl = SSL_new(tlsctx);
    SSL_set_fd(ssl, s);
    SSL_connect(ssl);

    return ssl;
}