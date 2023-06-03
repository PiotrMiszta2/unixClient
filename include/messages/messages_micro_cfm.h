#ifndef RASPBERRY_MESSAGES_MICRO_CFM_H
#define RASPBERRY_MESSAGES_MICRO_CFM_H
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
#include "messages_types.h"
#include "messages_micro.h"
#include <stdint.h>
#include <stdbool.h>
/* Definitions ********************************************************************************************************/
#define message_create_micro_cfm_create(msg)           ( message_create(MESSAGE_TYPE_CFM, msg, sizeof(MessageMicroCfmS)) )
#define message_micro_cfm_get_payload(msg)             ( (MessageMicroCfmS*) (message_get_payload(msg)) )
/* Type Declarations **************************************************************************************************/
typedef struct MessageMicroCfmS
{
    uint16_t request;
    uint8_t micro;
    uint8_t confirm;
}MessageMicroCfmS;

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageMicroCfmS* message_micro_cfm_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType);
bool message_micro_cfm_check_value(const MessageMicroCfmS* restrict msg);
void message_micro_cfm_free(MessageMicroCfmS* msg);
#endif //RASPBERRY_MESSAGES_MICRO_CFM_H
