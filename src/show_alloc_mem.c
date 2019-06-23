#include "ft_malloc_int.h"
#include "ft_printf.h"
#include "utils.h"

static inline void	show_chunks_from_pool(t_area *pool)
{
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;

	chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
	cur = 0;
	end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
	while (cur < end)
	{
		if (chunk->user_mem != (void *)0 && chunk->size_chunk > 0
				&& chunk->size_user_requested > 0 && chunk->is_used)
		{
			ft_pf("%p - %p : %u bytes\n", chunk->user_mem,
					chunk->user_mem + chunk->size_user_requested,
					chunk->size_user_requested);
		}
		chunk = chunk + 1;
		++cur;
	}
}

void			show_alloc_mem(void)
{
	t_area	*pool;
	int		idx;

	idx = 0;
	while (idx < SIZE_KIND)
	{
		pool = g_mdata.izone[idx];
		ft_pf("TODO KIND : TODO ADDRESS\n", pool + 1);
		while (pool != (t_area *)0)
		{
			show_chunks_from_pool(pool);
			pool = pool->fd;
		}
		++idx;
	}
}
