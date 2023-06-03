/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file
 * @brief
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include "logger.h"
#include "queue.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
static void function_to_free_if_null(void* arg)
{
    (void)(arg);
}
typedef struct NodeS
{
    struct NodeS*    next;
    void*           data_p;
} NodeS;

typedef struct Queue{
    NodeS*          head; // Pointer to last poped object
    NodeS*          tail; //Pointer to last pushed object
    size_t          size;
    void (*fun)(void *);
}Queue;
/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
Queue* queue_create(void (*functionFree)(void*))
{
    Queue* que = malloc(sizeof(Queue));
    assert(que);
    que->head = NULL;
    que->tail = NULL;
    que->size = 0;
    if(functionFree == NULL)
        que->fun = function_to_free_if_null;
    else
        que->fun = functionFree;
    return que;
}
size_t queue_sizeof(void)
{
    return sizeof(Queue);
}
void queue_destroy(Queue* que)
{
    if(!que)
        return;
    if(queue_empty(que))
    {
        free(que);
        return;
    }
    else
    {
        while(que->head->next != NULL)
        {
            NodeS* temp = que->head->next;
            que->fun(que->head->data_p);
            que->head->data_p = NULL;
            free(que->head);
            que->head = NULL;
            que->head = temp;
        }
        que->fun(que->head->data_p);
        free(que->head);
        que->head = NULL;
        que->tail = NULL;
        free(que);
    }
}

void queue_push_back(Queue* que, void* data)
{
    NodeS* newNode = malloc(sizeof(NodeS));
    newNode->data_p = data;
    newNode->next = NULL;
    if(queue_empty(que))
    {
        que->head = newNode;
        que->tail = newNode;
    }
    else
    {
        que->tail->next = newNode;
        que->tail = newNode;
    }
    que->size++;
}

void* queue_pop(Queue* que)
{
    if(que)
    {
        NodeS* temp = que->head;
        que->head = que->head->next;
        void* ptr = temp->data_p;
        free(temp);
        que->size--;
        return ptr;
    }
    else
    {
        return NULL;
    }


}

bool queue_empty(Queue* que)
{
    if(!que)
    {
        return true;
    }
    else if(que->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t queue_get_size(Queue* que)
{
    return que->size;
}
/* Static Function Definitions ****************************************************************************************/
