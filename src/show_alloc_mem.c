#include <unistd.h>
#include "ft_malloc_int.h"
#include "ft_printf.h"
#include "utils.h"

static inline void	*get_user_smallest_mem(const int kind)
{
	t_area	*pool;
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;
	void	*res;

	res = (void *)((size_t)-1);
	pool = g_mdata.izone[kind];
	while (pool != (t_area *)0)
	{
		chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
		cur = 0;
		end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
		while (cur < end)
		{
			if (chunk->user_mem != (void *)0 && chunk->size_chunk > 0
					&& chunk->size_user_requested > 0 && chunk->is_used
					&& chunk->user_mem < res)
				res = chunk->user_mem;
			chunk = chunk + 1;
			++cur;
		}
		pool = pool->fd;
	}
	if (res == (void *)((size_t)-1))
		return ((void *)0);
	return (res);
}

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
		if (pool != (t_area *)0)
			ft_pf("%s : %p\n", kind_to_string((const int)idx),
					get_user_smallest_mem((const int)idx));
		while (pool != (t_area *)0)
		{
			show_chunks_from_pool(pool);
			pool = pool->fd;
		}
		++idx;
	}
}

static inline void	print_chunk_hexdump(t_chunk *chunk)
{
	unsigned char	*dump;
	unsigned char	c;
	size_t	size;
	size_t	cur;

	dump = (unsigned char *)chunk->user_mem;
	size = chunk->size_user_requested;
	cur = 0;
	while (cur < size)
	{
		c = (dump[cur] >= 0x20 && dump[cur] < 0x7f) ? dump[cur] : '.';
		write(1, &c, 1);
		++cur;
	}
}

static inline void	show_chunks_from_pool_hex(t_area *pool)
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
			ft_pf("|");
			print_chunk_hexdump(chunk);
			ft_pf("|\n");
		}
		chunk = chunk + 1;
		++cur;
	}
}

void			show_alloc_mem_hex(void)
{
	t_area	*pool;
	int		idx;

	idx = 0;
	while (idx < SIZE_KIND)
	{
		pool = g_mdata.izone[idx];
		if (pool != (t_area *)0)
			ft_pf("%s : %p\n", kind_to_string((const int)idx),
					get_user_smallest_mem((const int)idx));
		while (pool != (t_area *)0)
		{
			show_chunks_from_pool_hex(pool);
			pool = pool->fd;
		}
		++idx;
	}
}
