/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:25:58 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:25:58 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnew(size_t size)
{
	char	*memory;

	if (size == 0)
	{
		return (NULL);
	}
	memory = malloc(size + 1);
	if (memory == NULL)
	{
		return (NULL);
	}
	ft_memset(memory, '\0', size + 1);
	return (memory);
}

/*int main()
{
	size_t size = 10;
	char *str_test = (char *)ft_strnew(size * sizeof(char));

	if (str_test != NULL)
	{
		for (size_t i = 0; i < size; ++i)
		{
			printf("%c ", str_test[i]);
		}

		free(str_test);
	}

	return (0);
}*/
