#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void sig_handler(int sig) {
    if (sig == SIGINT) {
        sigint_flag = 1;
    } else if (sig == SIGTERM) {
        sigterm_flag = 1;
    }
}

int main() {
    char buffer[256];

    // xử lý tín hiệu
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    printf("Program running. Type something or press Ctrl+C (SIGINT), send SIGTERM to exit.\n");

    while (1) {
        // Kiểm tra cờ tín hiệu
        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }
        if (sigterm_flag) {
            printf("SIGTERM received. Exiting.\n");
            exit(0);
        }

        // Chuẩn bị cho select()
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        // Timeout = 1s để vòng lặp không bị treo 
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
            // Đọc input từ bàn phím
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                buffer[strcspn(buffer, "\n")] = 0; // bỏ newline
                printf("User input: %s\n", buffer);
            }
        }
    }
    return 0;
}
