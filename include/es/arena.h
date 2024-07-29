#pragma once

#ifndef __ES_ARENA_H__
#define __ES_ARENA_H__

#include <es/essentials.h>
#include <es/assert.h>
#include <es/debug.h>

struct es_arena {
    byte *beg;
    byte *end;
};

/**
 * Create a new arena. It uses `buf` as its source of memory. buf is assumed
 * to have a capacity of `buf_cap` bytes.
 */
static inline struct es_arena es_arena_new(void *buf, sz buf_cap)
{
    struct es_arena arn;

    assert(buf);

    arn.beg = buf;
    arn.end = arn.beg + buf_cap;

    return arn;
}

static inline void *es_arena_alloc_aligned(struct es_arena *arn, sz n_bytes,
                                           sz align)
{
    assert(arn);

    /* Code adapted from "Arena allocator tips and tricks" by Chris Wellons,
     * https://nullprogram.com/blog/2023/09/27/
     */

    sz padding = -(uptr)arn->beg & (align - 1);
    sz available = arn->end - arn->beg - padding;
    if (available < 0 || n_bytes > available)
        es_crash("Out of memory\n");
    void *p = arn->beg + padding;
    arn->beg += padding + n_bytes;
    return p;
}

/**
 * Allocate `n_bytes` out of the arena. Crashes if the arena doesn't have
 * enough space. Never returns NULL. The returned bytes are always zeroed.
 */
static inline void *es_arena_alloc(struct es_arena *arn, sz n_bytes)
{
    return es_arena_alloc_aligned(arn, n_bytes, alignof(void *));
}

/**
 * Alloactes `n * size` bytes of of the arena. Will return `NULL` if the
 * arguments overflow the multiplication.
 */
static inline void *es_arena_alloc_array(struct es_arena *arn, sz n, sz size)
{
    /* Overflow check based on "calloc when multiply overflows" by David Jones:
     * https://drj11.wordpress.com/2008/06/04/calloc-when-multiply-overflows/
     */

#if SZ_WIDTH == 4
    if (((n > 65535) || (size > 65535)) && SZ_MAX / n < size)
        return NULL;
#elif SZ_WIDTH == 8
    if (((n > 4294967295) || (size > 4294967295)) && SZ_MAX / n < size)
        return NULL;
#else
#error "Unsupported width of sz"
#endif
    return es_arena_alloc_aligned(arn, n * size, alignof(void *));
}

#endif /* __ES_ARENA_H__ */
