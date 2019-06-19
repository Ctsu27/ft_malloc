#include "ft_malloc_int.h"

t_chunk *find_chunk_by_ptr(void *ptr)
{
	t_area	*pool;
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;
	int		idx;

	idx = 0;
	while (idx < SIZE_KIND)
	{
		pool = g_mdata.izone[idx];
		while (pool != (t_area *)0)
		{
			chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
			end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
			cur = 0;
			while (cur < end)
			{
				if (chunk->user_mem == ptr)
					return (chunk);
				chunk  = chunk + 1;
				++cur;
			}
			pool = pool->fd;
		}
		++idx;
	}
	return ((t_chunk *)0);
}
