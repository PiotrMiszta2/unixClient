#ifndef RASPBERRY_MESSAGES_MICRO_H
#define RASPBERRY_MESSAGES_MICRO_H
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
#include "util.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/
#define MESSAGE_MICRO_REQ_CONFIRM_VALUE     (98)
#define MESSAGE_MICRO_REJ_CONFIRM_VALUE     (99)
#define MESSAGE_MICRO_CFM_CONFIRM_VALUE     (100)

/* Type Declarations **************************************************************************************************/
typedef enum MessageMicroReqTypeE
{
    //TODO:think about it
    MESSAGE_MICRO_REQ_TYPE_LD1,
    MESSAGE_MICRO_REQ_TYPE_LD2,

}MessageMicroReqTypeE;
typedef enum MessageMicroReqMicroTypeE
{
    MESSAGE_MICRO_REQ_MICRO_TYPE_STM32,
    MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO,
}MessageMicroReqMicroTypeE;

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/

#endif //RASPBERRY_MESSAGES_MICRO_H
