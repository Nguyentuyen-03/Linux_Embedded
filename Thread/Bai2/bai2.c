#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3
#define INCREMENT_TIMES 1000000

long long counter = 0; // Biến toàn cục chia sẻ
pthread_mutex_t counter_mutex; // Khai báo mutex

void* increment(void* arg) {
    for (int i = 0; i < INCREMENT_TIMES; i++) {
        pthread_mutex_lock(&counter_mutex);     // Khóa mutex
        counter++;                               // Tăng biến chia sẻ
        pthread_mutex_unlock(&counter_mutex);   // Mở khóa mutex
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&counter_mutex, NULL); // Khởi tạo mutex

    // Tạo 3 luồng
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Error while creating");
            return 1;
        }
    }

    // Đợi các luồng hoàn thành
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter_mutex); // Hủy mutex

    printf("Final value of counter: %lld\n", counter);
    return 0;
}
