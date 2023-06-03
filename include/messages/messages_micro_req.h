#ifndef RASPBERRY_MESSAGES_MICRO_REQ_H
#define RASPBERRY_MESSAGES_MICRO_REQ_H
/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file    messages_micro_req.h
 * @brief   file specify format of request action from microconroler: stm32 or arduino in our case
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include "messages_types.h"
#include "messages_micro.h"

#include <stdint.h>
#include <stdbool.h>
/* Definitions ********************************************************************************************************/
/**
 * @brief to wrap function
 *
*/
#define message_create_micro_req_create(msg)           ( message_create(MESSAGE_TYPE_REQ, msg, sizeof(MessageMicroReqS)) )
#define message_micro_req_get_payload(msg)             ( (MessageMicroReqS*) (message_get_payload(msg)) )
/* Type Declarations **************************************************************************************************/

typedef struct MessageMicroReqS
{
    uint16_t request;
    uint8_t micro;
    uint8_t confirm;
}MessageMicroReqS;
//for all messages type need to static_assert padding

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageMicroReqS* message_micro_req_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType);
bool message_micro_req_check_value(const MessageMicroReqS* restrict msg);
void message_micro_req_free(MessageMicroReqS* msg);
#endif //RASPBERRY_MESSAGES_REQ_MICRO_H
