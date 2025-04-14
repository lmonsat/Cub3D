/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:21:14 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:21:14 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (c == s[i])
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	char src[] = "test";
	char src2[] = "dest";
	char src3[] = "set";

	printf("character : %p\n", ft_strchr(src, 'e'));
	printf("character : %p\n", strchr(src2, 'e'));
	printf("character : %p\n", strchr(src, 'e'));
}*/
