#pragma once

// 0 = FULL
// 1 = MINI
// 2 = OFF
#define CONSOLE_DEBUG_MODE 0

// Logger Max Buffer Log Size
#define MAX_LOGSIZE 0x500
// If console support colors change to 1 if not 0
#define COLOR_SUPPORT 1

enum LogLevels
{
    LL_None,
    LL_Info,
    LL_Warn,
    LL_Error,
    LL_Debug,
    LL_All
};

#define KNRM "\x1b[0m"
#define KRED "\x1b[31m"
#define KGRN "\x1b[32m"
#define KYEL "\x1b[33m"
#define KBLU "\x1b[34m"
#define KMAG "\x1b[35m"
#define KCYN "\x1b[36m"
#define KWHT "\x1b[37m"



struct logger_t
{
    char *loggerName;
    enum LogLevels logLevel;
    char buffer[MAX_LOGSIZE];
    char finalBuffer[MAX_LOGSIZE];
    volatile int logHandle;
    int spinlock;
};


void logger_init(struct logger_t *logger);
void writeLog(struct logger_t *logger, enum LogLevels level, char *fmt, ...);
void writeFunctionLog(struct logger_t *logger, enum LogLevels level, char *function, int line, const char *fmt, ...);