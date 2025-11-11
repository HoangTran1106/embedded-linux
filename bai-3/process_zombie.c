#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    
    printf("=== ZOMBIE PROCESS DEMONSTRATION ===\n");
    printf("Parent PID: %d\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process - exits immediately
        printf("Child PID: %d - Exiting immediately\n", getpid());
        printf("Child: I will become a zombie!\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent: Created child with PID: %d\n", pid);
        printf("Parent: NOT calling wait() - child will become zombie\n");
        printf("\nTo see zombie process, open another terminal and run:\n");
        printf("  ps aux | grep %d\n", pid);
        printf("  or\n");
        printf("  ps -l | grep defunct\n");
        printf("\nParent: Sleeping for 30 seconds...\n");
        printf("(The child is now in <defunct> zombie state)\n\n");
        
        sleep(30);
        
        printf("\nParent: Waking up and exiting\n");
        printf("Parent: Zombie will be cleaned up by init/systemd\n");
    }
    
    return 0;
}

/*
EXPLANATION:

ZOMBIE PROCESS:
- A zombie (defunct) process is a process that has completed execution but 
  still has an entry in the process table
- This happens when the child exits but the parent hasn't called wait()
- The zombie holds minimal resources (just the process table entry)
- It shows as <defunct> in ps output
- Purpose: Allows parent to retrieve child's exit status later

WHY IT EXISTS:
- Linux keeps the exit status available for the parent
- Parent might call wait() later to get the status
- If parent never calls wait(), zombie persists until parent dies
- When parent dies, init/systemd adopts the zombie and cleans it up
*/
