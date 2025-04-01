/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:24:12 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:24:12 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;
	char			*new_string;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_string[i] = s2[j];
		i++;
		j++;
	}
	new_string[i] = '\0';
	return (new_string);
}

/*#include <stdio.h>
int main ()
{
	char const *string1 = "Hello,";
	char const *string2 = " World!";

	char *result = ft_strjoin(string1, string2);

	printf("result : %s\n", result);

	free(result);

	return (0);
}*/
