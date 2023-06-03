#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "connection.h"
#include <logger.h>

#define PORT            8080
#define HOST            "127.0.0.1"

int connection_connect(void) {
    int sock = -1;
    struct sockaddr_in address;
    struct hostent* host;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock <= 0) {
        LOG_ERROR("cannot create socket");
        return -3;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    host = gethostbyname("127.0.0.1");

    memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
    if (connect(sock, (struct sockaddr *)&address, sizeof(address))) {
        LOG_ERROR("cannot connect to host");
        return -5;
    }
    return sock;
}
