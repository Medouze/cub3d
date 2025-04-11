/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/11 20:15:08 by qmorinea         ###   ########.fr       */
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

void draw_image_collumn(t_mlx mlx, t_point wall, int wall_height, int collumn);

/* void test2(t_mlx mlx)
{
	t_point v = calculate_point(&mlx, mlx.player.rotation);
	double posX = mlx.player.x;
	double posY = mlx.player.y;
	double planeX = -v.y * 0.66;
	double planeY = v.x * 0.66;

		for (int x = 0; x < WIDTH; x++)
		{
			double cameraX = 2 * x / (double) WIDTH -1;
			double rayDirX = v.x + planeX * cameraX;
			double rayDirY = v.y + planeY * cameraX;
			int mapX = (int) posX;
			int mapY = (int) posY;
			double sideDistX;
			double sideDistY;
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			double perpWallDist;
			int stepX;
			int stepY;
			int hit = 0;
			int side;
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while (!hit)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (mlx.map[mapY][mapX] == '1')
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			int lineHeight = (int) (HEIGHT * perpWallDist);
			int drawstart = -lineHeight / 2 + HEIGHT / 2;
			if (drawstart < 0)
				drawstart = 0;
			int drawend = lineHeight / 2 + HEIGHT / 2;
				drawend = HEIGHT - 1;
			for (int y = drawstart; y < drawend; y++)
			{
				if (side == 0)
					put_pixel(mlx, x, y, 0xFF0000);
				else
					put_pixel(mlx, x, y, 0x0000FF);
			}
		}
} */

void test2(t_mlx mlx) {
	t_player p;

	p = mlx.player;
    double posX = mlx.player.x;
    double posY = mlx.player.y;
    double planeX = -p.vy * 0.66;
    double planeY = p.vx * 0.66;

    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;  // Camera X (field of view)
        double rayDirX = p.vx + planeX * cameraX;  // Direction of the ray in X
        double rayDirY = p.vy + planeY * cameraX;  // Direction of the ray in Y
		printf("raydir = %f | %f\n", rayDirX, rayDirY);
        int mapX = (int) posX;
        int mapY = (int) posY;
        double sideDistX;
        double sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;
        int stepX;
        int stepY;
        int hit = 0;
        int side;

        // Initialize step and sideDist for ray in X direction
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        // Initialize step and sideDist for ray in Y direction
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // DDA loop: check every step of the ray
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // If the ray hits a wall ('1')
            if (mlx.map[mapY][mapX] == '1') {
                hit = 1;
            }
        }

        // Calculate the perpendicular distance to the wall
        perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);

        // Calculate the line height based on the distance to the wall
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Calculate where the wall should start and end on the screen
        int drawstart = -lineHeight / 2 + HEIGHT / 2;
        if (drawstart < 0) drawstart = 0;
        int drawend = lineHeight / 2 + HEIGHT / 2;
        if (drawend >= HEIGHT) drawend = HEIGHT - 1;
        for (int y = drawstart; y < drawend; y++) {
            if (side == 0)
			{
				if (stepX < 0)
	                put_pixel(mlx, x, y, 0xFFFF00);
				else
					put_pixel(mlx, x, y, 0x00FF00);
			}
            else
			{
				if (stepY < 0)
	                put_pixel(mlx, x, y, 0x0000FF);
				else
					put_pixel(mlx, x, y, 0xFF0000); 
			}
        }
    }
}

/* t_point	raycast(t_mlx mlx, float rad_angle)
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
} */

/*  t_point	raycast(t_mlx mlx, float rad_angle)
{
	int		hit;
	t_point	p;
	double	delta[2];
	double x;
	double y;


	
	hit = 0;
	delta[0] = cos(rad_angle);
	delta[1] = sin(rad_angle);

	double planeX = -delta[1] * 0.66;
	double planeY = delta[0] * 0.66;

	x = mlx.player.x;
	y = mlx.player.y;
	int mapX = (int) (x);
	int mapY = (int) (y);

	double sideDistX, sideDistY;

	double deltaDistX = (delta[0] == 0) ? 1e30 : fabs(1 / delta[0]);
	double deltaDistY = (delta[1] == 0) ? 1e30 : fabs(1 / delta[1]);
	
	int stepX, stepY;
	if (delta[0] < 0)
	{
		stepX = -1;
		sideDistX = (x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = ((mapX + 1.0) - x) * deltaDistX;
	}
	if (delta[1] < 0)
	{
		stepY = -1;
		sideDistY = (y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = ((mapY + 1.0) - y) * deltaDistY;
	}
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			p.x = mapX;
			p.y = y + (sideDistX - deltaDistX) * delta[1];
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			p.x = x + (sideDistY - deltaDistY) * delta[0];
			p.y = mapY;
		}
		if (mlx.map[(int) (y / mlx.scaling)][(int) (x / mlx.scaling)] == '1')
			hit = 1;
	}
	if (sideDistX < sideDistY)
		p.color = (delta[0] < 0) ? EAST : WEST;
	else
		p.color = (delta[1] < 0) ? SOUTH : NORTH;
	return (p);
} */

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
				float a = (float) i / wall_height * 64.0 + 32;
				float b = (float) i / wall_height* 64.0 + 32;
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
	//t_point	wall;

	collumn = -1;
	while (++collumn < WIDTH)
	{
		//wall = raycast(mlx, angle);
		t_point wall;
		distance = sqrt((wall.x-mlx.player.x) * (wall.x-mlx.player.x) + (wall.y-mlx.player.y) * (wall.y-mlx.player.y));

		z = distance * cos(angle - base_angle);
		//if (distance < mlx.player.view_distance)
		//{
			draw_image_collumn(mlx, wall, HEIGHT / z, collumn);
		//}
		angle += step;
	}
}

/* void render_wall(t_mlx mlx)
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
} */

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
	test2(*mlx);
	//render_wall(*mlx);
	if (mlx->show_map)
		show_minimap(*mlx);
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

