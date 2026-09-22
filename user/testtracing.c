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
    int val = fork();
    if(val == 0){
        printf("Child Tracking value: 0\n");
        uptime();
        exit(0);
    }
    else{
        printf("Parent Tracking value: 1\n");
    }
   
    
    uptime();

    return 0;
}
