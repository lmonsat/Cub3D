/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/04/14 17:18:31 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_put_pixel(int x, int y, struct s_array *array, int color)
{
	char *pxl;
	int width;
	int height;

	width = array->elmt.cols * 40;
	height = array->elmt.rows * 40;
	pxl = NULL;

	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		pxl = array->draw.addr + (y * array->line_len + x
		* (array->draw.bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void ft_draw_grid(struct s_array *array, struct s_vars *vars)
{
    int x, y;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;

    // Dessiner les lignes verticales
    for (x = 0; x < width; x += 40)
    {
        for (y = 0; y < height; y++)
        {
            if (array->line[(int)y / 40][(int)x / 40] == '1')
                ft_put_pixel(x, y, array, BLUE); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE);
        }
    }

    // Dessiner les lignes horizontales
    for (y = 0; y < height; y += 40)
    {
        for (x = 0; x < width; x++)
        {
            if (array->line[(int)y / 40][(int)x / 40] == '1')
                ft_put_pixel(x, y, array, BLUE); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE);
        }
    }
    // Envoyer l'image mise à jour dans la fenêtre
    mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
}
//algo DDA moins performant que bresenham car calcule de float
void ft_draw_line1(struct s_trace_line *pos, struct s_array *array, struct s_vars *vars, struct s_position *player)
{
    float dy;
    int swap;
    int x;
    int y;
    float var_y;
    int width;
    int height;

    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;

    width = array->elmt.cols * 40;
    height = array->elmt.rows * 40;

    pos->x_end = width - 1;
    pos->y_end = player->y_pixel;

    //calcule du taux de variation de la pente
    dy = (float)(pos->y_end - pos->y_start) / (float)(pos->x_end - pos->x_start);

    //defini si la ligne est plutot horizontal ou verticale
    if (fabsf(dy) < 1)
    {
        if (pos->x_start > pos->x_end)
        {
            //swap de x_start et x_end
            swap = pos->x_start;
            pos->x_start = pos->x_end;
            pos->x_end = swap;

            //swap de y_start et y_end
            swap = pos->y_start;
            pos->y_start = pos->x_start;
            pos->y_end = swap;
        }
        var_y = 0;
        x = pos->x_start;
        while (x <= pos->x_end )
        {
            y = round((float)pos->y_start + var_y);
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                //si la ray rencontre un mur elle s' arrete
                if (array->line[(int)y / 40][(int)x / 40] == '1')
                    break;
                ft_put_pixel(x, y, array, RED);
            }
            var_y += dy;
            x++;
        }
        mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
    }
}
// algo de bresenham inspirer de la version c++ https://www.youtube.com/watch?v=Frl1cLwfs1U
//todo: cree une fonction swap
//todo: mettre les variables dans une structure et ajouter une fonction data init
void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_vars *vars, struct s_position *player)
{
    int dx;
    int dy;
    int swap;
    int x_inc;
    int y_inc;
    int y;
    int d;
    int x;
    int width;
    int height;

    width = array->elmt.cols * 40;
    height = array->elmt.rows * 40;
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->x_end = width - 1;
    pos->y_end = player->y_pixel;
    dx = pos->x_end - pos->x_start;
    dy = pos->y_end - pos->y_start;

    if(abs(dx) > abs(dy))
    {
        if (pos->x_start > pos->x_end)
        {
              //swap de x_start et x_end
              swap = pos->x_start;
              pos->x_start = pos->x_end;
              pos->x_end = swap;

              //swap de y_start et y_end
              swap = pos->y_start;
              pos->y_start = pos->y_end;
              pos->y_end = swap;

              dx = -dx;
              dy = -dy;
        }
        y_inc = 1;
        if (dy < 0)
        {
            y_inc = -1;
            dy = -dy;
        }
        y = pos->y_start;
        d = 2 * dy - dx;
        x = pos->x_start;
        while(x <= pos->x_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                //si la ray rencontre un mur elle s' arrete
                if (array->line[(int)y / 40][(int)x / 40] == '1')
                    break;
                ft_put_pixel(x, y, array, GREEN);
            }
            if (d < 0)
                d += 2 * dy;
            else
            {
                d += 2 * (dy - dx);
                y += y_inc;
            }
            x++;
        }
    }
    else
    {
        if (pos->y_start > pos->y_end)
        {
                    //swap de x_start et x_end
                    swap = pos->x_start;
                    pos->x_start = pos->x_end;
                    pos->x_end = swap;

                    //swap de y_start et y_end
                    swap = pos->y_start;
                    pos->y_start = pos->y_end;
                    pos->y_end = swap;

                    dx = -dx;
                    dy = -dy;
        }
        x_inc = 1;
        if (dx < 0)
        {
            x_inc = -1;
            dx = -dx;
        }
        x = pos->x_start;
        d = 2 * (dx - dy);
        y = pos->y_start;
        while (y <= pos->y_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                 //si la ray rencontre un mur elle s' arrete
                if (array->line[(int)y / 40][(int)x / 40] == '1')
                    break;
                ft_put_pixel(x, y, array, RED);
            }
            if (d < 0)
                d += 2 * dx;
            else
            {
                d += 2 * (dx - dy);
                x += x_inc;
            }
            y++;
        }
    }
    mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
}
