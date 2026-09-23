#include "user.h"

int main(){

    //int pid = getpid();
    
    //uptime();
    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() implementation...\n");
    syscalltrace(1);

    sbrk(50);
    getpid();
    pause(50);
    fork();

    return 0;
}
