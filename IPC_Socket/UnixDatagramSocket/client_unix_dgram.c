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
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    cliaddr.sun_family = AF_UNIX;
    strcpy(cliaddr.sun_path, CLIENT_PATH);
    unlink(CLIENT_PATH);
    bind(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, SERVER_PATH);

    char *msg = "Hello Unix Datagram Server";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&servaddr, len);

    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Server says: %s\n", buffer);

    close(sockfd);
    unlink(CLIENT_PATH);
    return 0;
}
