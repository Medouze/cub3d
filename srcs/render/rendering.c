/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/08 16:55:46 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(t_mlx mlx, int x, int y, int color)
{
	char *dst = mlx.address + y * mlx.size_line +  x * (mlx.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

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
		if (mlx.map[((int) tmp[1]) / mlx.scaling][((int) tmp[0]) / mlx.scaling])
		{
			hit = 1;
			if (fabs(delta[0]) > fabs(delta[1])) {
				if (delta[0] < 0)
					p.wall = EAST;
				else
					p.wall = WEST;
            } else {
				if (delta[0] < 0)
					p.wall = SOUTH;
				else
					p.wall = NORTH;
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

	delta[0] = (x * mlx.scaling - mlx.player.pos.x * mlx.scaling);
	delta[1] = (y * mlx.scaling - mlx.player.pos.y * mlx.scaling);
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	tmp[0] = mlx.player.pos.x * mlx.scaling;
	tmp[1] = mlx.player.pos.y * mlx.scaling;
	wall = near_wall(mlx, delta, tmp, color);
	return (wall);
} 

void draw_wall(t_mlx mlx, float x, float y, int i)
{
	t_point wall;
	char	*dst;

	wall = cast_ray(mlx, x, y, 0xFF0000);
	float dis = sqrtf((wall.x-mlx.player.pos.x) * (wall.x-mlx.player.pos.x) + (wall.y-mlx.player.pos.y) * (wall.y-mlx.player.pos.y));
	if (dis < mlx.player.view_distance)
	{
		float tmp = (float) mlx.player.view_distance / (float) HEIGHT; // store 1/600e of 100%;
		float count = mlx.player.view_distance;
		for (int j = 0; j < HEIGHT / 2; j++)
		{
			if (count > dis)
			{
				dst = mlx.address + ((HEIGHT / 2 - j) * mlx.size_line) + (i * (mlx.bits_per_pixel / 8));
				*(unsigned int *)dst = wall.wall;
				dst = mlx.address + ((HEIGHT / 2 + j) * mlx.size_line) + (i * (mlx.bits_per_pixel / 8));
				*(unsigned int *)dst = wall.wall;
				count -= tmp * 2;
			}
		}
	}
}

void render_wall(t_mlx mlx)
{
	t_point v1;
	t_point v2;

	v1 = calculate_point(&mlx, mlx.player.rotation + mlx.player.fov / 2);
	v2 = calculate_point(&mlx, mlx.player.rotation - mlx.player.fov / 2);

	float dif_x = (v1.x - v2.x) / WIDTH;
	float dif_y = (v1.y - v2.y) / WIDTH;
	int count = 0;
	while (count <= WIDTH)
	{
		draw_wall(mlx, v1.x, v1.y, count);
		v1.x -= dif_x;
		v1.y -= dif_y;
		count++;
	}
}

void draw_map(t_mlx mlx)
{
	t_point v1;
	t_point v2;

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int i = 0; i < mlx.scaling; i++)
			{
				for (int j = 0; j < mlx.scaling; j++)
				{
					char *dst = mlx.address + ((y * mlx.scaling + i) * mlx.size_line + (x * mlx.scaling + j) * (mlx.bits_per_pixel / 8));
					if (mlx.map[y][x] == 1)
						*(unsigned int *)dst = 0xFF0000;
					else
						*(unsigned int *)dst = 0x00FF00;
				}
			}
		}
	}
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

void render_frame(t_mlx mlx)
{
	if (mlx.img)
		mlx_destroy_image(mlx.mlx_ptr, mlx.img);
	mlx.img = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!mlx.img)
	{
		printf("ERROR");
		exit(0);
	}
	mlx.address = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endians);
	if (!mlx.address)
	{
		printf("ERROR");
		exit(0);
	}
	render_wall(mlx);
	if (mlx.show_map)
		draw_map(mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);
}

