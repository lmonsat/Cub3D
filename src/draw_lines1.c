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
    fov_angle = 2.0f * atanf(NUM_RAYS / cam_dist);

    //renvoie l' angle du joueur en radian
    player_angle = array->ray.rotation * PI / 180.0f;

    //renvoie l' angle de la ray en radian
    ray_angle = player_angle - (fov_angle / 2.0f) + (i * fov_angle / NUM_RAYS);

    raydirx = cos(ray_angle);
    raydiry = sin(ray_angle);

    //calcule la distance brut de la ray et la met dans array->ray.brutdist
    ft_dda_draw_ray(player, raydirx, raydiry, array);

    array->ray.perpdist = array->ray.brutdist * cos(ray_angle - player_angle);
    //printf("Distance no fisheye: %f\n", array->ray.perpdist);
    /*float hit_x = player->x_pixel / 40.0f + array->ray.perpdist * raydirx;
    float hit_y = player->y_pixel / 40.0f + array->ray.perpdist * raydiry;

    array->ray.wall_hit_x[(NUM_RAYS - 1) - i] = hit_x;
    array->ray.wall_hit_y[(NUM_RAYS - 1) - i] = hit_y;*/
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
    for (int i = 0; i < NUM_RAYS; i++)
    {
        printf("Rayon %3d : %f\n", i, pos->perp_tab[i]);
    }
}

void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{

    int i; 
    int j; 
    int xi; 
    int yi;
    float x; 
    float y;

    ft_init_line(pos, array, player);
    x = pos->x_pass;
    y = pos->y_pass;
    i = 0;
    while (i < NUM_RAYS/2)
    {
        x -= pos->dx_step;
        y -= pos->dy_step;
        i++;
    }
    i = 0;
    while (i < NUM_RAYS)
    {
        x += pos->dx_step;
        y += pos->dy_step;
        ft_init_line1(pos, player, x, y);
        loop(pos, array, player);
        distance(array, player, i);
        pos->perp_tab[(NUM_RAYS - 1) - i] = pos->perpdist;
        pos->hit_orien[(NUM_RAYS - 1) - i] = pos->orientation;
        i++;
    }
    print_perp_tab(pos); 
}
