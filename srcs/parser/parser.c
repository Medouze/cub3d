/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:34:46 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/12 15:53:11 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	print_config(const t_config *config)
{
	int	i;

	i = 0;
	if (!config) 
	{
		printf("Config is NULL\n");
		return;
	}
	printf("=== Configuration ===\n");
	printf("NO Texture: %s\n", config->no_texture
	? config->no_texture : "(null)");
	printf("SO Texture: %s\n", config->so_texture
	? config->so_texture : "(null)");
	printf("WE Texture: %s\n", config->we_texture 
	? config->we_texture : "(null)");
	printf("EA Texture: %s\n", config->ea_texture 
	? config->ea_texture : "(null)");
	printf("Floor Color: 0x%06X\n", config->floor_color);
	printf("Ceiling Color: 0x%06X\n", config->ceiling_color);
	printf("Width map: %d\n", config->width);
	printf("Height map: %d\n", config->height);
	printf("Map:\n");
	if (config->map) 
	{
		while (config->map[i])
		{
			printf("  [%d] %s\n", i, config->map[i]
			? config->map[i] : "(null row)");
			i++;
		}
	}
	else
		printf("  (null)\n");
}


void	parser(t_config *data, char *path)
{
	check_file(path);
	fill_data(data, path);
	if (info_empty(data) || !data->map)
		print_error(ERR_MISSINGTEXT, data);
	print_config(data);
}
