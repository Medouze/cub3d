/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:52:48 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/15 18:51:35 by qmorinea         ###   ########.fr       */
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
	if (fabs(x - WIDTH * 0.5) > 3)
		rotate_player_vector(game, (float) dx * 0.08);
	/* if (x > WIDTH * 0.9 || x < WIDTH * 0.1
		|| y > HEIGHT * 0.9 || y < HEIGHT * 0.1) */
	mlx_mouse_move(game->mlx.mlx_ptr,
			game->mlx.win_ptr, WIDTH * 0.5, HEIGHT * 0.5);
	//render_frame(game, &game->mlx);
	return (0);
}
