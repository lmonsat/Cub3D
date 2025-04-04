/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:24 by drenquin          #+#    #+#             */
/*   Updated: 2024/05/21 15:06:46 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len_s;
	char	*new_s;

	i = 0;
	len_s = ft_strlen(s);
	new_s = (char *) malloc (sizeof(char) * (len_s + 1));
	if (len_s == 0)
		return (ft_free(new_s), NULL);
	if (new_s == NULL)
		return (NULL);
	while (*s)
	{
		new_s[i] = *s;
		i++;
		s++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;
	int		len_n;

	if (start > ft_strlen(s))
		return ("");
	len_n = ft_strlen(s) - start + 1;
	if (len_n > (int)len)
		len_n = len + 1;
	dest = (char *)malloc(len_n * sizeof(char));
	if (!dest || !s)
		return (ft_free(dest), NULL);
	i = 0;
	while (s[start] != '\0' && len--)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			lenght;
	char			*join;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	lenght = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((lenght + 1) * (sizeof(char)));
	if (join == NULL)
		return (ft_free(join), NULL);
	while (ft_strlen(s1) > i)
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (ft_free(s1), join);
}

void	ft_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
}
