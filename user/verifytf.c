#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void){

    int n = 0;
    void *ptr[200];

    printf("First Allocation:");

    ptr[n] = block_alloc(28); //first allocation
    printf("Allocated 32-byte chunk at %p\n\n", ptr[n]);
    n++; //move to the next slot

    int first = trackframes();
    printf("Process page table has %d frames.\n", first);

    // keep allocating until frames go up
    while(n < 200){
        ptr[n] = block_alloc(28); //first allocation
        //manually calculating actual starting page for each print instead
        uint64 addr = (uint64)ptr[n];
        uint64 offset = addr % 4096;
        uint64 page = addr - offset;
        // convert the page address from a number back to a pointer
        char *realPage = (char *)page;
        printf("Allocated 32-byte chunk at %p (page %p)\n", ptr[n], realPage);
        n++; //move to the next slot

        int new = trackframes();
        printf("Current page count: %d\n", new);

        if(new > first){
            break;
        }
    }   
    //print final count of frames allocated
    // int final = trackframes();
    printf("Frames allocated: %d\n\n", n);

    printf("=========START FREEING=========\n\n");

    // start free
    for(int i = 0; i < n; i++){
        block_free(ptr[i]);
        uint64 addr = (uint64)ptr[i];
        uint64 offset = addr % 4096;
        uint64 page = addr - offset;
        // convert the page address from a number back to a pointer
        char *realPage = (char *)page;
        printf("Freed 32-byte chunk at %p (page %p)\n", ptr[i], realPage);
    }
    printf("All pages freed.\n");

    exit(0);
}