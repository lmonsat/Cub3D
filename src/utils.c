/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:35 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 01:25:45 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_path(struct s_array *array)
{
	if (array->no_path)
		free(array->no_path);
	if (array->so_path)
		free(array->so_path);
	if (array->we_path)
		free(array->we_path);
	if (array->ea_path)
		free(array->ea_path);
}

int	open_map_file(char *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n Error while opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_strchr_count(const char *s, int c)
{
	int	i;
	int	nb_char;

	nb_char = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			nb_char++;
		i++;
	}
	if ((char)c == '\0')
		return (0);
	return (nb_char);
}
