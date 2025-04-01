/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:21:57 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:21:57 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*#include <stdio.h>
int	main(void) {
	char source[] = "Hello, World!";
	char destination[20];

	printf("Source: %s\n", source);
	ft_strcpy(destination, source);
	printf("Destination (copie avec ft_strcpy): %s\n", destination);

	printf("Source: %s\n", source);
	strcpy(destination, source);
	printf("Destination (copie avec strcpy): %s\n", destination);

	return (0);
}*/
