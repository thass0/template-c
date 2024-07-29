#pragma once

#ifndef __ES_DEBUG_H__
#define __ES_DEBUG_H__

#include <es/essentials.h>

void __es_debug(const char *fmt, const char *file,
                const char *line, ...) __printf(1, 4);

#define _es_debug(fmt, file, line, ...) \
    __es_debug(fmt, file, STRINGIFY(line), ##__VA_ARGS__)

#define es_debug(fmt, ...) \
    _es_debug(fmt, __BASE_FILE__, __LINE__, ##__VA_ARGS__)

void __es_crash(void);

#define es_crash(msg, ...) \
    do { \
        es_debug("CRASH: " msg, ##__VA_ARGS__); \
        __es_crash(); \
    } while (0)

#endif /* __ES_DEBUG_H__ */
