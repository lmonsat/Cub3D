/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/04/29 15:19:50 by lmonsat          ###   ########.fr       */
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

void ft_draw_grid(struct s_array *array/*, struct s_vars *vars*/)
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
    //mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
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
/*void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_vars *vars, struct s_position *player)
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
    //int angle;

    width = array->elmt.cols * 40;
    height = array->elmt.rows * 40;
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->x_end = width - 1 + cos(60);
    pos->y_end = player->y_pixel + sin(80);
    printf("------------\nx start:%d\n y start:%d\n x end:%d\n y end:%d\n -----------\n", pos->x_start, pos->y_start, pos->x_end, pos->y_end);
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
}*/

//#define DEG2RAD(x) ((x) * M_PI / 180.0f)

/*void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_vars *vars, struct s_position *player)
{
    int dx, dy, swap, x_inc, y_inc, d, x, y;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;

    float angle_deg = 45.0f;                   // <- change ça pour tester différents angles
    float angle_rad = DEG2RAD(angle_deg);      // conversion en radians
    float ray_length = 1000.0f;                // distance max du rayon

    // Point de départ = joueur
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;

    // Point d’arrivée selon un angle et une distance
    pos->x_end = pos->x_start + cosf(angle_rad) * ray_length;
    pos->y_end = pos->y_start + sinf(angle_rad) * ray_length;

    // (le reste est inchangé — ton algo de Bresenham)
    dx = pos->x_end - pos->x_start;
    dy = pos->y_end - pos->y_start;

    if(abs(dx) > abs(dy))
    {
        if (pos->x_start > pos->x_end)
        {
            swap = pos->x_start; pos->x_start = pos->x_end; pos->x_end = swap;
            swap = pos->y_start; pos->y_start = pos->y_end; pos->y_end = swap;
            dx = -dx;
            dy = -dy;
        }
        y_inc = (dy < 0) ? -1 : 1;
        if (dy < 0) dy = -dy;
        y = pos->y_start;
        d = 2 * dy - dx;
        x = pos->x_start;
        while(x <= pos->x_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (array->line[y / 40][x / 40] == '1')
                    break;
                ft_put_pixel(x, y, array, GREEN);
            }
            if (d < 0) d += 2 * dy;
            else { d += 2 * (dy - dx); y += y_inc; }
            x++;
        }
    }
    else
    {
        if (pos->y_start > pos->y_end)
        {
            swap = pos->x_start; pos->x_start = pos->x_end; pos->x_end = swap;
            swap = pos->y_start; pos->y_start = pos->y_end; pos->y_end = swap;
            dx = -dx;
            dy = -dy;
        }
        x_inc = (dx < 0) ? -1 : 1;
        if (dx < 0) dx = -dx;
        x = pos->x_start;
        d = 2 * dx - dy;
        y = pos->y_start;
        while(y <= pos->y_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (array->line[y / 40][x / 40] == '1')
                    break;
                ft_put_pixel(x, y, array, RED);
            }
            if (d < 0) d += 2 * dx;
            else { d += 2 * (dx - dy); x += x_inc; }
            y++;
        }
    }
    mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
}*/

/*void ft_draw_line(struct s_trace_line *pos, struct s_array *array, float angle_deg, struct s_position *player)
{
    int dx, dy, swap, x_inc, y_inc, y, d, x;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;

    // Image temporaire pour le rayon
    //void *line_img = mlx_new_image(vars->mlx, width, height);
    //int *data = (int *)mlx_get_data_addr(line_img, &(int){0}, &(int){0}, &(int){0});
    //float angle_deg = 45.0f;                   // <- change ça pour tester différents angles
    float angle_rad = DEG2RAD(angle_deg);      // conversion en radians
    float ray_length = 1000.0f;                // distance max du rayon

    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->x_end = player->x_pixel + cos(angle_rad) * ray_length;
    pos->y_end = player->y_pixel + sin(angle_rad) * ray_length;

    dx = pos->x_end - pos->x_start;
    dy = pos->y_end - pos->y_start;

    if (abs(dx) > abs(dy))
    {
        if (pos->x_start > pos->x_end)
        {
            swap = pos->x_start; pos->x_start = pos->x_end; pos->x_end = swap;
            swap = pos->y_start; pos->y_start = pos->y_end; pos->y_end = swap;
            dx = -dx; dy = -dy;
        }
        y_inc = (dy < 0) ? -1 : 1;
        dy = abs(dy);
        y = pos->y_start;
        d = 2 * dy - dx;
        x = pos->x_start;

        while (x <= pos->x_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (array->line[y / 40][x / 40] == '1')
                    break;
                //data[y * width + x] = 0x00FF00; // GREEN pixel (format RGB)
                ft_put_pixel(x, y, array, RED);
            }
            if (d < 0) d += 2 * dy;
            else { d += 2 * (dy - dx); y += y_inc; }
            x++;
        }
    }
    else
    {
        if (pos->y_start > pos->y_end)
        {
            swap = pos->x_start; pos->x_start = pos->x_end; pos->x_end = swap;
            swap = pos->y_start; pos->y_start = pos->y_end; pos->y_end = swap;
            dx = -dx; dy = -dy;
        }
        x_inc = (dx < 0) ? -1 : 1;
        dx = abs(dx);
        x = pos->x_start;
        d = 2 * dx - dy;
        y = pos->y_start;

        while (y <= pos->y_end)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (array->line[y / 40][x / 40] == '1')
                    break;
                //data[y * width + x] = 0xFF0000; // RED pixel
                ft_put_pixel(x, y, array, RED);
            }
            if (d < 0) d += 2 * dx;
            else { d += 2 * (dx - dy); x += x_inc; }
            y++;
        }
    }
}*/

void ft_draw_line(struct s_trace_line *pos, struct s_array *array, float angle_deg, struct s_position *player)
{
    float angle_rad = DEG2RAD(angle_deg);
    float ray_length = 1000.0f;

    float x = player->x_pixel;
    float y = player->y_pixel;

    float dx = cos(angle_rad);
    float dy = sin(angle_rad);

    float step_size = 0.5f; // plus petit = plus précis
    float max_steps = ray_length / step_size;

    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;

    pos->x_start = (int)x;
    pos->y_start = (int)y;

    for (int i = 0; i < max_steps; i++)
    {
        int xi = (int)x;
        int yi = (int)y;

        if (xi < 0 || xi >= width || yi < 0 || yi >= height)
            break;

        if (array->line[yi / 40][xi / 40] == '1')
            break;

        ft_put_pixel(xi, yi, array, RED);

        x += dx * step_size;
        y += dy * step_size;
    }

    pos->x_end = (int)x;
    pos->y_end = (int)y;
}

void draw_fov(struct s_vars *vars)
{
    float first_line;
    float last_line;
    float current_angle;
    float rotation_offset;

    rotation_offset = vars->array->ray.rotation;
    first_line = -FOV / 2.0f;
    last_line = FOV / 2.0f;

    while (first_line <= last_line)
    {
        // On ajoute la rotation ici :
        current_angle = first_line + rotation_offset;

        // On garde l'angle entre 0 et 360
        if (current_angle < 0)
            current_angle += 360;
        if (current_angle >= 360)
            current_angle -= 360;

        ft_draw_line(&vars->array->ray, vars->array, current_angle, &vars->player.pos);
        first_line++;
    }
}


void draw_fov_360(struct s_vars *vars)
{
    float angle = 0.0f;

    // Tu peux changer ça pour + de rayons (ex: 0.5 pour plus de densité)
    float angle_step = 1.0f;

    while (angle < 60.0f)
    {
        ft_draw_line(&vars->array->ray, vars->array, angle, &vars->player.pos);
        angle += angle_step;
    }
}






