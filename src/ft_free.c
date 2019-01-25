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
#include "malloc.h"

#include "ft_printf.h"
void	free(void *ptr)
{
	ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	// size_t	*s;

	(void)ptr;
	// if (ptr != NULL)
	// {
	// 	s = (size_t *)(ptr - sizeof(size_t));
	// 	munmap(ptr, *s);
	// }
//	munmap(ptr, ((t_malloc *)ptr)->size_alloc);
}
