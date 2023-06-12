#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "messages.h"
#include "connection.h"
char temp[] =   "Unix client console version\n" \
                "-h HELP\n"   \
                "ld1 - zapala diode\n"
                "ld2 - gasi diode\n"
                "im1 - wyswietla zielone tlo\n"
                "im2 - wysiwetla biale tlo\n"
                "im3 - wyswietla czarne tlo\n"
                "gt  - wyswietla temperature\n";

static int parse_msg(void) {
    char buff[1024];
    while(1) {
        printf("$ ");
        scanf("%s", buff);
        if(strcmp(buff, "-h") == 0) {
            printf("%s", temp);
        }
        else if(strcmp(buff, "ld1") == 0) {
            return 0;
        }
        else if(strcmp(buff, "ld2") == 0) {
            return 1;
        }
        else if(strcmp(buff, "im1") == 0) {
            return 2;
        }
        else if(strcmp(buff, "im2") == 0) {
            return 3;
        }
        else if(strcmp(buff, "im3") == 0) {
            return 4;
        }
        else if(strcmp(buff, "gt") == 0) {
            return 5;
        }
        else if(strcmp(buff, "-q") == 0) {
            return -3;
        }
        else {
            printf("Usage: -h\n");
        }
    }

}


int main(int argc, char ** argv)
{
    if(argc < 2) {
        printf("Bad number oif args\n Use ./client <addressip>\n");
        exit(EXIT_FAILURE);
    }
    logger_init("logger.txt");
    int sock = connection_connect(argv[1]);
    if(sock > 0) {
        LOG_INFO("Connected to server");
    }
    else {
        LOG_ERROR("Unable to connect abort()");
        abort();
    }

    while(1) {
        MessageMicroReqS* msg_req;
        switch(parse_msg()) {
            case 0:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_LD1,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case 1:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_LD2,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case 2:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_IM1,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case 3:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_IM2,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case 4:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_IM3,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case 5:
                msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_GT,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                break;
            case -3:
                return 0;
                break;
        }
        MessageS* msg =  message_create_micro_req_create(msg_req);
        MessageCharS* buff = message_create_char(msg);

        write(sock, &buff->len, sizeof(int));
        write(sock, buff->msg, buff->len);
    }
    close(sock);
    logger_close();
    return 0;
}
