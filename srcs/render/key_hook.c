/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/10 10:24:41 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	calculate_point(t_mlx *mlx, int rotation)
{
	float	x;
	float	y;
	t_point p;

	p.x = mlx->player.x + mlx->player.x_dir;
	p.y = mlx->player.y + mlx->player.y_dir;
	x = cos(to_radians(rotation)) * (p.x - mlx->player.x) - sin(to_radians(rotation)) * (p.y - mlx->player.y) + mlx->player.x;
	y = sin(to_radians(rotation)) * (p.x - mlx->player.x) - cos(to_radians(rotation)) * (p.y - mlx->player.y) + mlx->player.y;
	p.x = x;
	p.y = y;
	return (p);
}

int handle_keypress(int key, t_mlx *mlx)
{
	//printf("key = %d\n", key);
	if (key == 65307) //esc
	{
		destroy_window(mlx, 0);
	}
	else if (key == 65362) //up
	{
		t_point v = calculate_point(mlx, mlx->player.rotation);
		float dif_x = (mlx->player.x - v.x) * 0.1;
		float dif_y = (mlx->player.y - v.y) * 0.1;
		//printf("difx = %f, dify = %f\n", dif_x, dif_y);
		mlx->player.x -= dif_x;
		mlx->player.y -= dif_y;
	}
	else if (key == 65364) //down
	{
		t_point v = calculate_point(mlx, mlx->player.rotation);
		float dif_x = (mlx->player.x - v.x) * 0.1;
		float dif_y = (mlx->player.y - v.y) * 0.1;
		//printf("difx = %f, dify = %f\n", dif_x, dif_y);
		mlx->player.x += dif_x;
		mlx->player.y += dif_y;
	}
	if (key == 65361) //left
	{
		mlx->player.rotation += 3;
		if (mlx->player.rotation >= 360)
			mlx->player.rotation = 0;
	}
	else if (key == 65363) //right
	{
		mlx->player.rotation -= 3;
		if (mlx->player.rotation < 0)
			mlx->player.rotation = 357;
	}
	if (key == 109) // M
	{
		mlx->show_map = !mlx->show_map;
	}
	render_frame(mlx);
	return (0);
}