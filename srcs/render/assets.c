/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:04:25 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/14 16:44:23 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	init_img(void)
{
	t_img	img;

	ft_bzero(&img, sizeof(t_img));
	return (img);
}

static void	load_sprite(t_game *game, t_img *img, char *path)
{
	int		height;
	int		width;

	height = 0;
	width = 0;
	printf("sprite = %s\n", path);
	img->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &width, &height);
	if (!img->img)
	{
		destroy_sprite_img(game, 1);
		print_error(".xpm file doesn't exist.", game->config);
	}
	img->add =  mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endians);
	if (!img->add)
	{
		destroy_sprite_img(game, 1);
		print_error("Function 'mlx_get_data_addr()' failed.", game->config);
	}
	img->height = height;
	img->width = width;
}

t_game init_assets(t_game *game)
{
	game->north = init_img();
	game->south = init_img();
	game->west = init_img();
	game->east = init_img();
	game->door = init_img();
	game->floor_ceil = init_img();
	load_sprite(game, &game->north, game->config->no_texture);
	load_sprite(game, &game->south, game->config->so_texture);
	load_sprite(game, &game->west, game->config->we_texture);
	load_sprite(game, &game->east, game->config->ea_texture);
	if (game->config->door_texture)
		load_sprite(game, &game->door, game->config->door_texture);
	return (*game);
}
