#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

void sigint_handler(int sig) {
  
    count++;
    printf("SIGINT received (%d)\n", count);

    if (count >= 3) {
        printf("Exiting after 3 SIGINT signals.\n");
        exit(0);
    }
}

int main() {

    signal(SIGINT, sigint_handler);

    printf("Program is running. Press Ctrl+C to send SIGINT.\n");

    while (1) {
        printf("Working...\n");
        sleep(1);
    }
    return 0;
}
