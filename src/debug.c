
#include	<stdarg.h>
#include    <stdio.h>
#include    "debug.h"

void trace(char *str, ...)
{
#ifdef TRACE
    va_list ap;
    va_start(ap, str);
    vprintf(str, ap);
    putchar('\n');
    va_end(ap);
#endif
}
