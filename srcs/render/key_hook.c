/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 21:44:03 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game, t_player *player)
{
	float	margin;
	float	mov_x;
	float	mov_y;

	if (player->vx < 0)
		margin = -0.2;
	else
		margin = 0.2;
	mov_x = player->x + player->vx * 0.1;
	if (game->map[(int) player->y][(int)(mov_x + margin)] != '1')
		player->x += player->vx * 0.1;
	if (player->vy < 0)
		margin = -0.2;
	else
		margin = 0.2;
	mov_y = player->y + player->vy * 0.1;
	if (game->map[(int)(mov_y + margin)][(int) player->x] != '1')
		player->y += player->vy * 0.1;
}

void	move_backward(t_game *game, t_player *player)
{
	float	margin;
	float	mov_x;
	float	mov_y;

	if (player->vx < 0)
		margin = 0.2;
	else
		margin = -0.2;
	mov_x = player->x + -player->vx * 0.1;
	if (game->map[(int) player->y][(int)(mov_x + margin)] != '1')
		player->x -= player->vx * 0.1;
	if (player->vy < 0)
		margin = 0.2;
	else
		margin = -0.2;
	mov_y = player->y + -player->vy * 0.1;
	if (game->map[(int)(mov_y + margin)][(int) player->x] != '1')
		player->y -= player->vy * 0.1;
}

void	rotate_player_vector(t_game *game, int rotation)
{
	t_player	*p;
	double		angle;
	float		vx;
	float		vy;

	angle = to_radians(rotation);
	p = &game->player;
	vx = p->vx * cos(angle) - p->vy * sin(angle);
	vy = p->vx * sin(angle) + p->vy * cos(angle);
	p->vx = vx;
	p->vy = vy;
}

int	handle_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		destroy_window(game);
	else if (key == XK_Up)
		move_forward(game, &game->player);
	else if (key == XK_Down)
		move_backward(game, &game->player);
	if (key == XK_Left)
		rotate_player_vector(game, -5);
	else if (key == XK_Right)
		rotate_player_vector(game, 5);
	if (key == XK_m)
		game->show_map = !game->show_map;
	render_frame(game, &game->mlx);
	return (0);
}
