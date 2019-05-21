#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_pool.h"

MemoryPool* mem_pool_create(int chunk_size, int factor){
    MemoryPool* mp = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!mp)
        return NULL;
    mp->block_cnt = 1;  //配置
    mp->next = NULL;
    int now_factor = 1;
    for (int i = 0; i < mp->block_cnt; i++){
        Block* next_block = mp->next;
        Block* header_block = (Block*)malloc(sizeof(Block));
        if (!header_block){
            free(mp);
            return NULL;
        }
        header_block->next = next_block;
        mp->next = header_block;
        header_block->chunk_cnt = 10;
        header_block->chunk_size = chunk_size * now_factor;
        now_factor *= factor;
        for (int j = 0; j < header_block->chunk_cnt; j++){
            Chunk* next_chunk = header_block->chunk_list;
            Chunk* header_chunk = (Chunk*)malloc(sizeof(Chunk)+header_block->chunk_size);
            header_chunk->next = next_chunk;
            header_block->chunk_list = header_chunk;
            header_chunk->chunk_size = header_block->chunk_size;
            memset(header_chunk->buf, 0, header_block->chunk_size);
        }

    }
    return mp;
}

void* mem_pool_alloc(MemoryPool* pool){
    Block *block = pool->next;
    Chunk *ret = block->chunk_list;
    if (ret){
        block->chunk_list = block->chunk_list->next;
        printf("mem_pool_alloc %p,%p\n",ret, ret->buf);
        return (char*)ret+sizeof(Chunk);
    }
    return NULL;
}

void mem_pool_free(MemoryPool* pool, void* memory){
    Chunk *old = pool->next->chunk_list;
    Chunk* now = (Chunk*)(memory - sizeof(Chunk));
    printf("mem_pool_free %p\n", now);
    pool->next->chunk_list = now;
    pool->next->chunk_list->next = old;
}

void mem_pool_destroy(MemoryPool* pool){

}