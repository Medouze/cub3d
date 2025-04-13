/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:45:23 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 11:19:38 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fetch_texture_color(int x, int y, t_img *img)
{
	int		offset;
	int		color;

	color = 0;
	if (x < img->width && y < img->height)
	{
		offset = (y * img->size_line + x * (img->bpp / 8));
		color = *(int *)(img->add + offset);
	}
	return (color);
}

void draw_collumn_loop(t_game *game, t_ray ray, float sprite[2], int x)
{
	int		y;
	int		color;
	int		start_wall;
	int		drawend;
	float	y_sprite_step;
	t_mlx	*mlx;

	mlx = &game->mlx;
	start_wall = -ray.wall.height / 2 + HEIGHT / 2;
	drawend = ray.wall.height / 2 + HEIGHT / 2;
	y_sprite_step = 64.0 / (float) ray.wall.height;
	y = -1;
	while (++y < drawend)
	{
		color = 0xFF0000;
		if (ray.side_hit == HORIZONTAL && ray.x_step < 0)
		{
			//printf("west = x = %f, y = %f\n", sprite[0], sprite[1]);
			color = fetch_texture_color(sprite[0], sprite[1], &game->west);
		}
		else if (ray.side_hit == HORIZONTAL)
		{
			//printf("east = x = %f, y = %f\n", sprite[0], sprite[1]);
			color = fetch_texture_color(sprite[0], sprite[1], &game->east);
		}
		else if (ray.y_step < 0)
		{
			//printf("north = x = %f, y = %f\n", sprite[0], sprite[1]);
			color = fetch_texture_color(sprite[0], sprite[1], &game->north);
		}
		else
			color = fetch_texture_color(sprite[0], sprite[1], &game->south);
		if (y < ray.wall.height && start_wall + y >= 0 && start_wall + y < HEIGHT)
			put_pixel(mlx, x, start_wall + y, color);
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
				* game->west.width;
		else
			sprite_xy[0] = (ray.wall.y - floor(ray.wall.y)) * game->east.width;
	}
	else
	{
		if (ray.y_step < 0)
			sprite_xy[0] = (ray.wall.x - floor(ray.wall.x)) * game->north.width;
		else
			sprite_xy[0] = fabs(1 - (ray.wall.x - floor(ray.wall.x)))
				* game->south.width;
	}
	sprite_xy[1] = 0;
	draw_collumn_loop(game, ray, sprite_xy, x);
}
