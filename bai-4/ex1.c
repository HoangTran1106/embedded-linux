// bai1_thread_basic.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    pthread_t thread_id = pthread_self();
    int thread_num = *(int *)arg;
    
    printf("Thread %d voi ID %lu dang chay!\n", thread_num, thread_id);
    sleep(1);
    printf("Thread %d voi ID %lu da hoan thanh!\n", thread_num, thread_id);
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int thread1_num = 1, thread2_num = 2;
    
    printf("=== BAI TAP 1: TAO VA CHAY LUONG CO BAN ===\n\n");
    printf("Luong chinh dang chay voi ID: %lu\n\n", pthread_self());
    
    pthread_create(&thread1, NULL, thread_function, &thread1_num);
    pthread_create(&thread2, NULL, thread_function, &thread2_num);
    
    printf("Luong chinh dang cho 2 luong con hoan thanh...\n\n");
    
    pthread_join(thread1, NULL);
    printf("Luong chinh: Thread 1 da join thanh cong\n");
    
    pthread_join(thread2, NULL);
    printf("Luong chinh: Thread 2 da join thanh cong\n");
    
    printf("\nTat ca cac luong con da hoan thanh. Chuong trinh ket thuc.\n");
    return 0;
}