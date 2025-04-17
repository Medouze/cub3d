/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/17 17:59:09 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		destroy_window(game);
	else if (key == XK_w)
		move_forward(game, &game->player);
	else if (key == XK_s)
		move_backward(game, &game->player);
	else if (key == XK_a)
		move_left(game, &game->player);
	else if (key == XK_d)
		move_right(game, &game->player);
	else if (key == XK_Left)
		rotate_player_vector(game, -7);
	else if (key == XK_Right)
		rotate_player_vector(game, 7);
	else if (key == XK_m)
		game->show_map = !game->show_map;
	else if (key == XK_space)
		open_door(game);
	else
		return (0);
	game->is_key_pressed = 1;
	return (0);
}
