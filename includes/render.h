/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:58:50 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/12 02:02:18 by qmorinea         ###   ########.fr       */
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
# define HORIZONTAL 0
# define VERTICAL 1

typedef struct s_config	t_config;

typedef struct s_point
{
	int		height;
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	int 	side_hit;
	int 	x_step;
	int 	y_step;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	vector_x;
	double	vector_y;
	double	wall_dis;
	t_point	wall;
}	t_ray;

typedef struct s_player
{
	int		fov;
	int		view_distance;
	int		rotation;
	float	x;
	float	y;
	float	vx;
	float	vy;
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
	void		*north_img;
	void		*south_img;
	void		*west_img;
	void		*east_img;
	t_player	player;
	t_config	*config;
}	t_mlx;

t_mlx	init_window(t_config *data);
int		handle_keypress(int key, t_mlx *mlx);
void	render_frame(t_mlx *mlx);
void	rotate_player_vector(t_mlx *mlx, int rotation);

/******************** MLX ********************/

void	destroy_window(t_mlx *mlx, int is_error);

/****************** RAYCAST ******************/

void digital_differential_analyzer(t_mlx *mlx, t_ray *ray);

/****************** MINIMAP ******************/

void	draw_map(t_mlx mlx);
void	show_minimap(t_mlx mlx);

/******************* UTILS *******************/

double	to_degree(double radian);
double	to_radians(double degree);
void	put_pixel(t_mlx mlx, int x, int y, int color);

#endif