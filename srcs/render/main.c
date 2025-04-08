/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:04:04 by qmorinea          #+#    #+#             */
/*   Updated: 2025/04/07 20:36:14 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	// to remove
	int *map[10];

	int tmp1[] = {1, 1, 1, 1, 1};
	map[0] = tmp1;
	int tmp2[] = {1, 0, 1, 0, 1};
	map[1] = tmp2;
	int tmp3[] = {1, 0, 0, 0, 1};
	map[2] = tmp3;
	int tmp4[] = {1, 0, 0, 0, 1};
	map[3] = tmp4;
	int tmp5[] = {1, 1, 0, 1, 1};
	map[4] = tmp5;
	int tmp6[] = {1, 1, 0, 1, 1};
	map[5] = tmp6;
	int tmp7[] = {1, 0, 0, 0, 1};
	map[6] = tmp7;
	int tmp8[] = {1, 1, 1, 0, 1};
	map[7] = tmp8;
	int tmp9[] = {1, 0, 0, 0, 1};
	map[8] = tmp9;
	int tmp10[] = {1, 1, 1, 1, 1};
	map[9] = tmp10;


	t_mlx mlx = init_window();
	mlx.map = map;
	mlx.scaling = 30;
	mlx.img = NULL;
	mlx.address = NULL;

	//mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}