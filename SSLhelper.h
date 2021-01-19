#pragma once

#include <openssl/ssl.h>
#include "sock.h"
#include <stdlib.h>
#include <assert.h>

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

typedef byte uint8_t;

SSL* openssl_conn(SOCKET conn);

int ssl_recv(SSL* ssl, byte** buffer);

void ssl_send(SSL* ssl, byte* input, int byte_amount);