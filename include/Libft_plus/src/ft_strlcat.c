/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:24:26 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:24:26 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <bsd/string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = strlen(src);
	dest_len = strlen(dst);
	i = 0;
	while (i < size && src[i] != '\0')
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (i < size)
	{
		dst[dest_len + i] = '\0';
	}
	return (dest_len + src_len);
}
/*#include <stdio.h>
int	main(void) {
	char dest1[20] = "Hello, ";
	char source1[] = "World!";

	printf("dest1: %s\n", dest1);
	printf("source1: %s\n", source1);
	size_t result1 = ft_strlcat(dest1, source1, sizeof(dest1));
	printf("concatenate value (avec ft_strlcat): %ld\n", result1);
	printf("new dest1: %s\n", dest1);
	printf("source1: %s\n\n", source1);

	char dest2[20] = "Hello, ";
	char source2[] = "World!";

	printf("dest2: %s\n", dest2);
	printf("source2: %s\n", source2);
	size_t result2 = strlcat(dest2, source2, sizeof(dest2));
	printf("concatenate value (avec strlcat): %ld\n", result2);
	printf("new dest2: %s\n", dest2);
	printf("source2: %s\n", source2);

	if (strcmp(dest1, dest2) == 0 && result1 == result2)
	{
		printf("Results match!\n");

	}
	else
	{
		printf("Results differ.\n");
	}

	return (0);
}*/
