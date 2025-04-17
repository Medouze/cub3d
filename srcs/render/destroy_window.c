/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:26:03 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/17 15:10:22 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_img(t_mlx *mlx, t_img *img)
{
	if (img->img)
		mlx_destroy_image(mlx->mlx_ptr, img->img);
}

static void	free_door_img(t_game *game, t_mlx *mlx)
{
	int	i;
	int	len;

	len = 0;
	while (game->config->door_texture[len])
		len ++;
	i = -1;
	while (++i < len)
		free_img(mlx, &game->door_array[i]);
}

void	destroy_sprite_img(t_game *game, int exit)
{
	free_img(&game->mlx, &game->north);
	free_img(&game->mlx, &game->south);
	free_img(&game->mlx, &game->west);
	free_img(&game->mlx, &game->east);
	free_img(&game->mlx, &game->floor_ceil);
	if (game->config->door_texture)
		free_door_img(game, &game->mlx);
	if (exit)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
}

int	destroy_window(void *ptr)
{
	t_game	*game;
	t_mlx	*mlx;

	game = (t_game *) ptr;
	mlx = &game->mlx;
	mlx_loop_end(mlx->mlx_ptr);
	mlx_mouse_show(mlx->mlx_ptr, mlx->win_ptr);
	destroy_sprite_img(game, 0);
	free_img(&game->mlx, &game->mlx.main);
	free(mlx->mlx_ptr);
	free_config(game->config);
	exit(0);
	return (0);
}
