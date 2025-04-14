/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:30:17 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:30:17 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*string1;
	const unsigned char	*string2;
	size_t				i;

	string1 = s1;
	string2 = s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n)
	{
		if (string1[i] != string2[i])
		{
			return ((int)(string1[i] - string2[i]));
		}
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int	main(void)
{
	char str1[] = "test";
	char str2[] = "ceci est un";
	char str3[] = "test";

	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len3 = strlen(str3);

	int result1 = ft_memcmp(str1, str2, len1 < len2 ? len1 : len2);
	printf("Comparison of '%s' and '%s': %d\n", str1, str2, result1);

	int result2 = memcmp(str1, str2, len1 < len2 ? len1 : len2);
	printf("Comparison using standard memcmp: %d\n", result2);

	int result3 = ft_memcmp(str1, str3, len1 < len3 ? len1 : len3);
	printf("Comparison of '%s' and '%s': %d\n", str1, str3, result3);

	int result4 = memcmp(str1, str3, len1 < len3 ? len1 : len3);
	printf("Comparison using standard memcmp: %d\n", result4);

	return (0);
}*/
