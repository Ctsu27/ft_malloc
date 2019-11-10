/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:53:59 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/19 23:35:19 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>

extern void	*calloc(size_t count, size_t size);
extern void	free(void *ptr);
extern void	*malloc(size_t size);
extern void	*realloc(void *ptr, size_t size);
extern void	*reallocf(void *ptr, size_t size);
extern void	show_alloc_mem(void);
extern void	show_alloc_mem_hex(void);

#endif
