/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/05/07 17:15:33 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"


void distance_central(struct s_array *array, struct s_position *player)
{
    float ray_angle;
    float player_angle;
    float raydirx;
    float raydiry;

    // Angle du joueur en radians
    player_angle = array->ray.rotation * PI / 180.0f;

    ray_angle = player_angle;

    raydirx = cos(ray_angle);
    raydiry = sin(ray_angle);

    ft_dda_draw_ray(player, raydirx, raydiry, array);
}

//attention cette fonction modifie mon point de depart pos->x.. me referer a player_x...
//que je ne modifie pas afin de garder la position du joueur en memoire
//pos-> x et y_pass a redefinir a chaque utilisation de la fonction
void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
   int i;
   int xi;
   int yi;

   i = 0;
   pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
   pos->dx /= pos->step;
   pos->dy /= pos->step;

   while (i < 1000)
   {
        xi = (int)roundf(pos->x_start);
        yi = (int)roundf(pos->y_start);
        if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
            break;
        if (array->line[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel(xi, yi, array, YELLOW);
        pos->x_start += pos->dx;
        pos->y_start += pos->dy;
        i++;
   }
   distance_central(array, player);
}

void distance(struct s_array *array, struct s_position *player, int i)
{
    float fov_angle;
    float ray_angle;
    float player_angle;
    float raydirx;
    float raydiry;

    //le premier 80 correspont a la taille du plan camera
    //le deuxieme 80 a la distance entre le joueur et le plan camera
    //fov angle est donner en radian
    fov_angle = 2.0f * atanf(80.0f / cam_dist);

    //renvoie l' angle du joueur en radian
    player_angle = array->ray.rotation * PI / 180.0f;

    //renvoie l' angle de la ray en radian
    ray_angle = player_angle - (fov_angle / 2.0f) + (i * fov_angle / 80.0f);

    raydirx = cos(ray_angle);
    raydiry = sin(ray_angle);

    //calcule la distance brut de la ray et la met dans array->ray.brutdist
    ft_dda_draw_ray(player, raydirx, raydiry, array);

    array->ray.perpdist = array->ray.brutdist * cos(ray_angle - player_angle);
    printf("Distance no fisheye: %f\n", array->ray.perpdist);
}

void distance1(struct s_array *array, struct s_position *player, int i)
{
    float fov_angle;
    float ray_angle;
    float player_angle;
    float raydirx;
    float raydiry;

    //le premier 80 correspont a la taille du plan camera
    //le deuxieme 80 a la distance entre le joueur et le plan camera
    //fov angle est donner en radian
    fov_angle = 2.0f * atanf(80.0f / 80.0f);

    //renvoie l' angle du joueur en radian
    player_angle = array->ray.rotation * PI / 180.0f;

    //renvoie l' angle de la ray en radian
    ray_angle = player_angle - (fov_angle / 2.0f) + (i * fov_angle / 80.0f);

    raydirx = cos(ray_angle);
    raydiry = sin(ray_angle);

    //calcule la distance brut de la ray et la met dans array->ray.brutdist
    ft_dda_draw_ray(player, raydirx, raydiry, array);

    array->ray.perpdist = array->ray.brutdist * cos(player_angle - ray_angle);
}

void print_perp_tab(struct s_trace_line *pos)
{
    printf("Contenu de pos->perp_tab (160 rayons de gauche à droite) :\n");
    for (int i = 0; i < 160; i++)
    {
        printf("Rayon %3d : %f\n", i, pos->perp_tab[i]);
    }
}

void swap_90(struct s_trace_line *pos) 
{
    int tmp;
    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;
}

void fov1(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    printf("fonction fov\n");
    int i, j, xi, yi;
    float x, y, ldx, ldy;

    //initiation des valeurs 
    ft_init_line(pos, array, player);

    //rotation de 90 degrées afin de dessiner le plan caméra
    swap_90(pos);

    // Normalisation pour parcourir la perpendiculaire
    pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
    pos->dx /= pos->step;
    pos->dy /= pos->step;

    x = pos->x_pass;
    y = pos->y_pass;

    // === 1ère moitié de la FOV ===
    for (i = 0; i < 80; i++)
    {
        x += pos->dx;
        y += pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;
        float prev_rx = rx;
        float prev_ry = ry;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
            {
                /*if (fabsf(rx - prev_rx) > fabsf(ry - prev_ry))
                {
                    printf("Mur touché en X\n");
                }
                else
                {
                    printf("Mur touché en Y\n");
                }*/
                break;
            }
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }
        distance(array, player, i);
        pos->perp_tab[79 - i] = pos->perpdist;
    }
    //=== 2ème moitié de la FOV (inverse) ===
    x = pos->x_pass;
    y = pos->y_pass;
    for (i = 0; i < 80; i++)
    {
        x -= pos->dx;
        y -= pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;
        float rx = player->x_pixel;
        float ry = player->y_pixel;
        float prev_rx = rx;
        float prev_ry = ry;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
            {
                /*if (fabsf(rx - prev_rx) > fabsf(ry - prev_ry))
                {
                    printf("Mur touché en X\n");
                }
                else
                {
                    printf("Mur touché en Y\n");
                }*/
                break;
            }
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }
        distance1(array, player, i);
        pos->perp_tab[80 + i] = pos->perpdist;
    }
}
void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i, j, xi, yi;
    float x, y, ldx, ldy;

    // Initialisation des valeurs
    ft_init_line(pos, array, player);

    // Normalisation pour parcourir la perpendiculaire au regard du joueur
    float dx_step = pos->dx_side;
    float dy_step = pos->dy_side;

    pos->step = fmaxf(fabsf(dx_step), fabsf(dy_step));
    dx_step /= pos->step;
    dy_step /= pos->step;

    x = pos->x_pass;
    y = pos->y_pass;

    // === 1ère moitié de la FOV ===
    for (i = 0; i < 80; i++)
    {
        x += dx_step;
        y += dy_step;

        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;

        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);

            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;

            if (array->line[yi / 40][xi / 40] == '1')
                break;

            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }

        distance(array, player, i);
        pos->perp_tab[79 - i] = pos->perpdist;
    }

    // === 2ème moitié de la FOV (inverse) ===
    x = pos->x_pass;
    y = pos->y_pass;

    for (i = 0; i < 80; i++)
    {
        x -= dx_step;
        y -= dy_step;

        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;

        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);

            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;

            if (array->line[yi / 40][xi / 40] == '1')
                break;

            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }

        distance1(array, player, i);
        pos->perp_tab[80 + i] = pos->perpdist;
    }
}

