
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int buffer = 0;
pthread_mutex_t mutex;



void *thread_func() {
{
    void *counter;
    counter= 0;


    for (counter; pthread_mutex_lock(&mutex) || buffer < 15; counter++, pthread_mutex_unlock(&mutex))
    {
        printf("TID: %lu, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
        pthread_mutex_unlock(&mutex);
        buffer++;
        sleep(0.1);

    }
    pthread_mutex_unlock(&mutex);
    return (void *)counter;
}
}
int main()
{
    pthread_t thread1, thread2, thread3;

    int thread1_count;
    int thread2_count;
    int thread3_count;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, &thread_func, NULL);
    pthread_create(&thread2, NULL, &thread_func, NULL);
    pthread_create(&thread3, NULL, &thread_func, NULL);

    pthread_join(thread1, (void **)&thread1_count);
    pthread_join(thread2, (void **)&thread2_count);
    pthread_join(thread3, (void **)&thread3_count);

    printf("TID %lu worked on the buffer %d times\n", thread1, thread1_count);
    printf("TID %lu worked on the buffer %d times\n", thread2, thread2_count);
    printf("TID %lu worked on the buffer %d times\n", thread3, thread3_count);

    printf("Total buffer accesses: %d\n", buffer);
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}
