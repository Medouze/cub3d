/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getInfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:57:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 12:04:46 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void    parse_file(t_config *data)
{
    char    *line;
    int     fd;
    
    fd = open("../../maps/maptest.cub", O_RDONLY);
    if (fd == -1)
        ft_error("Error with file\n");
    while (line)
    {
        line = get_next_line()
    }
}