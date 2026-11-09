#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void){

    int n = 0;
    void *ptr[200];

    printf("First Allocation:");

    ptr[n] = block_alloc(28); //first allocation
    void *ogPage = ptr[n]; // saving original page number from where we started
    printf("Allocated 32-byte chunk at %p\n\n", ptr[n]);
    n++; //move to the next slot

    int first = trackframes();
    printf("Process page table has %d frames.\n", first);

    // keep allocating until frames go up
    while(n < 200){
        ptr[n] = block_alloc(28); //first allocation
        printf("Allocated 32-byte chunk at %p (page %p)\n", ptr[n], ogPage);
        n++; //move to the next slot

        int new = trackframes();
        printf("Current page count: %d\n", new);

        if(new > first){
            printf("Current page count: %d\n\n", new);
            break;
        }
    }   
    //print final count of frames allocated
    int final = trackframes();
    printf("Frames allocated: %d\n\n", final);

    printf("=========START FREEING=========\n");

    // started at 1 to skip starting chunk
    for(int i = 1; i < n; i++){
        block_free(ptr[i]);
        printf("Freed 32-byte chunk at %p\n", ptr[i]);
    }

    exit(0);
}