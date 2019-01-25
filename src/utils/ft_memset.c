/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:32:39 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:33:15 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)b;
	c = (unsigned int)c;
	while (i < len)
	{
		dest[i] = c;
		i++;
	}
	return (dest);
}
