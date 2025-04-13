/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:27:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 11:24:46 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	t_img	img;

	img = mlx->main;
	mlx->main.add = mlx_get_data_addr(img.img,
			&img.bpp, &img.size_line, &img.endians);
	dst = img.add + y * img.size_line + x * (img.bpp / 8);
	*(unsigned int *)dst = color;
}

double	to_radians(double degree)
{
	return (degree * M_PI / 180);
}

double	to_degree(double radian)
{
	return (radian * 180 / M_PI);
}
