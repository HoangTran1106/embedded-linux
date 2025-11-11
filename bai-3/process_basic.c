#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, child_pid;
    int status;
    
    printf("Parent Process: Starting...\n");
    printf("Parent PID: %d\n", getpid());
    
    // Create child process
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        printf("\nChild Process: Started\n");
        printf("Child PID: %d\n", getpid());
        printf("Child: Exiting with code 10\n");
        exit(10);
    } else {
        // Parent process
        child_pid = pid;
        printf("Parent: Created child with PID: %d\n", child_pid);
        printf("Parent: Waiting for child to finish...\n");
        
        // Wait for child process to finish
        wait(&status);
        
        // Check if child exited normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("\nParent: Child exited normally with status: %d\n", exit_status);
        } else {
            printf("\nParent: Child did not exit normally\n");
        }
        
        printf("Parent: Exiting\n");
    }
    
    return 0;
}
