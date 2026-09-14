/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:03:56 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 01:27:02 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/* Extrait le chemin des textures en fonction de la position donnée,
	les assigne aux variables de la structure (-1 pour "\n") */
void	copy_path(struct s_array *array, char *line, char pos[2], int start)
{
	int	len;

	len = 0;
	if (pos[0] == 'N' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->no_path = ft_substr(line, start, (len - start - 1));
	}
	else if (pos[0] == 'S' && pos[1] == 'O')
	{
		len = ft_strlen(line);
		array->so_path = ft_substr(line, start, (len - start - 1));
	}
	else if (pos[0] == 'W' && pos[1] == 'E')
	{
		len = ft_strlen(line);
		array->we_path = ft_substr(line, start, (len - start - 1));
	}
	else if (pos[0] == 'E' && pos[1] == 'A')
	{
		len = ft_strlen(line);
		array->ea_path = ft_substr(line, start, (len - start - 1));
	}
}

static void	init_pointer_error(struct s_array *array, char pos[2])
{
	if (pos[0] == 'N' && pos[1] == 'O')
	{
		array->no_path = NULL;
		array->so_path = NULL;
		array->we_path = NULL;
		array->ea_path = NULL;
	}
	else if (pos[0] == 'S' && pos[1] == 'O')
	{
		array->so_path = NULL;
		array->we_path = NULL;
		array->ea_path = NULL;
	}
	else if (pos[0] == 'W' && pos[1] == 'E')
	{
		array->we_path = NULL;
		array->ea_path = NULL;
	}
	else if (pos[0] == 'E' && pos[1] == 'A')
		array->ea_path = NULL;
}

static void	error_parse_textures(struct s_array *array, char pos[2])
{
	printf("%s: path format incorrect: %s\n", pos, strerror(errno));
	free_array(array->line);
	free_array(array->sorted);
	free_array(array->map);
	init_pointer_error(array, pos);
	free_path(array);
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
	if (!line)
		error_parse_textures(array, pos);
	if ((line) && (line[0] != pos[0] || line[1] != pos[1]))
		error_parse_textures(array, pos);
	while ((line && line[i]) && line[i] != '.')
		i++;
	if ((line) && (line[i] == '\n' || line[i] == '\0'))
		error_parse_textures(array, pos);
	if ((line && line[i] && line[i + 1]) && line[i + 1] != '/')
		error_parse_textures(array, pos);
	copy_path(array, line, pos, i);
}
