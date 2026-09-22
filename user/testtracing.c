#include "user.h"

int main(){

    int pid = getpid();
    
    //uptime();
    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() implementation...\n");
    syscalltrace(1);

    sbrk(50);
    pause(50);
    int checkForkVal = fork();
    
    if(checkForkVal > 0){
        printf("Parent Tracking Value: %d\n", myproc()->traceValue);
    }
    else{
        printf("Child Tracking Value: %d\n", myproc()->traceValue);
        uptime();
        exit(0);
    }
    uptime();

    return 0;
}
