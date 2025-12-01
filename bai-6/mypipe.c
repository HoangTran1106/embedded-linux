#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define MSG_SIZE 30

int main(int argc, char const *argv[])
{
    char mes[MSG_SIZE];
    int p[2];
    int status1;
    int status2;

    // 1.
    if (pipe(p) < 0)
    {
        perror("pipe");
        exit(1);
    }
    
    // 2. 
    pid_t child_ls_l = fork();
    if (0 == child_ls_l)
    {
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
        execlp("ls", "ls" ,"-l", NULL);
    } else if (0 < child_ls_l)
    {
        pid_t child_wc_l = fork();
        if (0 == child_wc_l)
        {
            close(p[1]);
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
            execlp("wc", "wc" ,"-l", NULL);
        } else if (0 < child_wc_l)
        {
            close(p[0]);
            close(p[1]);
            wait(&status1);
            wait(&status2);
        }
    }

    return 0;
}
