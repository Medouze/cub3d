/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:23:07 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 22:17:05 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	is_valid_rgb_number(const char *str)
{
	while (*str)
	{
		if (!ft_is_digit(*str) && *str != ' ' && *str != ',')
			return (0);
		str++;
	}
	return (1);
}

void	check_valid_rgb(t_config *data, int *value, char *rgb)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		count;

	count = 0;
	while (*rgb && !ft_is_digit(*rgb))
		rgb++;
	if (!is_valid_rgb_number(rgb))
		print_error("Invalid char in rgb", data);
	split = ft_split(rgb, ',');
	while (split[count])
		count++;
	if (count != 3)
		print_error("RGB must have 3 values", data);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("RGB must be between 0 and 255", data);
	*value = rgb_to_int(r, g, b);
	free_double(split);
}
