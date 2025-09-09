#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_stream.sock"

int main() {
    int sockfd, connfd;
    char buffer[1024];
    struct sockaddr_un servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, SOCKET_PATH);

    unlink(SOCKET_PATH);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    printf("Unix Stream Server listening...\n");

    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    read(connfd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    char *msg = "Hello from Unix Stream Server";
    send(connfd, msg, strlen(msg), 0);

    close(connfd);
    close(sockfd);
    unlink(SOCKET_PATH);
    return 0;
}
