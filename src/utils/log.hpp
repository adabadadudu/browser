#ifndef LOG_HPP
#define LOG_HPP

#include <cstring>
#include <stdarg.h>
#include <stddef.h>
#include <string>
#include <cwctype>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

enum
{
    DEBUG,
    INFO,
    ERROR,
    WARNING
};

void __log(int level, const char *file, int line, const char *format, ...);

#define log(level, fmt, ...) __log(level, __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)

#endif
