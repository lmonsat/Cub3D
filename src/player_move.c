/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/07 17:32:19 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	clear_image(struct s_array *array, int width, int height)
{
	int	x, y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_put_pixel(x, y, array, BLACK);
			x++;
		}
		y++;
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
                ft_put_pixel(x, y, array, BLUE);
            else
                ft_put_pixel(x, y, array, BROWN);
        }
    }
}


void	render_frame(struct s_vars *vars)
{
	clear_image(vars->array, vars->array->ray.width, vars->array->ray.height); // Efface tout avant de redessiner
	vars->array->ray.perp_tab = NULL;	// évite l'invalid free dans ft_init_line()
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	ft_draw_grid(vars->array);
	ft_draw_line(&vars->array->ray, vars->array, &vars->player.pos);
	fov(&vars->array->ray, vars->array, &vars->player.pos);//fonction necessaire au rendu 3d car elle cree l 'array de float
	ft_draw_half_screen(vars->array, vars->array->ray.width, vars->array->ray.height);
	draw_walls(&vars->array->ray, vars->array);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
	free(vars->array->ray.perp_tab);
}
