/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:36 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 17:48:31 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
	{
		mem = malloc(1);
		if (mem != NULL)
			ft_bzero(mem, 1);
		return (mem);
	}
	if (nmemb >= 65535 || size >= 65535)
		return (NULL);
	mem = (void *)malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
/*#include <stdio.h>
int	main(void)
{
	size_t nmemb = 5;
	size_t size = sizeof(int);

	int *array = (int *)ft_calloc(nmemb, size);
	if (array == NULL) {
		printf("Allocation failed\n");
		return (1);
	}

	printf("Allocation succesful\n");

	printf("Array :\n");
	for (size_t i = 0; i < nmemb; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	free(array);

	return (0);
}*/
