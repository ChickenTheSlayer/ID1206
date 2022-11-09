#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int p[2];
    pipe(p);

    pid_t pid = fork();

    if(pid == 0)
    {
        dup2(p[1], 1);
        close(p[0]);
        execlp("ls","ls","/", NULL);
        exit(1);
    }
    else if(pid > 0)
    {
        dup2(p[0],0);
        close(p[1]);
        execlp("wc","wc","-l",NULL);
        exit(1);
    }
}