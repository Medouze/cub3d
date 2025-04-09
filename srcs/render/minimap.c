/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:31:04 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/09 18:03:44 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	near_wall(t_mlx mlx, float delta[2], float tmp[2], int color)
{
	t_point p;
	int hit;

	hit = 0;
	while (!hit)
	{
		put_pixel(mlx, roundf(tmp[0]), roundf(tmp[1]), color); //tmp
		tmp[0] += delta[0];
		tmp[1] += delta[1];
		if (mlx.map[((int) tmp[1]) / mlx.scaling][((int) tmp[0]) / mlx.scaling] == '1')
		{
			hit = 1;
			if (fabs(delta[0]) > fabs(delta[1])) {
				if (delta[0] < 0)
					p.color = EAST;
				else
					p.color = WEST;
            } else {
				if (delta[0] < 0)
					p.color = SOUTH;
				else
					p.color = NORTH;
            }
		}

	}
	p.x = tmp[0] / mlx.scaling;
	p.y = tmp[1] / mlx.scaling;
	return (p);
}

t_point cast_ray(t_mlx mlx, float x, float y, int color)
{
	float	delta[2];
	float	tmp[2];
	t_point	wall;
	float length;

	delta[0] = (x * mlx.scaling - mlx.player.x * mlx.scaling);
	delta[1] = (y * mlx.scaling - mlx.player.y * mlx.scaling);
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	tmp[0] = mlx.player.x * mlx.scaling;
	tmp[1] = mlx.player.y * mlx.scaling;
	wall = near_wall(mlx, delta, tmp, color);
	return (wall);
} 

void draw_map(t_mlx mlx)
{

	int y;
	int x;

	y = -1;
	while (++y < mlx.scaling && mlx.map[y])
	{
		x = -1;
		while (++x < mlx.scaling && mlx.map[y][x])
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

void	draw_fov(t_mlx mlx)
{
	t_point v1;
	t_point v2;

	v1 = calculate_point(&mlx, mlx.player.rotation + mlx.player.fov / 2);
	v2 = calculate_point(&mlx, mlx.player.rotation - mlx.player.fov / 2);
	cast_ray(mlx, v1.x, v1.y, 0xFFFF00);
	cast_ray(mlx, v2.x, v2.y, 0xFFFF00);

	float dif_x = (v1.x - v2.x) / WIDTH;
	float dif_y = (v1.y - v2.y) / WIDTH;
	int count = 0;
	while (count <= WIDTH)
	{
		cast_ray(mlx, v1.x, v1.y, 0xFFFF00);
		v1.x -= dif_x;
		v1.y -= dif_y;
		count++;
	}
}

void show_minimap(t_mlx mlx)
{
	draw_map(mlx);
	draw_fov(mlx);
}