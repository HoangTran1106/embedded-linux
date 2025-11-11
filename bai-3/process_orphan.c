#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    
    printf("=== ORPHAN PROCESS DEMONSTRATION ===\n");
    printf("Parent PID: %d\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process - will become orphan
        printf("Child PID: %d\n", getpid());
        printf("Child: My parent PID (PPID): %d\n", getppid());
        printf("Child: Parent will exit soon, I'll become orphan\n");
        
        // Give parent time to exit
        sleep(2);
        
        printf("\nChild: After parent exited\n");
        printf("Child: My new parent PID (PPID): %d\n", getppid());
        printf("Child: I've been adopted by init/systemd!\n");
        
        // Continue printing PPID to show it stays with init
        for (int i = 1; i <= 5; i++) {
            printf("Child: [%d] Still alive, PPID: %d\n", i, getppid());
            sleep(2);
        }
        
        printf("Child: Exiting now\n");
        exit(0);
        
    } else {
        // Parent process - exits immediately
        printf("Parent: Created child with PID: %d\n", pid);
        printf("Parent: Exiting immediately (child will be orphaned)\n");
        exit(0);
    }
    
    return 0;
}

/*
EXPLANATION:

ORPHAN PROCESS:
- An orphan process is a running process whose parent has terminated
- When a parent dies before its child, the child becomes an orphan
- The init process (PID 1) or systemd automatically adopts all orphans
- The orphan continues to run normally under its new parent

WHY IT EXISTS:
- Prevents processes from having invalid parent PIDs
- Ensures all processes have a proper parent in the process tree
- init/systemd becomes the new parent and will clean up when child exits
- This is intentional system behavior to maintain process hierarchy

KEY OBSERVATION:
- Watch the PPID change from the original parent to 1 (or systemd PID)
- The orphan continues running normally - it's not a problem
- When orphan exits, init/systemd properly reaps it (no zombie)
*/
