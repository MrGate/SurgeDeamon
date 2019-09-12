#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#include "util/logger.h"
#include "util/toolbox.h"


void logger_init(struct logger_t *logger)
{
    if(!logger)
        return;

    logger->logLevel = LL_Error;
    logger->logHandle = -1;
    logger->spinlock = 0;

    memset(logger->buffer, 0, sizeof(logger->buffer));
    memset(logger->finalBuffer, 0, sizeof(logger->finalBuffer));
}

void writeLog(struct logger_t *logger, enum LogLevels level, char *fmt, ...)
{
    if(!logger)
        return;

    if(logger->logLevel <= LL_None)
        return;

    if(level > logger->logLevel)
        return;

    // enter custom spinlock to prevent crashes
    cSpinLock();

    va_list args;
    va_start(args, fmt);
    vsnprintf(logger->buffer, sizeof(logger->buffer), fmt, args);
    va_end(args);

    const char *levelString = "None";
    const char *levelColor = KNRM;

    switch(level)
    {
        case LL_Info:
            levelString = "Info";
            levelColor = KGRN;
        break;
        case LL_Warn:
            levelString = "Warn";
            levelColor = KYEL;
        break;
        case LL_Error:
            levelString = "Error";
            levelColor = KRED;
        break;
        case LL_Debug:
            levelString = "Debug";
            levelColor = KMAG;
        break;
        case LL_None:
        default:
            levelString = "None";
            levelColor = KNRM;
        break;
    }

    // Detect if colors are supported

    if(COLOR_SUPPORT == 1)
    {
        snprintf(logger->finalBuffer, sizeof(logger->finalBuffer), "%s[%s] %s %s\n", levelColor, levelString, logger->buffer, KNRM);
    }
    else
    {
        snprintf(logger->finalBuffer, sizeof(logger->finalBuffer), "[%s] %s\n", levelString, logger->buffer);
    }

     // with %s so the compiler don't complain during cross compiles
    printf("%s", logger->finalBuffer);
    // exit custom spinlock
    cSpinUnlock();
}

void writeFunctionLog(struct logger_t *logger, enum LogLevels level, char *function, int line, const char *fmt, ...)
{
    if(!logger)
        return;

    if(logger->logLevel <= LL_None)
        return;

    if(level > logger->logLevel)
        return;

    // enter custom spinlock to prevent crashes
    cSpinLock();

    va_list args;
    va_start(args, fmt);
    vsnprintf(logger->buffer, sizeof(logger->buffer), fmt, args);
    va_end(args);

    const char *levelString = "None";
    const char *levelColor = KNRM;

    switch(level)
    {
        case LL_Info:
            levelString = "Info";
            levelColor = KGRN;
        break;
        case LL_Warn:
            levelString = "Warn";
            levelColor = KYEL;
        break;
        case LL_Error:
            levelString = "Error";
            levelColor = KRED;
        break;
        case LL_Debug:
            levelString = "Debug";
            levelColor = KMAG;
        break;
        case LL_None:
        default:
            levelString = "None";
            levelColor = KNRM;
        break;
    }

    // Detect if colors are supported

    if(COLOR_SUPPORT == 1)
    {
        snprintf(logger->finalBuffer, sizeof(logger->finalBuffer), "%s[%s] %s:%d - %s %s\n", levelColor, levelString, function, line, logger->buffer, KNRM);
    }
    else
    {
        snprintf(logger->finalBuffer, sizeof(logger->finalBuffer), "[%s] %s:%d - %s\n", levelString, function, line, logger->buffer);
    }

     // with %s so the compiler don't complain during cross compiles
    printf("%s", logger->finalBuffer);
    // exit custom spinlock
    cSpinUnlock();
}

