/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:57:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/09 18:43:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	count_check_map_lines(t_config *data, int fd)
{
	int		count;
	char	*line;
	int		eof;

	count = 0;
	eof = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_only_whitespace(line))
			eof = 1;
		if (eof == 1 && !is_only_whitespace(line))
			print_error(ERR_EMPTYMAP, data);
		count++;
		free(line);
	}
	return (count);
}

void	allocate_map(t_config *data, int fd)
{
	int		size;

	size = count_check_map_lines(data, fd);
	data->map = malloc(sizeof(char *) * (size + 2));
	if (!data->map)
		print_error(ERR_MALLOC, data);
	close(fd);
}

void	copy_map(t_config *data, int fd, char *path)
{
	char	*line;
	int		i;

	i = 0;
	allocate_map(data, fd);
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(VALID_STARTMAP, line[0]))
		{
			ft_trim_in_place(line, "\n");
			data->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	data->map[i] = NULL;
	valid_map(data);
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
		if (!line)
			break ;
		if (!is_only_whitespace(line))
			check_valid_infos(data, line);
		if (ft_strchr(VALID_STARTMAP, line[0]))
		{
			if (info_empty(data))
				print_error(ERR_MISSINGTEXT, data);
			copy_map(data, fd, path);
		}
		free(line);
	}
	return ;
}
