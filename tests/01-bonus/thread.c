#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 100
#define MAX_ALLOCS 100

static void *f(void *arg)
{
	char *ptrs[MAX_ALLOCS];
	int i;

	for (i = 0; i < MAX_ALLOCS; i++) {
		ptrs[i] = malloc(1 + i * i);
		ptrs[i][0] = 42;
		ptrs[i] = realloc(ptrs[i], 1 + i * i * i);
	}

	for (i = 0; i < MAX_ALLOCS; i++)
		free(ptrs[i]);

	return arg;
}

int		main()
{
	pthread_t threads[MAX_THREADS];
	int i;

	for (i = 0; i < MAX_THREADS; i++)
		pthread_create(threads + i, NULL, f, NULL);

	for (i = 0; i < MAX_THREADS; i++)
		pthread_join(threads[i], NULL);

	return (0);
}

#include <stdio.h>

__attribute__((constructor)) void ke_begin (void)
{
	printf("%sstart test%s %s%s%s\n", "\033[32m", "\033[0m",
		"\033[33m", __FILE__, "\033[0m");
}

__attribute__((destructor)) void ke_end (void)
{
	printf("%send test%s %s%s%s\n\n", "\033[31m", "\033[0m",
		"\033[33m", __FILE__, "\033[0m");
}
