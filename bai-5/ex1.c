// File: bai1_sigint.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Biến đếm toàn cục
volatile sig_atomic_t sigint_count = 0;

// Hàm xử lý tín hiệu SIGINT
void sigint_handler(int signum) {
    sigint_count++;
    printf("\nSIGINT received (count: %d)\n", sigint_count);
    
    // Kết thúc chương trình sau lần thứ 3
    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting...\n");
        exit(0);
    }
}

int main() {
    // Đăng ký hàm xử lý cho tín hiệu SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }
    
    printf("Program is running. Press Ctrl+C to send SIGINT.\n");
    printf("Program will exit after receiving SIGINT 3 times.\n");
    
    // Vòng lặp vô hạn, chờ tín hiệu
    while (1) {
        printf("Waiting for signal... (SIGINT count: %d)\n", sigint_count);
        sleep(2);
    }
    
    return 0;
}