#ifndef RASPBERRY_DOUBLELINKEDLIST_H
#define RASPBERRY_DOUBLELINKEDLIST_H
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
#include <stdio.h>
#include <stdlib.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct DoubleLinkedList DoubleLinkedList;
typedef DoubleLinkedList DLL;
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
/**
 * @brief Constructor for double linked list
 * @param custom_free function to free data passed into double linked list
 * @return returning pointer to doubly linked list
 ***************************************************************/
DoubleLinkedList* dll_create(void (*custom_free)(void* data),
                             int (*custom_cmp)(void* arg, void* arg2));
/**
 * @brief Destructor for double linked list
 * @param doubleLinkedList structure for deallocating
 */
void dll_destroy(DoubleLinkedList* doubleLinkedList);

/**
 * @brief dll_push_back() adding data to end of list
 * @param doubleLinkedList list where add data
 * @param data data to add
 */
void dll_push_back(DoubleLinkedList* doubleLinkedList, void* data);

/**
 * @brief dll_push_forward()
 * function adding data to start of list
 * @param doubleLinkedList list where add data
 * @param data data to add
 */
void dll_push_forward(DoubleLinkedList* doubleLinkedList, void* data);

/**
 * @brief Function returning data from last entry in list
 * @param doubleLinkedList Pointer to DoubleLinkedList
 * @return Returns data from node which was poped
 */
void* dll_pop_back(DoubleLinkedList* doubleLinkedList);

/**
 * @brief Function returning data from first entry in list
 * @param doubleLinkedList Pointer to DoubleLinkedList
 * @return Returns data from node which was poped
 */
void* dll_pop_forward(DoubleLinkedList* doubleLinkedList);

/**
 * @brief Function returning data from specified entry by index in list
 * @param doubleLinkedList Pointer to DoubleLinkedList
 * @param index size_t index for data to pop
 * @return Returns data from node which was poped
 */
//TODO: implement me
//void* dll_pop_index(DoubleLinkedList* doubleLinkedList, size_t index);

/**
 * @brief Deleting last element from list
 * @param doubleLinkedList Pointer to DoubleLinkedList
 */
int dll_find(DoubleLinkedList* doubleLinkedList, void* data);

/**
 * @brief Sorting data in list
 * @param doubleLinkedList Pointer to DoubleLinkedList
 * @return  index  on success
 *          -1 on fail
 */
size_t dll_get_size(DoubleLinkedList* doubleLinkedList);

#endif //RASPBERRY_DOUBLELINKEDLIST_H
