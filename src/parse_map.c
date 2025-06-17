/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:09:18 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 13:28:37 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	free_check_walls(struct s_array *array)
{
	free_array(array->line);
	free_array(array->sorted);
	free_array(array->ceiling);
	free_array(array->floor);
	free_path(array);
	exit(EXIT_FAILURE);
}

static void	check_walls_condition(struct s_array *array, int *i, int start,
		int end)
{
	int	j;

	j = 0;
	if ((*i) == 0 || array->map[(*i) + 1] == NULL)
	{
		j = start;
		while (j <= end)
		{
			if (array->map[(*i)][j] != '1')
			{
				printf("Error: map border not closed at line %d\n", (*i));
				free_check_walls(array);
			}
			j++;
		}
	}
	else
	{
		if (array->map[(*i)][start] != '1' || array->map[(*i)][end] != '1')
		{
			printf("Error: map not closed on sides at line %d\n", (*i));
			free_check_walls(array);
		}
	}
}

void	check_walls(struct s_array *array)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	while (array->map[i])
	{
		start = 0;
		while (array->map[i][start] == ' ')
			start++;
		end = ft_strlen(array->map[i]) - 1;
		while (end > start && (array->map[i][end] == ' '
			|| array->map[i][end] == '\n' || array->map[i][end] == '\t'))
			end--;
		check_walls_condition(array, &i, start, end);
		i++;
	}
}

static void	free_psp(struct s_array *array)
{
	free_array(array->line);
	free_array(array->map);
	free_array(array->sorted);
	free_array(array->floor);
	free_array(array->ceiling);
	free_path(array);
	exit(1);
}

/* Check si la position du joueur est marqué sur la map et,
		si elle est unique */
void	check_player_start_pos(struct s_array *array,
		struct s_game_stats *value)
{
	int	i;

	value->nb_start_pos = 0;
	i = 0;
	if (!array->map[i])
	{
		printf("Error: Map is missing\n");
		free_psp(array);
	}
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
		perror("Error\n More or less than 1 player start position");
		free_psp(array);
	}
}
