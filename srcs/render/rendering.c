/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:52:31 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/16 22:11:17 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game, t_mlx *mlx)
{
	char	*tmp;

	if (mlx->main.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->main.img);
	mlx->main.img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->main.img)
		destroy_window(game);
	mlx->main.add = mlx_get_data_addr(mlx->main.img, &mlx->main.bpp,
			&mlx->main.size_line, &mlx->main.endians);
	tmp = mlx_get_data_addr(game->floor_ceil.img, &mlx->main.bpp,
			&mlx->main.size_line, &mlx->main.endians);
	if (!mlx->main.add)
		destroy_window(game);
	mlx->main.add = ft_memcpy(mlx->main.add, tmp, mlx->main.size_line * HEIGHT);
	raycasting(game);
	if (game->show_map)
		show_minimap(game);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->main.img, 0, 0);
}

static	void	increment_door(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '9')
				game->map[i][j] = 'd';
			else if (game->map[i][j] == 'z')
				game->map[i][j] = 'D';
			else if (game->map[i][j] >= '2' && game->map[i][j] <= '9')
				game->map[i][j]++;
			else if (game->map[i][j] <= 'z' && game->map[i][j] >= 's')
				game->map[i][j]++;
		}
	}
}

static	void	door_animation(t_game *game)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
	if (now - game->tmp_time > 200)
	{
		increment_door(game);
		game->tmp_time = now;
	}
}

static void	check_animation(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] >= '2' && game->map[i][j] <= '9')
				return ;
			else if (game->map[i][j] <= 'z' && game->map[i][j] >= 's')
				return ;
		}
	}
	game->is_animating = 0;
}

int	render_loop(void *ptr)
{
	t_game	*game;

	game = (t_game *) ptr;
	check_animation(game);
	if (game->is_animating)
		door_animation(game);
	render_frame(game, &game->mlx);
	return (0);
}
