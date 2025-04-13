/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:26:03 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 11:37:38 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_img(t_mlx *mlx, t_img *img)
{
	if (img->img)
		mlx_destroy_image(mlx->mlx_ptr, img->img);
}

int	destroy_window(void *ptr)
{
	t_game	*game;
	t_mlx	*mlx;

	game = (t_game *) ptr;
	mlx = &game->mlx;
	mlx_loop_end(mlx->mlx_ptr);
	//mlx_mouse_show(mlx->mlx_ptr, mlx->win_ptr);
	free_img(mlx, &mlx->main);
	free_img(mlx, &game->north);
	free_img(mlx, &game->south);
	free_img(mlx, &game->west);
	free_img(mlx, &game->east);
	free_img(mlx, &game->floor_ceil);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free_config(game->config);
	exit(0);
	return (0);
}
