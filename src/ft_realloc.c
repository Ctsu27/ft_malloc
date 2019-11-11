#include "malloc.h"
#include "ft_malloc_int.h"
#include "utils.h"

void	*realloc(void *ptr, size_t size)
{
	PRINT_FILE();
	(void)ptr;
	(void)size;
	return (NULL);
}


void	*reallocf(void *ptr, size_t size)
{
	PRINT_FILE();
	void	*res;

	res = realloc(ptr, size);
	if (res == NULL)
		free(ptr);
	return (res);
}
