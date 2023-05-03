#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h> //for Random

#define DISK_SIZE 5000
#define NUM_REQ 1000

int FCFS(int *request, int Head);
int SSTF(int *request, int *Req_S, int Head);
int SCAN(int *request, int *Req_S, int Head);
int CSCAN(int *request, int *Req_S, int Head);
int Look(int *request, int *Req_S, int Head);
int CLook(int *request, int *Req_S, int Head);
int parseCmdArg(char *arg);
int comparator(const void * temp1, const void * temp2);
int Findex(int *array, int value);

int disk[DISK_SIZE];
int request[NUM_REQ];
int Req_S[NUM_REQ];


int main(int argc, char *argv[]) {
    int takenIntegers[DISK_SIZE]; 
    int Head;
    if (argc > 2) {
        printf("Error 1 \n");
        exit(1);              
    }
    else if (argc == 2) {
        Head = parseCmdArg(argv[1]);
    }
    else {
        printf("Error2 \n");
        exit(1);
    }
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = i;
        takenIntegers[i] = 0;
    }  

    srand(time(NULL)); 
    int Rcounter = 0;
    while (Rcounter < NUM_REQ) {
        int Rnum = rand() % DISK_SIZE;
        if (takenIntegers[Rnum] == 0) {
            request[Rcounter] = Rnum;
            takenIntegers[Rnum] = 1; 
            Rcounter++;
        }
    }

    memcpy(Req_S, request, NUM_REQ * sizeof(int));
    qsort(Req_S, NUM_REQ, sizeof(*request), comparator);

    printf("FCFS head movement: %d\n", FCFS(request, Head));
    printf("SSTF head movement: %d\n", SSTF(request, Req_S, Head));
    printf("SCAN head movement: %d\n", SCAN(request, Req_S, Head));
    printf("C-SCAN  head movement: %d\n", CSCAN(request, Req_S, Head));
    printf("Look head movement: %d\n", Look(request, Req_S, Head));
    printf(" C-Look  head movement: %d\n\n", CLook(request, Req_S, Head));

    return 0;
}


int FCFS(int *request, int head) {
    int Dist = 0;
    int distance = head;
    for (int i = 0; i < NUM_REQ; i++){
        Dist += abs(distance - request[i]);
        distance = request[i];
    }
    return distance;
}

int SSTF(int *request, int *Req_S, int Head) {
        
        int Dist = 0;
        for (int i = 0; i < NUM_REQ; i++){
            int min = DISK_SIZE + 1;
            int index;
            for (int i = 0; i < NUM_REQ; i++)
            {
            Dist = abs (Head - Req_S[i]);

            if (Dist < min)
            {
                min = Dist;
                index = i;
            }
            
        }
        Head = Req_S[index];
        Dist += min;
        Req_S[index] = -1;
    }
    return Dist;
    }


int SCAN(int *request, int *Req_S, int Head) {
    int Dist = 0;
    int CHead = Head;
 
    for (int i = Head; i >= 0; i--)
    {
        for (int j = 0; j < NUM_REQ; j++)
        {
            if (Req_S[j] == i)
            {
                Dist += abs(Head - i);
                Head = i;
                break;
            }
        }
    Dist += Head;
    CHead = 0;

    for (int i = Head + 1; i < DISK_SIZE; i++)
    {
        for (int j = 0; j < NUM_REQ; j++)
        {
            if (Req_S[j] == i)
            {
                Dist += abs(CHead - i);
                CHead = i;
                break;
            }
        }
    }

    return Dist;
}
}

int CSCAN(int *request, int *Req_S, int Head) {
    int Dist = 0;
    int CHead = Head;
 
    for (int i = CHead; i < DISK_SIZE; i++)
    {
        for (int j = 0; j < NUM_REQ; j++)
        {
            if (Req_S[j] == i)
            {
                Dist += abs(Head - i);
                Head = i;
                break;
            }
        }
    Dist += (DISK_SIZE - 1)-Head;
    Head = 0;

    for (int i = 0; i < CHead; i++)
    {
        for (int j = 0; j < NUM_REQ; j++)
        {
            if (Req_S[j] == i)
            {
                Dist += abs(Head - i);
                Head = i;
                break;
            }
        }
    }

    return Dist;
}
}


int Look(int *request, int *Req_S, int Head) {
    int Dist = 0;
    int CHead = Head;
    int SIndex = Findex(Req_S, Head);
    for (int i = SIndex-1; i >= 0; i--){
        Dist += abs(CHead - Req_S[i]);
        CHead = Req_S[i];
    }
    
    for (int j = SIndex; j < NUM_REQ; j++){
        Dist += abs(CHead - Req_S[j]);
        CHead = Req_S[j];
    }
    
    return Dist;
}

int CLook(int *request, int *Req_S, int Head) {
    int Dist = 0;
    int CHead = Head;
    int SIndex = Findex(Req_S, Head);
    for (int i = SIndex-1; i >= 0; i--){
        Dist += abs(CHead - Req_S[i]);
        CHead = Req_S[i];
    }

    for (int j = NUM_REQ-1; j >= SIndex; j--){
        Dist += abs(CHead - Req_S[j]);
        CHead = Req_S[j];
    }
    return Dist;
}

int comparator(const void *temp1, const void *temp2) {
  return (*(int*)temp1 - *(int*)temp2);
}

int Findex(int *array, int v) {
    int index = 0;
    while (v > array[index]) {
        index++;
    }
    return index;
}
int parseCmdArg(char *arg) { //referenced from GeekForGeek
    int errno_backup = errno;
    errno = 0; 
    char *endptr;
    long parsed_argument = strtol(arg, &endptr, 10);
    if (errno != 0) {
        printf("error\n");
        exit(EXIT_FAILURE);
    }
    if (*endptr != 0) {
        printf("error\n");
        exit(EXIT_FAILURE);
    }
    if (parsed_argument < 0 || parsed_argument > 4999) {
        printf("error: not in range\n");
        exit(EXIT_FAILURE); 
    }

    errno = errno_backup;
    return (int) parsed_argument;
}