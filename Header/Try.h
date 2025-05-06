#ifndef ___TRY___
#define ___TRY___

#include <stdint.h>

typedef struct StackLocation
{
    const char *File;
    const char *Function;
    size_t Line;
} StackLocation;

extern void (*OnException)();

extern const size_t StackTraceMax;
extern StackLocation StackTrace[20];
extern size_t StackTraceCount;

void ExceptionOccurred(const char *file, const char *functionName, size_t line);
void ClearStackTrace();
void PrintStackTrace();
void PrintStackLocation(const StackLocation *stackLocation);

#define Try(statement, returnValue, ...) \
    do \
    {\
        if(statement) \
        {\
            ExceptionOccurred(__FILE__, __func__, __LINE__);\
            switch(errno) \
            {\
                default: \
                {\
                    return returnValue;\
                }\
                __VA_ARGS__ \
            }\
        }\
    } while (0)

#define Catch(error) case error:

#endif