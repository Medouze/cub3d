/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:57:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 21:49:43 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static int	count_lines(char *path)
// {
// 	int		size;
// 	char	*line;
// 	int		fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		print_error(ERR_OPEN, NULL, NULL);
// 	size = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line)
// 		{
// 			if (!is_only_whitespace(line))
// 				size++;
// 		}
// 		else
// 			break ;
// 		free(line);
// 	}
// 	close(fd);
// 	return (size);
// }

void	print_infos(char **infos) // delete plus tard
{
	char	*str;

	if (infos == NULL)
		return ;
	while (*infos != NULL)
	{
		str = *infos;
		while (*str != '\0')
		{
			write(1, str, 1);
			str++;
		}
		write(1, "\n", 1);
		infos++;
	}
}

void	fill_data(t_config *data, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error(ERR_OPEN, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!is_only_whitespace(line))
			{
				ft_trim_in_place(line, " \n\t");
				check_valid_infos(data, line);
			}
			free(line);
		}
		else
			break ;
	}
	close(fd);
}
