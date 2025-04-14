/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:25:46 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:25:46 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && (i < n))
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
/*#include <stdio.h>
int	main(void)
{
	char const *string1 = "Hello, World!";
	char const *string2 = "World!";

	printf("Case 1, string1 != string2 :\n");
	printf("value : %d\n\n", ft_strnequ(string1, string2, 5));

	string1 = "Hello,";
	string2 = "Hello, World!";

	printf("Case 2, string1 = string2 :\n");
	printf("value : %d\n\n", ft_strnequ(string1, string2, 7));

	string1 = "Hello, World!";
	string2 = "Hello, World!";

	printf("Case 3, string1 = string2 :\n");
	printf("value : %d\n", ft_strnequ(string1, string2, 13));

	return (0);
}*/
