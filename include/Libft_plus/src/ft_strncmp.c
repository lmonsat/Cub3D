/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:25:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:25:21 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s1 == *s2 && *s1 && i < n)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/*#include <stdio.h>
int	main(void)
{
	char *string1 = "Hello, World!";
	char *string2 = "World!";
	size_t n = 6;

	printf("Case 1, string1 > string2 :\n");
	printf("value : %d\n", ft_strncmp(string1, string2, n));
	printf("value : %d\n\n", strncmp(string1, string2, n));

	string1 = "World!";
	string2 = "Hello, World!";

	printf("Case 2, string1 < string2 :\n");
	printf("value : %d\n", ft_strncmp(string1, string2, n));
	printf("value : %d\n\n", strncmp(string1, string2, n));

	string1 = "Hello, World!";
	string2 = "Hello, World!";

	printf("Case 3, string1 = string2 :\n");
	printf("value : %d\n", ft_strncmp(string1, string2, n));
	printf("value : %d\n", strncmp(string1, string2, n));
}*/
