#include "malloc.h"
#include "ft_malloc_int.h"
#include "utils.h"

void	*realloc(void *ptr, size_t size)
{
	PRINT_FILE();
	t_chunk	*meta;
	void	*res;
	size_t	size_to_copy;
	int		kind;

	if (ptr == NULL)
		return (malloc(size));
	kind = get_kind((const size_t)size);
	if (kind == NONE
			|| (meta = find_chunk_by_user_mem(ptr)) == NULL
			|| (res = malloc(size)) == NULL)
		return (NULL);
	size_to_copy = meta->user_size < size ? meta->user_size : size;
	ft_memcpy(res, ptr, size_to_copy);
	return (res);
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
