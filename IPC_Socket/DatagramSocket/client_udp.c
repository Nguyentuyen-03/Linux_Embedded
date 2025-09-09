#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char *msg = "Hello UDP Server";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&servaddr, len);

    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, &len);
    printf("Server says: %s\n", buffer);

    close(sockfd);
    return 0;
}
