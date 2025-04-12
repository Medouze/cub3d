/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:31:04 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 15:00:45 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	near_wall(t_mlx mlx, float delta[2], int color)
{
	float	p_x;
	float	p_y;

	p_x = mlx.player.x * mlx.scaling;
	p_y = mlx.player.y * mlx.scaling;
	int i = -1;
	while (++i < mlx.scaling * 2)
	{
		put_pixel(mlx, roundf(p_x), roundf(p_y), color);
		p_x += delta[0];
		p_y += delta[1];
		if (mlx.map[(int) p_y / mlx.scaling][(int) p_x / mlx.scaling] == '1')
			break;
	}
}

void cast_ray(t_mlx mlx, float x, float y, int color)
{
	float	delta[2];
	float length;

	delta[0] = x;
	delta[1] = y;
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	near_wall(mlx, delta, color);
}

void draw_map(t_mlx mlx)
{

	int y;
	int x;

	y = -1;
	while (mlx.map[++y])
	{
		x = -1;
		while (mlx.map[y][++x])
		{
			for (int i = 0; i < mlx.scaling; i++)
			{
				for (int j = 0; j < mlx.scaling; j++)
				{
					char *dst = mlx.address + ((y * mlx.scaling + i) * mlx.size_line + (x * mlx.scaling + j) * (mlx.bits_per_pixel / 8));
					if (mlx.map[y][x] == '1')
						*(unsigned int *)dst = 0xFFFFFF;
					else
						*(unsigned int *)dst = 0x000000;
				}
			}
		}
	}
}

t_point	calculate_point(t_mlx *mlx, int rotation)
{
	float	x;
	float	y;
	t_point p;

	p.x = mlx->player.vx;
	p.y = mlx->player.vy;
	
	x = cos(to_radians(rotation)) * (p.x) - sin(to_radians(rotation)) * (p.y);
	y = sin(to_radians(rotation)) * (p.x) - cos(to_radians(rotation)) * (p.y);
	p.x = x;
	p.y = y;
	return (p);
}

void	draw_fov(t_mlx mlx)
{
	int i = -1;
	float vx;
	float vy;
	mlx.player.fov = 66;
	float angle = to_radians(-(mlx.player.fov / 2));
	float step = (float) to_radians(mlx.player.fov / (float) WIDTH);
	while (++i < WIDTH)
	{
		vx = mlx.player.vx * cos(angle) - mlx.player.vy * sin(angle);
		vy = mlx.player.vx * sin(angle) + mlx.player.vy * cos(angle);
		cast_ray(mlx, vx, vy, 0xFFFF00);
		angle += step;
	}
}

void cast_ray_player(t_mlx mlx, float x, float y, int color)
{
	float	delta[2];
	float length;

	delta[0] = x;
	delta[1] = y;
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	float	p_x;
	float	p_y;

	p_x = mlx.player.x * mlx.scaling;
	p_y = mlx.player.y * mlx.scaling;
	int i = -1;
	while (++i < mlx.scaling / 4)
	{
		put_pixel(mlx, roundf(p_x), roundf(p_y), color);
		p_x += delta[0];
		p_y += delta[1];
		if (mlx.map[(int) p_y / mlx.scaling][(int) p_x / mlx.scaling] == '1')
			break;
	}
}

void	draw_player(t_mlx mlx)
{
	int i = -1;
	float vx;
	float vy;

	while (++i < 360)
	{
		vx = mlx.player.vx * cos(to_radians(i)) - mlx.player.vy * sin(to_radians(i));
		vy = mlx.player.vx * sin(to_radians(i)) + mlx.player.vy * cos(to_radians(i));
		cast_ray_player(mlx, vx, vy, 0xFF0000);
	}
}

void show_minimap(t_mlx mlx)
{
	int x_max = 33;
	int y_max = 14;
	int width_map = 200;

	mlx.scaling = width_map / fmax(y_max, x_max);
	mlx.scaling = 20;
	draw_map(mlx);
	draw_fov(mlx);
	draw_player(mlx);
}