/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/11 00:46:02 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	is_valid_char(char c)
{
	return (ft_strchr("10WSEN \n\t", c) != NULL);
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

/* Permet de vérifier qu'il n'y a pas de caractère incohérent dans la map */
void	check_characters_in_map(struct s_array *array)
{
	int	i;
	int	j;

	i = 0;
	while (array->map[i] != NULL)
	{
		j = 0;
		while (array->map[i][j] != '\0')
		{
			if (!is_valid_char(array->map[i][j]))
			{
				perror("Error\n Map contains unneeded characters");
				free_1_array(array);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
/* Check si la position du joueur est marqué sur la map et si elle est unique */
void	check_player_start_pos(struct s_array *array, struct s_game_stats *value)
{
	int	i;

	value->nb_start_pos = 0;
	i = 0;
	while (1)
	{
		value->nb_start_pos += ft_strchr_count(array->map[i], 'W');
		value->nb_start_pos += ft_strchr_count(array->map[i], 'N');
		value->nb_start_pos += ft_strchr_count(array->map[i], 'S');
		value->nb_start_pos += ft_strchr_count(array->map[i], 'E');
		i++;
		if (array->map[i] == NULL)
			break ;
	}
	if (value->nb_start_pos != 1)
	{
		free_1_array(array);
		perror("Error\n More or less than 1 player start position");
		exit(EXIT_FAILURE);
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

/* Trouve la première ligne de la map dans un char ** */
int find_first_line(char **lines)
{
    char *line;
    int map_index;

	map_index = 0;
    while (lines[map_index] != NULL)
    {
        line = lines[map_index];
        if (line[0] == '1' || line[0] == ' ' || line[0] == '\t')
            break;
        map_index++;
    }
    return (map_index);
}

/* Vérifie si l'on a bien la bonne ligne, step ici permet de s'assurer du bon ordre */
static int is_line_valid_for_step(char *line, int step)
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
static int index_data_array(struct s_array *array)
{
    int i;
    static int step = 0;

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
static int sort_data_array(struct s_array *array, unsigned int len)
{
	int i;
	int next;
	int map_index;

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
		//printf("test next: %d\n", next);
		if (next == -1)
			break;
		array->sorted[i] = ft_strdup(array->line[next]);
		i++;
	}
	array->sorted[i] = NULL;
	i = 0;
	return (map_index);
}

/* Allocation dynamique a zéro de l'entièreté du fichier map */
void alloc_data_array(int fd, struct s_array *array, char *argv[])
{
	char *line;
	unsigned int len;
	int i;

	i = 0;
	len = dynamic_map_lenght(fd, line);
	//printf("test len: %d\n", len);
	clear_line_gnl(fd);
	close(fd);
	fd = open_map_file(argv);
	//line = find_first_line(fd, &len);
	line = get_next_line(fd);
	//printf("len: %u\n", len);
	array->line = calloc(len + 1, sizeof(char *));
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
			break;
		array->line[i++] = line;
	}
	sort_data_array(array, len);
	i = 0;
	while (i < len)
	{
		printf("%s", array->line[i++]);
	}
	//clear_line_gnl(fd);
	close(fd);
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

void error_parse_textures(struct s_array *array, char *line, char pos[2])
{
	printf("%s: path format incorrect: %s\n", pos, strerror(errno));
	//free_1_array(array);
	free_array(array->sorted);
	//free(line);
	exit(1);
}

void error_parse_fc(struct s_array *array, char *line, char type)
{
	printf("%c: format incorrect: %s\n", type, strerror(errno));
	//free_1_array(array);
	free_array(array->sorted);
	//free(line);
	exit(1);
}

void error_parse_fc_2(struct s_array *array, char *line, char *new_line)
{
	//free_1_array(array);
	free_array(array->sorted);
	//free(line);
	free(new_line);
	exit(1);
}

/* get_next_line les 4 première lignes afin de parser les textures,
	parse également les position pour vérifier leurs cohérance */
void check_position(struct s_array *array, char pos_1, char pos_2)
{
	char *line;
	char pos[2];
	int i;
	static int j = 0;

	i = 0;
	pos[0] = pos_1;
	pos[1] = pos_2;
	line = array->sorted[j++];
	if (line && (line[0] != pos[0] || line[1] != pos[1]))
	{
		error_parse_textures(array, line, pos);
	}
	while ((line && line[i]) && line[i] != '.')
		i++;
	if (line && line[i] == '\n')
	{
		error_parse_textures(array, line, pos);
	}
	if ((line && line[i] && line[i + 1]) && line[i + 1] != '/')
	{
		error_parse_textures(array, line, pos);
	}
	copy_path(array, line, pos, i);
}

/* Permet de rechercher une ligne spécifique dans array->sorted */
static char *fc_get_line(struct s_array *array, char type)
{
	int i;
	
	i = 0;
	while (array->sorted[i])
	{
		if (array->sorted[i] && array->sorted[i][0] == type)
			break;
		i++;
	}
	if (!array->sorted[i])
		return (NULL);

	while (array->sorted[i] && !ft_strcmp(array->sorted[i], "\n"))
		i++;

	return (array->sorted[i]);
}

int array_len(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

/* Mesure la valeur max d'un element d'un char ** */
int array_max_value(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (1);
	while (array[i])
	{
		if (ft_atoi(array[i]) > 255 || ft_atoi(array[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

/* Découpe les différentes valeurs rgb de F et C et les attribut a des variables, 
	dans la structure */
static void fc_split_rgb(struct s_array *array, char *new_line, char *line, char type)
{
	int i;

	i = 0;
	if (type == 'F')
	{
		array->floor = ft_split(new_line, ',');
		if (array_max_value(array->floor))
			error_parse_fc(array, line, type);
	}
	else if (type == 'C')
	{
		array->ceiling = ft_split(new_line, ',');
		if (array_max_value(array->ceiling))
			error_parse_fc(array, line, type);
	}
	//free(line);
	free(new_line);
}

/* Parse les lignes floor et ceiling, et extrait les valeurs RGB en allouant,
	un char ** pour ces valeurs */
void check_floor_and_ceilling(struct s_array *array, char type)
{
	char *line;
	char *new_line;
	int i;

	i = 0;
	line = fc_get_line(array, type);
	//printf("line[%d]: %c\n", i, line[i]);
	if (line[i] != type)
		error_parse_fc(array, line, type);
	if (ft_strchr_count(line, ',') != 2)
		error_parse_fc(array, line, type);
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
			error_parse_fc_2(array, line, new_line);
		}
		i++;
	}
	fc_split_rgb(array, new_line, line, type);
}

int fill(char **tab, t_point size, char target, int row, int col)
{
    // Vérification des limites de la carte
    if (row < 0 || col < 0 || row >= size.y || col >= size.x || !tab[row] || !tab[row][col])
        return (1); 

    if (tab[row][col] == ' ' || tab[row][col] == '\n' || tab[row][col] == '\0')
        return (1);

    if (tab[row][col] != target)
        return (0);

    tab[row][col] = 'F';

    // Vérification des limites avant chaque appel récursif
    if ((row > 0 && fill(tab, size, target, row - 1, col)) ||
        (row < size.y - 1 && fill(tab, size, target, row + 1, col)) ||
        (col > 0 && fill(tab, size, target, row, col - 1)) ||
        (col < size.x - 1 && fill(tab, size, target, row, col + 1)))
        return (1);

    return (0);
}

static void free_flood_fill(struct s_array *array)
{
	free_array(array->map);
	free_array(array->ceiling);
	free_array(array->floor);
	free_path(array);
	exit(1);
}

void flood_fill(struct s_array *array, char **tab, t_point size, t_point begin)
{
    char target;
    int i;

    i = 0;
    // Vérification des limites avant d'accéder à la carte
    if (begin.y < 0 || begin.y >= size.y || begin.x < 0 || begin.x >= size.x ||
        !tab[begin.y] || !tab[begin.y][begin.x])
    {
        printf("Map building incorrect: Invalid starting position\n");
		free_flood_fill(array);
    }

    tab[begin.y][begin.x] = '0';
    target = tab[begin.y][begin.x];
    
    if (fill(tab, size, target, begin.y, begin.x))
    {
        printf("Map building incorrect: Map is not closed\n");
        free_flood_fill(array);
    }

    // Affichage de la carte pour debug
    while (i < size.y && array->map[i])
    {
        printf("%s", array->map[i++]);
    }
}

/* Permet d'extraire et de copier le map jouable depuis le char** stockant toutes
	les informations du fichier (allocation dynamique) */
void realloc_data_array(struct s_array *array)
{
    int start;
    int total_len;
    int new_len;
    int i;
    
    i = 0;
    start = find_first_line(array->line);
    total_len = array_len(array->line);
    new_len = total_len - start;
    
    array->map = calloc(new_len + 1, sizeof(char *));
    if (!array->map)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    while(i < new_len)
    {
        array->map[i] = ft_strdup(array->line[start + i]);
		printf("array->map[%d]: %s\n", i, array->map[i]);
        i++;
    }
    array->map[new_len] = NULL;
}

/* Si la map du joueur se retoruve en premier dans le fichier exit & free */
int is_map_first_in_file(int fd, struct s_array *array, char *argv[])
{
	char *line;

	fd = open_map_file(argv);
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

void parse_textures(struct s_array *array)
{
	check_position(array, 'N', 'O');
	check_position(array, 'S', 'O');
	check_position(array, 'W', 'E');
	check_position(array, 'E', 'A');
	check_floor_and_ceilling(array, 'F');
	check_floor_and_ceilling(array, 'C');
}

/* Initialisation des variables utilisé par le flood fill */
char **init_flood_fill(struct s_array *array, struct s_vars *vars, t_point *begin, t_point *size)
{
	char **flooded_map;

	begin->x = (int)vars->player.pos.x;
	begin->y = (int)vars->player.pos.y;
	size->x = get_max_width(array->map);
	size->y = get_max_height(array->map);
	flooded_map = copy_array(array->map, array_len(array->map));
	return (flooded_map);
}

/* Parsing du fichier entier MAP */
void	parse_map(struct s_vars *vars, struct s_array *array,
    struct s_game_stats *value, char *argv[])
{
    int	fd;
	t_point begin;
	t_point size;
	int map_index;
	char **flooded_map;
	
	fd = is_map_first_in_file(fd, array, argv);
	alloc_data_array(fd, array, argv);
	clear_line_gnl(fd);
	close(fd);
	realloc_data_array(array);
	parse_textures(array);
    check_characters_in_map(array);
	check_player_start_pos(array, value);
	mapping(array, vars); // la fonction mapping definie la position initial du joueur
	flooded_map = init_flood_fill(array, vars, &begin, &size);
	printf("test begin.x %d\n", begin.x);
	flood_fill(array, flooded_map, size, begin);
    free_array(array->sorted);
	free_array(array->line);
	free_array(flooded_map);
	vars->array = array;
}
