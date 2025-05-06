#include <stdio.h>
#include <stdlib.h>
#include "Try.h"

int TestFunc1()
{
    errno = ENOMEM;
    return -1;
}

int TestFunc()
{
    Try(TestFunc1(), -1);
}

int main(int argc, char **argv)
{
    Try(TestFunc(), 0, 
        Catch(ENOMEM)
        printf("Caught\n");
        PrintStackTrace();
        ClearStackTrace();
        return 0;
    );
}
