/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 15:12:06 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	parse_textures(struct s_array *array)
{
	check_position(array, 'N', 'O');
	check_position(array, 'S', 'O');
	check_position(array, 'W', 'E');
	check_position(array, 'E', 'A');
	check_floor_and_ceilling(array, 'F');
	check_floor_and_ceilling(array, 'C');
}

/* Permet d'extraire et de copier le map jouable depuis
	le char** stockant toutes les informations,
	du fichier (allocation dynamique) */
void	realloc_data_array(struct s_array *array)
{
	int	start;
	int	total_len;
	int	new_len;
	int	i;

	i = 0;
	start = find_first_line(array->line);
	total_len = array_len(array->line);
	new_len = total_len - start;
	array->map = ft_calloc(new_len + 1, sizeof(char *));
	if (!array->map)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	while (i < new_len)
	{
		array->map[i] = ft_strdup(array->line[start + i]);
		printf("array->map[%d]: %s\n", i, array->map[i]);
		i++;
	}
	array->map[new_len] = NULL;
}

static int	is_map_empty(int fd, char *argv[], struct s_array *array)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		printf("Map file empty\n");
		free(line);
		exit(1);
	}
	free(line);
	clear_line_gnl(fd);
	close(fd);
	fd = open_map_file(argv);
	return (fd);
}

/* Si la map du joueur se retoruve en premier dans,
		le fichier exit & free */
int	is_map_first_in_file(int fd, struct s_array *array, char *argv[])
{
	char	*line;

	fd = open_map_file(argv);
	fd = is_map_empty(fd, argv, array);
	line = ft_strdup("\n");
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
		if (line[0] == ' ' || line[0] == '\t' || line[0] == '1')
		{
			free(line);
			clear_line_gnl(fd);
			close(fd);
			printf("Map before textures\n");
			exit(1);
		}
	}
	free(line);
	clear_line_gnl(fd);
	close(fd);
	fd = open_map_file(argv);
	return (fd);
}

/* Parsing du fichier entier MAP */
void	parse_map(struct s_vars *vars, struct s_array *array,
		struct s_game_stats *value, char *argv[])
{
	int		fd;
	t_point	begin;
	t_point	size;
	int		map_index;
	char	**flooded_map;

	array->floor = NULL;
	array->ceiling = NULL;
	fd = is_map_first_in_file(fd, array, argv);
	alloc_data_array(fd, array, argv);
	clear_line_gnl(fd);
	close(fd);
	realloc_data_array(array);
	parse_textures(array);
	check_characters_in_map(array);
	check_walls(array);
	check_player_start_pos(array, value);
	mapping(array, vars);
	flooded_map = init_flood_fill(array, vars, &begin, &size);
	size.tab = flooded_map;
	flood_fill(array, size.tab, size, begin);
	free_array(array->sorted);
	free_array(array->line);
	free_array(size.tab);
	vars->array = array;
}
