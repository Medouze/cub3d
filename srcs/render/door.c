/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:14 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/15 12:51:36 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	detect_door(t_game *game)
{
	t_player	p;
	t_ray		ray;

	p = game->player;
	ray.plane_x = -p.vy * tan(to_radians(p.fov) / 2);
	ray.plane_y = p.vx * tan(to_radians(p.fov) / 2);
	ray.map_x = (int) p.x;
	ray.map_y = (int) p.y;
	init_raycasting(&p, &ray, WIDTH / 2);
	digital_differential_analyzer(game, &ray, "1Dd");
	ray.wall.x = p.x + ray.wall_dis * ray.vector_x;
	ray.wall.y = p.y + ray.wall_dis * ray.vector_y;
	return (ray);
}

void	open_door(t_game *game)
{
	struct timeval tv;
	float	dis_x;
	float	dis_y;
	t_ray	ray;
		
	ray = detect_door(game);
	dis_x = fabs((ray.map_x + 0.5) - game->player.x);
	dis_y = fabs((ray.map_y + 0.5) - game->player.y);
	if (dis_x < 2 && dis_y < 2 && dis_x + dis_y >= 0.79)
	{
		printf("anim = %d\n", game->is_animating);
		if (game->map[ray.map_y][ray.map_x] == 'D' && !game->is_animating)
		{
			gettimeofday(&tv, NULL);
			game->tmp_time = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
			game->is_animating = 1;
			game->map[ray.map_y][ray.map_x] = '2';
		}
		else if (game->map[ray.map_y][ray.map_x] == 'd'  && !game->is_animating)
		{
			gettimeofday(&tv, NULL);
			game->tmp_time = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
			game->is_animating = 1;
			game->map[ray.map_y][ray.map_x] = 's';
		}	
	}
}
