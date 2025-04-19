/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:02:49 by mlavergn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/17 21:59:53 by mlavergn         ###   ########.fr       */
=======
/*   Updated: 2025/04/17 14:37:35 by qmorinea         ###   ########.fr       */
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	char	**map_ptr;
	int		i;

	i = -1;
	if (!config)
		return ;
	free(config->no_texture);
	free(config->so_texture);
	free(config->we_texture);
	free(config->ea_texture);
	while (config->door_texture[++i])
		free(config->door_texture[i]);
	free(config->door_texture);
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
