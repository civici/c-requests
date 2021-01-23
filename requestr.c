#include "requestr.h"


void request_lib_init(){

    WSADATA wsadata;
    WORD version = MAKEWORD(2,2);
    WSAStartup(version, &wsadata);
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void request_lib_destroy(){
    WSACleanup();
}

char* build_request(req* r){

    char* request = "GET /--page-- HTTP/1.1\r\n"
                    "Host: --host--\r\n"
                    "\r\n";

    int finallen = strlen(r->host);
    if (r->page != NULL){
        finallen += strlen(r->page);
    }
    char* final = calloc(finallen + 26, 1);
    int finali = 0;
    for (int i = 0; i < strlen(request); i++){

        if (request[i] == '-'){
            char* blank = calloc(9, 1);
            for (int j = 0; j < 8; j++){
                blank[j] = request[i + j];
            }
            if (strcmp(blank, "--page--") == 0){
                puts("page found");
                if (r->page != NULL){
                    for (int reqp_index = 0; reqp_index < strlen(r->page); reqp_index++){
                        final[finali] = r->page[reqp_index];
                        finali++;
                    }
                }
                i += 7;
            } else if (strcmp(blank, "--host--") == 0){
                puts("host found");
                for (int hosti = 0; hosti < strlen(r->host); hosti++){
                    final[finali] = r->host[hosti];
                    finali++;
                }
                i+= 7;
            } else {
                final[finali] = request[i];
                finali++;
            }
            free(blank);
        } else {
            final[finali] = request[i];
            finali++;
        }
    }
    printf("final is %s\n", final);
    return final;
}


req* request_new(char* url){

    int urllen = strlen(url);
    req* r = malloc(sizeof(req));

    /* check for protocol */
    /* https:// http:// */
    
    char* proto = calloc(8, 1);

    for (int i = 0; i < 7; i++){
        proto[i] = url[i];
    }
    proto[7] = '\0';

    if (!strcmp(proto, "http://")){
        r->proto = PROTO_HTTP;
        r->port = "80";
    } else if (!strcmp(proto, "https:/")){
        if (url[7] == '/'){
            r->proto = PROTO_HTTPS;
            r->port = "443";
        }
    }
    
    /* check for protocol ends */



    /* parse host */

    int hostindex = 7 + r->proto;
    int hostlen = 0;

    for (int i = hostindex; i < urllen; i++){

        if (i == urllen - 1){
            if (url[i] != '/'){
                hostlen++;
            }
            break;
        }

        if (url[i] == '/'){
            break;
        }
        hostlen++;
    }

    char* host = calloc(hostlen + 1, 1);

    for (int i = 0; i < hostlen; i++){
        host[i] = url[i + hostindex];
    }

    r->host = host;

    /* parse host */

    /* parse page */

    int pagelen = urllen - 7 - 0  /* if http 0 else 1 */ - hostlen;
    if (pagelen > 1){
        char* page = calloc(pagelen + 1, 1);
        for (int i = hostindex + hostlen + 1; i < urllen; i++){
            page[i - hostindex - hostlen - 1] = url[i];
        }
        r->page = page;
    } else {
        r->page = NULL;
    }

    /* parse page */

    return r;

}

char* request_get(char* url){

    char* resp;

    req* r = request_new(url);
    char* final = build_request(r);
    SOCKET s = openConnection(r->host, r->port);
    if (r->proto == PROTO_HTTP){
        socket_send(s, final);
        resp = socket_recv(s);
        closesocket(s);
    } else if (r->proto == PROTO_HTTPS){
        SSL* ssl = openSecConnection(s);
        secure_send(ssl, final);
        resp = secure_recv(ssl);
        SSL_free(ssl);
    }
    return resp;

}


