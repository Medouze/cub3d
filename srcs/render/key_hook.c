/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/11 20:18:23 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player_vector(t_mlx *mlx, int rotation)
{
	t_player	p;
	double		angle;
	float		vx;
	float		vy;

	angle = to_radians(rotation);
	p = mlx->player;
	vx = p.vx * cos(angle) - p.vy * sin(angle);
	vy = p.vx * sin(angle) + p.vy * cos(angle);
	mlx->player.vx = vx;
	mlx->player.vy = vy;
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
		mlx->player.x += mlx->player.vx * 0.1;
		mlx->player.y += mlx->player.vy * 0.1;
	}
	else if (key == 65364) //down
	{
		mlx->player.x -= mlx->player.vx * 0.1;
		mlx->player.y -= mlx->player.vy * 0.1;
	}
	if (key == 65361) //left
		rotate_player_vector(mlx, -3);
	else if (key == 65363) //right
		rotate_player_vector(mlx, 3);
	if (key == 109) // M
	{
		mlx->show_map = !mlx->show_map;
	}
	render_frame(mlx);
	return (0);
}