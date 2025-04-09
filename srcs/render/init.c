/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:47:59 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/10 00:16:24 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player init_player(t_mlx mlx)
{
	t_player player;

	player.x = mlx.config->player_pos_x + 0.5;
	player.y = mlx.config->player_pos_y + 0.5;
	player.x_dir = 0;
	player.y_dir = 0;
	if (mlx.config->player_direction == 'N')
		player.y_dir = 1;
	else if (mlx.config->player_direction == 'S')
		player.y_dir = -1;
	else if (mlx.config->player_direction == 'W')
		player.x_dir = -1;
	else
		player.x_dir = 1;
	player.fov = 80;
	player.rotation = 0;
	player.view_distance = 10;
	return (player);
}

t_mlx	init_window(t_config *data)
{
	t_mlx	mlx;

	mlx.show_map = 1;
	mlx.config = data;
	mlx.map = data->map;
	mlx.mlx_ptr = mlx_init();
	mlx.img = NULL;
	mlx.address = NULL;
	//protect
	if (!mlx.mlx_ptr)
	{
		printf("ERROR");
		exit(0);
	}
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	//protect
	if (!mlx.win_ptr)
	{
		printf("ERROR");
		exit(0);
	}
	mlx.player = init_player(mlx);
	return (mlx);
}
