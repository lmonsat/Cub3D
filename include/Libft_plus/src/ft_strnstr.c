/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:26:08 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:26:08 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char *largestring = "Hello, World!";
	const char *smallstring = "World";
	size_t length = 15;
	size_t length2 = 5;

	printf("case 1, lenght >= largestring :\n");
	printf("character : %p\n", ft_strnstr(largestring, smallstring, length));
	printf("character : %p\n\n", strnstr(largestring, smallstring, length));

	printf("case 2, lenght <= largestring :\n");
	printf("character : %p\n", ft_strnstr(largestring, smallstring, length2));
	printf("character : %p\n\n", strnstr(largestring, smallstring, length2));

	printf("case 3, big < little :\n");
	printf("character : %p\n", ft_strnstr(smallstring, largestring, length));
	printf("character : %p\n\n", strnstr(smallstring, largestring, length));
}*/
