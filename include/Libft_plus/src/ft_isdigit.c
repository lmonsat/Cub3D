/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:29:20 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:29:20 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*#include <ctype.h>
#include <stdio.h>

int main ()
{
	int test = '9';
	printf("case 1, is digit :\n");
	printf("value : %d\n", ft_isdigit(test));
	printf("value (isdigit) : %d\n\n", isdigit(test));

	int test2 = 'A';
	printf("case 2, non digit :\n");
	printf("value : %d\n", ft_isdigit(test2));
	printf("value (isdigit) : %d", isdigit(test2));
}*/
