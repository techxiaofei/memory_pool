#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory_pool.h"

int main(){
    MemoryPool* pool = mem_pool_create(32, 1);
    if (pool==NULL){
        return 0;
    }
    char* buffer = mem_pool_alloc(pool);
    printf("buffer %p\n",buffer);
    char* buffer2 = mem_pool_alloc(pool);
    printf("buffer2 %p\n",buffer2);
    if (!buffer || !buffer2){

    }

    strcpy(buffer,"abcdefgh\n");
    strcpy(buffer2,"abcdefghij\n");

    printf("%s",buffer);
    printf("%s",buffer2);

    mem_pool_free(pool, buffer);
    mem_pool_free(pool, buffer2);
    //re test
    char* buffer3 = mem_pool_alloc(pool);
    printf("buffer3 %p\n",buffer3);
    if (!buffer3){

    }

    strcpy(buffer3,"abcd\n");

    printf("%s",buffer3);

    mem_pool_free(pool, buffer3);

    return 0;
}

//gcc -o test memory_pool.c main.c