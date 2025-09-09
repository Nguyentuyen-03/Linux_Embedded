#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/unix_dgram_server.sock"
#define CLIENT_PATH "/tmp/unix_dgram_client.sock"

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_un servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, SERVER_PATH);

    unlink(SERVER_PATH);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Unix Datagram Server listening...\n");

    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
    printf("Received: %s\n", buffer);

    char *msg = "Hello from Unix Datagram Server";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&cliaddr, len);

    close(sockfd);
    unlink(SERVER_PATH);
    return 0;
}
