/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/04 00:02:17 by lmonsat          ###   ########.fr       */
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
        if (array->map[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel1(xi, yi, array, YELLOW);
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
    float wall_x;
    int tex_x;

    // FOV angle (en radians)
    fov_angle = 2.0f * atanf((float)NUM_RAYS / cam_dist);

    // Angle du joueur
    player_angle = array->ray.rotation * PI / 180.0f;

    // Angle du rayon actuel
    ray_angle = player_angle - (fov_angle / 2.0f) + (i * fov_angle / NUM_RAYS);

    raydirx = cos(ray_angle);
    raydiry = sin(ray_angle);

    // Appel DDA pour détecter le mur
    ft_dda_draw_ray(player, raydirx, raydiry, array);

    // Correction fisheye
    array->ray.perpdist = array->ray.brutdist * cos(ray_angle - player_angle);

    // Calcul point d'impact sur le mur
    if (array->ray.orientation == EAST || array->ray.orientation == WEST)
        wall_x = player->y_pixel / 40.0f + array->ray.perpdist * raydiry;
    else
        wall_x = player->x_pixel / 40.0f + array->ray.perpdist * raydirx;

    wall_x -= floorf(wall_x); // On garde uniquement la partie fractionnaire
    tex_x = (int)(wall_x * tex_width);

    // Correction pour certaines directions
    if ((array->ray.orientation == EAST && raydirx < 0) ||
        (array->ray.orientation == NORTH && raydiry > 0))
        tex_x = tex_width - tex_x - 1;
    array->ray.tex_x[(NUM_RAYS - 1) - i] = tex_x;
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

void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i;  
    float x; 
    float y;

    ft_init_line(pos, array, player);
    x = pos->x_pass;
    y = pos->y_pass;
    i = -1;
    while (++i < NUM_RAYS / 2)
    {
        x -= pos->dx_step;
        y -= pos->dy_step;
    }
    i = -1;
    while (++i < NUM_RAYS)
    {
        x += pos->dx_step;
        y += pos->dy_step;
        ft_init_line1(pos, player, x, y);
        loop(pos, array, player);
        distance(array, player, i);
        pos->perp_tab[(NUM_RAYS - 1) - i] = pos->perpdist;
        pos->hit_orien[(NUM_RAYS - 1) - i] = pos->orientation;
    }
}
