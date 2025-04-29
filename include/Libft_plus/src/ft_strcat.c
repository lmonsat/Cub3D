/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:32:10 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:32:10 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
/*#include <stdio.h>
int	main(void) {
	char dest1[] = "Hello";
	char source1[] = ", World!";

	printf("dest1: %s\n", dest1);
	printf("source1: %s\n", source1);
	printf("concatenate value (avec ft_strcat): %s\n",ft_strcat(dest1,
			source1));

	char dest2[] = "Hello";
	char source2[] = ", World!";

	printf("dest2: %s\n", dest2);
	printf("source2: %s\n", source2);
	printf("concatenate value (avec strcat): %s\n",strcat(dest2, source2));

	return (0);
}*/
