#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd, connfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    printf("Server TCP listening...\n");

    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    read(connfd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    char *msg = "Hello from TCP Server";
    send(connfd, msg, strlen(msg), 0);

    close(connfd);
    close(sockfd);
    return 0;
}
