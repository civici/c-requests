#include "request.h"


enum a{
    PROTO_HTTP,
    PROTO_HTTPS
};

int check_protocol(char* url){

    char* proto = calloc(8, 1);
    for (int i = 0; i < 7; i++){
        proto[i] = url[i];
    }
    proto[7] = '\0';
    if (strcmp(proto, "http://") == 0){
        return PROTO_HTTP;
    } else if (strcmp(proto, "https:/") == 0){
        free(proto);
        proto = calloc(9, 1);
        for (int i = 0; i < 8; i++){
            proto[i] = url[i];
        }
        if (strcmp(proto, "https://") == 0){
            return PROTO_HTTPS;
        } else {
            puts("not supported protocol");
        }
    } else {
        puts("not supported protocol");
    }
    return -1;


}

void build_request(req* request){

    int final_len = 27 + strlen(request->host);
    if (request->page != NULL){
        final_len += strlen(request->page);
    }
    char* final_req = calloc(final_len + 1, 1);
    char* req = "GET /%s HTTP/1.1\r\n"
                "Host: %s\r\n"
                "\r\n";

    int str_index = 0;
    int final_req_index = 0;
    for (int i = 0; i < final_len; i++){
        if (i < final_len - 1 && req[i] == '%'){
            if (req[i + 1] == 's'){
                i++;
                if (str_index == 0){
                    if (request->page != NULL){
                        for (int j = 0; j < strlen(request->page); j++){
                            final_req[final_req_index] = request->page[j];
                            final_req_index++; 
                        }
                    } else {
                        puts("req page null");
                    }
                    str_index++;
                } else if (str_index == 1){
                    for (int j = 0; j < strlen(request->host); j++){
                        final_req[final_req_index] = request->host[j];
                        final_req_index++;
                    }
                    str_index++;
                }
            }
        } else {
            final_req[final_req_index] = req[i];
            final_req_index++;
        }
    }

    final_req[final_len] = '\0';
    puts(final_req);

}

req* new_request(int request_type, char* url){
    int proto_type;
    int urllen = strlen(url);
    char* protocol = calloc(5, 1);
    req* request = malloc(sizeof(req));
    for (int i = 0; i < 7; i++){
        protocol[i] = url[i];
    }

    proto_type = check_protocol(url);
    if (proto_type == -1){
        return;
    }
    request->proto = proto_type;

    int hostlen = 0;
    int hostindex = proto_type + 7;
    int pageindex = 0;
    for (int i = hostindex; i < urllen; i++){

        if (i == urllen - 1){
            hostlen++;
            pageindex = -1;
            break;
        }

        if (url[i] == '/'){
            pageindex = i + 1;
            break;
        }
        hostlen++;
    }
    printf("hostlen %d p0roto %d hostindex %d urllen %d\n", hostlen, proto_type, hostindex, urllen);
    char* host = calloc(hostlen + 1, 1);
    for (int i = hostindex; i < urllen; i++){
        host[i - hostindex] = url[i]; 
    }
    host[hostlen] = 0;
    request->host = host;
    puts(host);

    if (pageindex != -1){
        int pagelen = urllen - hostlen - proto_type + 7;
        char* page = calloc(pagelen + 1, 1);
        for (int i = 0; i < pagelen; i++){
            page[i] = url[i + pageindex];
        }
        page[pagelen] = 0;
        puts(page);
        request->page = page;
    } else {
        request->page = NULL;
    }
    
    return request;
}

void request_get(char* url){
    
}