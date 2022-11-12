#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <string.h> //for strtok
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int MAX_SIZE = 100;
    int MAX_NUM_MSG = 10;
    char *my_mq = "/mymq";

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_NUM_MSG;
    attr.mq_msgsize = MAX_SIZE;


    int pid = fork();

    if (pid < 0)
    {
        perror("fork error \n");
        exit(1);
    }

    

    if (pid == 0) // Child (Send)
    {
    char buf[MAX_SIZE];

    FILE *file;
    file = fopen("test.txt", "r");
    if (file == NULL){
        perror("No file found");
    }
    fgets(buf, MAX_SIZE, file);
    mqd_t mq = mq_open(my_mq, O_WRONLY);

    mq_send(mq, buf, strlen(buf), 0);

    mq_close(mq);
    
    }



    else if (pid > 0){ // Parent (Receive)
    char *token;
    char buf[MAX_SIZE];
    mqd_t mq = mq_open(my_mq, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, &attr);
    
    mq_receive(mq, buf, MAX_SIZE, NULL);
    
    mq_close(mq);
    
    token = strtok(buf, " ");
    int count = 0;

    while (token != NULL)
    {
        count++;
        token = strtok(NULL, " ");
    }

    printf("%d\n", count);

    }
    mq_unlink(my_mq);


}
