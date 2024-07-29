#include <es/assert.h>

#include <stdio.h>
#include <stdlib.h>

void __assert(const char *expr, const char *file, const char *line)
{
    fprintf(stderr, "%s:%s: Assertion failed '%s'\n",
            file ? file : "<missing file>",
            line ? line : "<missing line>",
            expr ? expr : "<missing expression>");
    exit(-1);
}
