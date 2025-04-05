/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:34:46 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 21:48:02 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_config(const t_config *config)
{
	int	i;

	i = 0;
	if (!config) 
	{
		printf("Config is NULL\n");
		return;
	}
	printf("\n=== Configuration ===\n");
	printf("NO Texture: %s\n", config->no_texture ? config->no_texture : "(null)");
	printf("SO Texture: %s\n", config->so_texture ? config->so_texture : "(null)");
	printf("WE Texture: %s\n", config->we_texture ? config->we_texture : "(null)");
	printf("EA Texture: %s\n", config->ea_texture ? config->ea_texture : "(null)");
	printf("Floor Color: 0x%06X\n", config->floor_color);
	printf("Ceiling Color: 0x%06X\n", config->ceiling_color);
	printf("Map:\n");
	if (config->map) 
	{
		while (config->map[i])
		{
			printf("  [%d] %s\n", i, config->map[i] ? config->map[i] : "(null row)");
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
	print_config(data);
	print_error("FREED ALL", data);
}
