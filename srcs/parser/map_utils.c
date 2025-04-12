/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:40:36 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/12 15:48:01 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_longest_line(char **map)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_line(char *line, int width)
{
	int		i;
	int		len;
	char	*new_line;

	i = 0;
	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	while (i < width)
	{
		if (i < len)
			new_line[i] = line[i];
		else
			new_line[i] = '2';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	**pad_map_lines(t_config *data, char **map)
{
	char	**padded_map;
	int		i;

	data->width = get_longest_line(map);
	while (map[data->height])
		data->height++;
	padded_map = malloc(sizeof(char *) * (data->height + 1));
	if (!padded_map)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		padded_map[i] = pad_line(map[i], data->width);
		i++;
	}
	padded_map[data->height] = NULL;
	return (padded_map);
}

void	check_player_stuck(t_config *data)
{
	int	x;
	int	y;

	x = data->player_pos_x;
	y = data->player_pos_y;
	if ((data->map[y + 1][x] == '1') && (data->map[y - 1][x] == '1')
		&& (data->map[y][x + 1] == '1') && (data->map[y][x - 1] == '1'))
		print_error(ERR_PLAYERSTUCK, data);
}
