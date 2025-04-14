/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:04:25 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/14 16:13:11 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	init_img(void)
{
	t_img	img;

	ft_bzero(&img, sizeof(t_img));
	return (img);
}

static void	load_sprite(t_config *config, t_game *game, char *path)
{
	int		height;
	int		width;
	t_img	data;

	height = 0;
	width = 0;
	printf("sprite = %s\n", path);
	data.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &width, &height);
	if (!data.img)
		print_error(".xpm file doesn't exist.", config);
	data.add =  mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endians);
	if (!data.add)
		print_error("Function 'mlx_get_data_addr()' failed.", config);
	data.height = height;
	data.width = width;
}

t_game init_assets(t_game *game)
{
	game->north = init_img();
	game->south = init_img();
	game->west = init_img();
	game->east = init_img();
	game->door = init_img();
	game->floor_ceil = init_img();
	load_sprite(game->config, game, game->config->no_texture);
	load_sprite(game->config, game, game->config->so_texture);
	load_sprite(game->config, game, game->config->we_texture);
	load_sprite(game->config, game, game->config->ea_texture);
	if (game->config->door_texture)
		load_sprite(game->config, game, game->config->door_texture);
	return (*game);
}
