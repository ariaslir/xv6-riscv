#include "user.h"


int main(){

    //int pid = getpid();
    struct proc *np;
    struct proc *p = myproc();
    
    //uptime();
    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() implementation...\n");
    syscalltrace(1);

    sbrk(50);
    getpid();
    pause(50);
    fork();
    // if(p->traceValue > 0){
    //     printf("Parent Tracking Value: %d\n", p->traceValue);
    // }
    // else{
    //     printf("Child Tracking Value: %d\n", p->traceValue);
    // }
    uptime();//added uptime to match output

    return 0;
}
