#include <malloc.h>

int		main()
{
	malloc(32);
	malloc(64);
	malloc(1023);
	malloc(1024);
    malloc(1025);
	malloc(1025);
	show_alloc_mem();
	return (0);
}
