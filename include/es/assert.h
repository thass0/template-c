#pragma once

#ifndef __ES_ASSERT_H__
#define __ES_ASSERT_H__

#include <es/essentials.h>

void __assert(const char *expr, const char *file, const char *line);

#define _assert(x, str_of_x, file, line) \
    do {\
        if (!(x)) {\
            __assert(str_of_x, file, STRINGIFY(line));\
        }\
    } while (0);

#define assert(x) _assert((x), #x, __BASE_FILE__, __LINE__)

#endif /* __ES_ASSERT_H__ */
