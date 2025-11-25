#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int status;
    pid_t ret_val = fork();
    if (0 == ret_val)  {
        printf("In child process: my PID is: %d\n", getpid());
        exit(1020);
    } else if (ret_val > 0) {
        printf("In parent process, my child PID is: %d, my pid is %d\n", ret_val, getpid());
        wait(&status);
        if (WIFEXITED(status)){
            printf("exit code: %d\n", WEXITSTATUS(status));
        } 
    }
    return 0;
}
