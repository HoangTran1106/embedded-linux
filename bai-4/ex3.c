// bai3_producer_consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int data = 0;
int data_ready = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        // Tao du lieu ngau nhien
        int value = rand() % 100;
        
        pthread_mutex_lock(&mutex);
        
        // San xuat du lieu
        data = value;
        data_ready = 1;
        printf("Producer: San xuat du lieu %d (lan %d/10)\n", value, i + 1);
        
        // Bao hieu cho Consumer
        pthread_cond_signal(&cond);
        
        pthread_mutex_unlock(&mutex);
        
        usleep(100000); // Nghi 100ms
    }
    
    printf("Producer: Da hoan thanh!\n");
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        
        // Cho doi cho den khi co du lieu
        while (!data_ready) {
            printf("Consumer: Dang cho du lieu...\n");
            pthread_cond_wait(&cond, &mutex);
        }
        
        // Tieu thu du lieu
        printf("Consumer: Nhan duoc du lieu %d (lan %d/10)\n", data, i + 1);
        data_ready = 0;
        
        pthread_mutex_unlock(&mutex);
    }
    
    printf("Consumer: Da hoan thanh!\n");
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    
    srand(time(NULL));
    
    printf("=== BAI TAP 3: PRODUCER-CONSUMER ===\n\n");
    
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    printf("\nChuong trinh hoan thanh!\n");
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}