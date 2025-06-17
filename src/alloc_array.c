/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:10:20 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 15:19:59 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/* Définis la taille max pour array->line
	(prend en compte les textures et F C dans sa taille)*/
static unsigned int	dynamic_map_lenght(int fd, char *line)
{
	unsigned int	len;

	len = 0;
	line = "value";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len++;
		free(line);
	}
	return (len);
}

/* Vérifie si l'on a bien la bonne ligne,
	step ici permet de s'assurer du bon ordre */
static int	is_line_valid_for_step(char *line, int step)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	if (step == 0 && line[0] == 'N' && line[1] == 'O')
		return (1);
	if (step == 1 && line[0] == 'S' && line[1] == 'O')
		return (1);
	if (step == 2 && line[0] == 'W' && line[1] == 'E')
		return (1);
	if (step == 3 && line[0] == 'E' && line[1] == 'A')
		return (1);
	if (step == 4 && line[0] == 'F')
		return (1);
	if (step == 5 && line[0] == 'C')
		return (1);
	return (0);
}

/* Permet d'aller chercher le bon index dans array->line afin de suivre,
	l'ordre logique de la map */
static int	index_data_array(struct s_array *array)
{
	int			i;
	static int	step = 0;

	i = 0;
	while (array->line[i] != NULL)
	{
		if (is_line_valid_for_step(array->line[i], step))
			return (step++, i++);
		i++;
	}
	return (-1);
}

/* Permet de trier de manière logique le fichier de la map
	en suivant cette ordre : NO, WE, SO, EA, F, C */
static int	sort_data_array(struct s_array *array, unsigned int len, int fd)
{
	int	i;
	int	next;
	int	map_index;

	i = 0;
	next = 0;
	map_index = find_first_line(array->line);
	array->sorted = calloc(6 + 1, sizeof(char *));
	if (!array->sorted)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	while (next != -1 && array->line != NULL)
	{
		next = index_data_array(array);
		if (next == -1)
			break ;
		array->sorted[i] = ft_strdup(array->line[next]);
		i++;
	}
	array->sorted[i] = NULL;
	i = 0;
	close(fd);
	return (map_index);
}

/* Allocation dynamique a zéro de l'entièreté du fichier map */
void	alloc_data_array(int fd, struct s_array *array, char *argv[])
{
	char			*line;
	unsigned int	len;
	int				i;

	i = 0;
	len = dynamic_map_lenght(fd, line);
	clear_line_gnl(fd);
	close(fd);
	fd = open_map_file(argv);
	line = get_next_line(fd);
	array->line = ft_calloc(len + 1, sizeof(char *));
	if (!array->line)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	array->line[i++] = line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		array->line[i++] = line;
	}
	sort_data_array(array, len, fd);
}
