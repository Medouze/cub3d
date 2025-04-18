/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:52:48 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/18 10:40:56 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/Xlib.h>

int	handle_mouse_move(int x, int y, void *param)
{
	int		dx;
	t_game	*game;

	dx = x - WIDTH * 0.5;
	game = (t_game *) param;
	(void) y;
	if (fabs(x - WIDTH * 0.5) > 10)
	{
		game->is_using_mouse = 1;
		rotate_player_vector(game, (float) dx * 0.07);
		mlx_mouse_move(game->mlx.mlx_ptr,
			game->mlx.win_ptr, WIDTH * 0.5, HEIGHT * 0.5);
	}
	return (0);
}
