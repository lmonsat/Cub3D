/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:21:49 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:21:49 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
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

	printf("Case 1, string1 > string2 :\n");
	printf("value : %d\n", ft_strcmp(string1, string2));
	printf("value : %d\n\n", strcmp(string1, string2));

	string1 = "World!";
	string2 = "Hello, World!";

	printf("Case 2, string1 < string2 :\n");
	printf("value : %d\n", ft_strcmp(string1, string2));
	printf("value : %d\n\n", strcmp(string1, string2));

	string1 = "Hello, World!";
	string2 = "Hello, World!";

	printf("Case 3, string1 = string2 :\n");
	printf("value : %d\n", ft_strcmp(string1, string2));
	printf("value : %d\n", strcmp(string1, string2));
}*/
