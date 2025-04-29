/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:35 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/29 16:45:07 by lmonsat          ###   ########.fr       */
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
	/*i = 0;
	while (vars->array->backtracking[i] != NULL)
	{
		free(vars->array->backtracking[i]);
		i++;
	}
	free(vars->array->backtracking);*/
}

void free_array(char **array)
{
	int i;

	i = 0;
	if(!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void free_path(struct s_array *array)
{
	free(array->NO_path);
	free(array->SO_path);
	free(array->WE_path);
	free(array->EA_path);
}

void	free_1_array(struct s_array *array)
{
	int	i;

	if (!array || !array->line)
		return;
	i = 0;
	while (array->line[i])
	{
		free(array->line[i]);
		i++;
	}
	free(array->line);
	array->line = NULL;
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
	printf("fd vaut %d",fd);
	return (fd);
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

int	ft_strchr_count(const char *s, int c)
{
	int	i;
	int	nb_char;

	nb_char = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			nb_char++;
		i++;
	}
	if ((char)c == '\0')
		return (0);
	return (nb_char);
}

int get_max_width(char **array)
{
	int len;
	int i;
	int j;

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

int get_max_height(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
