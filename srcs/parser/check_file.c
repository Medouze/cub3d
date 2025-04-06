/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/07 00:33:20 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int info_empty(t_config *data)
{
    // Check if any of the required fields are still empty (NULL or -1)
    if (!data->no_texture || !data->so_texture || !data->we_texture || !data->ea_texture
        || data->floor_color == -1 || data->ceiling_color == -1)
        return (1);  // Return 1 if any required field is empty
    return (0);  // Return 0 if all fields are filled
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
	else if (ft_strncmp(line, "F", 1) == 0)
		check_valid_rgb(data, &data->floor_color, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		check_valid_rgb(data, &data->ceiling_color, line);
	else
		print_error(ERR_UNKNOWNID, data);
}
