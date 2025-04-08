/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:31:36 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/08 16:16:00 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_player_pos(t_config *data, int *player_count, int i, int j)
{
	*player_count += 1;
	if (*player_count > 1)
		print_error(ERR_MULTPLAYER, data);
	if (data->map[i][j] == 'N')
		data->player_direction = 'N';
	else if (data->map[i][j] == 'S')
		data->player_direction = 'S';
	else if (data->map[i][j] == 'E')
		data->player_direction = 'E';
	else if (data->map[i][j] == 'W')
		data->player_direction = 'W';
	data->player_pos_x = j;
	data->player_pos_y = i;
}

void	check_tab_start(t_config *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			print_error(ERR_TABMAP, data);
		i++;
	}
}

void	check_map_info(t_config *data, char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		check_tab_start(data, map[i]);
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(PLAYERCHAR, map[i][j]))
				get_player_pos(data, &player_count, i, j);
			if (!ft_strchr(VALID_MAPCHAR, map[i][j]))
				print_error(ERR_INVALIDMAPCHAR, data);
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (player_count == 0)
		print_error(ERR_NOPLAYER, data);
}

void	print_map(char **map)
{
	int i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	valid_map(t_config *data)
{
	char	**map_copy;

	check_map_info(data, data->map);
	map_copy = pad_map_lines(data->map);
	check_player_stuck(data);
	check_walls(map_copy, data);
	free_double(map_copy);
}
