/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:27:04 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/14 15:30:59 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	while (i + 1 < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (src_len);
}
/*#include <stdio.h>
int	main(void) {
	char source[] = "Hello, World!";
	char destination[20];

	printf("Source: %s\n", source);
	printf(" lenght : %ld\n", ft_strlcpy(destination, source, 10));
	printf("Destination (copie avec ft_strlcpy): %s\n", destination);

	char source2[] = "Hello, World!";
	char destination2[20];
	printf("Source: %s\n", source);
	printf(" lenght : %ld\n", strlcpy(destination2, source2, 10));
	printf("Destination (copie avec strcpy): %s\n", destination);

	return (0);
}*/
