#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

const char *ingredients[9] = {
    "white leaf",
    "green leaf", 
    "oolong tea leaf",
    "chamomile tea", 
    "peppermint oil", 
    "hibiscus leaves",
    "puffed rice",
    "spice",
    "dried berries"
};

int pouches[4]; // number of ingrediants
pthread_mutex_t mutex; // mutex: guards pouch
sem_t supplier_sem[4]; // wakes supplier i 
sem_t available_sem[4]; // wake waiting enthusiasts
int waiting[4]; // number of enthusiasts waiting on i 



int main(void){
    printf("CS 370 Project 5 - Tea Enthusiast Problem - Solved by Jesse Arias\n");

    // just to ensure the access was correct and can print out the names
    for(int i = 0; i < 9; i++){
        printf("Ingredient name: %s\n", ingredients[i]);
    }
    return 0;
}






