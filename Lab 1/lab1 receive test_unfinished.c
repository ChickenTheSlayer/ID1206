#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

   void send_t(const char* fileName) {

    FILE *fptr;
    fptr = fopen ("test.txt", "r")

    const int size_of_each_message = sizeof(struct message) - sizeof(long);

    struct message sndMsg;
    sndMsg.mtype = SENDER_DATA_TYPE;

    struct message rcvMsg;
    rcvMsg.mtype = RECV_DONE_TYPE;

    while (!feof(fp)) {

    sndMsg.size = 0;

    fclose(fp);
}


    }

int main(int test, char** argv) {



    send_t(argv[1]);

    cleanUp(sharedMemPtr);

    return 0;
}

