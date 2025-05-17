#ifndef ___TRY___
#define ___TRY___

#include <stdint.h>
#include <errno.h>

typedef struct ErrorInfo
{
    char *Message;
    const char *File;
    const char *Function;
    size_t Line;
} ErrorInfo;

extern __thread ErrorInfo ErrorCurrent;

ErrorInfo ErrorInfoInit(int error, const char *file, const char *function, size_t line, char *message, ...);
void ErrorInfoPrint(const ErrorInfo *errorInfo);
void ErrorCurrentPrint();
void ErrorInfoClear(ErrorInfo *errorInfo);
void ErrorCurrentClear();

#define ThrowDo(error, action, message, ...)\
    do \
    {\
        ErrorCurrent = ErrorInfoInit(error, __FILE__, __func__, __LINE__, message, ## __VA_ARGS__);\
        action\
    } while (0)

#define Throw(error, returnValue, message, ...) ThrowDo(error, return returnValue, message, __VA_ARGS__)

#define TryDo(statement, ...)\
    do \
    {\
        if(statement) \
        {\
            __VA_ARGS__ \
        }\
    } while (0)

#define Try(statement, returnValue, ...) TryDo(statement, __VA_ARGS__ return returnValue;)

#define TryNotNull(statement, returnValue, ...) Try((statement) == NULL, returnValue, __VA_ARGS__)

#endif