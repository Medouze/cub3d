/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:14 by qmorinea          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/17 22:04:13 by mlavergn         ###   ########.fr       */
=======
/*   Updated: 2025/04/17 16:35:12 by qmorinea         ###   ########.fr       */
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e
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

static t_img	*fetch_door_texture(t_game *game, char c1, char c2, int len)
{
	int	tmp;

	tmp = abs(c1 - c2);
	if (tmp % len == 0)
		return (&game->door_array[0]);
	else if (tmp % len == 1)
		return (&game->door_array[1]);
	else if (tmp % len == 2)
		return (&game->door_array[2]);
	else if (tmp % len == 3)
		return (&game->door_array[3]);
	else
		return (NULL);
}

t_img	*door_texture_animation(t_game *game, char c)
{
	t_img	*texture;
	int		len;

	len = 0;
	while (game->config->door_texture[len])
		len++;
	if (c == 'D')
		texture = &game->door_array[0];
	else if (c >= '2' && c <= '9')
		texture = fetch_door_texture(game, '2', c, len);
	else
		texture = fetch_door_texture(game, 's', c, len);
	return (texture);
}

void	open_door(t_game *game)
{
	float			dis_x;
	float			dis_y;
	struct timeval	tv;
	t_ray			ray;

	ray = detect_door(game);
	dis_x = fabs((ray.map_x + 0.5) - game->player.x);
	dis_y = fabs((ray.map_y + 0.5) - game->player.y);
	if (dis_x < 2 && dis_y < 2 && fmax(dis_x, dis_y) >= 0.7)
	{
		if (game->map[ray.map_y][ray.map_x] == 'D' && !game->is_animating)
		{
			gettimeofday(&tv, NULL);
			game->tmp_time = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
			game->is_animating = 1;
			game->map[ray.map_y][ray.map_x] = '2';
		}
		else if (game->map[ray.map_y][ray.map_x] == 'd' && !game->is_animating)
		{
			gettimeofday(&tv, NULL);
			game->tmp_time = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
			game->is_animating = 1;
			game->map[ray.map_y][ray.map_x] = 's';
		}
	}
}
<<<<<<< HEAD

t_img	*door_texture_animation(t_game *game, char c)
{
	t_img	*texture;

	texture = NULL;
	if (c == '5' || c == '9' || c == 'w' || c == 's' || c == 'D')
		texture = &game->door_array[0];
	if (c == '2' || c == '6' || c == 'z' || c == 'v')
		texture = &game->door_array[1];
	if (c == '3' || c == '7' || c == 'y' || c == 'u')
		texture = &game->door_array[2];
	if (c == '4' || c == '8' || c == 'x' || c == 't')
		texture = &game->door_array[3];
	return (texture);
}
=======
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e
