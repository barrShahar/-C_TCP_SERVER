#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <server ip> <server port>\n", argv[0]);
        return 1;
    }
    
    char *server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error: socket creation failed\n");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error: connection failed\n");
        return 1;
    }

    printf("Client: Connected to server\n");

    close(sockfd);
    return 0;
}