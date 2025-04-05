/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:53:33 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 21:27:00 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_only_whitespace(const char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
			&& *str != '\r' && *str != '\v' && *str != '\f')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*original_dest;

	if (dest == NULL || src == NULL)
		return (NULL);
	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n-- > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (n == (size_t) -1)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

int	has_spaces(const char *str)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == ' ' || *str == '\t')
			return (1);
		str++;
	}
	return (0);
}
