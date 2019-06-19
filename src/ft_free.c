/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:51 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/18 00:50:52 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

void	free(void *ptr)
{
	t_chunk	*chunk;

	chunk = find_chunk_by_ptr(ptr);
	if (chunk != (t_chunk *)0)
	{
		chunk->is_freed = 1;
	}
}

void	delete_chunks_from_pool(t_area *pool)
{
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;

	chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
	cur = 0;
	end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
	while (cur < end)
	{
		if (chunk->user_mem != (void *)0 && chunk->size_chunk > 0)
			munmap((void *)chunk, chunk->size_chunk);
		chunk = chunk + 1;
		++cur;
	}
}

__attribute__((destructor))
void	garbage_collector(void)
{
	t_area	*pool;
	t_area	*victim;
	int		idx;

	idx = 0;
	while (idx < SIZE_KIND)
	{
		pool = g_mdata.izone[idx];
		while (pool != (t_area *)0)
		{
			victim = pool;
			pool = pool->fd;
			delete_chunks_from_pool(victim);
			munmap((void *)victim, victim->size_map);
		}
		++idx;
	}
}
