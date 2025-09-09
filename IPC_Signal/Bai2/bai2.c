#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int seconds = 0;

void alarm_handler(int sig) {
    seconds++;
    printf("Timer: %d seconds\n", seconds);

    if (seconds >= 10) {
        printf("Finished after 10 seconds.\n");
        exit(0);
    }

    alarm(1); // đặt lại báo động để lặp lại mỗi giây
}

int main() {
    signal(SIGALRM, alarm_handler); // đăng ký xử lý tín hiệu

    printf("Start timer...\n");
    alarm(1); // hẹn báo sau 1 giây

    while (1) {
        pause(); // chờ tín hiệu
    }

    return 0;
}
