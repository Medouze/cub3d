/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:31:04 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/17 15:10:57 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_loop(t_game *game, t_mlx *mlx, int ij[2], int xy[2])
{
	char	c;
	int		i;
	int		j;
	int		x;
	int		y;

	i = ij[0];
	j = ij[1];
	x = xy[0];
	y = xy[1];
	c = game->map[y][x];
	if (c == '1')
		put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0xFFFFFF);
	else if (c == 'D')
		put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0xFF0000);
	else if (c == 'd')
		put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0x00FF00);
	else if (c == '0')
		put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0x000000);
	else if ((c >= '2' && c <= '9') || (c >= 's' && c <= 'z'))
		put_pixel(mlx, x * game->scaling + j, y * game->scaling + i, 0xFFAA00);
}

static void	draw_map(t_game *game, t_mlx *mlx)
{
	int	xy[2];
	int	ij[2];

	xy[1] = -1;
	while (game->map[++xy[1]])
	{
		xy[0] = -1;
		while (game->map[xy[1]][++xy[0]])
		{
			ij[0] = -1;
			while (++ij[0] < game->scaling)
			{
				ij[1] = -1;
				while (++ij[1] < game->scaling)
					draw_map_loop(game, mlx, ij, xy);
			}
		}
	}
}

void	show_minimap(t_game *game)
{
	draw_map(game, &game->mlx);
	draw_fov(game, &game->player);
	draw_player(game);
}
