#include <user.h>

int main(){

    int pid = getpid();
    printf("Process ID: %d\n", pid);
    
    uptime();
    printf("Process Uptime: %d\n", uptime());
    printf("Testing syscalltrace() Implementation...");
    syscalltrace(1);

    int checkForkVal = fork();
    
    if(checkForkVal > 0){
        printf("Parent Process ID: %d\n", getpid());
    }
    else{
        printf("Child Process ID: %d\n", getpid());
    }

    return 0;
}
