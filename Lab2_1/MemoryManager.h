#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#define MAX_MEMORY 99

typedef struct T_Node* T_Handler;

typedef struct T_Node
{
    unsigned int start;
    unsigned int end;
    T_Handler pNext;
} ;

/* Creates the required structure to manage the available memory */
void Create(T_Handler* pHandler);

/* Frees the required structure */
void Destroy(T_Handler* pHandler);

/*
 * Returns in "address" the memory address where the required block of memory with length "size" starts.
 * If this operation finishes successfully then "result" holds a TRUE value; FALSE otherwise.
 */
unsigned int Allocate(T_Handler* pHandler, unsigned int size, unsigned int* address);

/*
 * Frees a block of memory with length "size" which starts at "ad" address.
 * If needed, can be assumed to be a previous allocated block
 */
void Deallocate(T_Handler* pHandler, unsigned int size, unsigned int address);

/* Shows the current status of the memory */
void Show(T_Handler handler);


#endif /* MEMORYMANAGER_H_ */
