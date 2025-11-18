// File: bai4_signal_input.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

// Cờ để xử lý tín hiệu
volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;

// Handler cho SIGINT
void sigint_handler(int signum) {
    sigint_received = 1;
}

// Handler cho SIGTERM
void sigterm_handler(int signum) {
    sigterm_received = 1;
}

int main() {
    fd_set readfds;
    struct timeval tv;
    int retval;
    char buffer[256];
    
    // Đăng ký handlers
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal SIGINT");
        return 1;
    }
    
    if (signal(SIGTERM, sigterm_handler) == SIG_ERR) {
        perror("signal SIGTERM");
        return 1;
    }
    
    printf("Program started.\n");
    printf("- Press Ctrl+C to send SIGINT\n");
    printf("- Use 'kill -TERM %d' to send SIGTERM\n", getpid());
    printf("- Type text and press Enter to echo\n");
    printf("- Type 'quit' to exit\n\n");
    
    while (1) {
        // Kiểm tra cờ tín hiệu
        if (sigint_received) {
            printf("\nSIGINT received.\n");
            sigint_received = 0;
        }
        
        if (sigterm_received) {
            printf("\nSIGTERM received. Exiting...\n");
            break;
        }
        
        // Chuẩn bị cho select()
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        
        // Timeout 1 giây để kiểm tra tín hiệu thường xuyên
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        
        retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        
        if (retval == -1) {
            // select bị gián đoạn bởi tín hiệu, tiếp tục vòng lặp
            if (sigint_received || sigterm_received) {
                continue;
            }
            perror("select");
            break;
        } else if (retval > 0) {
            // Có dữ liệu từ stdin
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    // Xóa ký tự newline
                    buffer[strcspn(buffer, "\n")] = 0;
                    
                    if (strcmp(buffer, "quit") == 0) {
                        printf("Exiting...\n");
                        break;
                    }
                    
                    printf("You entered: %s\n", buffer);
                }
            }
        }
        // retval == 0 nghĩa là timeout, tiếp tục vòng lặp
    }
    
    return 0;
}