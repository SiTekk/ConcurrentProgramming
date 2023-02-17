#include "MemoryManager.h"

#include <stdio.h>
#include <stdlib.h>

void Create(T_Handler* pHandler)
{
    *pHandler = (T_Handler)malloc(sizeof(struct T_Node));

    if (*pHandler != NULL)
    {
        (*pHandler)->start = 0;
        (*pHandler)->end   = MAX_MEMORY;
        (*pHandler)->pNext = NULL;

        return;
    }

    printf("Malloc failed, exiting Program.");

    exit(-1);
}

void Destroy(T_Handler* handler)
{
    while (*handler)
    {
        T_Handler iterator = *handler;
        T_Handler previous = NULL;

        while (iterator->pNext)
        {
            previous = iterator;
            iterator = iterator->pNext;
        }

        if (previous)
            previous->pNext = NULL;
        else
            *handler = NULL;

        free(iterator);
    }
}

unsigned int Allocate(T_Handler* pHandler, unsigned int size, unsigned int* address)
{
    T_Handler iterator = *pHandler;
    T_Handler previous = NULL;

    if (size > MAX_MEMORY + 1)
        return 0;

    while (iterator && iterator->end + 1 - iterator->start < size)
    {
        previous = iterator;
        iterator = iterator->pNext;
    }

    if (iterator == NULL) // No free space
        return 0;

    if (iterator->end - iterator->start + 1 == size) // If the free size is fully occupied we have to delte the block
    {
        if (previous) // If previous is NULL we have to update the handler to point to the new first element
            previous->pNext = iterator->pNext;
        else
            *pHandler = iterator->pNext;

        *address = iterator->start;
        free(iterator);

        return 1;
    }
    else
    {
        *address = iterator->start;
        iterator->start += size;
        return 1;
    }
}

void Deallocate(T_Handler* pHandler, unsigned int size, unsigned int address)
{
    T_Handler iterator = *pHandler;
    T_Handler previous = NULL;

    if (address + size - 1 > MAX_MEMORY)
        return;

    if (*pHandler == NULL) // Edge Case if all space is used
    {
        *pHandler = (T_Handler)malloc(sizeof(struct T_Node));

        if (*pHandler)
        {
            (*pHandler)->start = address;
            (*pHandler)->end = address + size - 1;
            (*pHandler)->pNext = NULL;
        }

        return;
    }

    while (iterator != NULL)
    {
        if (iterator->start > address) //1st case: address is smaller than iterator
        {
            if (address + size == iterator->start)
            {
                iterator->start = address;
                return;
            }
            else if (previous == NULL)
            {
                (*pHandler) = (T_Handler)malloc(sizeof(struct T_Node));
                
                if (*pHandler)
                {
                    (*pHandler)->start = address;
                    (*pHandler)->end   = address + size - 1;
                    (*pHandler)->pNext = iterator;
                }
                return;
            }
            else if (previous->end + 1 == address)
            {
                previous->end += size;
                return;
            }
            else
            {
                T_Handler insertNode = (T_Handler)malloc(sizeof(struct T_Node));

                if (insertNode != NULL)
                {
                    insertNode->start = address;
                    insertNode->end   = address + size - 1;
                    insertNode->pNext = iterator;

                    previous->pNext   = insertNode;
                }

                return;
            }
        }
        else if (iterator->pNext == NULL) //  2nd case, if it is in the last spot
        {
            if (iterator->end + 1 == address)
            {
                iterator->end += size;
                return;
            }
            else
            {
                T_Handler newNode = (T_Handler)malloc(sizeof(struct T_Node));

                if (newNode != NULL)
                {
                    newNode->start = address;
                    newNode->end   = address + size - 1;
                    newNode->pNext = NULL;

                    iterator->pNext = NULL;

                    return;
                }
            }
        }

        previous = iterator;
        iterator = iterator->pNext;
    }
}

void Show(T_Handler handler)
{
    printf("\nHandlers:\n\n");
    for (; handler; handler = handler->pNext)
    {
        printf("Start:\t%d\n", handler->start);
        printf("End:\t%d\n", handler->end);
    }
    printf("\n");
}
