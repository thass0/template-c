#include <es/debug.h>
#include <es/essentials.h>
#include <es/assert.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BOLD    "\x1b[1m"

void __es_debug(const char *fmt, const char *file, const char *line, ...) {
    va_list args;
    const sz fmt_buf_size = 1024;
    char fmt_buf[fmt_buf_size];

    assert(fmt);
    assert(file);
    assert(line);

    va_start(args, line);

    vsnprintf(fmt_buf, fmt_buf_size, fmt, args);
    fprintf(stderr, ANSI_COLOR_BOLD "[%s:%s]" ANSI_COLOR_RESET " %s",
            file, line, fmt_buf);

    va_end(args);
}

void __es_crash(void)
{
    exit(-1);
}
