/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:30:00 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:30:00 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*destm;
	const unsigned char	*srcm;
	size_t				i;

	destm = dest;
	srcm = src;
	i = 0;
	while (i < n)
	{
		if (srcm[i] == (unsigned char)c)
		{
			destm[i] = c;
			return ((void *)(destm + i + 1));
		}
		destm[i] = srcm[i];
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	char source[] = "test";
	char destination[20];
	size_t n = sizeof(source);

	char *result = ft_memccpy(destination, source, 115, n);
	printf("Source: %s\n", source);
	printf("Destination: %s\n", destination);
	printf("Returned pointer: %p\n", (void *)result);

	result = memccpy(destination, source, 115, n);
	printf("Source: %s\n", source);
	printf("Destination: %s\n", destination);
	printf("Returned pointer: %p\n", (void *)result);
}*/
