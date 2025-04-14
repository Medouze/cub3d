/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:58:50 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/14 15:26:41 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define WIDTH 800
# define HEIGHT 600
# ifndef M_PI
#  define M_PI 3.14159265
# endif

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
	int		map_x;
	int		map_y;
	int 	side_hit;
	int 	x_step;
	int 	y_step;
	float	plane_x;
	float	plane_y;
	float	camera_x;
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

typedef struct s_img
{
	void	*img;
	void	*add;
	int		height;
	int		width;
	int		bpp;
	int		size_line;
	int		endians;
}	t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		main;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	char		**map;
	int			scaling;
	int			show_map;
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
	t_img		floor_ceil;
	t_img		door;
	t_player	player;
	t_config	*config;
}	t_game;

void	open_door(t_game *game);

/******************** INIT *******************/

t_game		init_window(t_config *data);

/******************** MLX ********************/

int		destroy_window(void *ptr);
int		handle_mouse_move(int x,int y, void *param);
int		handle_keypress(int key, t_game *mlx);

/****************** PLAYER *******************/

void	rotate_player_vector(t_game *game, int rotation);

/****************** RAYCAST ******************/

void	init_raycasting(t_player *p, t_ray *ray, int x);
void	raycasting(t_game *game);
void	digital_differential_analyzer(t_game *game, t_ray *ray, char *set);

/******************* RENDER ******************/

void	render_frame(t_game *game, t_mlx *mlx);
void	draw_wall_line(t_game *game, int x, t_ray ray);

/****************** MINIMAP ******************/

void	draw_line_minimap(t_game *game, int x, t_ray ray);
void	show_minimap(t_game *game);

/******************* UTILS *******************/

double	to_degree(double radian);
double	to_radians(double degree);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

#endif