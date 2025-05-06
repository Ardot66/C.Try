#include <stdio.h>
#include "Try.h"

void (*OnException)() = NULL;

const size_t StackTraceMax = 20;
StackLocation StackTrace[20];
size_t StackTraceCount = 0;

void ExceptionOccurred(const char *file, const char *functionName, size_t line)
{
    if(OnException != NULL)
        OnException();

    StackTrace[StackTraceCount] = (StackLocation){.File = file, .Function = functionName, .Line = line};
    StackTraceCount = StackTraceCount >= StackTraceMax ? StackTraceMax : StackTraceCount + 1;
}

void ClearStackTrace()
{
    StackTraceCount = 0;
}

void PrintStackTrace()
{
    for(int x = StackTraceCount - 1; x >= 0; x--)
        PrintStackLocation(StackTrace + x);
}

void PrintStackLocation(const StackLocation *stackLocation)
{
    printf("%s - %s() - Line %zu\n", stackLocation->File, stackLocation->Function, stackLocation->Line);
}