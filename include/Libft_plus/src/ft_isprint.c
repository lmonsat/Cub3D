/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:29:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:29:33 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isprint(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}
/*#include <ctype.h>
#include <stdio.h>

int main ()
{
	int test = 'A';
	printf("case 1, is printable :\n");
	printf("value : %d\n", ft_isprint(test));
	printf("value (isprint) : %d\n\n", isprint(test));

	int test2 = '\n';
	printf("case 2, non printable :\n");
	printf("value : %d\n", ft_isprint(test2));
	printf("value (isprint) : %d\n\n", isprint(test2));

	int test3 = 9;
	printf("case 3, non printable :\n");
	printf("value : %d\n", ft_isprint(test3));
	printf("value (isprint) : %d", isprint(test3));
}*/
