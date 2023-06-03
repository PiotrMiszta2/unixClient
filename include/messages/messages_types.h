#ifndef RASPBERRY_MESSAGES_TYPES_H
#define RASPBERRY_MESSAGES_TYPES_H
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
#include "util.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef enum MessageTypeE
{
    MESSAGE_TYPE_NUL,
    MESSAGE_TYPE_REQ,
    MESSAGE_TYPE_CFM,
    MESSAGE_TYPE_REJ,

}MessageTypeE;

typedef struct MessageHeaderS MessageHeaderS;

typedef struct MessageS MessageS;

typedef struct MessageCharS
{
    char* msg;
    int len;
}MessageCharS;
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageS* message_create(MessageTypeE type, void* restrict payload, size_t sizePayload);
MessageTypeE message_get_type(const MessageS* restrict msg);
void* message_get_payload(const MessageS* restrict msg);
size_t message_get_size_payload(const MessageS* restrict msg);
MessageCharS* message_create_char(const MessageS* restrict msg);
MessageS* message_create_from_char(const char* restrict msg);
bool message_check(const MessageS* restrict msg);
void message_free(MessageS* restrict msg);


#endif //RASPBERRY_MESSAGES_TYPES_H
