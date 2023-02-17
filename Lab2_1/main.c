#include <stdio.h>
#include <stdlib.h>
#include "MemoryManager.h"

int main()
{
    T_Handler handler = NULL;
    unsigned int result;
    unsigned int address;

    printf("The program has started.\n");

    Create(&handler);
    Show(handler);

    result = Allocate(&handler, 50, &address);
    if (result)
    {
        Show(handler);
        printf("Starting address is: %d\n", address);
    }
    else
    {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler, 20, address);
    Show(handler);


    Allocate(&handler, 25, &address, &result);
    if (result)
    {
        Show(handler);
        printf("Starting address is: %d\n", address);
    }
    else
    {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler, 10, 50);
    Show(handler);


    Allocate(&handler, 25, &address, &result);
    if (result)
    {
        Show(handler);
        printf("Starting address is: %d\n", address);
    }
    else
    {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler, 20, 75);
    Show(handler);

    Destroy(&handler);
    Show(handler);

    printf("End Of Program\n");

    return 0;
}
