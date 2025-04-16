/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:19:28 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 11:38:16 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Player */

static void	cast_ray_player(t_game *game, t_mlx *mlx, float x, float y)
{
	int		i;
	float	delta[2];
	float	length;
	float	p_xy[2];

	delta[0] = x;
	delta[1] = y;
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	p_xy[0] = game->player.x * game->scaling;
	p_xy[1] = game->player.y * game->scaling;
	i = -1;
	while (++i < game->scaling / 4)
	{
		put_pixel(mlx, roundf(p_xy[0]), roundf(p_xy[1]), 0xFF8800);
		p_xy[0] += delta[0];
		p_xy[1] += delta[1];
	}
}

void	draw_player(t_game *game)
{
	int		i;
	float	vx;
	float	vy;

	i = -1;
	while (++i < 360)
	{
		vx = game->player.vx * cos(to_radians(i))
			- game->player.vy * sin(to_radians(i));
		vy = game->player.vx * sin(to_radians(i))
			+ game->player.vy * cos(to_radians(i));
		cast_ray_player(game, &game->mlx, vx, vy);
	}
}

/* FOV */

static void	castray_fov(t_game *game, float delta[2], int color)
{
	int		i;
	float	p_x;
	float	p_y;

	p_x = game->player.x * game->scaling;
	p_y = game->player.y * game->scaling;
	i = -1;
	while (++i < game->scaling * 2)
	{
		put_pixel(&game->mlx, roundf(p_x), roundf(p_y), color);
		p_x += delta[0];
		p_y += delta[1];
	}
}

void	draw_fov(t_game *game, t_player *player)
{
	int		i;
	float	delta[2];
	float	step;
	float	angle;
	float	length;

	i = -1;
	player->fov = 66;
	angle = to_radians(-(player->fov / 2));
	step = (float) to_radians(player->fov / (float) WIDTH);
	while (++i < WIDTH)
	{
		delta[0] = player->vx * cos(angle) - player->vy * sin(angle);
		delta[1] = player->vx * sin(angle) + player->vy * cos(angle);
		length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		delta[0] /= length;
		delta[1] /= length;
		castray_fov(game, delta, 0xFFFF00);
		angle += step;
	}
}
