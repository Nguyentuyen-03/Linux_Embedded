#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define MAX_ITERATIONS 50

int shared_data = 0;  
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        pthread_rwlock_rdlock(&rwlock);  
        printf("Reader %d đọc dữ liệu: %d (lần %d)\n", id, shared_data, i+1);
        pthread_rwlock_unlock(&rwlock);  
        sleep(1); // 1s
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        pthread_rwlock_wrlock(&rwlock);  
        shared_data++;
        printf("Writer %d ghi dữ liệu: %d (lần %d)\n", id, shared_data, i+1);
        pthread_rwlock_unlock(&rwlock);  
        sleep(1); // 1s
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);  // Khởi tạo Read-Write Lock

    // Tạo Reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Tạo Writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Chờ các luồng kết thúc
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock); // Hủy khóa

    return 0;
}
