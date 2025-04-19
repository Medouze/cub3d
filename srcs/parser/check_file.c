/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/19 16:38:38 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(char *path)
{
	int	len;
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd > 0)
		print_error(ERR_ARGDIR, NULL);
	len = ft_strlen(path);
	if (path[len - 1] == 'b' && path[len - 2] == 'u'
		&& path[len - 3] == 'c' && path[len - 4] == '.')
		return ;
	else
		print_error(ERR_CUBEXT, NULL);
}

void	add_xmp(t_config *data, char **data_text, char *texture)
{
	int	len;
	int	fd;
	int	i;

	i = 0;
	ft_trim_in_place(texture, " \n\t");
	if (*data_text)
		print_error(ERR_MULTI, data);
	if (!has_spaces(texture))
		print_error(ERR_XPMSYNTAX, data);
	while (ft_strchr(VALID_ID, texture[i]))
		i++;
	fd = open(texture, __O_DIRECTORY);
	if (fd > 0)
		print_error(ERR_XPMDIR, data);
	len = ft_strlen(texture);
	if (texture[len - 1] == 'm' && texture[len - 2] == 'p'
		&& texture[len - 3] == 'x' && texture[len - 4] == '.')
	{
		*data_text = ft_strdup(texture + i);
		if (!data_text || has_spaces(*data_text))
			print_error(ERR_XPMSPACE, data);
	}
	else
		print_error(ERR_XPMSYNTAX, data);
}

int	info_empty(t_config *data)
{
	if (!data->no_texture || !data->so_texture
		|| !data->we_texture || !data->ea_texture
		|| data->floor_color == -1 || data->ceiling_color == -1)
		return (1);
	return (0);
}

char	**split_xmp(t_config *data, char **data_text, char *texture)
{
	char	**split;
	int		i;
<<<<<<< HEAD
=======
	int		len;
	char	*new_str;
	char	**test;
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e

	i = 0;
	if (data_text)
		print_error(ERR_MULTI, data);
	while (ft_strchr(VALID_ID, texture[i]))
		i++;
	split = ft_split(texture + i, ' ');
	if (!split)
		print_error(ERR_MALLOC, data);
	i = 0;
	while (split[i])
	{
		if (i > 4)
			print_error(ERR_4DOOR, data);
		ft_trim_in_place(split[i], " \n\t");
		if (!is_valid_xpm(split[i]))
			print_error(ERR_XPMSYNTAX, data);
		if (has_spaces(split[i]))
			print_error(ERR_XPMSPACE, data);
		i++;
	}
	return (split);
}

void	check_valid_infos(t_config *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		add_xmp(data, &data->no_texture, line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		add_xmp(data, &data->so_texture, line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		add_xmp(data, &data->we_texture, line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		add_xmp(data, &data->ea_texture, line);
	else if (ft_strncmp(line, "DT", 2) == 0)
		data->door_texture = split_xmp(data, data->door_texture, line);
	else if (ft_strncmp(line, "F", 1) == 0)
		check_valid_rgb(data, &data->floor_color, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		check_valid_rgb(data, &data->ceiling_color, line);
}
