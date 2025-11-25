#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int status;
    setenv("MY_COMMAND", "date", 1);
    pid_t child_pid = fork();
    if (0 == child_pid) {
        const char *my_command = getenv("MY_COMMAND");
        execlp(my_command, "ls", (char *) NULL); 
    } else if (child_pid > 0) {
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("exit code: %d\n", WEXITSTATUS(status));
        }
        printf("This is parent process !!\n");
    }
    return 0;
}
