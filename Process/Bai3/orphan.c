#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        for (int i = 0; i < 10; ++i) {
            printf("Child PID = %d, Parent PPID = %d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else {
        printf("Parent process (PPID = %d) exiting...\n", getpid());
        exit(0);
    }

    return 0;
}
