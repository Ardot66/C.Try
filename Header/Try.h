#ifndef ___TRY___
#define ___TRY___

#include <stdint.h>
#include <errno.h>

typedef struct ErrorInfo
{
    char Message[256];
    const char *File;
    const char *Function;
    size_t Line;
} ErrorInfo;

extern __thread ErrorInfo ErrorCurrent;

ErrorInfo ErrorInfoInit(int error, const char *file, const char *function, size_t line, char *message, ...);
void ErrorInfoPrint(const ErrorInfo *errorInfo);

#define Throw(error, returnValue, message, ...) \
    do \
    {\
        ErrorCurrent = ErrorInfoInit(error, __FILE__, __func__, __LINE__, message, ## __VA_ARGS__);\
        return returnValue;\
    } while (0)

#define Try(statement, returnValue, ...) \
    do \
    {\
        if(statement) \
        {\
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