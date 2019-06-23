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

char	*kind_to_string(const int kind)
{
	char	*s[SIZE_KIND + 1] = {
		[TINY] = "TINY",
		[SMALL] = "SMALL",
		[LARGE] = "LARGE",
		[SIZE_KIND] = "NONE"
	};

	if (kind == NONE)
		return (s[SIZE_KIND]);
	return (s[kind]);
}

void	*malloc(size_t size)
{
	PRINT_FILE();
	// ft_dpf(2, "USER REQUEST SIZE [%u]\n", size);
	void	*res;
	int		kind;

	kind = get_area_kind_by_size((const size_t)size);
	if (kind == NONE)
		return ((void *)0);
	if (g_mdata.page_size <= 0 && (g_mdata.page_size = getpagesize()) <= 0)
		return ((void *)0);
	res = get_user_mem((const int)kind, size);
	// ft_dpf(2, "%sAllocation address %s[%u] : %s[%p]%s\n",
	// 		C_P, kind_to_string(kind),
	// 		size,
	// 		C_Y, res, C_X);
	return (res);
}
