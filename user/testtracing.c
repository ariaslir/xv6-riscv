#include <user.h>

int main(){

    int pid = getpid();
    printf("Process ID: ", pid);
    
    uptime();
    printf("Process Uptime:", uptime());
    printf("Testing syscalltrace() Implementation...");
    syscalltrace(1);

    fork();
    printf("Parent ID: ", pid);
    printf("Child ID: ", getpid());

    return 0;
}
