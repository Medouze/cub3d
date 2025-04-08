/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:19:56 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/08 18:23:49 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_config	data;

	if (ac == 1)
		print_error(ERR_NOARG, NULL);
	init_config(&data);
	parser(&data, av[1]);
	printf("map = %p\n", data.map);
	rendering(data);
	return (0);
}
