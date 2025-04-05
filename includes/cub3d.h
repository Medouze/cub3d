/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:19:26 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 18:43:58 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../gnl/get_next_line.h"

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_config;


/*init*/
void	init_config(t_config *config);
/*error*/
void	print_error(char *str, t_config *data, char **infos);
/*parser*/
void	parser(t_config *data, char *path);
char	**fill_infos(char *path);
/*check*/
void	check_file(char *path);
void	check_valid_infos(t_config *data, char **infos);
/*utils.c*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_only_whitespace(const char *str);
char	*ft_strdup(const char *s);
int		has_spaces(const char *str);

#endif