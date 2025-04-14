/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/15 01:00:16 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game, t_mlx *mlx)
{
	char	*tmp;

	if (mlx->main.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->main.img);
	mlx->main.img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->main.img)
		destroy_window(game);
	mlx->main.add = mlx_get_data_addr(mlx->main.img, &mlx->main.bpp,
			&mlx->main.size_line, &mlx->main.endians);
	tmp = mlx_get_data_addr(game->floor_ceil.img, &mlx->main.bpp,
			&mlx->main.size_line, &mlx->main.endians);
	if (!mlx->main.add)
		destroy_window(game);
	mlx->main.add = ft_memcpy(mlx->main.add, tmp, mlx->main.size_line * HEIGHT);
	raycasting(game);
	if (game->show_map)
		show_minimap(game);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->main.img, 0, 0);
}

int	loop(void *ptr)
{
	t_game *game;
	struct timeval tv;

	game = (t_game *) ptr;

	gettimeofday(&tv, NULL);
	int res = tv.tv_usec / 250000;
	if (res == 0)
		game->door = game->door_array[0];
	if (res == 1)
		game->door = game->door_array[1];
	if (res == 2)
		game->door = game->door_array[2];
	if (res == 3)
		game->door = game->door_array[3];
	render_frame(game, &game->mlx);
	return (0);
}

void	rendering(t_config data)
{
	t_game	game;

	game = init_window(&data);
	//mlx_mouse_hide(game.mlx.mlx_ptr, game.mlx.win_ptr);
	mlx_hook(game.mlx.win_ptr, 17, 0, destroy_window, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 6, 1L << 6, handle_mouse_move, &game.mlx);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, handle_keypress, &game.mlx);
	mlx_loop_hook(game.mlx.mlx_ptr, loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
