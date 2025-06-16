/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:03:56 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 23:11:18 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/* Extrait le chemin des textures en fonction de la position donnée,
	les assigne aux variables de la structure */
void	copy_path(struct s_array *array, char *line, char pos[2], int start)
{
	int	len;

	len = 0;
	if (pos[0] == 'N' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->no_path = ft_substr(line, start, len - 4);
	}
	else if (pos[0] == 'S' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->so_path = ft_substr(line, start, len - 4);
	}
	else if (pos[0] == 'W' && pos[1] == 'E')
	{
		len = ft_strlen(line);
		array->we_path = ft_substr(line, start, len - 4);
	}
	else if (pos[0] == 'E' && pos[1] == 'A')
	{
		len = ft_strlen(line);
		array->ea_path = ft_substr(line, start, len - 4);
	}
}

static void	error_parse_textures(struct s_array *array, char *line, char pos[2])
{
	printf("%s: path format incorrect: %s\n", pos, strerror(errno));
	free_array(array->sorted);
	exit(1);
}

/* get_next_line les 4 première lignes afin de parser les textures,
	parse également les position pour vérifier leurs cohérance */
void	check_position(struct s_array *array, char pos_1, char pos_2)
{
	char		*line;
	char		pos[2];
	int			i;
	static int	j = 0;

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
