#include <sys/mman.h>
#include "ft_malloc_int.h"

void	*new_user_mem(size_t size)
{
	return (mmap((void *)0, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0));
}
