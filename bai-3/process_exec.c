#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t pid;
    
    printf("Parent Process: Setting environment variable...\n");
    
    // Set environment variable
    setenv("MY_COMMAND", "ls", 1);
    printf("Parent: MY_COMMAND=ls\n");
    
    // Create child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        printf("\nChild Process: Started\n");
        printf("Child PID: %d\n", getpid());
        
        // Read environment variable
        char *command = getenv("MY_COMMAND");
        
        if (command == NULL) {
            printf("Child: MY_COMMAND not found!\n");
            exit(1);
        }
        
        printf("Child: Read MY_COMMAND=%s\n", command);
        printf("Child: Executing command...\n");
        printf("----------------------------\n");
        
        // Execute the command using execlp()
        // This replaces the current process image
        execlp(command, command, "-l", NULL);
        
        // If exec() succeeds, the code below will never execute
        perror("execlp");
        exit(1);
        
    } else {
        // Parent process
        printf("Parent: Waiting for child to complete...\n");
        wait(NULL);
        printf("\nParent: Child completed\n");
        printf("Parent: Exiting\n");
    }
    
    return 0;
}

/*
EXPLANATION (for the report):

What happens to the address space and code of the child process after exec() is called successfully?

When exec() is called successfully:
1. The entire address space of the child process is replaced
2. The old program code is completely discarded
3. A new program (in this case, the 'ls' command) is loaded into memory
4. The stack, heap, and data segments are reset
5. The process retains the same PID, but everything else is new
6. File descriptors (except those marked close-on-exec) remain open
7. Environment variables are inherited by the new program

That's why any code after the execlp() call never executes - the process 
no longer contains that code!
*/
