/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:14 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/13 22:00:32 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	test(t_game *game, float delta[2], char *set)
{
	int		i;
	int		j;
	float	p_x;
	float	p_y;
	t_point	wall;

	p_x = game->player.x;
	p_y = game->player.y;
	i = -1;
	while (++i < game->scaling * 2)
	{
		printf("dx = %f, dy = %f, px = %f, py = %f\n", delta[0], delta[1], p_x, p_y);
		j = -1;
		while (set[++j])
		{
			printf("x = %d, y = %d\n", (int) p_y, (int) p_x);
			if (game->map[(int) p_y][(int) p_x] == set[j])
				break ;
			printf("%c != %c\n", game->map[(int) p_y][(int) p_x] ,set[j]);
		}
		p_x += delta[0];
		p_y += delta[1];
	}
	printf("scale = %d\n", game->scaling);
	wall.x = (int) p_x / game->scaling;
	wall.y = (int) p_y / game->scaling;
	return (wall);
}

void	open_door(t_game *game)
{
	t_point wall;
	float	delta[2];

	delta[0] = game->player.vx / game->scaling;
	delta[1] = game->player.vy / game->scaling;
	printf("scaling = %d\n", game->scaling);
	wall = test(game, delta, "1DA");
	if (game->map[(int) wall.y][(int) wall.x] == 'D')
	{
		game->map[(int) wall.y][(int) wall.x] = 'd';	
	}
	else if (game->map[(int) wall.y][(int) wall.x] == 'd')
	{
		game->map[(int) wall.y][(int) wall.x] = 'D';	
	}
}