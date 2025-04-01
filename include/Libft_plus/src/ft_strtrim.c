/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:15 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:27:15 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		j;
	int		i;
	char	*trimmed_string;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	j = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	trimmed_string = (char *)malloc(((end - start + 1) + 1) * sizeof(char));
	if (trimmed_string == NULL)
		return (NULL);
	i = start;
	while (i <= end)
		trimmed_string[j++] = s1[i++];
	trimmed_string[j] = '\0';
	return (trimmed_string);
}
/*#include <stdio.h>
int main ()
{
	char const *string1 = "****Hello, World!****";
	char const *set = "*";

	char *result = ft_strtrim(string1, set);

	printf("original string %s\n", string1);
	printf("modified string : %s\n\n", result);

	free(result);

	char const *string2 = "//Hello, World!//";
	char const *set2 = "/";

	char *result2 = ft_strtrim(string2, set2);

	printf("original string2 %s\n", string2);
	printf("modified string2 : %s\n", result2);

	free(result2);

	return (0);
}*/
