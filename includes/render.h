/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:58:50 by qmorinea          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/17 22:02:48 by mlavergn         ###   ########.fr       */
=======
/*   Updated: 2025/04/18 10:23:55 by qmorinea         ###   ########.fr       */
>>>>>>> 87efb7c2b26d782019ae27ad498d5dd74a39fa4e
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
	int		side_hit;
	int		x_step;
	int		y_step;
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
	int			scaling;
	int			is_animating;
	int			show_map;
	int			is_using_mouse;
	char		**map;
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
	t_img		floor_ceil;
	t_img		door;
	t_img		*door_array;
	t_player	player;
	t_config	*config;
	long		tmp_time;
	int			is_key_pressed;
}	t_game;

/******************** DOOR *******************/

void	open_door(t_game *game);
t_img	*door_texture_animation(t_game *game, char c);

/******************** INIT *******************/

t_game	init_assets(t_game *game);
t_game	init_window(t_config *data);

/******************** MLX ********************/

void	destroy_sprite_img(t_game *game, int exiting);
int		destroy_window(void *ptr);
int		handle_mouse_move(int x, int y, void *param);
int		handle_keypress(int key, t_game *mlx);

/****************** PLAYER *******************/

void	rotate_player_vector(t_game *game, int rotation);

/****************** RAYCAST ******************/

void	init_raycasting(t_player *p, t_ray *ray, int x);
void	raycasting(t_game *game);
void	digital_differential_analyzer(t_game *game, t_ray *ray, char *set);

/******************* RENDER ******************/

int		render_loop(void *ptr);
void	render_frame(t_game *game, t_mlx *mlx);
void	draw_wall_line(t_game *game, int x, t_ray ray);

/****************** MOVEMENT ******************/

int		mov_is_wall(t_game *game, float margin, float new_x, float new_y);
void	move_left(t_game *game, t_player *player);
void	move_right(t_game *game, t_player *player);
void	move_backward(t_game *game, t_player *player);
void	move_forward(t_game *game, t_player *player);

/****************** MINIMAP ******************/

void	draw_player(t_game *game);
void	draw_fov(t_game *game, t_player *player);
void	show_minimap(t_game *game);

/******************* UTILS *******************/

void	put_pixel(t_mlx *mlx, int x, int y, int color);
int		is_wall_set(t_game *game, t_ray *ray, char *set);
double	to_degree(double radian);
double	to_radians(double degree);

#endif