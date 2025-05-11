#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Try.h"

__thread ErrorInfo ErrorCurrent;

ErrorInfo ErrorInfoInit(int error, const char *file, const char *function, size_t line, char *message, ...)
{
    errno = error;
    ErrorInfo errorInfo = {.File = file, function, line};
    va_list args;
    va_start(args, message);
    vsnprintf(errorInfo.Message, 255, message, args);
    return errorInfo;
}

void ErrorInfoPrint(const ErrorInfo *errorInfo)
{
    printf("%s: %s at %s - %s() - Line %zu\n", strerror(errno), errorInfo->Message, errorInfo->File, errorInfo->Function, errorInfo->Line);
}