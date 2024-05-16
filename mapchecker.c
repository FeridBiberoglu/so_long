/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:49:17 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/16 17:19:03 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	border_check(struct t_data *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != (game->width - 1))
	{
		if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
		{
			ft_printf("Error\nNo visible sidelines.\n");
			return (0);
		}
		i++;
	}
	while (j != (game->height - 1))
	{
		if (game->map[j][0] != '1' || game->map[j][game->width - 1] != '1')
		{
			ft_printf("Error\nNo visible sidelines.\n");
			return (0);
		}
		j++;
	}
	return (1);
}

char	**make_temp_map(struct t_data *game)
{
	char	**temp_map;
	int		i;
	int		j;

	j = 0;
	i = 0;
	temp_map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!temp_map)
		return (NULL);
	while (j < game->height)
	{
		temp_map[j] = malloc(sizeof(char) * (game->width + 1));
		if (!temp_map[j])
			return (NULL);
		i = 0;
		while (game->map[j][i])
		{
			temp_map[j][i] = game->map[j][i];
			i++;
		}
		if (j == game->height)
			break ;
		j++;
	}
	return (temp_map);
}

void	fill_map(struct t_data *game, char **temp_map, int j, int i)
{
	int	he;
	int	wi;

	he = game->height;
	wi = game->width;
	if (j <= 0 || j >= he || i <= 0 || i >= wi || temp_map[j][i] == 'X'
		|| temp_map[j][i] == '1')
		return ;
	if (temp_map[j][i] == 'C')
		game->collectibles--;
	if (temp_map[j][i] == 'E')
		game->exit_check++;
	temp_map[j][i] = 'X';
	fill_map(game, temp_map, j + 1, i);
	fill_map(game, temp_map, j - 1, i);
	fill_map(game, temp_map, j, i + 1);
	fill_map(game, temp_map, j, i - 1);
}

void	ft_free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	floodfill(struct t_data *game)
{
	char	old;
	char	new;
	char	**temp_map;
	int		temp;

	if (!border_check(game))
		return (0);
	new = 'x';
	temp = game->collectibles;
	temp_map = make_temp_map(game);
	old = game->map[game->y][game->x];
	if (old == new)
		return (ft_free_array(temp_map, game->height), 1);
	player_position(game);
	fill_map(game, temp_map, game->y, game->x);
	ft_free_array(temp_map, game->height);
	if (game->collectibles != 0 || game->exit_check != 1)
	{
		ft_printf("Error\nThe game has been cancelled.\n");
		return (0);
	}
	game->collectibles = temp;
	return (1);
}
