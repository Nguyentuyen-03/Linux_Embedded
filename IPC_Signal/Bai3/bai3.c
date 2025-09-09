#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;

void child_handler(int sig) {
    printf("Received signal from parent\n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  
        // Process con
        signal(SIGUSR1, child_handler);

        while (1) {
            pause(); // chờ tín hiệu từ cha
        }
    } else {  
        // Process cha
        for (int i = 0; i < 5; i++) {
            sleep(2); // 2 giây
            kill(pid, SIGUSR1); // gửi tín hiệu cho con
        }

        printf("Parent finished sending signals.\n");
    }

    return 0;
}
