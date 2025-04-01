/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:55 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:28:55 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalnum(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}
/*#include <ctype.h>
#include <stdio.h>

int main ()
{
	int test = 'A';
	printf("case 1, is alpha :\n");
	printf("value : %d\n", ft_isalnum(test));
	printf("value (isalnum) : %d\n\n", isalnum(test));

	test = '9';
	printf("case 2, is num :\n");
	printf("value : %d\n", ft_isalnum(test));
	printf("value (isalnum) : %d\n\n", isalnum(test));

	test = '\t';
	printf("case 3, non alphanumeric :\n");
	printf("value : %d\n", ft_isalnum(test));
	printf("value (isalnum) : %d\n", isalnum(test));

}*/
