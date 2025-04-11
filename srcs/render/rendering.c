/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 00:37:10 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	test(t_mlx mlx, int x, int y, void *path)
{
	//printf("x = %d, y = %d\n", x, y);
	
	//printf("x = %d, y = %d\n", x, y);
	char *s = mlx_get_data_addr(path, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endians);
	int offset = (y * mlx.size_line +  x * (mlx.bits_per_pixel / 8));
	int dst = *(int *)(s + offset);
	//printf("color = %X\n", dst);
	return (dst);
}

void draw_wall_line(t_mlx mlx, int wall_height, int side, int x, int stepX, int stepY, t_point wall)
{
	int drawstart = -wall_height / 2 + HEIGHT / 2;
    int drawend = wall_height / 2 + HEIGHT / 2;
	(void) drawend;
	for (int y = 0 ;y < drawend; y++) 
	{
		if (y < wall_height)
		{
			if (side == 0)
			{
				float a = (float) y / (float) wall_height * 64.0;
				//float c = (float) y / (float) wall_height * 64.0 + 32;
				//float c = (float)(HEIGHT / 2 + y) / (float) wall_height * 64.0;
				float b = (wall.y - floor(wall.y)) * 64.0;
				//printf("a = %f, c = %f\n", a, c);
				if (stepX < 0)
				{	
					if (drawstart + y >= 0 && drawstart + y < HEIGHT)
						put_pixel(mlx, x, drawstart + y, test(mlx, b, a, mlx.west_img));
					//put_pixel(mlx, x, HEIGHT / 2 + y, test(mlx, b, c, mlx.west_img));
				}
				else
				{
					if (drawstart + y >= 0 && drawstart + y < HEIGHT)
						put_pixel(mlx, x, drawstart + y, test(mlx, b, a, mlx.east_img));
				}
			}
			else
			{
				float a = (float) y / (float) wall_height * 64.0;
				float b = (wall.x - floor(wall.x)) * 64.0;
				if (stepY < 0)
				{
					if (drawstart + y >= 0 && drawstart + y < HEIGHT)
						put_pixel(mlx, x, drawstart + y, test(mlx, b, a, mlx.north_img));
					//else
						//printf("y = %d, dra + y = %d\n", y, drawstart + y);
				}
				else
				{
					if (drawstart + y >= 0 && drawstart + y < HEIGHT)
						put_pixel(mlx, x, drawstart + y, test(mlx, b, a, mlx.south_img));
				}
			}
		}
	}
}

void test2(t_mlx mlx) {
	t_player p;

	p = mlx.player;
    double planeX = -p.vy * 0.66;
    double planeY = p.vx * 0.66;

    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;  // Camera X (field of view)
        double rayDirX = p.vx + planeX * cameraX;  // Direction of the ray in X
        double rayDirY = p.vy + planeY * cameraX;  // Direction of the ray in Y
        int mapX = (int) p.x;
        int mapY = (int) p.y;
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
            sideDistX = (p.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p.x) * deltaDistX;
        }

        // Initialize step and sideDist for ray in Y direction
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (p.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p.y) * deltaDistY;
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
        int wall_height = (int)(HEIGHT / perpWallDist);

        // Calculate where the wall should start and end on the screen
        int drawstart = -wall_height / 2 + HEIGHT / 2;
        if (drawstart < 0) drawstart = 0;
        int drawend = wall_height / 2 + HEIGHT / 2;
        if (drawend >= HEIGHT) drawend = HEIGHT - 1;
		t_point tmp;
		tmp.x = p.x + perpWallDist * rayDirX;
		tmp.y = p.y + perpWallDist * rayDirY;
		draw_wall_line(mlx, wall_height, side, x, stepX, stepY, tmp);
    }
}




/* void draw_image_collumn(t_mlx mlx, t_point wall, int wall_height, int collumn)
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
} */

/* void loop_render_wall(t_mlx mlx, double step, double angle, double base_angle)
{
	int		collumn;
	//double	z;
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
			//draw_image_collumn(mlx, wall, HEIGHT / z, collumn);
		//}
		angle += step;
	}
} */

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

