#include <sys/mman.h>
#include "ft_malloc_int.h"

#include "utils.h"
void	*new_user_mem(size_t size)
{
	PRINT_FILE();
	void	*res;

	res = mmap((void *)0, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	// ft_dpf(2, "%sMAP USER: %s%p%s\n", C_G, C_Y, res, C_X);
	if (res == MAP_FAILED)
		return ((void *)0);
	return (res);
}
