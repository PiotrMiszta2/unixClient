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
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/
static_assert(sizeof(MessageMicroRejS) ==       \
                sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t),
                "MessageMicroCfmS padded");
/* Global Function Definitions ****************************************************************************************/
MessageMicroRejS* message_micro_rej_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType)
{
    MessageMicroRejS* message = calloc(1, sizeof(MessageMicroRejS));
    assert(message);
    message->request = (uint16_t)(type);
    message->micro = (uint8_t)(microType);
    message->confirm = MESSAGE_MICRO_REJ_CONFIRM_VALUE;
    return message;
}
bool message_micro_rej_check_value(const MessageMicroRejS* restrict msg)
{
    bool ret = false;
    if(msg -> confirm == MESSAGE_MICRO_REJ_CONFIRM_VALUE)
    {
        ret = true;
    }

    return ret;

}

void message_micro_rej_free(MessageMicroRejS* msg)
{
    free(msg);
}
/* Static Function Definitions ****************************************************************************************/
