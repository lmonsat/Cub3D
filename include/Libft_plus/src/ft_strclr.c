/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:21:36 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:21:36 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_strclr(char *s)
{
	size_t	size;

	size = ft_strlen(s);
	ft_memset((void *)s, '\0', size + 1);
}

/*int main()
{
	char str[] = "Hello, World!";

	printf("Original string: %s\n", str);

	ft_strclr(str);

	printf("String after ft_strclr: %s\n", str);

	return (0);
}*/
