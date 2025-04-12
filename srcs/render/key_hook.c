/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 02:56:18 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward(t_mlx *mlx)
{
	float margin;
	float mov_x;
	float mov_y;

	margin = 0.2;
	mov_x = mlx->player.x + mlx->player.vx * 0.1 + mlx->player.vx * margin;
	if (mlx->map[(int) mlx->player.y][(int) (mov_x)] != '1')
  		mlx->player.x += mlx->player.vx * 0.1;
	mov_y = mlx->player.y + mlx->player.vy * 0.1 + mlx->player.vy * margin;
	if (mlx->map[(int) (mov_y)][(int) mlx->player.x] != '1')
  		mlx->player.y += mlx->player.vy * 0.1;
}

void move_backward(t_mlx *mlx)
{
	float margin;
	float mov_x;
	float mov_y;

	margin = 0.2;
	mov_x = mlx->player.x + -mlx->player.vx * 0.1 + -mlx->player.vx * margin;
	if (mlx->map[(int) mlx->player.y][(int) (mov_x)] != '1')
  		mlx->player.x += -mlx->player.vx * 0.1;
	mov_y = mlx->player.y + -mlx->player.vy * 0.1 + -mlx->player.vy * margin;
	if (mlx->map[(int) (mov_y)][(int) mlx->player.x] != '1')
  		mlx->player.y += -mlx->player.vy * 0.1;
}


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
		move_forward(mlx);
	else if (key == 65364) //down
		move_backward(mlx);
	if (key == 65361) //left
		rotate_player_vector(mlx, -3);
	else if (key == 65363) //right
		rotate_player_vector(mlx, 3);
	if (key == 109) // M
		mlx->show_map = !mlx->show_map;
	render_frame(mlx);
	return (0);
}