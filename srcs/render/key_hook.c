/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 18:52:29 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float margin, float new_x, float new_y)
{
	int		i;
	int		j;
	int		px_cell;
	int		py_cell;

	px_cell = (int) game->player.x;
	py_cell = (int) game->player.y;
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (i == 0 && j == 0)
				continue ;
			if (game->map[py_cell + j][px_cell + i] == '1')
			{
				if (fabs(px_cell + i + 0.5 - new_x) < margin
					&& fabs(py_cell + j + 0.5 - new_y) < margin)
					return (1);
			}
		}
	}
	return (0);
}


void	move_forward(t_game *game, t_player *player)
{
	float	margin;
	float	new_x;
	float	new_y;
	float	velocity;
	
	margin = 0.7;
	velocity = 0.1;
	new_x = player->x + player->vx * velocity;
	new_y = player->y + player->vy * velocity;
	if (!is_wall(game, margin, new_x, player->y))
		player->x = new_x;
	if (!is_wall(game, margin, player->x, new_y))
		player->y = new_y;
}

void	move_backward(t_game *game, t_player *player)
{
	float	margin;
	float	mov_x;
	float	mov_y;

	mov_x = player->x + -player->vx * 0.1;
	mov_y = player->y + -player->vy * 0.1;
	if (player->vx < 0)
		margin = 0.2;
	else
		margin = -0.2;
	if (game->map[(int) player->y][(int)(mov_x + margin)] != '1')
		player->x -= player->vx * 0.1;
	if (player->vy < 0)
		margin = 0.2;
	else
		margin = -0.2;
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
