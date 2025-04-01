/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:26:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:26:33 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (c == s[i])
		{
			return ((char *)(s + i));
		}
		i--;
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

	printf("character : %p\n", ft_strrchr(src, 'e'));
	printf("character : %p\n", strrchr(src2, 'e'));
	printf("character : %p\n", strrchr(src, 'e'));
}*/
