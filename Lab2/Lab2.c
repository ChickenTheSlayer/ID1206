#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int buffer = 0;
pthread_mutex_t lock;

void *thread_func() {
{
    void *counter;
    counter= 0;
    for (counter; pthread_mutex_lock(&lock) || buffer < 15; counter++)
    {
        buffer++;
        printf("TID: %lu, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
        pthread_mutex_unlock(&lock);
        sleep(0.5);


    }
    pthread_mutex_unlock(&lock);
    return (void *)counter;
}
}
int main()
{
    pthread_t t1, t2, t3;

    int count1,count2,count3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);
    pthread_create(&t3, NULL, thread_func, NULL);

    pthread_join(t1, (void **)&count1);
    pthread_join(t2, (void **)&count2);
    pthread_join(t3, (void **)&count3);

    printf("TID %lu worked on the buffer %d times\n", t1, count1);
    printf("TID %lu worked on the buffer %d times\n", t2, count2);
    printf("TID %lu worked on the buffer %d times\n", t3, count3);
    printf("Total buffer access: %d", buffer);
    pthread_exit(NULL);

    return 0;
}
