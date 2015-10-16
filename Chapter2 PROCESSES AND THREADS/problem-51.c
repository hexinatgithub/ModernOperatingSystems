#include <stdio.h>
#include <pthread.h>

#define MAN 1
#define WOMAN 0
#define EMPTY 2

pthread_mutex_t the_mutex;
pthread_cond_t cond_women;
pthread_cond_t cond_man;

int gender;
int number=0;

void woman_wants_to_enter() {
	pthread_mutex_lock(&the_mutex);
	if (gender == MAN) pthread_cond_wait(&cond_women, &the_mutex);
	number += 1;
	if (number == 1)
	{
		gender = WOMAN;
	}
	printf("woman_wants_to_enter\n");
	pthread_mutex_unlock(&the_mutex);
}

void man_wants_to_enter() {
	pthread_mutex_lock(&the_mutex);
	if (gender == WOMAN) pthread_cond_wait(&cond_man, &the_mutex);
	number += 1;
	printf("man_wants_to_enter\n");
	if (number == 1)
	{
		gender = MAN;
	}
	pthread_mutex_unlock(&the_mutex);
}

void woman_leaves() {
	pthread_mutex_lock(&the_mutex);
	if (gender == WOMAN)
	{
		number -= 1;
		if (number == 0)
		{
			gender = EMPTY;
			pthread_cond_signal(&cond_man);
		}
		printf("woman_leaves\n");
	}
	pthread_mutex_unlock(&the_mutex);
}

void man_leaves() {
	pthread_mutex_lock(&the_mutex);
	if (gender == MAN)
	{
		number -= 1;
		if (number == 0)
		{
			gender = EMPTY;
			pthread_cond_signal(&cond_women);
		}
		printf("man_leaves\n");
	}
	pthread_mutex_unlock(&the_mutex);
}

// pthread_t threads[10000];

// void W_E(void *P) {
// 	woman_wants_to_enter();
// }

// void M_E(void *P) {
// 	man_wants_to_enter();
// }

// void W_L(void *P) {
// 	woman_leaves();
// }

// void M_L(void *P) {
// 	man_leaves();
// }

// void WHI(void *P) {
// 	while (1);
// }

// int main(int argc, char const *argv[])
// {
// 	pthread_mutex_init(&the_mutex, 0);
// 	pthread_cond_init(&cond_women, 0);
// 	pthread_cond_init(&cond_man, 0);

// 	for (int i = 0; i < 3; ++i)
// 	{
// 		pthread_create(&threads[i], NULL, W_E, (void*)i);
// 	}

// 	pthread_create(&threads[3], NULL, M_E, (void*)NULL);
// 	for (int i = 0; i < 3; ++i)
// 	{
// 		pthread_create(&threads[3+i], NULL, W_L, NULL);
// 	}
// 	pthread_create(&threads[7], NULL, WHI, NULL);

// 	pthread_join(threads[7], NULL);

// 	pthread_cond_destroy(&cond_man);
// 	pthread_cond_destroy(&cond_women);
// 	pthread_mutex_destroy(&the_mutex);
// 	return 0;
// }


