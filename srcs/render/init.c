/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:47:59 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 11:19:38 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player(t_game mlx)
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

t_mlx	init_mlx(void)
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
	//protect
	if (!mlx.mlx_ptr)
	{
		printf("ERROR");
		exit(0);
	}
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	//protect
	if (!mlx.win_ptr)
	{
		printf("ERROR");
		exit(0);
	}
	return (mlx);
}

t_img	init_sprite(t_mlx *mlx, char *path)
{
	int		height;
	int		width;
	t_img	data;

	printf("path = %s\n", path);
	ft_bzero(&data, sizeof(t_img));
	height = 0;
	width = 0;
	data.img = NULL;
	data.add = NULL;
	data.img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &width, &height);
	if (!data.img)
		printf("ERROR\n");
	data.add =  mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endians);
	if (!data.add)
		printf("ERROR2\n");
	data.height = height;
	data.width = width;
	printf("w = %d, h = %d\n", width, height);
	return (data);
}

t_img	create_floor_ceil(t_game *game, t_mlx *mlx)
{
	int			x;
	int			y;
	int			half_height;
	char		*ceil;
	char		*floor;
	t_img		ceil_floor;		

	ceil_floor.img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	half_height = HEIGHT / 2;
	y = -1;
	ceil_floor.add = mlx_get_data_addr(ceil_floor.img, &mlx->main.bpp,
			&mlx->main.size_line, &mlx->main.endians);
	while (++y < half_height)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ceil = ceil_floor.add + y * mlx->main.size_line + x
				* (mlx->main.bpp / 8);
			*(unsigned int *)ceil = game->config->ceiling_color;
			floor = ceil_floor.add + (y + half_height) * mlx->main.size_line
				+ x * (mlx->main.bpp / 8);
			*(unsigned int *)floor = game->config->floor_color;
		}
	}
	return (ceil_floor);
}

t_game	init_window(t_config *data)
{
	t_game		game;

	game.mlx = init_mlx();
	game.show_map = 0;
	game.config = data;
	game.map = data->map;
	game.player = init_player(game);
	game.north = init_sprite(&game.mlx, game.config->no_texture);
	game.south = init_sprite(&game.mlx, game.config->so_texture);
	game.west = init_sprite(&game.mlx, game.config->we_texture);
	game.east = init_sprite(&game.mlx, game.config->ea_texture);
	game.floor_ceil = create_floor_ceil(&game, &game.mlx);
	return (game);
}
