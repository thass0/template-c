#pragma once

#ifndef __ES_POOL_H__
#define __ES_POOL_H__

#include <es/essentials.h>
#include <es/assert.h>

struct es_pool {
    ptr *head; /* First block in the list */
    sz size; /* Size of each block */
};

/**
 * Create a new pool. It uses `buf` as its source of memory. `buf` is assumed
 * to have a capacity of `buf_cap` bytes. Each block in the pool will have a
 * size of `block_size` bytes. The minimum block size is
 * `MAX(sizeof(ptr), alignof(void *))`.
 */
static inline struct es_pool es_pool_new(void *buf, sz buf_cap, sz block_size)
{
    struct es_pool pool = { .head = NULL, .size = 0 };
    sz align = MAX(sizeof(ptr), alignof(void *));
    sz n_blocks = 0;
    sz i = 0;
    ptr *block = NULL;

    assert(buf);

    block_size = (block_size + align - 1) & ~(align - 1);
    n_blocks = buf_cap / block_size;
    pool.size = block_size;

    /* Link all the blocks that are available */
    for (i = 0; i < n_blocks * block_size; i += block_size) {
        block = (ptr *)((byte *)buf + i);
        *block = (ptr)pool.head;
        pool.head = block;
    }

    return pool;
}

/**
 * Allocate a block from the pool. Returns `NULL` if the pool is empty.
 */
static inline void *es_pool_alloc(struct es_pool *pool)
{
    ptr *block = NULL;

    assert(pool);

    if (!pool->head)
        return NULL;

    block = pool->head;
    pool->head = (ptr *)*block;
    return block;
}

/**
 * Free a block back to the pool.
 */
static inline void es_pool_free(struct es_pool *pool, void *block)
{
    assert(pool);
    assert(block);

    *(ptr *)block = (ptr)pool->head;
    pool->head = block;
}

#endif /* __ES_POOL_H__ */
