/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:40:36 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/08 21:38:40 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

char	**pad_map_lines(char **map)
{
	int		height;
	int		width;
	char	**padded_map;
	int		i;

	height = 0;
	width = get_longest_line(map);
	while (map[height])
		height++;
	padded_map = malloc(sizeof(char *) * (height + 1));
	if (!padded_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		padded_map[i] = pad_line(map[i], width);
		i++;
	}
	padded_map[height] = NULL;
	return (padded_map);
}
char	get_tile(char **map, int i, int j)
{
	if (i < 0 || !map[i])
		return (0);
	if (j < 0 || j >= (int)ft_strlen(map[i]))
		return (0);
	return (map[i][j]);
}


void	check_walls(char **map, t_config *data)
{
	int	i, j;
	char	tile;

	for (i = 0; map[i]; i++)
	{
		for (j = 0; map[i][j]; j++)
		{
			tile = map[i][j];
			if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
			{
				if (get_tile(map, i - 1, j) == 0 || get_tile(map, i - 1, j) == '2' ||
					get_tile(map, i + 1, j) == 0 || get_tile(map, i + 1, j) == '2' ||
					get_tile(map, i, j - 1) == 0 || get_tile(map, i, j - 1) == '2' ||
					get_tile(map, i, j + 1) == 0 || get_tile(map, i, j + 1) == '2' ||
					get_tile(map, i - 1, j - 1) == 0 || get_tile(map, i - 1, j - 1) == '2' ||
					get_tile(map, i - 1, j + 1) == 0 || get_tile(map, i - 1, j + 1) == '2' ||
					get_tile(map, i + 1, j - 1) == 0 || get_tile(map, i + 1, j - 1) == '2' ||
					get_tile(map, i + 1, j + 1) == 0 || get_tile(map, i + 1, j + 1) == '2')
					print_error("Map is not surrounded by walls", data);
			}
		}
	}
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
