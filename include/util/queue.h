#ifndef RASPBERRY_QUEUE_H
#define RASPBERRY_QUEUE_H
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
#include <stdbool.h>
#include <stdio.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
/**
 * @struct Queue
 * @brief struct Queue is type for queue
 *
*/
typedef struct Queue Queue;
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
/**
 * @brief function create queue
 *
 * @param fun_to_free pointer to function to free element of queue
 * @return pointer to allocated queue
*/
Queue* queue_create(void (*fun_to_free)(void*));
/**
 * @brief free all element in queue
 *
 * @param que pointer to Queue to dealloc
*/
void queue_destroy(Queue* que);
/**
 * @brief add to end of queue one element
 *
 * @param que pointer to Queue
 * @param data pointer to data to push back in queue
*/
void queue_push_back(Queue* que, void* data);
/**
 * @brief remove first element in queue
 *
 * @param que pointer to Queue
 * @return first element of queue
*/
void* queue_pop(Queue* que);
/**
 * @brief check queue is empty
 *
 * @param que pointer to Queue
 * @return true if que is empty and false if not empty
*/
bool queue_empty(Queue* que);
/**
 * @brief returning size of que
 *
 * @param que pointer to Queue
 * @return size_t number of elements in queue
*/
size_t queue_get_size(Queue* que);
size_t queue_sizeof(void);

#endif //RASPBERRY_QUEUE_H
