#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv)
{
    int port = 8080;
    int sock = -1;
    struct sockaddr_in address;
    struct hostent * host;
    int len;
    /* create socket */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
        return -3;
    }

    /* connect to server */
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    host = gethostbyname("127.0.0.1");
    memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
    if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
    {
        fprintf(stderr, "error: cannot connect to host \n");
        return -5;
    }

    /* send text to server */
    char buff[] = "Testowy message";
    len = strlen(buff);

    while(1)
    {
        write(sock, &len, sizeof(int));
        write(sock, buff, len);
        sleep(1);
    }


    /* close socket */
    close(sock);

    return 0;
}
