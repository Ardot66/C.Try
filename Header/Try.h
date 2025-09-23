#ifndef ___TRY___
#define ___TRY___

#include <stdint.h>

typedef struct ErrorInfo
{
    char *Message;
    const char *File;
    const char *Function;
    size_t Line;
} ErrorInfo;

extern __thread ErrorInfo ErrorCurrent;

ErrorInfo ErrorInfoInit(int error, const char *file, const char *function, size_t line, const char *message, ...);
void ErrorInfoPrint(const ErrorInfo *errorInfo);
void ErrorCurrentPrint();
void ErrorInfoClear(ErrorInfo *errorInfo);
void ErrorCurrentClear();

#define ThrowDo(error, action, message, ...)\
    do \
    {\
        ErrorCurrent = ErrorInfoInit(error, __FILE__, __func__, __LINE__, message __VA_OPT__(,) __VA_ARGS__);\
        action\
    } while (0)

#define Throw(error, returnValue, message, ...) ThrowDo(error, return returnValue;, message, __VA_ARGS__)

#define TryDo(statement, ...)\
    do \
    {\
        if((statement)) \
        {\
            __VA_ARGS__ \
        }\
    } while (0)

#define TryNotNullDo(statement, ...) TryDo((statement) == NULL, __VA_ARGS__)
    
#define Try(statement, returnValue, ...) TryDo(statement, __VA_ARGS__ return returnValue;)

#define TryNotNull(statement, returnValue, ...) Try((statement) == NULL, returnValue, __VA_ARGS__)

#define AssertDoMsg(statement, error, action, message, ...) do { if((statement)) {ThrowDo(error, action, message, __VA_ARGS__);} } while(0)
#define AssertMsg(statement, error, returnValue, message, ...) AssertDoMsg(statement, error, return returnValue;, message, __VA_ARGS__)
#define AssertDo(statement, error, ...) AssertDoMsg(statement, error, __VA_ARGS__, "Assertion failed")
#define Assert(statement, error, returnValue, ...) AssertDoMsg(statement, error, __VA_ARGS__ return returnValue;, "Assertion failed")

#endif
