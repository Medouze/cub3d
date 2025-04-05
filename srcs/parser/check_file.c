/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 18:47:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_file(char *path)
{
    int	len;
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd > 0)
		print_error("Argument can't be a directory", NULL, NULL);
    len = ft_strlen(path);
	if (path[len - 1] == 'b' && path[len - 2] == 'u' && path[len - 3] == 'c' && path[len - 4] == '.')
		return ;
	else
		print_error("FILE ERROR : WRONG EXTENSION NEEDS TO BE .cub", NULL, NULL); 
}

void	add_xmp(t_config *data, char **data_text, char *texture)
{
	int	len;
	int	fd;
	int	i;

	i = 2;
	while (texture[i] == 32 || texture[i] == '\t')
		i++;
	fd = open(texture, __O_DIRECTORY);
	if (fd > 0)
		print_error("XPM can't be a directory", data, NULL);
    len = ft_strlen(texture);
	if (texture[len - 2] == 'm' && texture[len - 3] == 'p' && texture[len - 4] == 'x' && texture[len - 5] == '.')
	{
		*data_text = ft_strdup(texture + i);
		if (has_spaces(*data_text))
			print_error("FILE ERROR : HAS SPACES IN XPM FILE NAME", data, NULL); 
	}
	else
		print_error("FILE ERROR : WRONG EXTENSION NEEDS TO BE .xpm", data, NULL); 
}

// void	check_valid_rgb(t_config *data, int value, char *rgb)
// {
	
// }

void	check_valid_infos(t_config *data, char **infos)
{
	int	i;

	i = 0;
	while (infos[i])
	{
		if (ft_strncmp(infos[i], "NO ", 3) == 0)
			add_xmp(data, &data->no_texture, infos[i]);
		else if (ft_strncmp(infos[i], "SO ", 3) == 0)
			add_xmp(data, &data->so_texture, infos[i]);
		else if (ft_strncmp(infos[i], "WE ", 3) == 0)
			add_xmp(data, &data->we_texture, infos[i]);
		else if (ft_strncmp(infos[i], "EA ", 3) == 0)
			add_xmp(data, &data->ea_texture, infos[i]);
		i++;
	}
	// else if (ft_strncmp(infos[i], "F ", 2) == 0)
	// 	data->floor_color = 
}