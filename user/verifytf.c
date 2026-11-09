#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void){

    int n = 0;
    void *ptr[200];

    int frames = trackframes();
    printf("Frames at start:%d\n", frames);

    int first = trackframes();
    printf("Frames after first allocation:%d\n", first);

    // keep allocating until frames go up
    while(n < 200){
        ptr[n] = block_alloc(28); //first allocation
        printf("For testing (Chunk at):%p\n", ptr[n]);
        n++; //move to the next slot

        int new = trackframes();
        printf("Frames after first allocation:%d\n", new);

        if(new > first){
            printf("Stop loop, testing");//testing
            break;
        }
    }   

    for(int i = 0; i < n; i++){
        block_free(ptr[i]);
        printf("Freeing %p", ptr[i]);
    }

    exit(0);
}