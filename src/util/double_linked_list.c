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
#include "double_linked_list.h"
#include "logger.h"
/* Type Declarations **************************************************************************************************/
typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct DoubleLinkedList{
    Node* head;
    Node* tail;
    size_t size;
    void (*dll_free)(void* arg);
    int (*dll_cmp)(void* arg, void* arg2);
}DoubleLinkedList;
/* Definitions ********************************************************************************************************/
#define DLL_LOG_NULL_DATA
#define DLL_EMPTY()         dll_list_empty(__FILE__, __func__, __LINE__)
/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/
static inline void dll_list_empty(const char* file, const char* func, int line);
static inline Node* dll_node_malloc(void);
/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
DoubleLinkedList* dll_create(void (*custom_free)(void* data),
                             int (*custom_cmp)(void* arg, void* arg2))
{
    DLL* dll = malloc(sizeof(*dll));
    if(dll)
    {
        dll->head = NULL;
        dll->tail = NULL;
        dll->size = 0;
        dll->dll_free = custom_free;
        dll->dll_cmp = custom_cmp;
    }
    return dll;
}

void dll_destroy(DoubleLinkedList* dll)
{
    if(!dll)
    {
        return;
    }
    else if(dll->head == NULL && dll->tail == NULL)
    {
        free(dll);
        return;
    }
    else
    {
        Node* head = dll->head;
        while(head->next != NULL)
        {
            Node* temp;
            temp = head->next;
            head->next = NULL;
            dll->dll_free(head->data);
            free(head);
            head = temp;
        }
        dll->dll_free(head->data);
        free(head);
        dll->head = NULL;
        dll->tail = NULL;
        dll->dll_free = NULL;
        free(dll);
    }

}

void dll_push_back(DoubleLinkedList* doubleLinkedList, void* data)
{
    if(!doubleLinkedList)
    {
        DLL_EMPTY();
        return;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * WARNING: IF DATA POINTER WILL BE NULL, FUNCTION WILL PUSH THIS DATA                           *
     * WARNING: REMEMBER WHEN CALLING FUNCTION DESTROY OR ERASE                                      *
     * IF MACRO DLL_LOG_NULL_DATA IS DEFINED THERE WILL BE GENERETED WARNING TO LOG FILE             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifdef DLL_LOG_NULL_DATA
    if(data == NULL)
    {
        LOG_WARNING("Data pointer is null pointer");
    }
#endif
    Node* head = doubleLinkedList->head;
    Node* tail = doubleLinkedList->tail;
    if((head == NULL && tail != NULL) || (tail == NULL && head != NULL))
    {
        LOG_FATAL("FATAL ERROR FOR TERMINATING DLL, Aborted");
        FFATAL("Fatal error in dll aborted");
        abort();
    }
    else if(head == NULL && tail == NULL)
    {
        Node* node = dll_node_malloc();
        if(node)
        {
            doubleLinkedList->head = node;
            doubleLinkedList->tail = node;
            doubleLinkedList->head->data = data;
            doubleLinkedList->size ++;
        }
        else
        {
            LOG_ERROR("Can't allocate memory for Node");
            FERROR("Can't allocate memory for Node");
        }
    }
    else
    {
        Node* node = dll_node_malloc();
        if(node)
        {
            tail->next = node;
            node->prev = tail;
            node->data = data;
            doubleLinkedList->tail = node;
            doubleLinkedList->size ++;
        }
        else
        {
            LOG_ERROR("Can't allocate memory for Node");
            FERROR("Can't allocate memory for Node");
        }
    }
}

void dll_push_forward(DoubleLinkedList* doubleLinkedList, void* data)
{
    if(!doubleLinkedList)
    {
        DLL_EMPTY();
        return;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * WARNING: IF DATA POINTER WILL BE NULL, FUNCTION WILL PUSH THIS DATA                           *
     * WARNING: REMEMBER WHEN CALLING FUNCTION DESTROY OR ERASE                                      *
     * IF MACRO DLL_LOG_NULL_DATA IS DEFINED THERE WILL BE GENERETED WARNING TO LOG FILE             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifdef DLL_LOG_NULL_DATA
    if(data == NULL)
    {
        LOG_WARNING("Data pointer is null pointer");
    }
#endif
    Node* head = doubleLinkedList->head;
    Node* tail = doubleLinkedList->tail;
    if((head == NULL && tail != NULL) || (tail == NULL && head != NULL)) // one can be null pointer
    {
        LOG_FATAL("FATAL ERROR FOR TERMINATING DLL, Aborted");
        FFATAL("Fatal error in dll aborted");
        abort();
    }
    else if(head == NULL && tail == NULL)       //First object
    {
        Node* node = dll_node_malloc();
        if(node)
        {
            doubleLinkedList->head = node;
            doubleLinkedList->tail = node;
            doubleLinkedList->head->data = data;
            doubleLinkedList->size ++;
        }
        else
        {
            LOG_ERROR("Can't allocate memory for Node");
            FERROR("Can't allocate memory for Node");
        }
    }
    else
    {
        Node* node = dll_node_malloc();
        if(node)
        {
            head->prev = node;
            node->next = head;
            node->data = data;
            doubleLinkedList->head = node;
            doubleLinkedList->size ++;
        }
        else
        {
            LOG_ERROR("Can't allocate memory for Node");
            FERROR("Can't allocate memory for Node");
        }
    }
}

void* dll_pop_back(DoubleLinkedList* doubleLinkedList)
{
    if(!doubleLinkedList)
    {
        DLL_EMPTY();
        return NULL;
    }
    if(doubleLinkedList->tail == doubleLinkedList->head)
    {
        void* ret = doubleLinkedList->tail->data;
        free(doubleLinkedList->tail);
        doubleLinkedList->tail = NULL;
        doubleLinkedList->head = NULL;
        return ret;
    }
    else
    {
        void* ret = doubleLinkedList->tail->data;
        Node* temp = doubleLinkedList->tail->prev;
        free(doubleLinkedList->tail);
        doubleLinkedList->tail = temp;
        temp->next = NULL;
        return ret;
    }
}

void* dll_pop_forward(DoubleLinkedList* doubleLinkedList)
{
    if(!doubleLinkedList)
    {
        DLL_EMPTY();
        return NULL;
    }
    if(doubleLinkedList->size == 0)
    {
        return NULL;
    }
    else if(doubleLinkedList->size == 1)
    {
        void* ret = doubleLinkedList->head->data;
        free(doubleLinkedList->head);
        doubleLinkedList->tail = NULL;
        doubleLinkedList->head = NULL;
        doubleLinkedList->size --;
        return ret;
    }
    else
    {
        void* ret = doubleLinkedList->head->data;
        Node* temp = doubleLinkedList->head->next;
        free(doubleLinkedList->head);
        doubleLinkedList->head = temp;
        temp->prev = NULL;
        doubleLinkedList->size --;
        return ret;
    }
}

/*void* dll_pop_index(DoubleLinkedList* doubleLinkedList, size_t index)
{
    return NULL;
}*/

int dll_find(DoubleLinkedList* doubleLinkedList, void* data)
{
    if(!doubleLinkedList)
    {
        DLL_EMPTY();
        return -1;
    }
    else if (doubleLinkedList->head == NULL)
    {
        return -1;
    }
    else
    {
        Node* temp = doubleLinkedList->head;
        int (*cmp)(void*, void*) = doubleLinkedList->dll_cmp;
        size_t index = 0;
        while(temp->next != NULL)
        {
            if( cmp(temp->data, data) == 0)
            {
                return (int)index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }
}

size_t dll_get_size(DoubleLinkedList* doubleLinkedList)
{
    return doubleLinkedList->size;
}
/* Static Function Definitions ****************************************************************************************/
// FUNCTION TO CALL logger log bcs a lot of checking that pointer to struct is NULL
void dll_list_empty(const char* file, const char* func, int line)
{
    logger_log(ERROR, file, func, line, "Data is null pointer, first call dll_create()");
    fprintf(stderr, "%s %s %d: Data is null pointer, first call dll_create()", file, func, line);
}

Node* dll_node_malloc(void)
{
    Node* node = malloc(sizeof(*node));
    if(node)
    {
        node->next = NULL;
        node->prev = NULL;
        node->data = NULL;
    }
    return node;
}
