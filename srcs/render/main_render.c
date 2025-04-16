/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:15:02 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 11:17:14 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering(t_config data)
{
	t_game	game;

	game = init_window(&data);
	mlx_mouse_hide(game.mlx.mlx_ptr, game.mlx.win_ptr);
	mlx_hook(game.mlx.win_ptr, 17, 0, destroy_window, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 6, 1L << 6, handle_mouse_move, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, handle_keypress, &game.mlx);
	mlx_loop_hook(game.mlx.mlx_ptr, render_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
