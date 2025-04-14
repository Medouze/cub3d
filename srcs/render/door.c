/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:14 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/14 12:35:17 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	detect_door(t_game *game)
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
	t_ray	ray;
	
	ray = detect_door(game);
	if (game->map[ray.map_y][ray.map_x] == 'D')
		game->map[ray.map_y][ray.map_x] = 'd';
	else if (game->map[ray.map_y][ray.map_x] == 'd')
		game->map[ray.map_y][ray.map_x] = 'D';
}