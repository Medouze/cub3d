/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:45:11 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/14 22:32:25 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall_set(t_game *game, t_ray *ray, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		printf("y = %d, x = %d_n", ray->map_y, ray->map_x);
		if (game->map[ray->map_y][ray->map_x] == set[i])
			return (1);
	}
	return (0);
}

void	digital_differential_analyzer(t_game *game, t_ray *ray, char *set)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->x_step;
			ray->side_hit = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->y_step;
			ray->side_hit = VERTICAL;
		}
		if (is_wall_set(game, ray, set))
			hit = 1;
	}
	if (ray->side_hit == 0)
		ray->wall_dis = ray->side_dist_x - ray->delta_x;
	else
		ray->wall_dis = ray->side_dist_y - ray->delta_y;
}

void	init_raycasting(t_player *p, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->vector_x = p->vx + ray->plane_x * ray->camera_x;
	ray->vector_y = p->vy + ray->plane_y * ray->camera_x;
	ray->delta_x = 1e30;
	if (ray->vector_x != 0)
		ray->delta_x = fabs(1 / ray->vector_x);
	ray->delta_y = 1e30;
	if (ray->vector_y != 0)
		ray->delta_y = fabs(1 / ray->vector_y);
	ray->x_step = 1;
	if (ray->vector_x < 0)
	{
		ray->x_step = -1;
		ray->side_dist_x = (p->x - ray->map_x) * ray->delta_x;
	}
	else
		ray->side_dist_x = (ray->map_x + 1.0 - p->x) * ray->delta_x;
	ray->y_step = 1;
	if (ray->vector_y < 0)
	{
		ray->y_step = -1;
		ray->side_dist_y = (p->y - ray->map_y) * ray->delta_y;
	}
	else
		ray->side_dist_y = (ray->map_y + 1.0 - p->y) * ray->delta_y;
}

void	raycasting(t_game *game)
{
	t_player	p;
	t_ray		ray;
	int			x;

	p = game->player;
	ray.plane_x = -p.vy * tan(to_radians(p.fov) / 2);
	ray.plane_y = p.vx * tan(to_radians(p.fov) / 2);
	x = -1;
	while (++x < WIDTH)
	{
		ray.map_x = (int) p.x;
		ray.map_y = (int) p.y;
		init_raycasting(&p, &ray, x);
		digital_differential_analyzer(game, &ray, "1D");
		ray.wall.height = (int)(HEIGHT / ray.wall_dis);
		ray.wall.x = p.x + ray.wall_dis * ray.vector_x;
		ray.wall.y = p.y + ray.wall_dis * ray.vector_y;
		draw_wall_line(game, x, ray);
	}
}
