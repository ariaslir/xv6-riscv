#include "user.h"


int main(){

    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() implementation...\n");
    syscalltrace(1);

    sbrk(50);
    getpid();
    pause(10);
    fork();
    uptime();//added uptime to match output
    exit(0);

    return 0;
}
