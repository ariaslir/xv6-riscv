// #include "kernel/types.h"
#include "user/user.h"

// implementing a power function
int raiseTo(int number, int exponent){
    int result = 1; // need to set to one or else the number will always be 0
    for(int i = 0; i < exponent; i++){
        // raising to the power of the number of digits
        result *= number;
    }
    return result;
}

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

// Implementing Armstrong number check
int armstrongCheck(int LIMIT){
    // 
    int isArmstrong = 0; // number we will be returning
    int sumOfDigits = 0; //variable to get total ssum
    for(int i = 2; i <= LIMIT; i++){
        // doing calculation here
        int temp = i; // temp variable to seperate number into single digits
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

    printf("Number of Armstrong Numbers between 2 and 1000000: ", armstrongCheck(LIMIT));
}
