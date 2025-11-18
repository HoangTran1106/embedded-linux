// File: bai3_process_comm.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// Biến đếm cho process con
volatile sig_atomic_t signal_received = 0;

// Hàm xử lý SIGUSR1 trong process con
void sigusr1_handler(int signum) {
    signal_received++;
    printf("[Child] Received signal from parent (count: %d)\n", signal_received);
}

int main() {
    pid_t pid;
    int signal_count = 0;
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Process con
        printf("[Child] Child process started (PID: %d)\n", getpid());
        
        // Đăng ký handler cho SIGUSR1
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
            perror("signal");
            exit(1);
        }
        
        // Chờ tín hiệu
        while (1) {
            pause(); // Chờ tín hiệu
        }
        
    } else {
        // Process cha
        printf("[Parent] Parent process (PID: %d)\n", getpid());
        printf("[Parent] Child process created (PID: %d)\n", pid);
        
        sleep(1); // Đợi process con khởi động xong
        
        // Gửi tín hiệu SIGUSR1 5 lần, mỗi 2 giây
        for (signal_count = 1; signal_count <= 5; signal_count++) {
            sleep(2);
            printf("[Parent] Sending signal %d to child...\n", signal_count);
            
            if (kill(pid, SIGUSR1) < 0) {
                perror("kill");
                exit(1);
            }
        }
        
        printf("[Parent] Sent 5 signals. Terminating child process...\n");
        
        // Kết thúc process con
        kill(pid, SIGTERM);
        wait(NULL); // Chờ process con kết thúc
        
        printf("[Parent] Program completed.\n");
    }
    
    return 0;
}