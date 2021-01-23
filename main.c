#include "requestr.h"
#include "conn.h"

int main(){

    request_lib_init();
    char* test = request_get("https://example.com");
    puts(test);
    request_lib_destroy();
    puts("done");
    return 0;
}
