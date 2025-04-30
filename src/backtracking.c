/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:05:24 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/30 19:19:59 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	visited_mem_free(int **visited, int i)
{
	int	k;

	k = 0;
	perror("Failed to allocate memory for visited row");
	while (k < i)
	{
		free(visited[k]);
		k++;
	}
	free(visited);
}

void	visited_mem_alloc(struct s_array *array)
{
	int	i;

	i = 0;
	array->visited = malloc((array->elmt.rows + 1) * sizeof(int *));
	if (array->visited == NULL)
	{
		free_1_array(array);
		perror("Error\n Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while (i < array->elmt.rows)
	{
		array->visited[i] = malloc(array->elmt.cols * sizeof(int));
		if (array->visited[i] == NULL)
		{
			visited_mem_free(array->visited, i);
			return ;
		}
		ft_memset(array->visited[i], 0, array->elmt.cols * sizeof(int));
		i++;
	}
	array->visited[array->elmt.rows] = NULL;
}

int	is_valid(struct s_array *array, int row, int col)
{
	int	is_free_space;
	int	not_visited;

	//is_free_space = array->backtracking[row][col] != '1';
	//not_visited = !array->visited[row][col];
	return (1);
}

int	searching_map(struct s_array *array, int new_row, int new_col)
{
	if (is_valid(array, new_row, new_col))
	{
		if (array->stats.collected == array->stats.nb_collectibles
			&& array->is_exitable == 1)
		{
			return (1);
		}
		if (array->backtracking[new_row][new_col] == 'C')
		{
			array->stats.collected++;
			array->backtracking[new_row][new_col] = '0';
		}
		if (array->backtracking[new_row][new_col] == 'E')
			array->is_exitable = 1;
		if (array->backtracking[new_row][new_col] == '0'
			|| array->backtracking[new_row][new_col] == 'E')
		{
			if (can_reach(array, new_row, new_col)
				&& array->stats.collected == array->stats.nb_collectibles)
			{
				return (1);
			}
		}
	}
	return (0);
}

void	moving_in_rows(int dr[4])
{
	dr[0] = -1;
	dr[1] = 1;
	dr[2] = 0;
	dr[3] = 0;
}

void	moving_in_cols(int dc[4])
{
	dc[0] = 0;
	dc[1] = 0;
	dc[2] = -1;
	dc[3] = 1;
}

int	can_reach(struct s_array *array, int row, int col)
{
	int	new_row;
	int	new_col;
	int	i;

	if (array->backtracking[row][col] == 'E')
		return (1);
	array->visited[row][col] = 1;
	moving_in_rows(array->move.dr);
	moving_in_cols(array->move.dc);
	i = 0;
	while (i < 4)
	{
		new_row = row + array->move.dr[i];
		new_col = col + array->move.dc[i];
		if (searching_map(array, new_row, new_col))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_can_reach(struct s_array *array, int player_row, int player_col)
{
	array->is_exitable = 0;
	array->stats.collected = 0;
	if (!can_reach(array, player_row, player_col))
	{
		/*free_arrays(array);
		free_visited(array);
		perror("Error\n Exit or collectibles are unreachable\n");
		exit(EXIT_FAILURE);*/
	}
}

void	backtracking(struct s_array *array, struct s_vars *vars)
{
	int	i;
	int	j;

	visited_mem_alloc(array);
	i = 0;
	while (i < array->elmt.rows)
	{
		j = 0;
		while (j < array->elmt.cols)
		{
			if (array->backtracking[i][j] == 'P')
			{
				vars->player.pos.y = i;
				vars->player.pos.x = j;
				break ;
			}
			j++;
		}
		i++;
	}
	//handle_can_reach(array, vars->player.pos.y, vars->player.pos.x);
}
