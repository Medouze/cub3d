/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:45:23 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 11:14:09 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fetch_texture_color(int x, int y, t_img *img)
{
	int		offset;
	int		color;

	color = 0x000000;
	if (x < img->width && y < img->height)
	{
		offset = (y * img->size_line + x * (img->bpp / 8));
		color = *(int *)(img->add + offset);
	}
	return (color);
}

static t_img	*set_texture(t_game *game, t_ray *ray)
{
	if (game->map[ray->map_y][ray->map_x] != '0'
		&& game->map[ray->map_y][ray->map_x] != '1')
		return (door_texture_animation(game,
				game->map[ray->map_y][ray->map_x]));
	else
	{
		if (ray->side_hit == HORIZONTAL && ray->x_step < 0)
			return (&game->east);
		else if (ray->side_hit == HORIZONTAL)
			return (&game->west);
		else if (ray->y_step < 0)
			return (&game->south);
		else
			return (&game->north);
	}
}

static void	draw_collumn_loop(t_game *game, t_ray ray, float sprite[2], int x)
{
	int		y;
	int		start_wall;
	int		drawend;
	float	y_sprite_step;
	t_img	*texture;

	start_wall = -ray.wall.height / 2 + HEIGHT / 2;
	drawend = ray.wall.height / 2 + HEIGHT / 2;
	texture = set_texture(game, &ray);
	y_sprite_step = texture->height / (float) ray.wall.height;
	y = -1;
	while (++y < drawend && start_wall + y < HEIGHT)
	{
		if (y < ray.wall.height && start_wall + y >= 0)
			put_pixel(&game->mlx, x, start_wall + y,
				fetch_texture_color(sprite[0], sprite[1], texture));
		sprite[1] += y_sprite_step;
	}
}

void	draw_wall_line(t_game *game, int x, t_ray ray)
{
	float	sprite_xy[2];

	if (ray.side_hit == HORIZONTAL)
	{
		if (ray.x_step < 0)
			sprite_xy[0] = fabs(1 - (ray.wall.y - floor(ray.wall.y)))
				* game->east.width;
		else
			sprite_xy[0] = (ray.wall.y - floor(ray.wall.y)) * game->west.width;
	}
	else
	{
		if (ray.y_step < 0)
			sprite_xy[0] = (ray.wall.x - floor(ray.wall.x)) * game->south.width;
		else
			sprite_xy[0] = fabs(1 - (ray.wall.x - floor(ray.wall.x)))
				* game->north.width;
	}
	sprite_xy[1] = 0;
	draw_collumn_loop(game, ray, sprite_xy, x);
}
