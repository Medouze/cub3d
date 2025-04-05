/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:25:33 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/05 21:27:47 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

void	ft_trim_in_place(char *str, const char *set)
{
	int		start;
	int		end;
	int		i;

	start = 0;
	i = 0;
	if (!str || !set)
		return ;
	while (str[start] && is_in_set(str[start], set))
		start++;
	end = start;
	while (str[end])
		end++;
	end--;
	while (end > start && is_in_set(str[end], set))
		end--;
	i = 0;
	while (start <= end)
	{
		str[i] = str[start];
		start++;
		i++;
	}
	str[i] = '\0';
}

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*malloc_word(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**split;

	i = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			split[i] = malloc_word(s, c);
			if (!split[i])
				return (NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	split[i] = NULL;
	return (split);
}
