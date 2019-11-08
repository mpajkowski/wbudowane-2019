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

static void printTrace(const char* file, int line, int level, const char* trace, ...)
{
    static char outBuf[TRACE_BUF_SIZE];
    static char* formatBuf = outBuf + TRACE_BUF_SIZE / 2;

    if (level >= TRACE_LEVEL) {
        va_list args;
        va_start(args, trace);
        vsnprintf(formatBuf, TRACE_BUF_SIZE, trace, args);
        va_end(args);

        snprintf(outBuf,
                 TRACE_BUF_SIZE,
                 "%s:%d\t[%s]\t%s\r\n",
                 file,
                 line,
                 traceLevelStr[level],
                 formatBuf);

        serialPuts(outBuf);
    }
}

#define TRACE_DEBUG(...) printTrace(__FILE__, __LINE__, TRACE_DEBUG, __VA_ARGS__)
#define TRACE_INFO(...) printTrace(__FILE__, __LINE__, TRACE_INFO, __VA_ARGS__)
#define TRACE_WARNING(...) printTrace(__FILE__, __LINE__, TRACE_WARNING, __VA_ARGS__)
#define TRACE_ERROR(...) printTrace(__FILE__, __LINE__, TRACE_ERROR, __VA_ARGS__)

#endif