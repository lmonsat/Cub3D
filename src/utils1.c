/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:22:32 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 22:29:08 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

char	**copy_array(char **source, int size)
{
	int		i;
	char	**copy;

	i = 0;
	copy = ft_calloc(size + 1, sizeof(char *));
	if (copy == NULL)
	{
		printf("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while (i < size)
	{
		copy[i] = ft_strdup(source[i]);
		if (copy[i] == NULL)
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			printf("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}

int	get_max_width(char **array)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			j++;
		if (len < j)
			len = j;
		i++;
	}
	return (len);
}

int	get_max_height(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_tabs(struct s_vars *vars)
{
	int	i;

	i = 0;
	while (vars->array->line[i] != NULL)
	{
		free(vars->array->line[i]);
		i++;
	}
	free(vars->array->line);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
