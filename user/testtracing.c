#include "user.h"

int main(){

    int pid = getpid();
    printf("Process ID: %d\n", pid);
    
    //uptime();
    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() Implementation...\n");
    syscalltrace(1);

    sbrk(50);
    pause(50);
    int checkForkVal = fork();
    
    if(checkForkVal > 0){
        printf("Parent Process ID: %d\n", pid);
    }
    else{
        printf("Child Process ID: %d\n", getpid());
        uptime();
        exit(0);
    }

    return 0;
}
