// File: bai4_signal_input_poll.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;

void sigint_handler(int signum) {
    sigint_received = 1;
}

void sigterm_handler(int signum) {
    sigterm_received = 1;
}

int main() {
    struct pollfd fds[1];
    char buffer[256];
    int ret;
    
    // Đăng ký handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    
    printf("Program started (using poll).\n");
    printf("- Press Ctrl+C to send SIGINT\n");
    printf("- Use 'kill -TERM %d' to send SIGTERM\n", getpid());
    printf("- Type text and press Enter to echo\n");
    printf("- Type 'quit' to exit\n\n");
    
    // Cấu hình poll cho stdin
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    
    while (1) {
        // Kiểm tra tín hiệu
        if (sigint_received) {
            printf("\nSIGINT received.\n");
            sigint_received = 0;
        }
        
        if (sigterm_received) {
            printf("\nSIGTERM received. Exiting...\n");
            break;
        }
        
        // Poll với timeout 1000ms
        ret = poll(fds, 1, 1000);
        
        if (ret == -1) {
            // Poll bị gián đoạn bởi signal
            continue;
        } else if (ret > 0) {
            // Có dữ liệu từ stdin
            if (fds[0].revents & POLLIN) {
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = 0;
                    
                    if (strcmp(buffer, "quit") == 0) {
                        printf("Exiting...\n");
                        break;
                    }
                    
                    printf("You entered: %s\n", buffer);
                }
            }
        }
    }
    
    return 0;
}