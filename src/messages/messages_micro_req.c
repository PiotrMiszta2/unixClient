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
#include "messages.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
static_assert(  sizeof(MessageMicroReqS) ==  \
                sizeof(uint16_t) + sizeof(uint8_t) * 2,
                "MessageMicroReqS padded");

MessageMicroReqS* message_micro_req_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType)
{
    MessageMicroReqS* msg = malloc(sizeof(MessageMicroReqS));
    assert(msg);
    msg->micro = (uint8_t)(microType);
    msg->request = (uint16_t)(type);
    msg->confirm = MESSAGE_MICRO_REQ_CONFIRM_VALUE;
    return msg;
}
bool message_micro_req_check_value(const MessageMicroReqS* restrict msg)
{
    bool ret = false;
    if(msg->confirm == MESSAGE_MICRO_CFM_CONFIRM_VALUE)
    {
        ret = true;
    }
    return ret;
}

void message_micro_req_free(MessageMicroReqS* msg)
{
    free(msg);
}
/* Static Function Definitions ****************************************************************************************/
