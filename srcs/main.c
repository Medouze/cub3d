/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:19:56 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/17 14:39:24 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_config	data;

	if (ac != 2)
		print_error(ERR_NOARG, NULL);
	init_config(&data);
	parser(&data, av[1]);
	rendering(data);
	free_config(&data);
	return (0);
}
