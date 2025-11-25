#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t child_pid = fork();
    if (0 == child_pid) {
        printf("parent pid : %d\n", getppid());
        sleep(1);
        printf("parent pid : %d\n", getppid());
        sleep(1);
        while (1)
        {
            sleep(1);
            printf("parent pid : %d\n", getppid());
        }
        
    } else if (child_pid > 0) {
        sleep(4);
    }
    return 0;
}
