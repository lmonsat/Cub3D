/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:30:10 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:30:10 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	size_t				i;

	src = s;
	i = 0;
	if (n == 0)
	{
		return (NULL);
	}
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
		{
			return ((void *)(src + i));
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	char source[] = "test";
	size_t n = strlen(source);

	char *result = ft_memchr(source, 115, n);
	printf("Source: %s\n", source);
	printf("Returned pointer: %p\n", (void *)result);

	result = memchr(source, 115, n);
	printf("Source: %s\n", source);
	printf("Returned pointer: %p\n", (void *)result);
}*/
