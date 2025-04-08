/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:27:58 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/08 22:39:41 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx.address + y * mlx.size_line +  x * (mlx.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

float	to_radians(float degree)
{
	return (degree * M_PI / 180);
}
