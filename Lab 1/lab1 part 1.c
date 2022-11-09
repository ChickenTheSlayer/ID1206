#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{

    char *param1[] = {"ls", "/", NULL};
    char *param2[] = {"wc", "-l", NULL};

    int p[2];
    pipe(p);

    pid_t p1, p2;

    if ((p1 = fork()) == 0) {   // child 1
        dup2(p[1], 1);          // redirect stdout to pipe
        close(p[0]);
        execvp("ls", param1);
        perror("execvp ls failed");
    }
    else if (p1 < 0) {           // parent
        exit(1);
    }
    close(p[1]);

    if ((p2 = fork()) == 0) {   // child 2
        dup2(p[0], 0);          // get stdin from pipe
        char buff[1000] = {0};
        int lines = 0;
        
        read(STDIN_FILENO, buff, 250);
        for(int i = 0; i < strlen(buff); i++)
            if(buff[i] == '\n') lines++;

        printf("%d\n", lines);

    }
    else if (p2 == -1) {          // parent
        close(p[0]);
        wait(NULL);
        exit(1);
    }
    close(p[0]);

    wait(NULL);
    wait(NULL);
    return 0;
}
