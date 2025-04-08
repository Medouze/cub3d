/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:47:59 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/08 16:56:52 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player init_player(void)
{
	t_player player;

	player.pos.x = 2.5;
	player.pos.y = 2.5;
	player.dir.x = 0;
	player.dir.y = -1;
	player.fov = 60;
	player.view_distance = 10;
	return (player);
}

t_mlx	init_window(void)
{
	t_mlx	mlx;

	mlx.show_map = 1;
	mlx.mlx_ptr = mlx_init();
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
	mlx.player = init_player();
	return (mlx);
}