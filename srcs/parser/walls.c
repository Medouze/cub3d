/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:48:29 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/16 15:10:30 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	get_tile(char **map, int i, int j)
{
	if (i < 0 || !map[i])
	{
		printf("entered\n");
		return (0);
	}
	if (j < 0 || j >= (int)ft_strlen(map[i]))
		return (0);
	return (map[i][j]);
}

int	check_tile(char **map, int i, int j)
{
	if (get_tile(map, i - 1, j) == 0 || get_tile(map, i - 1, j) == '2'
		|| get_tile(map, i + 1, j) == 0 || get_tile(map, i + 1, j) == '2'
		|| get_tile(map, i, j - 1) == 0 || get_tile(map, i, j - 1) == '2'
		|| get_tile(map, i, j + 1) == 0 || get_tile(map, i, j + 1) == '2'
		/* || get_tile(map, i - 1, j - 1) == 0
		|| get_tile(map, i - 1, j - 1) == '2'
		|| get_tile(map, i - 1, j + 1) == 0
		|| get_tile(map, i - 1, j + 1) == '2'
		|| get_tile(map, i + 1, j - 1) == 0
		|| get_tile(map, i + 1, j - 1) == '2'
		|| get_tile(map, i + 1, j + 1) == 0
		|| get_tile(map, i + 1, j + 1) == '2' */)
		return (0);
	return (1);
}

void	check_walls(char **map, t_config *data)
{
	int		i;
	int		j;
	char	tile;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			tile = map[i][j];
			if (tile == '0' || tile == data->player_direction)
			{
				if (!check_tile(map, i, j))
					print_error("Map is not surrounded by walls", data);
			}
			j++;
		}
		i++;
	}
}
