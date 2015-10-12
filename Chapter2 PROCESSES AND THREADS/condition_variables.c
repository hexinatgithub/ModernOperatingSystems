#include <stdio.h>
#include <pthread.h>
#define MAX 1000000000
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer=0;

void *producer(void *ptr)
{
	for (int i = 0; i < MAX; ++i)
	{
		pthread_mutex_lock(&the_mutex);
		while (buffer != 0) pthread_cond_wait(&condp, &the_mutex);
		buffer = i;
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&the_mutex);
	}
}

void *consumer(void *ptr)
{
	for (int i = 0; i < MAX; ++i)
	{
		pthread_mutex_lock(&the_mutex);
		while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
		buffer = 0
		pthread_cond_signal(&condp);
		pthread_mutex_unlock(&the_mutex);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t pro, con;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destory(&condc);
	pthread_cond_destory(&condp);
	pthread_mutex_destory(&the_mutex);
	return 0;
}