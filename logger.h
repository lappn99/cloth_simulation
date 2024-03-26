
#ifndef _CLOTHSIM_LOGGING_H
#define _CLOTHSIM_LOGGING_H
/*
    Little logging utility made for for fun
    Made by Nathan Lapp. March 2023
*/
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>

//Enum of different log levels, indicates indice into LOG_PREFIXES
enum LogLevel
{
    INFO,
    ERROR,
    WARNING
};




void debug_log(int line, const char* file,enum LogLevel level,const char* fmt,...);


//Helper macro to print out INFO logs
#define LOG_INFO(fmt,...) debug_log(__LINE__,__FILE__,INFO,fmt,__VA_ARGS__)
//Helper macro to print out ERROR logs
#define LOG_ERROR(fmt,...) debug_log(__LINE__,__FILE__,ERROR,fmt,__VA_ARGS__)
//Helper macro to print out WARNING logs
#define LOG_WARNING(fmt,...) debug_log(__LINE__,__FILE__,WARNING,fmt,__VA_ARGS__)
//Helper macro for assertions
#define ASSERT(expr,fmt,...) if(!expr){\
d_debug_log(__LINE__,__FILE__,ERROR,fmt,__VA_ARGS__);\
assert(expr);\
}
#endif