// bai2_race_condition_mutex.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg) {
    int thread_num = *(int *)arg;
    printf("Thread %d bat dau tang counter...\n", thread_num);
    
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    
    printf("Thread %d da hoan thanh!\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_nums[3] = {1, 2, 3};
    
    printf("=== BAI TAP 2: RACE CONDITION VA MUTEX ===\n\n");
    printf("Gia tri ban dau: %lld\n\n", counter);
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, increment_counter, &thread_nums[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n=== KET QUA ===\n");
    printf("Gia tri cuoi cung: %lld\n", counter);
    printf("Gia tri mong doi: 3000000\n");
    
    if (counter == 3000000) {
        printf("CHINH XAC! Mutex da bao ve thanh cong.\n");
    } else {
        printf("SAI! Co van de dong bo hoa.\n");
    }
    
    pthread_mutex_destroy(&counter_mutex);
    return 0;
}