#include "SSLhelper.h"

SSL* openssl_conn(SOCKET conn)
{

	SSL_CTX* tlsctx = SSL_CTX_new(TLSv1_2_client_method());

	//SSL_CTX_use_certificate_file(tlsctx, "keys/cert.pem", SSL_FILETYPE_PEM);
	//SSL_CTX_use_PrivateKey_file(tlsctx, "keys/key.pem", SSL_FILETYPE_PEM);

	SSL* ssl = SSL_new(tlsctx);
	SSL_set_fd(ssl,(int) conn);

	int ssl_con = SSL_connect(ssl);

	return ssl;
}

int ssl_recv(SSL* ssl, byte** buffer){
	byte* buf = calloc(8192, 1);
	int bytes = SSL_read(ssl, buf, 8192);
	if (bytes <= 0){
		puts("error at ssl_recv");
	} else if (bytes > 8192){
		puts("bytes > 8192");
	} else {
		*buffer = malloc(bytes + 1);
	}

	for (int i = 0; i < bytes; i++){
		(*buffer)[i] = buf[i];
	}
	(*buffer)[bytes] = '\0';
	return bytes;
}

void ssl_send(SSL* ssl, byte* input, int byte_amount) {
	int status = SSL_write(ssl, input, byte_amount);
	if (status <= 0){
		puts("error at ssl_send");
	}
}