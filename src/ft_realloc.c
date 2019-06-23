/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:55 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/18 21:56:28 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_malloc_int.h"
#include "utils.h"

void	*realloc(void *ptr, size_t size)
{
	PRINT_FILE();
	void	*res;
	t_chunk	*chunk;
	size_t	size_to_copy;
	int		kind;

	if (ptr == (void *)0)
		return (malloc(size));
	kind = get_area_kind_by_size((const size_t)size);
	if (kind == NONE || (chunk = find_chunk_by_ptr(ptr)) == (t_chunk *)0
			|| (res = malloc(size)) == (void *)0)
		return ((void *)0);
	size_to_copy = chunk->size_user_requested < size
		? chunk->size_user_requested : size;
	ft_memcpy(res, ptr, size_to_copy);
	free(ptr);
	return (res);
}

// RODO reallocf to launch vim from bnoufel
