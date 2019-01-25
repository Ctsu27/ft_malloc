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

#include "ft_malloc_int.h"
#include "malloc.h"
#include "utils.h"


#include "ft_printf.h"
int		get_kind_by_ptr(void *p)
{
	t_ch	*ptr;

	ptr = p - sizeof(t_ch);
	return (ptr->kind);
}

size_t	get_map_size_by_ptr_and_kind(const void *p, const int kind)
{
	t_mem	*minju;
	t_ch	*minju_doooo;

	minju = g_data.izone[kind].map;
	while (minju != (t_mem *)0)
	{
		minju_doooo = (t_ch *)(((void *)minju)
				+ (sizeof(void *) * 2 + sizeof(size_t) * 2));
		while (minju_doooo != (t_ch *)0)
		{
			if (((void *)minju_doooo) + sizeof(size_t) + sizeof(void *) == p)
				return (minju->size);
			minju_doooo = minju_doooo->fd;
		}
		minju = minju->fd;
	}
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	void	*p;
	int		kind;
	size_t	n_cpy;

	if (ptr == (void *)0)
		return (malloc(size));
	kind = get_kind_by_ptr(ptr);
	if (kind == NONE || (p = malloc(size)) == (void *)0)
		return ((void *)0);
	if (kind == TINY)
		n_cpy = TINY_SIZE;
	else if (kind == SMALL)
		n_cpy = SMALL_SIZE;
	else
		n_cpy = get_map_size_by_ptr_and_kind((const void *)p, (const int)kind)
			- (sizeof(void *) * 3 + sizeof(size_t) * 3);
	// if (size < (*(size_t *)(ptr - sizeof(size_t))))
	// 	n_cpy = size;
	// else
	// 	n_cpy = (*(size_t *)(ptr - sizeof(size_t)));
	ft_dpf(2, "size to copy == %u\n", n_cpy);
	ft_dpf(2, "memcpy __enter\n");
	ft_memcpy(p, ptr, n_cpy);
	ft_dpf(2, "memcpy exit__\n");
	// free(ptr);
	return (p);
}
