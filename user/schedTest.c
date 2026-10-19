#include "kernel/types.h"
#include "user/user.h"

// function to get the number of digits in the number
int numDigits(int n){
    int count = 0;
    while(n > 0){
        count++;
        // removing last digit
        n /= 10;
    }
    return count;
}

// implementing a power function
int raiseTo(int number, int exponent){
    int result = 1; // need to set to one or else the number will always be 0
    for(int i = 0; i < exponent; i++){
        // raising to the power of the number of digits
        result *= number;
    }
    return result;
}

// Implementing Armstrong number check
int armstrongCheck(int LIMIT){
    // 
    int isArmstrong = 0; // number we will be returning
    int sumOfDigits = 0; //variable to get total ssum
    for(int i = 2; i <= LIMIT; i++){
        // doing calculation here
        int temp = i; // temp variable to seperate number into single digits
        sumOfDigits = 0; // reset
        int countOfDigits = numDigits(i); // variable that holds the count of seperate digits
        // checking digits  
        while(temp > 0){
            int digit = temp % 10;
            sumOfDigits += raiseTo(digit, countOfDigits);
            temp /= 10;
        }
        // if the original number is equal to the sumOfDigits, increment count++
        if(i == sumOfDigits){
            isArmstrong++;
        }
    }
    return isArmstrong;
}

int main(){ 
    int LIMIT = 1000000;
    // creating an array to set each priority for the forks
    int priorities[8] = {0, 0, 5, 5, 10, 10, 15, 15};
    //debug(1); // turn debug mode on

    // set up for user input of debug mode
    char buf[16];
    int inputMode = 0;
    printf("Input debug mode (0 or 1): ");
    gets(buf, sizeof(buf));
    inputMode = atoi(buf);
    
    if(inputMode < 0 || inputMode > 1){
        printf("Invalid selection, continuing with debug mode set to on (1)\n\n");
        inputMode = 1;
    }

    debug(inputMode);

    for(int i = 0; i < 8; i++){
        int pid = priority_fork(priorities[i]);    
        //printf("Process: %d\n", getpid()); 
        if(pid < 0){
            printf("Failure");
            break;
        }
        if(pid == 0){
            // in child fork
            //printf("Process: %d\n", getpid());
            printf("Number of Armstrong Numbers between 2 and %d: %d\nTime for process to complete: %d ticks\n\n",
                 uptime(), LIMIT, armstrongCheck(LIMIT));
            //printf("Time for process to complete: %d ticks\n\n", uptime());
            exit(0);
        }
        printf("Forking a process with PID: %d and Prioritiy: %d\n\n", pid, priorities[i]);

    }
    // printf("Number of Armstrong Numbers between 2 and %d: %d\n", LIMIT, armstrongCheck(LIMIT));
    // reset debug
    while(wait(0) > 0){

    }
    debug(0); // i am resetting debug mode that is most likely why it is only printing for one
    exit(0);
}
