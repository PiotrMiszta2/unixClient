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
#include <stdbool.h>
/* Definitions ********************************************************************************************************/
#define MESSAGES_MAX_LENGHT     (1024)
#define MESSAGES_SEP_LENGHT     (2)
#define MESSAGES_PAY_LENGHT     (MESSAGES_MAX_LENGHT - ( MESSAGES_SEP_LENGHT + sizeof(MessageHeaderS)))
/* Type Declarations **************************************************************************************************/
typedef struct MessageHeaderS
{
    uint32_t payloadSize;
    uint8_t check;   //should be always 1, 0 for sending checking data
    uint8_t type;    //CAST MessageTypeE to uint8_t
    uint8_t _padded[2];
}MessageHeaderS;
static_assert(  sizeof(MessageHeaderS) == \
                sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(char[2]),
                "MessageHeaderS padded");

typedef struct MessageS
{
    MessageHeaderS header;
    void* payload;
}MessageS;
static_assert(  sizeof(MessageS) == \
                sizeof(MessageHeaderS) + sizeof(void*),
                "MessageHeaderS padded");
/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
MessageS* message_create(MessageTypeE type, void* restrict payload, size_t sizePayload)
{
    MessageS* msg = malloc(sizeof(MessageS));
    assert(msg);
    msg->header.check = UINT8_MAX;
    msg->header.type = (uint8_t)(type);
    msg->header._padded[0] = UINT8_MAX;
    msg->header._padded[1] = UINT8_MAX;
    if(sizePayload > (MESSAGES_PAY_LENGHT))
    {
        LOG_ERROR("payload is too much");
        return NULL;
    }
    msg->header.payloadSize = (uint16_t)sizePayload;
    msg->payload = payload;
    return msg;
}
MessageTypeE message_get_type(const MessageS* restrict msg)
{
    if(msg)
    {
        return (MessageTypeE)(msg->header.type);
    }
    else
    {
        return MESSAGE_TYPE_NUL;
    }
}

void* message_get_payload(const MessageS* restrict msg)
{
    return msg->payload;
}

size_t message_get_size_payload(const MessageS* restrict msg)
{
    return msg->header.payloadSize;
}

MessageCharS* message_create_char(const MessageS* restrict msg)
{
    if(!msg)
    {
        LOG_ERROR("Msg is null pointer");
        return NULL;
    }
    else
    {
        if( msg->payload == NULL && msg->header.payloadSize != 0 )
        {
            LOG_ERROR("Msg payload is null pointer and payload size is not 0");
            return NULL;
        }
    }
    MessageCharS* ret2 = malloc(sizeof(MessageCharS));
    size_t size = sizeof(MessageHeaderS) + msg->header.payloadSize + MESSAGES_SEP_LENGHT;
    char* ret = malloc(size);
    assert(ret);
    memcpy(ret, &msg->header, sizeof(MessageHeaderS));
    size_t index = sizeof(MessageHeaderS);
    ret[index] = 2;
    index ++;
    memcpy(&ret[index], msg->payload, msg->header.payloadSize);
    index += msg->header.payloadSize;
    ret[index] = '\0';
    ret2->msg = ret;
    ret2->len = size;
    return ret2;
}

MessageS* message_create_from_char(const char* msg)
{
    MessageS* ret = malloc(sizeof(MessageS));
    assert(ret);
    memcpy(&ret->header, msg, sizeof(MessageHeaderS));
    size_t index = sizeof(MessageHeaderS);
    void* payload = malloc(ret->header.payloadSize);
    assert(payload);
    if(msg[index] != 2)
    {
        LOG_ERROR("Msg separator is wrong value %c", msg[index]);
        LOG_ERROR("Message is: %s", msg);
    }

    index++;
    memcpy(payload, &msg[index], ret->header.payloadSize);
    index += ret->header.payloadSize;
    ret->payload = payload;
    return ret;
}

bool message_check(const MessageS* restrict msg)
{
    bool ret = false;
    if(msg)
    {
        if( msg->header.check == UINT8_MAX &&
            msg->header._padded[0] == UINT8_MAX &&
            msg->header._padded[1] == UINT8_MAX )
        {
            ret = true;
        }
    }
    return ret;

}

void message_free(MessageS* restrict msg)
{
    if(msg)
    {
        free(msg->payload);
        msg->payload = NULL;
    }
    free(msg);

}
/* Static Function Definitions ****************************************************************************************/
