#include "ft_malloc_int.h"
#include "utils.h"

t_chunk	*get_meta_chunk_mem(const int kind)
{
	t_area	*pool;
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;

	if (g_mdata.izone[kind] == (t_area *)0
		|| (g_mdata.izone[kind] = new_meta_mem()) == (t_area *)0)
		return ((t_chunk *)0);
	pool = g_mdata.izone[kind];
    while (pool != (t_area *)0)
	{
		chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
		cur = 0;
		end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
		while (cur < end)
		{
			if (chunk->user_mem == (void *)0)
				return (chunk);
			chunk = chunk + 1;
			++cur;
		}
		pool = pool->fd;
	}
	return ((t_chunk *)0);
}
