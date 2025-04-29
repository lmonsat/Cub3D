/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:27:33 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_string;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (s[i] && j < len)
	{
		if (i >= start)
		{
			new_string[j] = s[i];
			j++;
		}
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}
/*#include <stdio.h>
int main ()
{
	char const *string = "Hello, World!";

	char *result = ft_substr(string, 7, 6);

	printf("original string : %s\n", string);
	printf("modified string : %s\n\n", result);

	free(result);

	char const *string2 = "Hello, World!";

	char *result2 = ft_substr(string, 0, 5);

	printf("original string : %s\n", string2);
	printf("modified string : %s\n", result2);

	free(result);

	return (0);
}*/
