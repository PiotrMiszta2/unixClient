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
static_assert(sizeof(MessageMicroCfmS) ==       \
                sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t),
                "MessageMicroCfmS padded");
/* Global Function Definitions ****************************************************************************************/
MessageMicroCfmS* message_micro_cfm_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType)
{
    MessageMicroCfmS* message = calloc(1, sizeof(MessageMicroCfmS));
    assert(message);
    message->micro = (uint8_t)(microType);
    message->request = (uint16_t) type;
    message->confirm = MESSAGE_MICRO_CFM_CONFIRM_VALUE;
    return message;
}

bool message_micro_cfm_check_value(const MessageMicroCfmS* restrict msg)
{
    bool ret = false;
    if(msg->confirm == MESSAGE_MICRO_CFM_CONFIRM_VALUE)
    {
        ret = true;
    }
    return ret;
}

void message_micro_cfm_free(MessageMicroCfmS* msg)
{
    free(msg);
}
/* Static Function Definitions ****************************************************************************************/
