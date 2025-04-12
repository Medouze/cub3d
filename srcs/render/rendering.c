/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 12:42:04 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fetch_texture_color(t_mlx mlx, int x, int y, void *texture)
{
	char	*buff;
	int		offset;
	int		color;

	buff = mlx_get_data_addr(texture, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endians);
	offset = (y * mlx.size_line +  x * (mlx.bits_per_pixel / 8));
	color = *(int *)(buff + offset);
	return (color);
}

void draw_wall_line(t_mlx mlx, int x, t_ray ray)
{
	int start_wall;
    int drawend;
	int y;


	start_wall = -ray.wall.height / 2 + HEIGHT / 2;
	drawend = ray.wall.height / 2 + HEIGHT / 2;
	y = -1;
	while (++y < drawend) 
	{
		if (y < ray.wall.height)
		{
			if (ray.side_hit == HORIZONTAL)
			{
				float a = (float) y / (float) ray.wall.height * 64.0;
				if (ray.x_step < 0)
				{	
					float b = fabs(1 - (ray.wall.y - floor(ray.wall.y))) * 64.0;
					if (start_wall + y >= 0 && start_wall + y < HEIGHT)
						put_pixel(mlx, x, start_wall + y, fetch_texture_color(mlx, b, a, mlx.west_img));
				}
				else
				{
					float b = (ray.wall.y - floor(ray.wall.y)) * 64.0;
					if (start_wall + y >= 0 && start_wall + y < HEIGHT)
						put_pixel(mlx, x, start_wall + y, fetch_texture_color(mlx, b, a, mlx.east_img));
				}
			}
			else
			{
				float a = (float) y / (float) ray.wall.height * 64.0;
				if (ray.y_step < 0)
				{
					float b = (ray.wall.x - floor(ray.wall.x)) * 64.0;
					if (start_wall + y >= 0 && start_wall + y < HEIGHT)
						put_pixel(mlx, x, start_wall + y, fetch_texture_color(mlx, b, a, mlx.north_img));
				}
				else
				{
					float b = fabs(1 - (ray.wall.x - floor(ray.wall.x))) * 64.0;
					if (start_wall + y >= 0 && start_wall + y < HEIGHT)
						put_pixel(mlx, x, start_wall + y, fetch_texture_color(mlx, b, a, mlx.south_img));
				}
			}
		}
	}
}

void digital_differential_analyzer(t_mlx *mlx, t_ray *ray)
{
	int 	hit;
	int 	map_x;
	int 	map_y;
	
	hit = 0;
	map_x = mlx->player.x;
	map_y = mlx->player.y;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			map_x += ray->x_step;
			ray->side_hit = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			map_y += ray->y_step;
			ray->side_hit = VERTICAL;
		}
		if (mlx->map[map_y][map_x] == '1')
			hit = 1;
	}
	ray->wall_dis = (ray->side_hit == 0) ? (ray->side_dist_x - ray->delta_x) : (ray->side_dist_y - ray->delta_y);
}

void test2(t_mlx mlx) {
	t_player p;
	t_ray ray;

	p = mlx.player;
    double planeX = -p.vy * 0.66;
    double planeY = p.vx * 0.66;

    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;  // Camera X (field of view)
        ray.vector_x = p.vx + planeX * cameraX;  // Direction of the ray in X
        ray.vector_y = p.vy + planeY * cameraX;  // Direction of the ray in Y
        int mapX = (int) p.x;
        int mapY = (int) p.y;
        ray.delta_x = (ray.vector_x == 0) ? 1e30 : fabs(1 / ray.vector_x);
        ray.delta_y = (ray.vector_y == 0) ? 1e30 : fabs(1 / ray.vector_y);

        // Initialize step and sideDist for ray in X direction
        if (ray.vector_x < 0) {
           	ray.x_step = -1;
            ray.side_dist_x = (p.x - mapX) * ray.delta_x;
        } else {
            ray.x_step = 1;
            ray.side_dist_x = (mapX + 1.0 - p.x) * ray.delta_x;
        }

        // Initialize step and sideDist for ray in Y direction
        if (ray.vector_y < 0) {
            ray.y_step = -1;
            ray.side_dist_y = (p.y - mapY) * ray.delta_y;
        } else {
            ray.y_step = 1;
            ray.side_dist_y = (mapY + 1.0 - p.y) * ray.delta_y;
        }
		digital_differential_analyzer(&mlx, &ray);

        ray.wall.height = (int)(HEIGHT / ray.wall_dis);
		ray.wall.x = p.x + ray.wall_dis * ray.vector_x;
		ray.wall.y = p.y + ray.wall_dis * ray.vector_y;
		draw_wall_line(mlx, x, ray);
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
	char *tmp = mlx_get_data_addr(mlx->floor_ceil_img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endians);
	if (!mlx->address)
	{
		printf("ERROR");
		exit(0);
	}
	mlx->address = ft_memcpy(mlx->address, tmp, mlx->size_line * HEIGHT);
	test2(*mlx);
	//render_wall(*mlx);
	//if (mlx->show_map)
		//show_minimap(*mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void create_floor_ceil(t_mlx *mlx)
{
	int 	x;
	int 	y;
	int		half_height;
	char	*ceil;
	char	*floor;

	mlx->floor_ceil_img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	half_height = HEIGHT / 2;
	y = -1;
	mlx->floor_ceil_address = mlx_get_data_addr(mlx->floor_ceil_img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endians);
	while (++y < half_height)
	{
		x = -1;
		while (++x <= WIDTH)
		{
			ceil = mlx->floor_ceil_address + y * mlx->size_line +  x * (mlx->bits_per_pixel / 8);
			*(unsigned int *)ceil = mlx->config->ceiling_color;
			floor = mlx->floor_ceil_address + (y + half_height) * mlx->size_line +  x * (mlx->bits_per_pixel / 8);
			*(unsigned int *)floor = mlx->config->floor_color;
		}
	}
}

void rendering(t_config data)
{
	t_mlx mlx;

	mlx = init_window(&data);
	mlx.scaling = 20;
	//mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	create_floor_ceil(&mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

