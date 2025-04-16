/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:28:39 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 10:53:23 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game, t_player *player)
{
	float	margin;
	float	new_x;
	float	new_y;
	float	velocity;
	
	margin = 0.7;
	velocity = 0.15;
	new_x = player->x + player->vx * velocity;
	new_y = player->y + player->vy * velocity;
	if (!mov_is_wall(game, margin, new_x, player->y))
		player->x = new_x;
	if (!mov_is_wall(game, margin, player->x, new_y))
		player->y = new_y;
}

void	move_backward(t_game *game, t_player *player)
{
	float	margin;
	float	new_x;
	float	new_y;
	float	velocity;

	margin = 0.7;
	velocity = 0.15;
	new_x = player->x + -player->vx * velocity;
	new_y = player->y + -player->vy * velocity;
	if (!mov_is_wall(game, margin, new_x, player->y))
		player->x = new_x;
	if (!mov_is_wall(game, margin, player->x, new_y))
		player->y = new_y;
}

void	move_left(t_game *game, t_player *player)
{
	float	margin;
	float	new_x;
	float	new_y;
	float	velocity;

	margin = 0.7;
	velocity = 0.15;
	new_x = player->x + player->vy  * velocity;
	new_y = player->y + -player->vx * velocity;
	if (!mov_is_wall(game, margin, new_x, player->y))
		player->x = new_x;
	if (!mov_is_wall(game, margin, player->x, new_y))
		player->y = new_y;
}

void	move_right(t_game *game, t_player *player)
{
	float	margin;
	float	new_x;
	float	new_y;
	float	velocity;

	margin = 0.7;
	velocity = 0.15;
	new_x = player->x + -player->vy * velocity;
	new_y = player->y + player->vx * velocity;
	if (!mov_is_wall(game, margin, new_x, player->y))
		player->x = new_x;
	if (!mov_is_wall(game, margin, player->x, new_y))
		player->y = new_y;
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
