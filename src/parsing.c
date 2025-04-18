/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/18 18:10:22 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	is_valid_char(char c)
{
	return (ft_strchr("10WSEN\n", c) != NULL);
}

void	check_characters_in_map(struct s_array *array)
{
	int	i;
	int	j;

	i = 0;
	while (array->line[i] != NULL)
	{
		j = 0;
		while (array->line[i][j] != '\0')
		{
			if (!is_valid_char(array->line[i][j]))
			{
				free_1_array(array);
				perror("Error\n Map contains unneeded characters");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	check_first_line(int fd, struct s_array *array)
{
	array->line = malloc(2048 * sizeof(char *));
	if (array->line == NULL)
	{
		perror("Error\n Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	array->elmt.cols = 0;
	array->line[0] = get_next_line(fd);
	if (array->line[0] == NULL)
	{
		free_1_array(array);
		perror("Error\n Map file is empty");
		exit(EXIT_FAILURE);
	}
	array->elmt.cols = ft_strlen(array->line[0]) - 1;
	array->elmt.first_line_nb_char = ft_strchr_count(array->line[0], '1');
}

void	check_player_start_pos(struct s_array *array,
		struct s_game_stats *value)
{
	int	i;

	value->nb_start_pos = 0;
	i = 0;
	while (1)
	{
		value->nb_start_pos += ft_strchr_count(array->line[i], 'W');
		value->nb_start_pos += ft_strchr_count(array->line[i], 'N');
		value->nb_start_pos += ft_strchr_count(array->line[i], 'S');
		value->nb_start_pos += ft_strchr_count(array->line[i], 'E');
		i++;
		if (array->line[i] == NULL)
			break ;
	}
	if (value->nb_start_pos != 1)
	{
		free_1_array(array);
		perror("Error\n More or less than 1 player start position");
		exit(EXIT_FAILURE);
	}
}

void	check_in_lines(int fd, struct s_array *array)
{
	int	line_nb_char;
	int	i;
	int	is_incomplete;

	is_incomplete = 0;
	i = 0;
	array->line_len = 0;
	array->elmt.rows = 0;
	while (1)
	{
		array->elmt.rows++;
		array->line[++i] = get_next_line(fd);
		if (array->line[i] == NULL)
			break ;
		array->line_len = ft_strlen(array->line[i]) - 1;
		line_nb_char = ft_strchr_count(array->line[i], '1');
		if (array->line[i][0] != '1' || array->line[i][array->line_len
			- 1] != '1' || array->elmt.cols != array->line_len)
			is_incomplete = 1;
	}
	array->line[array->elmt.rows + 1] = NULL;
	if (is_incomplete)
		free_in_lines(array);
}

/* Allocation dynamique a zéro de l'entièreté du fichier map */
void alloc_data_array(int fd, struct s_array *array, char *argv[])
{
	char *line;
	unsigned int len;
	int i;

	i = 0;
	len = 0;
	line = "value";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
    		break;
		len++;
		free(line);
	}
	printf("test len: %d\n", len);
	close(fd);
	fd = open_map_file(argv);
	array->line = calloc(len + 1, sizeof(char *));
	line = "value";
	while (array->line != NULL)
	{
		array->line[i] = get_next_line(fd);
		if (array->line[i] == NULL)
			break ;
		i++;
	}
	i = 0;
	while (i < len)
	{
		printf("%s", array->line[i++]);
	}
}
/* Extrait le chemin des textures en fonction de la position donnée, 
	les assigne aux variables de la structure */
void copy_path(struct s_array *array, char *line, char pos[2], int start)
{
	int len;

	len = 0;
	if (pos[0] == 'N' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->NO_path = ft_substr(line, start, len);
		printf("path: %s\n", array->NO_path);
	}
	else if (pos[0] == 'S' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->SO_path = ft_substr(line, start, len);
		printf("path: %s\n", array->SO_path);
	}
	else if (pos[0] == 'W' && pos[1] == 'E')
	{
		len = ft_strlen(line);
		array->WE_path = ft_substr(line, start, len);
		printf("path: %s\n", array->WE_path);
	}
	else if (pos[0] == 'E' && pos[1] == 'A')
	{
		len = ft_strlen(line);
		array->EA_path = ft_substr(line, start, len);
		printf("path: %s\n", array->EA_path);
	}
}

void error_parse_textures(int fd, struct s_array *array, char *line, char pos[2])
{
	printf("%s: path format incorrect: %s\n", pos, strerror(errno));
	free_1_array(array);
	free(line);
	close(fd);
	exit(1);
}

void error_parse_fc(int fd, struct s_array *array, char *line, char type)
{
	printf("%c: format incorrect: %s\n", type, strerror(errno));
	free_1_array(array);
	free(line);
	close(fd);
	exit(1);
}

/* get_next_line les 4 première lignes afin de parser les textures,
	parse également les position pour vérifier leurs cohérance */
void check_position(int fd, struct s_array *array, char pos_1, char pos_2)
{
	char *line;
	char pos[2];
	int i;

	i = 0;
	pos[0] = pos_1;
	pos[1] = pos_2;
	line = get_next_line(fd);
	if (line && (line[0] != pos[0] || line[1] != pos[1]))
	{
		error_parse_textures(fd, array, line, pos);
	}
	while ((line && line[i]) && line[i] != '.')
		i++;
	//printf("line[%d]: %c\n", i, line[i]);
	if (line && line[i] == '\n')
	{
		error_parse_textures(fd, array, line, pos);
	}
	if ((line && line[i] && line[i + 1]) && line[i + 1] != '/')
	{
		error_parse_textures(fd, array, line, pos);
	}
	copy_path(array, line, pos, i);
	free(line);
}

static char *fc_get_line(char *line, int fd)
{
	line = get_next_line(fd);
	while (1)
	{
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			break;
	}
	return (line);
}

static void fc_split_rgb(struct s_array *array, char *new_line, char *line, char type)
{
	if (type == 'F')
		array->floor = ft_split(new_line, ',');
	else if (type == 'C')
		array->ceiling = ft_split(new_line, ',');
	free(line);
	free(new_line);
}

/* Parse les lignes floor et ceiling, et extrait les valeurs RGB en allouant,
	un char ** pour ces valeurs */
void check_floor_and_ceilling(int fd, struct s_array *array, char type)
{
	char *line;
	char *new_line;
	int i;

	i = 0;
	line = fc_get_line(line, fd);
	printf("line[%d]: %c\n", i, line[i]);
	if (line[i] != type)
		error_parse_fc(fd, array, line, type);
	if (ft_strchr_count(line, ',') != 2)
		error_parse_fc(fd, array, line, type);
	while (line[++i] == ' ')
		continue ;
	new_line = ft_substr(line, i, ft_strlen(line));
	while (line[i] != '\n')
	{
		if (line[i] == ',')
			i++;
		if (!ft_isdigit(line[i]))
		{
			printf("%c: format incorrect: %s\n", type, strerror(errno));
			free_1_array(array);
			free(line);
			free(new_line);
			close(fd);
			exit(1);
		}
		i++;
	}
	fc_split_rgb(array, new_line, line, type);
}

void	parse_map(struct s_vars *vars, struct s_array *array,
    struct s_game_stats *value, char *argv[])
{
    int	fd;

    fd = open_map_file(argv);
    //check_first_line(fd, array);
    //check_in_lines(fd, array);
    //check_player_start_pos(array, value);
	alloc_data_array(fd, array, argv);
	close(fd);
	fd = open_map_file(argv);
	check_position(fd, array, 'N', 'O');
	check_position(fd, array, 'S', 'O');
	check_position(fd, array, 'W', 'E');
	check_position(fd, array, 'E', 'A');
	check_floor_and_ceilling(fd, array, 'F');
	check_floor_and_ceilling(fd, array, 'C');
    //check_characters_in_map(array);
    //array->backtracking = copy_array(array->line, array);
    //backtracking(array, vars);
    //vars->player.collected = 0;
    //vars->array = array;
}
