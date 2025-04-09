/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/10 00:02:55 by qmorinea         ###   ########.fr       */
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

void draw_image_collumn(t_mlx mlx, t_point wall, int wall_height, int line)
{
	int		i;
	int		half_wall;

	i = -1;
	half_wall = HEIGHT / 2;
	while (++i <= HEIGHT / 2)
	{
		if (i < wall_height / 2)
		{
			put_pixel(mlx, line, half_wall - i, wall.color);
			put_pixel(mlx, line, half_wall + i, wall.color);
		}
		else
		{
			put_pixel(mlx, line, half_wall - i, mlx.config->ceiling_color);
			put_pixel(mlx, line, half_wall + i, mlx.config->floor_color);
		}
	}
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
		double dis = sqrt((wall.x-mlx.player.x) * (wall.x-mlx.player.x) + (wall.y-mlx.player.y) * (wall.y-mlx.player.y));

		double z = dis * cos(angle - base_angle);
		int wall_height = (int) HEIGHT / z;
		if (dis < mlx.player.view_distance)
		{
			draw_image_collumn(mlx, wall, wall_height, line);
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

