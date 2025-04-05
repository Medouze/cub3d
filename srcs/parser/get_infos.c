/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:57:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 17:55:31 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_lines(char *path)
{
	int		size;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("Error while opening file", NULL, NULL);
	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!is_only_whitespace(line))
				size++;
		}
		else
			break ;
		free(line);
	}
	close(fd);
	return (size);
}

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
		infos++;
	}
}

char	**fill_infos(char *path)
{
	char	*line;
	char	**infos;
	int		fd;
	int		i;

	i = count_lines(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("Error while opening file", NULL, NULL);
	infos = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!is_only_whitespace(line))
			{
				infos[i] = ft_strdup(line);
				i++;
			}
			free(line);
		}
		else
			break ;
	}
	infos[i] = NULL;
	close(fd);
	print_infos(infos);
	return (infos);
}
