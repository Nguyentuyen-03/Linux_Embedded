#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // MY_COMMAND=date
    setenv("MY_COMMAND", "date", 1);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {

        char* cmd = getenv("MY_COMMAND");

        if (cmd == NULL) {
            fprintf(stderr, "MY_COMMAND not set\n");
            exit(1);
        }

        printf("Child executing command: %s\n", cmd);

        // execlp 
        execlp(cmd, cmd, NULL);

        perror("exec failed");
        exit(1);
    } 
    else {
        int status;  //status from child
        wait(&status);
        printf("Parent: Child process exited\n");
    }

    return 0;
}
