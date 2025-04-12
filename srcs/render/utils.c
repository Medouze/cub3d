/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:27:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 21:35:51 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	mlx->address = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel, &mlx->size_line, &mlx->endians);
	dst = mlx->address + y * mlx->size_line + x * (mlx->bits_per_pixel / 8);
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
