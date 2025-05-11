#ifndef ___TRY___
#define ___TRY___

#include <stdint.h>

typedef struct ErrorInfo
{
    const char *Message;
    const char *File;
    const char *Function;
    size_t Line;
} ErrorInfo;

extern ErrorInfo ErrorCurrent;

void ErrorInfoPrint(const ErrorInfo *errorInfo);

#define Throw(error, message, returnValue) \
    do \
    {\
        errno = error;\
        ErrorCurrent = (ErrorInfo){message, __FILE__, __func__, __LINE__};\
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