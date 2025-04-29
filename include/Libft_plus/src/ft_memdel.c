/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:30:30 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:30:30 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}
/*int main()
{
	int *intArray = (int *)malloc(5 * sizeof(int));
	if (intArray != NULL)
	{
		printf("Memory allocated successfully.\n");
		ft_memdel((void **)&intArray);
		if (intArray == NULL)
		{
			printf("Memory freed successfully.\n");
		}
		else
		{
			printf("Memory not freed.\n");
		}
	}
	else
	{
		printf("Memory allocation failed.\n");
	}

	return (0);
}*/
