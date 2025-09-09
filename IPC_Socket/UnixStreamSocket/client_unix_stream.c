#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_stream.sock"

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_un servaddr;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, SOCKET_PATH);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    char *msg = "Hello Unix Stream Server";
    send(sockfd, msg, strlen(msg), 0);
    read(sockfd, buffer, sizeof(buffer));
    printf("Server says: %s\n", buffer);

    close(sockfd);
    return 0;
}
