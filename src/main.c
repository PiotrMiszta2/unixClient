#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "messages.h"
#include "connection.h"
char temp[] =   "Unix client console version\n" \
                "-h HELP";

static int parse_msg(void) {
    char buff[1024];
    while(1) {
        printf("$ ");
        fgets(buff, 1024, stdin);
        if(strcmp(buff, "-h\n") == 0) {
            printf("Unix client console version\n");
        }
        else if(strcmp(buff, "ld2\n") == 0) {
            return 1;
        }
        else if(strcmp(buff, "-q\n") == 0) {
            return -3;
        }
        else {
            printf("Usage: -h\n");
        }
    }

}


int main(int argc, char ** argv)
{
    logger_init_full("logger.txt", "client", 1.0,
        "Piotr", "Miszta", "wrx85588@student.wsb.wroclaw.pl");
    int sock = connection_connect();
    if(sock > 0) {
        LOG_INFO("Connected to server");
    }
    else {
        LOG_ERROR("Unable to connect abort()");
        abort();
    }

    while(1) {
        switch(parse_msg()) {
            case 1:
                MessageMicroReqS* msg_req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_LD2,
                MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
                MessageS* msg =  message_create_micro_req_create(msg_req);
                MessageCharS* buff = message_create_char(msg);
                write(sock, &buff->len, sizeof(int));
                write(sock, buff->msg, buff->len);
                break;
            case -3:
                return 0;
                break;
        }
    }
    close(sock);
    logger_close();
    return 0;
}
