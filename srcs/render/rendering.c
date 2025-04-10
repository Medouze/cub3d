/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/10 14:46:48 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_point	raycast(t_mlx mlx, float rad_angle)
// {
// 	int		hit;
// 	t_point	p;
// 	double	delta[2];
// 	double x;
// 	double y;


	
// 	hit = 0;
// 	delta[0] = cos(rad_angle);
// 	delta[1] = sin(rad_angle);

// 	x = mlx.player.x * mlx.scaling;
// 	y = mlx.player.y * mlx.scaling;
// 	while (!hit)
// 	{
// 		x += delta[0];
// 		y += delta[1];
// 		if (mlx.map[(int) (y / mlx.scaling)][(int) (x / mlx.scaling)] == '1')
// 		{
// 			hit = 1;
// 			//printf("x = %f, y = %f\n", x / mlx.scaling , y / mlx.scaling);
// 			//printf("%f > %f\n", fabs(roundf(x / mlx.scaling) - x / mlx.scaling), fabs(roundf(y / mlx.scaling) - y / mlx.scaling));
// 			if (fabs(round(x / mlx.scaling) - x / mlx.scaling) < fabs(round(y / mlx.scaling) - y / mlx.scaling)) {
// 				//printf("true\n");
// 				if (delta[0] < 0)
// 					p.color = EAST;
// 				else
// 					p.color = WEST;
//             } else {
// 				//printf("false\n");
// 				if (delta[1] < 0)
// 					p.color = SOUTH;
// 				else
// 					p.color = NORTH;
//             }
// 		}
// 	}
// 	p.x = x / mlx.scaling;
// 	p.y = y / mlx.scaling;
// 	return (p);
// }

t_point	raycast(t_mlx mlx, float rad_angle)
{
	int		hit;
	t_point	p;
	double	delta[2];
	double x;
	double y;


	
	hit = 0;
	delta[0] = cos(rad_angle);
	delta[1] = sin(rad_angle);

	x = mlx.player.x * mlx.scaling;
	y = mlx.player.y * mlx.scaling;
	while (!hit)
	{
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

int	test(t_mlx mlx, int x, int y)
{
	//printf("x = %d, y = %d\n", x, y);
	
	char *s = mlx_get_data_addr(mlx.north_img, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endians);
	int offset = (y * mlx.size_line +  x * (mlx.bits_per_pixel / 8));
	int dst = *(int *)(s + offset);
	//printf("color = %X\n", dst);
	return (dst);
}

void draw_image_collumn(t_mlx mlx, t_point wall, int wall_height, int collumn)
{
	int		i;
	int		half_wall;

	i = -1;
	half_wall = HEIGHT / 2;

		while (++i <= HEIGHT / 2)
	{
		if (i < wall_height / 2)
		{
			if (wall.color == -1)
			{

				float a = (float) (half_wall - i) / (float) HEIGHT * 64.0;
				float b = (float) (half_wall + i) / (float) HEIGHT * 64.0;
				//printf("%f|%f\n", a, b);
				put_pixel(mlx, collumn, half_wall - i, test(mlx, (wall.x - floor(wall.x)) * 64, (int) a));
				put_pixel(mlx, collumn, half_wall + i, test(mlx, (wall.x - floor(wall.x)) * 64, (int) b));
			}
			else if (wall.color != -1)
			{
				put_pixel(mlx, collumn, half_wall - i, wall.color);
				put_pixel(mlx, collumn, half_wall + i, wall.color);
			}
		}
		else
		{
			put_pixel(mlx, collumn, half_wall - i, mlx.config->ceiling_color);
			put_pixel(mlx, collumn, half_wall + i, mlx.config->floor_color);
		}
	}
}

void loop_render_wall(t_mlx mlx, double step, double angle, double base_angle)
{
	int		collumn;
	double	z;
	double	distance;
	t_point	wall;

	collumn = -1;
	while (++collumn < WIDTH)
	{
		wall = raycast(mlx, angle);
		distance = sqrt((wall.x-mlx.player.x) * (wall.x-mlx.player.x) + (wall.y-mlx.player.y) * (wall.y-mlx.player.y));

		z = distance * cos(angle - base_angle);
		//if (distance < mlx.player.view_distance)
		//{
			draw_image_collumn(mlx, wall, HEIGHT / z, collumn);
		//}
		angle += step;
	}
}

void render_wall(t_mlx mlx)
{
	t_point	delta;
	double	step;
	double	base_angle;
	double	angle;

	delta = calculate_point(&mlx, mlx.player.rotation);
	step = to_radians((float) mlx.player.fov / (float) WIDTH);
	base_angle = atan2(delta.y - mlx.player.y, delta.x - mlx.player.x);
	angle = base_angle - to_radians(mlx.player.fov / 2);
	loop_render_wall(mlx, step, angle, base_angle);
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
	//if (mlx->show_map)
		//show_minimap(*mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void rendering(t_config data)
{
	t_mlx mlx;

	mlx = init_window(&data);
	mlx.scaling = 20;
	//mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

