#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int data = 0;                // Biến chia sẻ
int data_ready = 0;          // Cờ 

pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1); // Giả lập thời gian tạo dữ liệu

        int new_data = rand() % 100; // Tạo số ngẫu nhiên

        pthread_mutex_lock(&mutex);
        data = new_data;
        data_ready = 1;
        printf("Producer tạo dữ liệu: %d\n", data);

        pthread_cond_signal(&cond);  // Báo hiệu cho Consumer
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (!data_ready) {
            pthread_cond_wait(&cond, &mutex); // Đợi Producer báo hiệu
        }

        printf("Consumer đọc dữ liệu: %d\n", data);
        data_ready = 0;

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread;

    srand(time(NULL)); // Khởi tạo seed cho số ngẫu nhiên

    // Khởi tạo mutex và condition
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Tạo luồng Producer và Consumer
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Đợi cả hai luồng kết thúc
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Hủy mutex và condition
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Chương trình kết thúc.\n");
    return 0;
}
