/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:05:17 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 22:17:53 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/* Initialisation des variables utilisé par le flood fill */
char	**init_flood_fill(struct s_array *array, struct s_vars *vars,
		t_point *begin, t_point *size)
{
	char	**flooded_map;

	begin->x = (int)vars->player.pos.x;
	begin->y = (int)vars->player.pos.y;
	size->x = get_max_width(array->map);
	size->y = get_max_height(array->map);
	flooded_map = copy_array(array->map, array_len(array->map));
	return (flooded_map);
}

static int	fill(t_point *size, char target, int row, int col)
{
	if (row < 0 || col < 0 || row >= size->y || !size->tab[row]
		|| col >= (int)ft_strlen(size->tab[row]))
	{
		return (1);
	}
	if (size->tab[row][col] == ' ' || size->tab[row][col] == '\n'
		|| size->tab[row][col] == '\0')
	{
		return (1);
	}
	if (size->tab[row][col] != target)
		return (0);
	size->tab[row][col] = 'F';
	if ((row > 0 && fill(size, target, row - 1, col)) || (row < size->y - 1
			&& fill(size, target, row + 1, col)) || (col > 0 && fill(size,
				target, row, col - 1)) || (col < size->x - 1 && fill(size,
				target, row, col + 1)))
		return (1);
	return (0);
}

static void	free_flood_fill(struct s_array *array, char **tab)
{
	free_array(array->map);
	free_array(array->ceiling);
	free_array(array->floor);
	free_array(array->sorted);
	free_array(array->line);
	free_array(tab);
	free_path(array);
	exit(1);
}

void	flood_fill(struct s_array *array, char **tab, t_point size,
		t_point begin)
{
	char	target;
	int		i;

	i = 0;
	if (begin.y < 0 || begin.y >= size.y || begin.x < 0 || begin.x >= size.x
		|| !tab[begin.y] || !tab[begin.y][begin.x])
	{
		printf("Map building incorrect: Invalid starting position\n");
		free_flood_fill(array, tab);
	}
	tab[begin.y][begin.x] = '0';
	target = tab[begin.y][begin.x];
	if (fill(&size, target, begin.y, begin.x))
	{
		printf("Map building incorrect: Map is not closed\n");
		free_flood_fill(array, tab);
	}
	while (i < size.y && array->map[i])
	{
		printf("%s", array->map[i++]);
	}
}
