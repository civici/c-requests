#pragma once

#include "SSLhelper.h"
#include <string.h>

typedef struct req req;

struct req{

    int proto;
    char* host;
    char* page;

};


void build_request(req* request);

req* new_request(int request_type, char* url);