/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:19:26 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 12:21:45 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../gnl/get_next_line.h"

typedef struct s_config 
{
    char	*no_texture;
    char	*so_texture;
    char	*we_texture;
    char	*ea_texture;
    int		floor_color;
    int		ceiling_color;
    char	**map;
} t_config;

#endif