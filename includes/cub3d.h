/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:19:26 by mlavergn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/17 21:57:50 by mlavergn         ###   ########.fr       */
=======
/*   Updated: 2025/04/17 14:37:24 by qmorinea         ###   ########.fr       */
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"
# include "errors.h"
# include "render.h"

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	**door_texture;
	int		player_pos_x;
	int		player_pos_y;
	char	player_direction;
	int		floor_color;
	int		ceiling_color;
	int		width;
	int		height;
	char	**map;
}	t_config;

/*init*/
void	init_config(t_config *config);
/*error*/
void	print_error(char *str, t_config *data);
void	free_double(char **infos);
void	free_config(t_config *config);
/*parser*/
void	parser(t_config *data, char *path);
void	fill_data(t_config *data, char *path);
void	check_valid_rgb(t_config *data, int *value, char *rgb);
/*check*/
void	check_file(char *path);
void	check_valid_infos(t_config *data, char *line);
int		info_empty(t_config *data);
void	valid_map(t_config *data);
int		is_valid_xpm(const char *s);
/*map*/
char	**pad_map_lines(t_config *data, char **map);
void	check_walls(char **map, t_config *data);
void	check_player_stuck(t_config *data);
/*utils*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_only_whitespace(const char *str);
char	*ft_strdup(const char *s);
int		has_spaces(const char *str);
int		ft_is_digit(char c);
void	ft_trim_in_place(char *str, const char *set);
char	**ft_split(char const *s, char c);
int		ft_is_space(char c);
int		ft_atoi(const char *str);
char	**copy_double(char **map);
int		ft_isalpha(int c);
/* Render */
void	rendering(t_config data);
#endif