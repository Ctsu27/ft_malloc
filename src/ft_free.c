#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

void			free(void *ptr)
{
	PRINT_FILE();
	t_chunk	*meta;
	_Bool	*used;
	int		idx;

	if (ptr == (void *)0)
		return ;
	meta = find_chunk_idx_by_user_mem(ptr, &idx);
	if (meta != NULL)
	{
		used = (_Bool *)(meta + 1);
		used[idx] = 0;
	}
}
