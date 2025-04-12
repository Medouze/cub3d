/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:45:11 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 22:18:45 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	digital_differential_analyzer(t_game *game, t_ray *ray)
{
	int	hit;
	int	map_x;
	int	map_y;

	hit = 0;
	map_x = game->player.x;
	map_y = game->player.y;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			map_x += ray->x_step;
			ray->side_hit = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			map_y += ray->y_step;
			ray->side_hit = VERTICAL;
		}
		if (game->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (ray->side_hit == 0)
		ray->wall_dis = ray->side_dist_x - ray->delta_x;
	else
		ray->wall_dis = ray->side_dist_y - ray->delta_y;
}

void	raycasting(t_game *game)
{
	t_player	p;
	t_ray		ray;
	float		plane_x;
	float		plane_y;
	int			x;
	float		camera_x;
	int			map_x;
	int			map_y;

	p = game->player;
	plane_x = -p.vy * 0.66;
	plane_y = p.vx * 0.66;
	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray.vector_x = p.vx + plane_x * camera_x;
		ray.vector_y = p.vy + plane_y * camera_x;
		map_x = (int) p.x;
		map_y = (int) p.y;
		if (ray.vector_x == 0)
			ray.delta_x = 1e30;
		else
			ray.delta_x = fabs(1 / ray.vector_x);
		if (ray.vector_y == 0)
			ray.delta_y = 1e30;
		else
			ray.delta_y = fabs(1 / ray.vector_y);
		if (ray.vector_x < 0)
		{
			ray.x_step = -1;
			ray.side_dist_x = (p.x - map_x) * ray.delta_x;
		}
		else
		{
			ray.x_step = 1;
			ray.side_dist_x = (map_x + 1.0 - p.x) * ray.delta_x;
		}
		if (ray.vector_y < 0)
		{
			ray.y_step = -1;
			ray.side_dist_y = (p.y - map_y) * ray.delta_y;
		}
		else
		{
			ray.y_step = 1;
			ray.side_dist_y = (map_y + 1.0 - p.y) * ray.delta_y;
		}
		digital_differential_analyzer(game, &ray);
		ray.wall.height = (int)(HEIGHT / ray.wall_dis);
		ray.wall.x = p.x + ray.wall_dis * ray.vector_x;
		ray.wall.y = p.y + ray.wall_dis * ray.vector_y;
		draw_wall_line(game, x, ray);
	}
}
