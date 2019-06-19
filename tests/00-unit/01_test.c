#include <stdlib.h>
// #include <stdio.h>

int		main()
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

// #include <stdio.h>

// __attribute__((constructor)) void ke_begin (void)
// {
// 	printf("%sstart test%s %s%s%s\n", "\033[32m", "\033[0m",
// 			"\033[33m", __FILE__, "\033[0m");
// }

// __attribute__((destructor)) void ke_end (void)
// {
// 	printf("%send test%s %s%s%s\n\n", "\033[31m", "\033[0m",
// 			"\033[33m", __FILE__, "\033[0m");
// }
