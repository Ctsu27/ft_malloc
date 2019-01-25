#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void    print(char *s)
{
    write(1, s, strlen(s));
}

int		main()
{
    char    *addr;

    addr = malloc(16);
    free(NULL);
    free((void *)addr + 5);
    if (realloc((void *)addr + 5, 10) == NULL)
        print("Bonjours\n");
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
