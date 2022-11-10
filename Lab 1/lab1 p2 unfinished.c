#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <mqueue.h>
    const int MAX_SIZE = 1024;
    const int MAX_NUM_MSG = 10;
    const char *my_mq = "/mymq";

int main(int argc, char const *argv[])
{

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_NUM_MSG;
    attr.mq_msgsize = MAX_SIZE;


    int pid = fork();

    if (pid < 0)
    {
        perror("fork error \n");
        exit(1);
    }
    if (pid == 0) // Child test
    {
    char buf[MAX_SIZE];

    FILE *file;
    file = fopen("test.txt", "r");
    if (file == NULL){
    perror("No file \n");
    }


    fgets(buf, MAX_SIZE, file);
    mqd_t mq = mq_open(my_mq, O_CREAT | O_WRONLY, (S_IRUSR | S_IWUSR), &attr);
            
    mq_send(mq, buf, strlen(buf), 0);
    mq_close(mq);

    }
    else if (pid > 0){ //unfinished
    wait(NULL);
    char buf[MAX_SIZE];
    mqd_t mq = mq_open(my_mq, O_RDONLY);

    mq_receive(mq, buf, MAX_SIZE, NULL);
    mq_close(mq);
    mq_unlink(my_mq);

    char *test = strtok(buf, " ");
    int i = 0;
    while (test != NULL)
    {
         i++;
    }

    printf("%d\n", i);

    }

}
