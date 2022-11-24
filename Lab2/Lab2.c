#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int buffer = 0;
pthread_mutex_t lock;

void* thread_func(void* arg) {
	void* count = 0;
	while (pthread_mutex_lock(&lock) || buffer < 15) {
		printf("TID: %d, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
		pthread_mutex_unlock(&lock);
		count++
	}

int main() {

	//Array of threads to be joined upon
	pthread_t arr[3];
	pthread_mutex_init(&lock, NULL);
	for (int i = 0; i < 3; pthread_create(&threads[i++], NULL, thread_func, NULL));



}
