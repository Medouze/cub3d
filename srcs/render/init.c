/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:47:59 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/23 16:59:56 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_player	init_player(t_game mlx)
{
	t_player	player;

	player.x = mlx.config->player_pos_x + 0.5;
	player.y = mlx.config->player_pos_y + 0.5;
	player.vx = 0;
	player.vy = 0;
	if (mlx.config->player_direction == 'N')
		player.vy = -1;
	else if (mlx.config->player_direction == 'S')
		player.vy = 1;
	else if (mlx.config->player_direction == 'W')
		player.vx = -1;
	else
		player.vx = 1;
	player.fov = 90;
	player.rotation = 0;
	player.view_distance = 10;
	return (player);
}

static t_mlx	init_mlx(t_config *data)
{
	t_mlx	mlx;
	t_img	img;

	ft_bzero(&mlx, sizeof(t_mlx));
	mlx.win_ptr = NULL;
	mlx.mlx_ptr = NULL;
	img.img = NULL;
	img.add = NULL;
	img.bpp = 0;
	img.size_line = 0;
	img.endians = 0;
	mlx.main = img;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		print_error("Function 'mlx_init()' failed.", data);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!mlx.win_ptr)
		print_error("Function 'mlx_new_window()' failed.", data);
	return (mlx);
}

static void	floor_ceil_loop(t_game *game, t_img *ceil_floor, int x, int y)
{
	int		half_height;
	char	*ceil;
	char	*floor;

	half_height = HEIGHT / 2;
	ceil = ceil_floor->add + y * game->mlx.main.size_line + x
		* (game->mlx.main.bpp / 8);
	*(unsigned int *)ceil = game->config->ceiling_color;
	floor = ceil_floor->add + (y + half_height) * game->mlx.main.size_line
		+ x * (game->mlx.main.bpp / 8);
	*(unsigned int *)floor = game->config->floor_color;
}

static void	create_floor_ceil(t_game *game, t_mlx *mlx)
{
	int			x;
	int			y;
	int			half_height;

	game->floor_ceil.img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!game->floor_ceil.img)
	{
		destroy_sprite_img(game, 1);
		print_error("Function 'mlx_new_image()' failed.", game->config);
	}
	half_height = HEIGHT / 2;
	y = -1;
	game->floor_ceil.add = mlx_get_data_addr(game->floor_ceil.img,
			&mlx->main.bpp, &mlx->main.size_line, &mlx->main.endians);
	if (!game->floor_ceil.add)
	{
		destroy_sprite_img(game, 1);
		print_error("Function 'mlx_new_image()' failed.", game->config);
	}
	while (++y < half_height)
	{
		x = -1;
		while (++x < WIDTH)
			floor_ceil_loop(game, &game->floor_ceil, x, y);
	}
}

t_game	init_window(t_config *data)
{
	int		x_max;
	int		y_max;
	int		max;
	t_game	game;

	ft_bzero(&game,  sizeof(t_game));
	game.mlx = init_mlx(data);
	game.show_map = 1;
	game.is_animating = 0;
	game.is_using_mouse = 0;
	game.is_key_pressed = 0;
	game.config = data;
	game.map = data->map;
	game.player = init_player(game);
	game = init_assets(&game);
	create_floor_ceil(&game, &game.mlx);
	x_max = game.config->width;
	y_max = game.config->height;
	max = fmax(y_max, x_max);
	if (max == y_max)
		game.scaling = (HEIGHT / 3) / max;
	else
		game.scaling = (WIDTH / 3) / max;
	game.map[(int) game.player.y][(int) game.player.x] = '0';
	return (game);
}
