/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/07 17:19:53 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	to_radians(int degree)
{
	return (degree * PI/180);
}

t_point	calculate_point(t_mlx *mlx, int rotation)
{
	t_point p;

	p.x = mlx->player.pos.x + mlx->player.dir.x;
	p.y = mlx->player.pos.y + mlx->player.dir.y;

	float x = cos(to_radians(rotation)) * (p.x - mlx->player.pos.x) - sin(to_radians(rotation)) * (p.y - mlx->player.pos.y) + mlx->player.pos.x;
	float y = sin(to_radians(rotation)) * (p.x - mlx->player.pos.x) - cos(to_radians(rotation)) * (p.y - mlx->player.pos.y) + mlx->player.pos.y;
	p.x = x;
	p.y = y;
	return (p);
}

int handle_keypress(int key, t_mlx *mlx)
{
	printf("key = %d\n", key);
	if (key == 65307) //esc
	{
		mlx_loop_end(mlx->mlx_ptr);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		exit(0);
	}
	if (key == 65362) //up
	{
		t_point v = calculate_point(mlx, mlx->player.rotation);
		float dif_x = (mlx->player.pos.x - v.x) * 0.1;
		float dif_y = (mlx->player.pos.y - v.y) * 0.1;
		printf("difx = %f, dify = %f\n", dif_x, dif_y);
		mlx->player.pos.x -= dif_x;
		mlx->player.pos.y -= dif_y;
	}
	if (key == 65364) //down
	{
		t_point v = calculate_point(mlx, mlx->player.rotation);
		float dif_x = (mlx->player.pos.x - v.x) * 0.1;
		float dif_y = (mlx->player.pos.y - v.y) * 0.1;
		printf("difx = %f, dify = %f\n", dif_x, dif_y);
		mlx->player.pos.x += dif_x;
		mlx->player.pos.y += dif_y;
	}
	if (key == 65361) //left
	{
		mlx->player.rotation += 10;
		if (mlx->player.rotation >= 360)
			mlx->player.rotation = 0;
	}
	if (key == 65363) //right
	{
		mlx->player.rotation -= 10;
		if (mlx->player.rotation < 0)
			mlx->player.rotation = 350;
	}
	if (key == 109) // M
	{
		mlx->show_map = !mlx->show_map;
	}
	render_frame(*mlx);
	return (0);
}