/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:35 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/01 20:07:53 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

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
	i = 0;
	while (vars->array->backtracking[i] != NULL)
	{
		free(vars->array->backtracking[i]);
		i++;
	}
	free(vars->array->backtracking);
}

void	free_arrays(struct s_array *array)
{
	int	i;

	i = 0;
	while (array->line[i] != NULL)
	{
		free(array->line[i]);
		i++;
	}
	free(array->line);
	i = 0;
	while (array->backtracking[i] != NULL)
	{
		free(array->backtracking[i]);
		i++;
	}
	free(array->backtracking);
}

void	free_1_array(struct s_array *array)
{
	int	i;

	i = 0;
	while (array->line[i] != NULL)
	{
		free(array->line[i]);
		i++;
	}
	free(array->line);
}

void	free_in_lines(struct s_array *array)
{
	free_1_array(array);
	perror("Error\n Map edges incomplete");
	exit(EXIT_FAILURE);
}

int	open_map_file(char *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n Error while opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	free_visited(struct s_array *array)
{
	int	i;

	i = 0;
	while (array->visited[i] != NULL)
	{
		free(array->visited[i]);
		i++;
	}
	free(array->visited);
}

void	free_visited_vars(struct s_vars *vars)
{
	int	i;

	i = 0;
	while (vars->array->visited[i] != NULL)
	{
		free(vars->array->visited[i]);
		i++;
	}
	free(vars->array->visited);
}

void	handle_error_mem(struct s_array *array, char **copy)
{
	free_1_array(array);
	free(copy);
	perror("Error\n Memory allocation failed");
	exit(EXIT_FAILURE);
}

char	**copy_array(char **source, struct s_array *array)
{
	int		i;
	int		size;
	char	**copy;

	size = array->elmt.rows;
	i = 0;
	copy = malloc((size + 1) * sizeof(char *));
	if (copy == NULL)
		handle_error_mem(array, copy);
	while (i < size)
	{
		copy[i] = ft_strdup(source[i]);
		if (copy[i] == NULL)
		{
			free_1_array(array);
			while (i > 0)
				free(copy[--i]);
			free(copy);
			perror("Error\n Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}