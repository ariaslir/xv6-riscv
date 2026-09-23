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
    int forkVal = fork();

    if(forkVal > 0){
        printf("Parent Value: %d\n", forkVal);
    }
    else{
        printf("Child Value: %d\n", forkVal);
    }

    return 0;
}
