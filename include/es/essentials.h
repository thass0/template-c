#pragma once

#ifndef __ES_ESSENTIALS_H__
#define __ES_ESSENTIALS_H__

#ifndef __GNUC__
#error "ES requires GCC for non-standard macros and extensions"
#endif

/* Fundamental types */

typedef unsigned char byte;
typedef __UINT8_TYPE__ u8;
typedef __UINT16_TYPE__ u16;
typedef __UINT32_TYPE__ u32;
typedef __UINT64_TYPE__ u64;
typedef __INT8_TYPE__ i8;
typedef __INT16_TYPE__ i16;
typedef __INT32_TYPE__ i32;
typedef __INT64_TYPE__ i64;
typedef __INTPTR_TYPE__ ptr;
typedef __UINTPTR_TYPE__ uptr;
typedef __PTRDIFF_TYPE__ sz;
#define SZ_WIDTH __SIZEOF_PTRDIFF_T__
typedef __SIZE_TYPE__ usz;
#if __SIZEOF_FLOAT__ == 4
typedef float f32;
#endif
#if __SIZEOF_DOUBLE__ == 8
typedef double f64;
#endif
typedef int BOOL;

#define SZ_MAX __PTRDIFF_MAX__

/* Fundamental macros */

#define sizeof(x) ((sz)sizeof(x))
#define alignof(x) ((sz)__alignof__(x))
#define array_size(x) (sizeof(x) / sizeof(x[0]))
#define NULL ((void *)0)
#define FALSE 0
#define TRUE 1
#define STRINGIFY(x) #x
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Compiler attributes */

#define __printf(str_idx, first_arg_idx) \
    __attribute__((format(printf, str_idx, first_arg_idx)))
#define __used __attribute__((used))
#define __section(s) __attribute__((section(s)))
#define __align(a) __attribute__((aligned(a)))
#define __no_sanitize_address __attribute__((no_sanitize_address))

#endif /* __ES_ESSENTIALS_H__ */
