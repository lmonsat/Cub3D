/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:29:43 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:29:43 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	nb_len(int n)
{
	int	total_len;

	total_len = 1;
	if (n < 0)
	{
		total_len++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		total_len++;
	}
	return (total_len);
}

char	*ft_itoa(int n)
{
	char	*str_nb;
	int		len;
	int		sign_nb;

	len = nb_len(n);
	sign_nb = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign_nb = -sign_nb;
	str_nb = (char *)malloc((len + 1) * sizeof(char));
	if (str_nb == NULL)
		return (NULL);
	str_nb[len] = '\0';
	while (len--)
	{
		str_nb[len] = '0' + (n % 10) * sign_nb;
		n /= 10;
	}
	if (sign_nb == -1)
		str_nb[0] = '-';
	return (str_nb);
}
/*#include <stdio.h>
int	main(void)
{
	int n = 5;

	printf("value : %s\n", ft_itoa(n));
}*/
