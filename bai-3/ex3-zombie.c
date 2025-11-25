#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t child_pid = fork();
    if (0 == child_pid) {
        // die immediately
    } else if (child_pid > 0) {
        sleep(600000);
    }
    // Then ps aux | grep Z
    // Result: hoang      56568  0.0  0.0      0     0 pts/0    Z+   16:01   0:00 [ex3] <defunct>
    return 0;
}
