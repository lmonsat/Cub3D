/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:23:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/02 18:26:42 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*#include <stdio.h>
int	main(void)
{
	char source1[] = "hello";
	printf("Source1: %s\n", source1);
	char *test1 = ft_strdup(source1);
	printf("returned value1: %s\n", test1);
	free(test1);

	char source2[] = "world";
	printf("Source2: %s\n", source2);
	char *test2 = strdup(source2);
	printf("returned value2: %s\n", test2);
	free(test2);

}*/
