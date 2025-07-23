#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, child_pid;
    int status;

    pid = fork(); 

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        exit(10);  
    }
    else {

        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        child_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        } else {
            printf("Child %d did not exit normally\n", child_pid);
        }
    }

    return 0;
}
