/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/22 23:14:51 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	is_valid_char(char c)
{
	return (ft_strchr("10WSEN \n\t", c) != NULL);
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

void player_start_pos(struct s_array *array)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (array->line[i])
	{
		/* code */
	}
	
}

/* Définis la taille max pour array->line 
	(prend en compte les textures et F C dans sa taille)*/
static unsigned int dynamic_map_lenght(int fd, char *line)
{
	unsigned int len;

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
	return (len);
}

/* Trouve la première ligne de la map pour copier uniquement la map, 
	dans le tableau*/
static char *find_first_line(int fd, unsigned int *total_len)
{
	char *line;
	char *cmp_line;
	unsigned int len;

	len = 0;
	line = "value";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if ((line[0] == '1' || line[0] == ' ' || line[0] == '\t')/* || !ft_strcmp(line, "\n")*/)
			break ;
		free(line);
		len++;
	}
	*total_len -= len;
	return(line);
}

static int index_data_array(struct s_array *array)
{
	static int i = 0;

	while (array->line[i] != NULL)
	{
		printf("%s", array->line[i]);
		if (array->line[i][0] == 'N' && array->line[i][1] == 'O')
		{
			return (i++);
		}
		else if (array->line[i][0] == 'S' && array->line[i][1] == 'O')
		{
			return (i++);
		}
		else if (array->line[i][0] == 'W' && array->line[i][1] == 'E')
		{
			return (i++);
		}
		else if (array->line[i][0] == 'W' && array->line[i][1] == 'E')
		{
			return (i++);
		}
		else if (array->line[i][0] == 'F')
		{
			return (i++);
		}
		else if (array->line[i][0] == 'C')
		{
			return (i++);
		}
		else
		{
			return (-1);
		}
	}
	return (i);
}

static void sort_data_array(struct s_array *array, unsigned int len)
{
	int i;
	int next;
	char **array_sorted;

	i = 0;
	next = 0;
	array_sorted = calloc(len + 1, sizeof(char *));
	if (!array_sorted)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	while (next != -1 && array->line != NULL)
	{
		printf("test\n");
		next = index_data_array(array);
		if (next == -1)
			break;
		array_sorted[i] = array->line[next];
		i++;
	}
	i = 0;
	while (i < len)
	{
		printf("%s", array_sorted[i]);
		i++;
	}
	exit(1);
}

/* Allocation dynamique a zéro de l'entièreté du fichier map */
void alloc_data_array(int fd, struct s_array *array, char *argv[])
{
	char *line;
	unsigned int len;
	int i;

	i = 0;
	len = dynamic_map_lenght(fd, line);
	printf("test len: %d\n", len);
	close(fd);
	fd = open_map_file(argv);
	line = find_first_line(fd, &len);
	printf("len: %u\n", len);
	array->line = calloc(len + 1, sizeof(char *));
	if (!array->line)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	array->line[i++] = line; 
	while (array->line != NULL)
	{
		array->line[i] = get_next_line(fd);
		if (array->line[i] == NULL)
			break ;
		i++;
	}
	sort_data_array(array, len);
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
		//printf("path: %s\n", array->NO_path);
	}
	else if (pos[0] == 'S' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->SO_path = ft_substr(line, start, len);
		//printf("path: %s\n", array->SO_path);
	}
	else if (pos[0] == 'W' && pos[1] == 'E')
	{
		len = ft_strlen(line);
		array->WE_path = ft_substr(line, start, len);
		//printf("path: %s\n", array->WE_path);
	}
	else if (pos[0] == 'E' && pos[1] == 'A')
	{
		len = ft_strlen(line);
		array->EA_path = ft_substr(line, start, len);
		//printf("path: %s\n", array->EA_path);
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

void error_parse_fc_2(int fd, struct s_array *array, char *line, char *new_line)
{
	free_1_array(array);
	free(line);
	free(new_line);
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

static char *fc_get_line(int fd)
{
	char *line;
	
	line = get_next_line(fd);
	while (1)
	{
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			break ;
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
	line = fc_get_line(fd);
	//printf("line[%d]: %c\n", i, line[i]);
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
			error_parse_fc_2(fd, array, line, new_line);
		}
		i++;
	}
	fc_split_rgb(array, new_line, line, type);
}

int fill(char **tab, t_point size, char target, int row, int col)
{
    if (row < 0 || col < 0 || row >= size.y || col >= size.x)
        return (0); 

    if (tab[row][col] == ' ' || tab[row][col] == '\n' || tab[row][col] == '\0' )
        return (1);

    if (tab[row][col] != target)
        return (0);

    tab[row][col] = 'F';

    if (fill(tab, size, target, row - 1, col) ||
        fill(tab, size, target, row + 1, col) ||
        fill(tab, size, target, row, col - 1) ||
        fill(tab, size, target, row, col + 1))
        return (1);

    return (0);
}

void flood_fill(struct s_array *array, char **tab, t_point size, t_point begin)
{
    char target;
	int i;

	i = 0;
	tab[begin.y][begin.x] = '0';
	target = tab[begin.y][begin.x];
	if (fill(tab, size, target, begin.y, begin.x))
	{
		printf("Map building incorrect\n");
		free_1_array(array);
		free_array(array->ceiling);
		free_array(array->floor);
		free_path(array);
		exit(1);
	}
	while (i < 15)
	{
		printf("%s", array->line[i++]);
	}
}
/*	Permet de clear le buffer gnl entièrement car si l'on ne parcourt par jusqu'au EOF,
	le buffer reste encore alloué dans gnl */
void clear_line_gnl(int fd)
{
	char *line;
	
	line = "value";
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
}

void	parse_map(struct s_vars *vars, struct s_array *array,
    struct s_game_stats *value, char *argv[])
{
    int	fd;
	t_point begin;
	t_point size;

    fd = open_map_file(argv);
	alloc_data_array(fd, array, argv);
	close(fd);
	/*fd = open(argv[1], O_RDWR);
	char *line;

	line = "value";
	while (line)
	{
		get_next_line(fd);
		write(fd, &"\0", 4);
	}
	close(fd);
	exit(1);*/
	fd = open_map_file(argv);
	check_position(fd, array, 'N', 'O');
	check_position(fd, array, 'S', 'O');
	check_position(fd, array, 'W', 'E');
	check_position(fd, array, 'E', 'A');
	check_floor_and_ceilling(fd, array, 'F');
	check_floor_and_ceilling(fd, array, 'C');
	clear_line_gnl(fd);
    check_characters_in_map(array);
	check_player_start_pos(array, value);
	mapping(array, vars); // la fonction mapping definie la position initial du joueur 
	begin.x = (int)vars->player.pos.x;
	begin.y = (int)vars->player.pos.y;
	size.x = get_max_width(array->line);
	size.y = get_max_height(array->line);
	flood_fill(array, array->line, size, begin);
    //vars->array = array;
}
