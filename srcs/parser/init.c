/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:36:40 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/15 14:10:21 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->door_texture = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->player_pos_x = 0;
	config->player_pos_y = 0;
	config->player_direction = ' ';
	config->width = 0;
	config->height = 0;
	config->map = NULL;
}
