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
    char    *addr1;
    char    *addr3;

    addr1 = (char *)malloc(16 * M);
    strcpy(addr1, "Bonjours\n");
    print(addr1);
    addr3 = (char *)realloc(addr1, 128 * M);
    addr3[127 * M] = 42;
    print(addr3);
	return (0);
}

// #include <stdio.h>

// __attribute__((constructor)) void ke_begin (void)
// {
// 	printf("%sstart test%s %s%s%s\n", "\033[32m", "\033[0m",
// 		"\033[33m", __FILE__, "\033[0m");
// }

// __attribute__((destructor)) void ke_end (void)
// {
// 	printf("%send test%s %s%s%s\n\n", "\033[31m", "\033[0m",
// 		"\033[33m", __FILE__, "\033[0m");
// }
