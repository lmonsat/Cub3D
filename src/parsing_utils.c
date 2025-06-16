/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:11:00 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 22:24:12 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	is_valid_char(char c)
{
	return (ft_strchr("10WSEN \n\t", c) != NULL);
}

/*	Permet de clear le buffer gnl entièrement car si l'on ne,
    parcourt pas jusqu'au EOF le buffer reste encore alloué dans gnl */
void	clear_line_gnl(int fd)
{
	char	*line;

	line = "value";
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

/* Trouve la première ligne de la map dans un char ** */
int	find_first_line(char **lines)
{
	char	*line;
	int		map_index;

	map_index = 0;
	while (lines[map_index] != NULL)
	{
		line = lines[map_index];
		if (line[0] == '1' || line[0] == ' ' || line[0] == '\t')
			break ;
		map_index++;
	}
	return (map_index);
}

/* Mesure la valeur max d'un element d'un char ** */
int	array_max_value(char **array)
{
	int	i;

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
