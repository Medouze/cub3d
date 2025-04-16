/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:27:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 10:37:10 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	t_img	img;

	if (x >= 0 && x < WIDTH)
	{
		if (y >= 0 && y < HEIGHT)
		{
			img = mlx->main;
			mlx->main.add = mlx_get_data_addr(img.img,
					&img.bpp, &img.size_line, &img.endians);
			dst = img.add + y * img.size_line + x * (img.bpp / 8);
			*(unsigned int *)dst = color;
		}
	}
}

double	to_radians(double degree)
{
	return (degree * M_PI / 180);
}

double	to_degree(double radian)
{
	return (radian * 180 / M_PI);
}

int	mov_is_wall(t_game *game, float margin, float new_x, float new_y)
{
	char	c;
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
			c = game->map[py_cell + j][px_cell + i];
			if ((c >= '1' && c <= '9') || (c >= 's' && c <= 'z') || c == 'D')
			{
				if (fabs(px_cell + i + 0.5 - new_x) < margin
					&& fabs(py_cell + j + 0.5 - new_y) < margin)
					return (1);
			}
		}
	}
	return (0);
}
