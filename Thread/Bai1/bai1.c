#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    long thread_id = (long)arg;
    printf("Thread ID %ld running!\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2]; 
    int i;

    for (i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void*)(long)i) != 0) {
            perror("Erorr while creating");
            return 1;
        }
    }

    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All thread have ended. End of main program.\n");
    return 0;
}
