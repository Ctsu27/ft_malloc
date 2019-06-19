/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:52 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/18 21:56:25 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "ft_printf.h"

t_meta	g_mdata = {
	.nako = (t_area *)0,
	.yena = (t_area *)0,
	.wonyoung = (t_area *)0,
	.page_size = 0
};

void	*malloc(size_t size)
{
	int		kind;

	kind = get_area_kind_by_size((const size_t)size);
	if (kind == NONE)
		return ((void *)0);
	if (g_mdata.page_size <= 0 && (g_mdata.page_size = getpagesize()) <= 0)
		return ((void *)0);
	return (get_user_mem((const int)kind, size));
}
