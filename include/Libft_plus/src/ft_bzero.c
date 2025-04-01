/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:27 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:28:27 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n != 0)
	{
		*p++ = '\0';
		n--;
	}
}
/*
#include <stdio.h>

int	main(void) {
	char testA[10] = {'a','b','c','d'};

	printf("Using standard bzero: %s\n", testA);
	ft_bzero(testA, sizeof(testA));
	printf("Using custom bzero: %s\n", testA);

	testA[0] = 'a';

	printf("testA value: %s\n", testA);
	bzero(testA, sizeof(testA));
	printf("Using standard bzero: %s\n", testA);
	return (0);
}*/
