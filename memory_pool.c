#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_pool.h"

MemoryPool* mem_pool_create(int chunk_size, int factor){
    MemoryPool* mp = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!mp)
        return NULL;
    mp->block_cnt = 4;  //配置
    mp->next = NULL;
    int now_factor = 1;
    Block* last_block = mp->next;
    for (int i = 0; i < mp->block_cnt; i++){
        Block* next_block = (Block*)malloc(sizeof(Block));
        if (!next_block){
            free(mp);
            return NULL;
        }
        if (last_block == NULL){
            mp->next = next_block;
            last_block = next_block;
        }else{
            last_block->next = next_block;
            last_block = next_block;
        }
        next_block->chunk_cnt = 10;
        next_block->chunk_size = chunk_size * now_factor;
        now_factor *= factor;
        for (int j = 0; j < next_block->chunk_cnt; j++){
            Chunk* next_chunk = next_block->chunk_list;
            Chunk* header_chunk = (Chunk*)malloc(sizeof(Chunk)+next_block->chunk_size);
            header_chunk->next = next_chunk;
            next_block->chunk_list = header_chunk;
            header_chunk->chunk_size = next_block->chunk_size;
            memset(header_chunk->buf, 0, next_block->chunk_size);
        }

    }
    return mp;
}

void* mem_pool_alloc(MemoryPool* pool, int size){
    Block *block = pool->next;
    while (block && block->chunk_size < size){
        block = block->next;
    }
    if (!block)return NULL;
    Chunk *ret = block->chunk_list;
    if (ret){
        block->chunk_list = block->chunk_list->next;
        printf("mem_pool_alloc %p,%p\n",ret, ret->buf);
        return (char*)ret+sizeof(Chunk);
    }
    return NULL;
}

void mem_pool_free(MemoryPool* pool, void* memory){
    Chunk* now = (Chunk*)(memory - sizeof(Chunk));
    int size = now->chunk_size;
    printf("mem_pool_free %d, %p\n", now->chunk_size, now);
    
    Block *block = pool->next;
    while (block && block->chunk_size < size){
        block = block->next;
    }
    if (!block || block->chunk_size != size)return;
    Chunk *old = block->chunk_list;
    block->chunk_list = now;
    block->chunk_list->next = old;
}

void mem_pool_destroy(MemoryPool* pool){

}