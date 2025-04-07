/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:31:36 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/07 16:38:28 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int check_char_map(t_config *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (!ft_strchr(VALID_MAPCHAR, data->map[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void    replace_spaces(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
                map[i][j] = '1';
            j++;
        }
        i++;
    }
}

void    valid_map(t_config *data)
{
    if (!check_char_map(data))
        print_error(ERR_INVALIDMAPCHAR, data);
    replace_spaces(data->map);
}