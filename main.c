#include <stdio.h>
#include <stdlib.h>
#include "request.h"

int main(){
    
    req* r = new_request(0, "https://www.example.com");
    build_request(r);
    puts("done");
    return 0;

}