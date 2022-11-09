#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int p[2];
    //p[0] = read
    //p[1] = write

    pipe(p);

    pid_t pid = fork();

    if(pid == 0) // child process
    {
        //duplicat to stdout
        dup2(p[1], 1);

        close(p[0]);

        //command
        execlp("ls","ls","/", NULL);
        exit(1);
    }
    else if(pid > 0) // parent process
    {
    //duplicat to stdin
        dup2(p[0],0);
        close(p[1]);
        execlp("wc","wc","-l",NULL);
        exit(1);
    }
}
