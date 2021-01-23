#pragma once

#define PROTO_HTTP  0
#define PROTO_HTTPS 1

#include "conn.h"

typedef struct req req;


struct req{

    int proto;
    char* host;
    char* page;
    char* port;

};

void request_lib_init();

void request_lib_destroy();

int check_protocol(char* url);

req* request_new(char* url);

char* build_request(req* request);

char* request_get(char* url);

req* test(char* url);