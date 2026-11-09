#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void){

    int n = 0;
    void *ptr[200];

    int frames = trackframes();
    printf("Frames at start:%d\n", frames);

    ptr[n] = block_alloc(28); //first allocation
    n++; //move to the next slot

    int first = trackframes();
    printf("Frames after first allocation:%d\n", first);

    printf("For testing (Chunk at):%d", ptr[n]);


    exit(0);
}