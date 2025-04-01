/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:25:37 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:25:37 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
/*#include <stdio.h>
int	main(void) {
	char source[] = "Hello, World!";
	char destination[20];
	char destination2[20];
	size_t n = 5;

	printf("Source: %s\n", source);
	ft_strncpy(destination, source, n);
	printf("Destination (copie avec ft_strncpy): %s\n", destination);

	printf("Source: %s\n", source);
	strncpy(destination2, source, n);
	printf("Destination (copie avec strncpy): %s\n", destination2);

	return (0);
}*/
