/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:48:40 by fbiberog          #+#    #+#             */
/*   Updated: 2024/02/15 20:56:55 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*mod_substr(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;
	size_t	k;

	i = 0;
	k = ft_strlen(s);
	if (start > k)
		return (NULL);
	if (len > k - start)
		len = k - start;
	array = (char *)malloc(len + 2);
	if (array == 0)
		return (0);
	while (i < len)
	{
		array[i] = s[start + i];
		i++;
	}
	array[i] = '\n';
	array[i + 1] = '\0';
	return (array);
}

static int	wordcounter(char const *s, char c)
{
	int	i;
	int	j;
	int	wordcount;

	wordcount = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && j == 0)
		{
			wordcount++;
			j = 1;
		}
		if (s[i] == c)
			j = 0;
		i++;
	}
	return (wordcount);
}

static int	cfinder(char const *s, int x, char c, int execute)
{
	int	i;

	i = 0;
	if (execute == 0)
	{
		while (s[x] && s[x] != c)
		{
			i++;
			x++;
		}
	}
	else if (execute == 1)
	{
		while (s[x] == c)
		{
			i++;
			x++;
		}
	}
	if (execute == 0)
		return (i);
	else
		return (x);
}

char	**ft_split2(char const *s, char c)
{
	size_t	i;
	int		j;
	char	**str;

	j = 0;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (wordcounter(s, c) + 1));
	if (str == 0)
		return (0);
	while (s[i] && j < wordcounter(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		str[j] = mod_substr(s, i, cfinder(s, i, c, 0));
		i = cfinder(s, i, c, 0) + cfinder(s, i, c, 1);
		if (str[j] == 0)
		{
			ft_free2(str, j);
			return (0);
		}
		j++;
	}
	str[j] = 0;
	return (str);
}
