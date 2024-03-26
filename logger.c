#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

void 
debug_log(int line, const char* file,enum LogLevel info,const char* fmt, ...)
{
    //Array of prefixes
    //Uses ANSI escape sequences for coloring.
    //Fun!
    const char* LOG_PREFIXES[] = {
        "\x1b[32m[INFO] %s:%d: %s\x1b[0m\n",
        "\x1b[1;31m[ERROR] %s:%d: %s\x1b[0m\n",
        "\x1b[1;33m[WARNING] %s:%d: %s\x1b[0m\n"
    };
    //Get prefix
    const char* prefix = LOG_PREFIXES[info];    
    char* logStr;

    //Get variadic arguments
    va_list ap;
    va_start(ap,fmt);

    vasprintf(&logStr,fmt,ap);
    va_end(ap);
    fprintf(stderr,prefix,file,line,logStr);
    free(logStr);
    
    
}