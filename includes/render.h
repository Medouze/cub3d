/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:58:50 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/08 22:53:44 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define WIDTH 800
# define HEIGHT 600
# ifndef M_PI
# define M_PI 3.14159265
# endif

# define NORTH 0xFF0000
# define SOUTH 0x0000FF
# define EAST  0x00FF00
# define WEST 0xFFFF00

typedef struct s_config	t_config;

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}	t_point;

typedef struct s_player
{
	int		fov;
	int		view_distance;
	int		rotation;
	float	x;
	float	y;
	int		x_dir;
	int		y_dir;
}	t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	void		*address;
	int			bits_per_pixel;
	int			size_line;
	int			endians;
	char		**map;
	int			scaling;
	int			show_map;
	t_player	player;
	t_config	*config;
}	t_mlx;

t_mlx	init_window(t_config *data);
int		handle_keypress(int key, t_mlx *mlx);
void	render_frame(t_mlx *mlx);
t_point	calculate_point(t_mlx *mlx, int rotation);

/******************** MLX ********************/

void	destroy_window(t_mlx *mlx, int is_error);

/******************* UTILS *******************/

float	to_radians(float degree);
void	put_pixel(t_mlx mlx, int x, int y, int color);

#endif