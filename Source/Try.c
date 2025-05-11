#include <stdio.h>
#include <string.h>
#include "Try.h"

ErrorInfo ErrorCurrent;

void ErrorInfoPrint(const ErrorInfo *errorInfo)
{
    printf("%s: %s at %s - %s() - Line %zu\n", strerror(errno), errorInfo->Message, errorInfo->File, errorInfo->Function, errorInfo->Line);
}