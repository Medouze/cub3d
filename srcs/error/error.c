/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:02:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/23 16:33:20 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_door_texture(char **door_texture)
{
	int		i;

	i = -1;
	if (!door_texture)
		return ;
	while (door_texture[++i])
		free(door_texture[i]);
	free(door_texture);
}

void	free_config(t_config *config)
{
	char	**map_ptr;

	if (!config)
		return ;
	free(config->no_texture);
	free(config->so_texture);
	free(config->we_texture);
	free(config->ea_texture);
	if (config->door_texture)
		free_door_texture(config->door_texture);
	if (config->map)
	{
		map_ptr = config->map;
		while (*map_ptr)
		{
			free(*map_ptr);
			map_ptr++;
		}
		free(config->map);
	}
	*config = (t_config){0};
}

void	free_double(char **infos)
{
	int	i;

	i = 0;
	if (!infos)
		return ;
	while (infos[i])
	{
		free(infos[i]);
		infos[i] = NULL;
		i++;
	}
	free(infos);
}

void	print_error(char *str, t_config *data)
{
	free_config(data);
	printf("Error\n");
	printf("%s\n", str);
	if (ft_strncmp("FREED ALL ", str, ft_strlen(str)) == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
