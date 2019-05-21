#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory_pool.h"

int main(){
    MemoryPool* pool = mem_pool_create(8, 2);
    if (pool==NULL){
        return 0;
    }
    char* buffer = mem_pool_alloc(pool,8);
    printf("buffer %p\n",buffer);
    char* buffer2 = mem_pool_alloc(pool,8);
    printf("buffer2 %p\n",buffer2);
    if (!buffer || !buffer2){

    }

    strcpy(buffer,"abcdefg\n");
    strcpy(buffer2,"bcdefgh\n");

    printf("%s",buffer);
    printf("%s",buffer2);

    mem_pool_free(pool, buffer);
    mem_pool_free(pool, buffer2);
    //re test
    char* buffer3 = mem_pool_alloc(pool,16);
    printf("buffer3 %p\n",buffer3);

    strcpy(buffer3,"abcdefghi\n");
    printf("%s",buffer3);
    mem_pool_free(pool, buffer3);

    //re test
    char* buffer4 = mem_pool_alloc(pool,8);
    printf("buffer4 %p\n",buffer4);

    strcpy(buffer4,"abcdefg\n");
    printf("%s",buffer4);
    mem_pool_free(pool, buffer4);

    return 0;
}

//gcc -o test memory_pool.c main.c