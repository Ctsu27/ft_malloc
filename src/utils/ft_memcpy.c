#include <sys/types.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srcs;
	size_t			i;

	i = 0;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}
