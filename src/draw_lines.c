/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/05 17:07:45 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_put_pixel(int x, int y, struct s_array *array, int color, int is_minimap)
{
    char *pxl;
	int map_x;
	int map_y;

    if (!is_minimap && (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height))
    {
        pxl = array->draw.addr + (y * array->line_len + x * (array->draw.bpp / 8));
        *(unsigned int *)pxl = color;
    }
    if (is_minimap)
    {
        map_x = x / 2;
        map_y = y / 2;
        if (map_x >= 0 && map_x < array->ray.width / 2 && map_y >= 0 && map_y < array->ray.height / 2)
        {
            pxl = array->draw.addr_map + (map_y * array->line_len_map + map_x * (array->draw.bpp_map / 8));
            *(unsigned int *)pxl = color;
        }
    }
}


void ft_draw_half_screen(struct s_array *array, int width, int height)
{
    int x, y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (y < height / 2)
                ft_put_pixel(x, y, array, BLUE, 0);
            else
                ft_put_pixel(x, y, array, BROWN, 0);
        }
    }
}

static void print_grid(struct s_array *array, int x, int y)
{
	if (array->map[(int)y / 40][(int)x / 40] == '1')
		ft_put_pixel(x, y, array, BLUE, 1);
	else
		ft_put_pixel(x, y, array, WHITE, 1);
}

void ft_draw_grid(struct s_array *array)
{
    int x;
    int y;

    x = 0;
    while (x < array->ray.width)
    {
        y = 0;
        while (y < array->ray.height)
        {
			print_grid(array, x, y);
            y++;
        }
        x += 40;
    }
    y = 0;
    while (y < array->ray.height)
    {
        x = 0;
        while (x < array->ray.width)
        {
    		print_grid(array, x, y);
            x++;
        }
        y += 40;
    }
}


/*void	ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	x = player->x;
	y = player->y;
	while (i < 1000)
	{
		if (array->map[(int)y / 40][(int)x / 40] == '1')
			break;
		ft_put_pixel((int)x, (int)y, array, RED, 0);
		x += pos->dx;
		y += pos->dy;
		i++;
	}
}*/

