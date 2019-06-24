#include "ft_malloc_int.h"

#include "utils.h"

int		move_chunk(t_chunk *chunk, const int kind)
{
	t_chunk	*new;

	new = get_meta_chunk_mem(kind);
	if (new != (t_chunk *)0 || (append_area(new_meta_mem(), kind) == 0
				&& (new = get_meta_chunk_mem(kind)) != (t_chunk *)0))
	{
		new->user_mem = chunk->user_mem;
		new->size_chunk = chunk->size_chunk;
		new->size_user_requested = chunk->size_user_requested;
		new->is_used = 1;
		ft_memset((void *)chunk, 0, sizeof(*chunk));
	}
	return (-1);
}

void	*seach_available_user_mem(const int kind, size_t size)
{
	PRINT_FILE();
	t_area	*minju;
	t_chunk	*chunk;
	void	*res;
	size_t	cur;
	size_t	end;
	int		idx;

	// if ((minju = g_mdata.izone[kind]) == (t_area *)0)
	// 	return ((void *)0);
	idx = 0;
	while (idx < SIZE_KIND)
	{
		minju = g_mdata.izone[idx];
		while (minju != (t_area *)0)
		{
			chunk = (t_chunk *)(((void *)minju) + sizeof(*minju));
			cur = 0;
			end = (minju->size_map - sizeof(*minju)) / sizeof(*chunk);
			while (cur < end)
			{
				if (chunk->user_mem != (void *)0 && chunk->size_chunk >= size
						&& !chunk->is_used)
				{
					// ft_dpf(2, "=== user mem available [%u]\n", cur);
					chunk->size_user_requested = size;
					chunk->is_used = 1;
					// TODO move chunk to right pool/area
					split_chunk(chunk);
					if (idx == kind)
						return (chunk->user_mem);
					res = chunk->user_mem;
					if (move_chunk(chunk, kind) == 0)
						return (res);
				}
				chunk = chunk + 1;
				++cur;
			}
			minju = minju->fd;
		}
		++idx;
	}
	// ft_dpf(2, "no user mem available\n");
	return ((void *)0);
}
