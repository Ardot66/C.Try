#include <stdio.h>
#include <stdlib.h>
#include "Try.h"

int TestFunc1()
{
    Throw(ENOMEM, -1, "This is a test %d", 100);
}

int TestFunc()
{
    Try(TestFunc1(), -1);
    return 0;
}

int main(int argc, char **argv)
{
    Try(TestFunc(), 0, 
        if(errno == ENOMEM)
        {
            printf("Caught\n");
            ErrorCurrentPrint();
            ErrorCurrentClear();
            return 0;
        }
    );
}
