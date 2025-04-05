/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:36:40 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 21:12:52 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_config(t_config *config)
{
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->floor_color = 0;
	config->ceiling_color = 0;
	config->map = NULL;
}
