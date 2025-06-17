/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceilling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:10:20 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 14:42:53 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	error_parse_fc_2(struct s_array *array, char *line, char *new_line)
{
	free_array(array->sorted);
	free(new_line);
	exit(1);
}

static void	error_parse_fc(struct s_array *array, char *line, char type)
{
	printf("%c: format incorrect: %s\n", type, strerror(errno));
	free_array(array->sorted);
	free_array(array->line);
	free_array(array->map);
	free_path(array);
	if (array->floor)
		free_array(array->floor);
	if (array->ceiling)
		free_array(array->ceiling);
	exit(1);
}

/* Permet de rechercher une ligne spécifique dans array->sorted */
static char	*fc_get_line(struct s_array *array, char type)
{
	int	i;

	i = 0;
	while (array->sorted[i])
	{
		if (array->sorted[i] && array->sorted[i][0] == type)
			break ;
		i++;
	}
	if (!array->sorted[i])
		return (NULL);
	while (array->sorted[i] && !ft_strcmp(array->sorted[i], "\n"))
		i++;
	return (array->sorted[i]);
}

/* Découpe les différentes valeurs rgb de F et C et les attribut,
	a des variables dans la structure */
static void	fc_split_rgb(struct s_array *array, char *new_line, char *line,
		char type)
{
	int	i;

	i = 0;
	if (type == 'F')
	{
		array->floor = ft_split(new_line, ',');
		free(new_line);
		if (array_max_value(array->floor))
			error_parse_fc(array, line, type);
	}
	else if (type == 'C')
	{
		array->ceiling = ft_split(new_line, ',');
		free(new_line);
		if (array_max_value(array->ceiling))
			error_parse_fc(array, line, type);
	}
}

/* Parse les lignes floor et ceiling, et extrait les valeurs RGB en allouant,
	un char ** pour ces valeurs */
void	check_floor_and_ceilling(struct s_array *array, char type)
{
	char	*line;
	char	*new_line;
	int		i;

	i = 0;
	line = fc_get_line(array, type);
	if (!line || line[i] != type)
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
