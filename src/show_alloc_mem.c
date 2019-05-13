#include "stddef.h"
#include "ft_malloc_int.h"
#include "ft_printf.h"

#include "unistd.h"
void	show_alloc_mem(void)
{
	static const char	*type[3] = {
		"NAKO",
		"YENA",
		"WONYOUNG"
	};
	static const char	*state_str[2] = {
		"UNUSED",
		"USED"
	};
	t_mem	*minju;
	t_ch	*minju_doooo;
	t_ch	*produce_forty_eight;
	size_t	size;
	size_t	idx;
	int		state;

	idx = 0;
	while (idx < 3)
	{
		minju = (t_mem *)g_data.izone[idx].map;
		while (minju != (t_mem *)0)
		{
			ft_pf("%s : %p\n", type[idx], (void *)minju);
			minju_doooo = (t_ch *)(((void *)minju)
					+ sizeof(void *) * 2 + sizeof(size_t) * 2);
			if (minju_doooo != (t_ch *)0)
			{
				while (minju_doooo != (t_ch *)0)
				{
					state = 0;
					size = 0;
					produce_forty_eight = (void *)minju_doooo + sizeof(t_ch);
					if (minju_doooo->used)
					{
						state = 1;
						while (minju_doooo != (t_ch *)0
								&& minju_doooo->used == USED)
						{
							if (minju->kind == TINY)
								size += TINY_SIZE;
							else if (minju->kind == SMALL)
								size += SMALL_SIZE;
							else
								size += minju->size;
							minju_doooo = minju_doooo->fd;
						}
					}
					else
					{
						while (minju_doooo != (t_ch *)0
								&& minju_doooo->used == UNUSED)
						{
							if (minju->kind == TINY)
								size += TINY_SIZE;
							else if (minju->kind == SMALL)
								size += SMALL_SIZE;
							else
								size += minju->size;
							minju_doooo = minju_doooo->fd;
						}
					}
					ft_pf("%p - %p : %u bytes -> [%s]\n",
							produce_forty_eight, produce_forty_eight,
							size, state_str[state]);
				}
			}
			minju = minju->fd;
		}
		++idx;
	}
}

// void	show_alloc_mem(void)
// {
// 	static const char	*type[3] = {
// 		"NAKO",
// 		"YENA",
// 		"WONYOUNG"
// 	};
// 	static const char	*state_str[2] = {
// 		"UNUSED",
// 		"USED"
// 	};
// 	t_mem	*minju;
// 	t_ch	*minju_doooo;
// 	size_t	size;
// 	int		state;
// 	size_t	idx;

// 	idx = 0;
// 	while (idx < 3)
// 	{
// 		minju = (t_mem *)g_data.izone[idx].map;
// 		while (minju != (t_mem *)0)
// 		{
// 			ft_pf("%s : %p\n", type[idx], (void *)minju);
// 			minju_doooo = (t_ch *)(((void *)minju)
// 					+ sizeof(void *) * 2 + sizeof(size_t) * 2);
// 			size = 0;
// 			state = 0;
// 			if (minju_doooo != (t_ch *)0)
// 			{
// 				state = minju_doooo->used + 1;
// 				while (minju_doooo != (t_ch *)0)
// 				{
// 					if (!(state & (minju_doooo->used + 1)))
// 					{
// 						ft_pf("%p - %p : %u bytes -> [%s]\n",
// 								minju_doooo, minju_doooo,
// 								size, state_str[state - 1]);
// 						size = 0;
// 						state ^= 0x3;
// 					}
// 					else
// 					{
// 						if (minju->kind == TINY)
// 							size += TINY_SIZE;
// 						else if (minju->kind == SMALL)
// 							size += SMALL_SIZE;
// 						else
// 							size += minju->size;
// 					}
// 					minju_doooo = minju_doooo->fd;
// 				}
// 				ft_pf("%p - %p : %u bytes -> [%s]\n",
// 								minju_doooo, minju_doooo,
// 								size, state_str[state - 1]);
// 			}
// 			minju = minju->fd;
// 		}
// 		++idx;
// 	}
// }
