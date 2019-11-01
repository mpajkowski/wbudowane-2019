#ifndef _TRACE_H
#define _TRACE_H

#include "serial.h"
#include "stdarg.h"
#include "string.h"

enum TraceLevel
{
    TRACE_DEBUG = 0,
    TRACE_INFO,
    TRACE_WARNING,
    TRACE_ERROR,
};

static char* traceLevelStr[] = { "TRACE_DEBUG", "TRACE_INFO", "TRACE_WARNING", "TRACE_ERROR" };

#ifndef TRACE_LEVEL
#define TRACE_LEVEL TRACE_DEBUG
#endif

#ifndef TRACE_BUF_SIZE
#define TRACE_BUF_SIZE 100
#endif

static inline void printTrace(const char* file, int line, int level, const char* trace, ...)
{
    static char buf[TRACE_BUF_SIZE];

    if (level >= TRACE_LEVEL) {

        va_list args;
        va_start(args, trace);

        snprintf(
          buf, TRACE_BUF_SIZE, "%s:%d\t[%s]\t%s\r\n", file, line, traceLevelStr[level], trace);
        vsnprintf(buf, TRACE_BUF_SIZE, buf, args);

        va_end(args);

        serialPuts(buf);
    }
}

#define TRACE_DEBUG(STR, args...) printTrace(__FILE__, __LINE__, TRACE_DEBUG, STR, ##args)
#define TRACE_INFO(STR, args...) printTrace(__FILE__, __LINE__, TRACE_INFO, STR, ##args)
#define TRACE_WARNING(STR, args...) printTrace(__FILE__, __LINE__, TRACE_WARNING, STR, ##args)
#define TRACE_ERROR(STR, args...) printTrace(__FILE__, __LINE__, TRACE_ERROR, STR, ##args)

#endif