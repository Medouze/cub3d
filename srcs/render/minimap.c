/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:31:04 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 21:34:46 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	near_wall(t_game *game, float delta[2], int color)
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
		if (game->map[(int) p_y / game->scaling][(int) p_x / game->scaling] == '1')
			break ;
	}
}

void	cast_ray(t_game *game, float x, float y, int color)
{
	float	delta[2];
	float	length;

	delta[0] = x;
	delta[1] = y;
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	near_wall(game, delta, color);
}

void	draw_map(t_game *game, t_mlx *mlx)
{
	int		y;
	int		x;
	int		i;
	int		j;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			i = -1;
			while (++i < game->scaling)
			{
				j = -1;
				while (++j < game->scaling)
				{
					if (game->map[y][x] == '1')
						put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0xFFFFFF);
					else
						put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0x000000);
				}
			}
		}
	}
}

t_point	calculate_point(t_game *game, int rotation)
{
	float	x;
	float	y;
	t_point	p;

	p.x = game->player.vx;
	p.y = game->player.vy;
	x = cos(to_radians(rotation)) * (p.x) - sin(to_radians(rotation)) * (p.y);
	y = sin(to_radians(rotation)) * (p.x) - cos(to_radians(rotation)) * (p.y);
	p.x = x;
	p.y = y;
	return (p);
}

void	draw_fov(t_game *game, t_player *player)
{
	int		i;
	float	vx;
	float	vy;
	float	step;
	float	angle;	

	i = -1;
	player->fov = 66;
	angle = to_radians(-(player->fov / 2));
	step = (float) to_radians(player->fov / (float) WIDTH);
	while (++i < WIDTH)
	{
		vx = player->vx * cos(angle) - player->vy * sin(angle);
		vy = player->vx * sin(angle) + player->vy * cos(angle);
		cast_ray(game, vx, vy, 0xFFFF00);
		angle += step;
	}
}

void	cast_ray_player(t_game *game, t_mlx *mlx, float x, float y, int color)
{
	int		i;
	float	delta[2];
	float	length;
	float	p_x;
	float	p_y;

	delta[0] = x;
	delta[1] = y;
	length = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	delta[0] /= length;
	delta[1] /= length;
	p_x = game->player.x * game->scaling;
	p_y = game->player.y * game->scaling;
	i = -1;
	while (++i < game->scaling / 4)
	{
		put_pixel(mlx, roundf(p_x), roundf(p_y), color);
		p_x += delta[0];
		p_y += delta[1];
		if (game->map[(int) p_y / game->scaling][(int) p_x / game->scaling] == '1')
			break ;
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
		vx = game->player.vx * cos(to_radians(i)) - game->player.vy * sin(to_radians(i));
		vy = game->player.vx * sin(to_radians(i)) + game->player.vy * cos(to_radians(i));
		cast_ray_player(game, &game->mlx, vx, vy, 0x00FF00);
	}
}

void	show_minimap(t_game *game)
{
	/* int	x_max = 33; // ICI
	int	y_max = 14;
	int	width_map = 200;

	game->scaling = width_map / fmax(y_max, x_max); */
	game->scaling = 20;
	draw_map(game, &game->mlx);
	draw_fov(game, &game->player);
	draw_player(game);
}
