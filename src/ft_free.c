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
#include "ft_malloc_int.h"

#include "ft_printf.h"
void	free(void *ptr)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_ch	*minju;
	t_mem	*minju_doooo;
	size_t	idx;

	// return ;
	if (ptr == (void *)0)
		return ;
	if (DEBUG_DPF)
		ft_dpf(2, "ptr address to free ===> %p\n", ptr);
	if (DEBUG_DPF)
		ft_dpf(2, "offset ptr address to free ===> %p\n", ptr - sizeof(t_ch));
	minju = (t_ch *)(ptr - sizeof(t_ch));
	idx = 0;
	while (idx < 3)
	{
		minju_doooo = g_data.izone[idx].map;
		while (minju_doooo != (t_mem *)0)
		{
			// if (DEBUG_DPF)
			// 	ft_dpf(2, "%sCOUCOU%s\n", "\033[36m", "\033[0m");
			if ((void *)minju_doooo < ptr && ptr < ((void *)minju_doooo) + minju_doooo->size)
			{
				if (DEBUG_DPF)
					ft_dpf(2, "%sSET UNUSED%s\n", "\033[36m", "\033[0m");
				minju->used = UNUSED;
				return;
			}
			minju_doooo = minju_doooo->fd;
		}
		++idx;
	}
	return ;
	minju = (t_ch *)(ptr - sizeof(t_ch));
	if (DEBUG_DPF)
		ft_dpf(2, "minju ===> %p\n", (t_ch *)(ptr - sizeof(t_ch)));
	if (DEBUG_DPF)
		ft_dpf(2, "kind ===> %d\n", minju->kind);
	minju_doooo = g_data.izone[minju->kind].map;
	if (DEBUG_DPF)
		ft_dpf(2, "%sALLO%s\n", "\033[36m", "\033[0m");
	while (minju_doooo != (t_mem *)0)
	{
		if (DEBUG_DPF)
			ft_dpf(2, "%sCOUCOU%s\n", "\033[36m", "\033[0m");
		if ((void *)minju_doooo < ptr
				&& ptr < ((void *)minju_doooo) + minju_doooo->size)
		{
			if (DEBUG_DPF)
				ft_dpf(2, "%sSET UNUSED%s\n", "\033[36m", "\033[0m");
			minju->used = UNUSED;
			return ;
		}
		minju_doooo = minju_doooo->fd;
	}
}

 __attribute__((destructor))void	izone_ending_contract(void)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem	*minju;
	t_mem	*minju_doooo;
	size_t	idx;
	char	*tmp[3] = {
		"nako",
		"yena",
		"wonyoung"
	};
	size_t	nb_of_map;

	nb_of_map = 0;
	idx = 0;
	while (idx < 3)
	{
		minju = (t_mem *)g_data.izone[idx].map;
		while (minju != (t_mem *)0)
		{
			++nb_of_map;
			minju = minju->fd;
		}
		++idx;
	}
	// ft_dpf(2, "nb of mmap() call -> %u\n", nb_of_map);
	// show_alloc_mem();
	idx = 0;
	while (idx < 3)
	{
		if (DEBUG_DPF)
			ft_dpf(2, "%s%s%s fan club\n", "\033[33m", tmp[idx], "\033[0m");
		minju = (t_mem *)g_data.izone[idx].map;
		while (minju != (t_mem *)0)
		{
			if (!DEPLOY_DPF)
				ft_dpf(2, "%smunmap()%s --> [%p]\n", "\033[31m", "\033[0m", minju);
			minju_doooo = minju->fd;
			munmap(minju, minju->size);
			minju = minju_doooo;
		}
		++idx;
	}
}
