/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:02:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 18:48:45 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_config(t_config *config)
{
	if (!config)
		return;
	free(config->no_texture);
	free(config->so_texture);
	free(config->we_texture);
	free(config->ea_texture);
	if (config->map)
	{
		char **map_ptr = config->map;
		while (*map_ptr)
		{
			free(*map_ptr);
			map_ptr++;
		}
		free(config->map);
	}
	*config = (t_config){0};
}

void    free_infos(char **infos)
{
    if (!infos)
        return;
    for (int i = 0; infos[i] != NULL; i++)
    {
        free(infos[i]);
        infos[i] = NULL;
    }
    free(infos);
}

void	print_error(char *str, t_config *data, char **infos)
{
	free_config(data);
	free_infos(infos);
	printf("Error : %s\n", str);
	exit(EXIT_FAILURE);
}
