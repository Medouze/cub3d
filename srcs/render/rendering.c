/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/09 17:56:58 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	raycast(t_mlx mlx, float rad_angle)
{
	int		hit;
	t_point	p;
	double	delta[2];


	
	hit = 0;
	delta[0] = cos(rad_angle);
	delta[1] = sin(rad_angle);
	double x;
	double y;

	x = mlx.player.x * mlx.scaling;
	y = mlx.player.y * mlx.scaling;
	while (!hit)
	{
		put_pixel(mlx, roundf(x), roundf(y), 0xFFFFFF); //tmp
		x += delta[0];
		y += delta[1];
		if (mlx.map[(int) (y / mlx.scaling)][(int) (x / mlx.scaling)] == '1')
		{
			hit = 1;
			//printf("x = %f, y = %f\n", x / mlx.scaling , y / mlx.scaling);
			//printf("%f > %f\n", fabs(roundf(x / mlx.scaling) - x / mlx.scaling), fabs(roundf(y / mlx.scaling) - y / mlx.scaling));
			if (fabs(round(x / mlx.scaling) - x / mlx.scaling) < fabs(round(y / mlx.scaling) - y / mlx.scaling)) {
				//printf("true\n");
				if (delta[0] < 0)
					p.color = EAST;
				else
					p.color = WEST;
            } else {
				//printf("false\n");
				if (delta[1] < 0)
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
	double step = to_radians((float) mlx.player.fov / (float) WIDTH);
	double base_angle = atan2(v.y - mlx.player.y, v.x - mlx.player.x);
	double angle = base_angle - to_radians(mlx.player.fov / 2);
	while (++line < WIDTH)
	{
		t_point wall = raycast(mlx, angle);
		//test
		char *dst;
		double dis = sqrt((wall.x-mlx.player.x) * (wall.x-mlx.player.x) + (wall.y-mlx.player.y) * (wall.y-mlx.player.y));
		//printf("dis = %f\n", dis);
		double z;
		/* if (wall.color == NORTH || wall.color == SOUTH)
			z = fabs(dis * sin(angle)) + 1;
		else */
			z = dis * cos(angle);

		//int wall_height = HEIGHT / fabs(z);
		int wall_height = /* fabs((dis / mlx.player.view_distance) * HEIGHT - HEIGHT) */ 300.0/HEIGHT * HEIGHT / fabs(z);
		//printf("z = %f, dis = %f, wall height = %d\n", z, dis, wall_height);
		(void) wall_height;
		if (dis < mlx.player.view_distance)
		{
			float tmp = (float) mlx.player.view_distance / (float) HEIGHT; // store 1/600e of 100%;
			float count = mlx.player.view_distance;
			for (int j = 0; j <= HEIGHT / 2; j++)
			{
				//if (j == 0)
					//printf("count = %f\n", count);
				//if (j < wall_height / 2)
				if (count > dis)
				{
					dst = mlx.address + ((HEIGHT / 2 - j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = wall.color;
					dst = mlx.address + ((HEIGHT / 2 + j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = wall.color;
					count -= tmp * 2;
				}
				else
				{
					dst = mlx.address + ((HEIGHT / 2 - j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = 0x00FFFF;
					dst = mlx.address + ((HEIGHT / 2 + j) * mlx.size_line) + (line * (mlx.bits_per_pixel / 8));
					*(unsigned int *)dst = 0xFF00FF;
					count -= tmp * 2;
				}
			}
		}
		angle += step;
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
		show_minimap(*mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void rendering(t_config data)
{
	// to remove
	/* char *map[] = {
			"11111",
			"10101",
			"10001",
			"10001",
			"11011",
			"11011",
			"10001",
			"11101",
			"10001",
			"11111"}; */

	t_mlx mlx = init_window(&data);
	/* mlx.map = map;
	mlx.player.x = 2.5;
	mlx.player.y = 2.5; */
	mlx.scaling = 30;
	mlx.img = NULL;
	mlx.address = NULL;

	//mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

