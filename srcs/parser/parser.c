/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:34:46 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 18:25:00 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void print_config(const t_config *config)
{
    if (!config) {
        printf("Config is NULL\n");
        return;
    }

    printf("\n=== Configuration ===\n");
    
    // Print textures (check each for NULL)
    printf("NO Texture: %s\n", config->no_texture ? config->no_texture : "(null)");
    printf("SO Texture: %s\n", config->so_texture ? config->so_texture : "(null)");
    printf("WE Texture: %s\n", config->we_texture ? config->we_texture : "(null)");
    printf("EA Texture: %s\n", config->ea_texture ? config->ea_texture : "(null)");
    
    // Print colors (always valid integers)
    printf("Floor Color: 0x%06X\n", config->floor_color);
    printf("Ceiling Color: 0x%06X\n", config->ceiling_color);
    
    // Print map (check for NULL and each row)
    printf("Map:\n");
    if (config->map) {
        for (int i = 0; config->map[i]; i++) {
            printf("  [%d] %s\n", i, config->map[i] ? config->map[i] : "(null row)");
        }
    } else {
        printf("  (null)\n");
    }
}

void	parser(t_config *data, char *path)
{
	char    **infos;

	check_file(path);
	infos = fill_infos(path);
	check_valid_infos(data, infos);
	print_config(data);
	print_error("FREED ALL", data, infos);
}