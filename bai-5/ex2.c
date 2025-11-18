// File: bai2_timer.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Biến đếm thời gian
volatile sig_atomic_t timer_count = 0;

// Hàm xử lý tín hiệu SIGALRM
void sigalrm_handler(int signum) {
    timer_count++;
    printf("Timer: %d seconds\n", timer_count);
    
    // Dừng sau 10 giây
    if (timer_count >= 10) {
        printf("Timer reached 10 seconds. Exiting...\n");
        exit(0);
    }
    
    // Đặt lại alarm để lặp lại sau 1 giây
    alarm(1);
}

int main() {
    // Đăng ký hàm xử lý cho SIGALRM
    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }
    
    printf("Starting timer...\n");
    
    // Bắt đầu alarm đầu tiên
    alarm(1);
    
    // Vòng lặp chờ tín hiệu
    while (1) {
        pause(); // Chờ tín hiệu
    }
    
    return 0;
}