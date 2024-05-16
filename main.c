/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:06:07 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/16 18:14:54 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_mapname(char *argv, struct t_data *game)
{
	int	i;

	i = ft_strlen(argv);
	game->fd = open(argv, O_RDONLY);
	if (game->fd == -1)
		return (0);
	if (i <= 4 || !ft_strnstr(argv + (i - 4), ".ber", i))
		return (0);
	return (1);
}

int	measurements(char *map, struct t_data *game)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (map[i])
	{
		if (map[i] != 'C' && map[i] != 'E' && map[i] != 'P' && map[i] != '1'
			&& map[i] != '0' && map[i] != '\n')
		{
			ft_printf("Error\nThis field is unplayable.\n");
			return (0);
		}
		if (map[i] == '\n')
			j++;
		i++;
	}
	game->width = ft_strchr2(map, '\n');
	game->height = j;
	return (1);
}

char	*file_to_array(struct t_data *game)
{
	char	*map;
	char	*temp;
	int		len;
	int		lenold;

	map = NULL;
	while (1)
	{
		temp = get_next_line(game->fd);
		if (!temp)
			return (NULL);
		len = ft_strlen(temp);
		if (!map)
			lenold = len;
		map = ft_strjoin2(map, temp, 0);
		if (len != lenold && ft_strchr2(temp, '\n') >= 0)
			return (free(temp), free(map), NULL);
		if ((len + 1 == lenold && ft_strchr2(temp, '\n') == -1))
			break ;
		free(temp);
	}
	return (free(temp), map);
}

void	free_images(struct t_data *game)
{
	mlx_delete_image(game->mlx, game->img0);
	mlx_delete_image(game->mlx, game->img1);
	mlx_delete_image(game->mlx, game->imgc);
	mlx_delete_image(game->mlx, game->imge);
	mlx_delete_image(game->mlx, game->imgp);
}

int	main(int argc, char **argv)
{
	struct t_data	game;
	char			*temp;

	game = (struct t_data){0};
	if (argc != 2 || !valid_mapname(argv[1], &game))
		return (ft_printf("Error\nInvalid mapname.\n"), 0);
	temp = file_to_array(&game);
	close(game.fd);
	if (!temp)
		return (ft_printf("Error\nThe stadium is under construction.\n"), 0);
	if (character_check(temp, &game) == (0))
		return (free(temp), 0);
	game.map = ft_split(temp, '\n');
	free(temp);
	if (!floodfill(&game))
		return (ft_free2(game.map, game.height), 0);
	display_map(&game);
	mlx_key_hook(game.mlx, (void *)&pressed_key, &game);
	mlx_loop(game.mlx);
	if (game.map[game.y][game.x] == 'E' && game.collectibles == 0)
		ft_printf("The GOAT with yet another Ballon d'Or!\n");
	mlx_terminate(game.mlx);
	return (ft_free2(game.map, game.height), 0);
}
