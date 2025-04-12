/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 22:18:49 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game, t_mlx *mlx)
{
	char	*tmp;

	if (mlx->img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		printf("ERROR");
		exit(0);
	}
	mlx->address = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endians);
	tmp = mlx_get_data_addr(game->floor_ceil.img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endians);
	if (!mlx->address)
	{
		printf("ERROR");
		exit(0);
	}
	mlx->address = ft_memcpy(mlx->address, tmp, mlx->size_line * HEIGHT);
	raycasting(game);
	if (game->show_map)
		show_minimap(game);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void	rendering(t_config data)
{
	t_game	game;

	game = init_window(&data);
	mlx_mouse_hide(game.mlx.mlx_ptr, game.mlx.win_ptr);
	render_frame(&game, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 17, 0, destroy_window, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 6, 1L << 6, handle_mouse_move, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, handle_keypress, &game.mlx);
	mlx_loop(game.mlx.mlx_ptr);
}
