/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/08 22:51:10 by qmorinea         ###   ########.fr       */
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

t_point	raycast(t_mlx mlx, float rad_angle)
{
	int		hit;
	t_point	p;
	float	delta[2];


	
	hit = 0;
	delta[0] = cos(rad_angle);
	delta[1] = sin(rad_angle);
	float x;
	float y;

	x = mlx.player.x * mlx.scaling;
	y = mlx.player.y * mlx.scaling;
	while (!hit)
	{
		//put_pixel(mlx, roundf(x), roundf(y), 0xFFFFFF); //tmp
		x += delta[0];
		y += delta[1];
		if (mlx.map[(int) (y / mlx.scaling)][(int) (x / mlx.scaling)] == '1')
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
	p.x = x / mlx.scaling;
	p.y = y / mlx.scaling;
	return (p);
}

void render_wall(t_mlx mlx)
{
	// test
	int line = -1;

	t_point v = calculate_point(&mlx, mlx.player.rotation);
	float step = to_radians((float) mlx.player.fov / (float) WIDTH);
	float base_angle = atan2(v.y - mlx.player.y, v.x - mlx.player.x);
	float angle = base_angle - to_radians(mlx.player.fov / 2);
	while (++line < WIDTH)
	{
		t_point wall = raycast(mlx, angle);
		//test
		char *dst;
		float dis = sqrtf((wall.x-mlx.player.x) * (wall.x-mlx.player.x) + (wall.y-mlx.player.y) * (wall.y-mlx.player.y));
		if (dis < mlx.player.view_distance)
		{
			float tmp = (float) mlx.player.view_distance / (float) HEIGHT; // store 1/600e of 100%;
			float count = mlx.player.view_distance;
			for (int j = 0; j < HEIGHT / 2; j++)
			{
				if (count > dis)
				{
					dst = mlx.address + ((HEIGHT / 2 - j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = wall.color;
					dst = mlx.address + ((HEIGHT / 2 + j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = wall.color;
					count -= tmp * 2;
				}
			}
		}
		//test
		//printf("angle = %f, base = %f\n", angle, base_angle);
		angle += step;
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
					if (mlx.map[y][x] == '1')
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

void render_frame(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		printf("ERROR");
		exit(0);
	}
	mlx->address = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endians);
	if (!mlx->address)
	{
		printf("ERROR");
		exit(0);
	}
	render_wall(*mlx);
	if (mlx->show_map)
		draw_map(*mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void rendering(t_config data)
{
	// to remove
	char *map[] = {
			"11111",
			"10101",
			"10001",
			"10001",
			"11011",
			"11011",
			"10001",
			"11101",
			"10001",
			"11111"};

	t_mlx mlx = init_window(&data);
	mlx.map = map;
	mlx.player.x = 2.5;
	mlx.player.y = 2.5;
	mlx.scaling = 30;
	mlx.img = NULL;
	mlx.address = NULL;

	//mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

