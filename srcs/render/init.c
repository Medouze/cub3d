/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:47:59 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/11 20:16:30 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player init_player(t_mlx mlx)
{
	t_player player;

	player.x = mlx.config->player_pos_x + 0.5;
	player.y = mlx.config->player_pos_y + 0.5;
	player.vx = 0;
	player.vy = 0;
	if (mlx.config->player_direction == 'N')
		player.vy = 1;
	else if (mlx.config->player_direction == 'S')
		player.vy = -1;
	else if (mlx.config->player_direction == 'W')
		player.vx = -1;
	else
		player.vx = 1;
	player.fov = 90;
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
	int a = 64;
	int b = 64;
	mlx.north_img = mlx_xpm_file_to_image(mlx.mlx_ptr, mlx.config->no_texture, &a, &b);
	return (mlx);
}
