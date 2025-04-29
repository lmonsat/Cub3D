/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:03 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:31:03 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n != 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(void) {
	char test[10];

	memset(test, 'A', sizeof(test));
	printf("Using standard memset: %s\n", test);

	ft_memset(test, 'B', sizeof(test));
	printf("Using custom memset: %s\n", test);

	return (0);
}*/
