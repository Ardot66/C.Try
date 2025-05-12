#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "Try.h"

__thread ErrorInfo ErrorCurrent = {.Message = NULL};

ErrorInfo ErrorInfoInit(int error, const char *file, const char *function, size_t line, char *message, ...)
{
    errno = error;

    ErrorInfoClear(&ErrorCurrent);
    
    va_list args;
    va_start(args, message);
    
    size_t messageLength = vsnprintf(NULL, 0, message, args) + 1;
    ErrorInfo errorInfo = {.File = file, .Function = function, .Line = line};
    errorInfo.Message = malloc(messageLength + 1);
    if(errorInfo.Message != NULL)
        vsnprintf(errorInfo.Message, messageLength, message, args);
    else
        errorInfo.Message = "Insufficient memory to allocate error message";
    return errorInfo;
}

void ErrorCurrentPrint() {ErrorInfoPrint(&ErrorCurrent);}

void ErrorInfoPrint(const ErrorInfo *errorInfo)
{
    printf("%s: %s at %s - %s() - Line %zu\n", strerror(errno), errorInfo->Message, errorInfo->File, errorInfo->Function, errorInfo->Line);
}

void ErrorCurrentClear() {ErrorInfoClear(&ErrorCurrent);}

void ErrorInfoClear(ErrorInfo *errorInfo)
{   
    free(errorInfo->Message);
    *errorInfo = (ErrorInfo){NULL, "", "", 0};
}