/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/14 16:38:04 by lmonsat          ###   ########.fr       */
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
	close(fd);
}

void check_position(int fd, struct s_array *array, char pos_1, char pos_2)
{
	char *line;
	char *path;
	int i;

	i = 0;
	line = get_next_line(fd);
	if (line[0] != pos_1 || line[1] != pos_2)
	{
		//perror("NO format not respected");
		printf("%c%c format incorrect: %s\n", pos_1, pos_2, strerror(errno));
		free_1_array(array);
		close(fd);
		exit(1);
	}
	while (line[i] != '.')
		i++;
	//printf("line[%d]: %c\n", i, line[i]);
	if (line[i] == '\n')
	{
		printf("path format incorrect: %s\n", strerror(errno));
		free_1_array(array);
		close(fd);
		exit(1);
	}
	if (line[i + 1] != '/')
	{
		printf("path format incorrect: %s\n", strerror(errno));
		free_1_array(array);
		close(fd);
		exit(1);
	}
	//ft_strncpy(array->path, array->line, )
	close(fd);
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
	fd = open_map_file(argv);
	check_position(fd, array, 'N', 'O');
	check_position(fd, array, 'S', 'O');
	check_position(fd, array, 'W', 'E');
	check_position(fd, array, 'E', 'A');
    //check_characters_in_map(array);
    //array->backtracking = copy_array(array->line, array);
    //backtracking(array, vars);
    //vars->player.collected = 0;
    vars->array = array;
}