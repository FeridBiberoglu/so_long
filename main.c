/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:06:07 by fbiberog          #+#    #+#             */
/*   Updated: 2024/04/23 21:46:57 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			ft_printf("This field is unplayable.\n");
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

char	*file_to_array(char *file)
{
	char	*map;
	char	*temp;
	int		fd;
	int		len;
	int		lenold;

	fd = open(file, O_RDONLY);
	while (1)
	{
		temp = get_next_line(fd);
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
	close(fd);
	return (free(temp), map);
}

void	free_images(struct t_data *game)
{
	free(game->img0);
	free(game->img1);
	free(game->imgc);
	free(game->imge);
	free(game->imgp);
}

int	main(int argc, char **argv)
{
	struct t_data	game;
	char			*temp;

	if (argc != 2)
		return (ft_printf("Invalid number of arguments.\n"), 0);
	game = (struct t_data){0};
	temp = file_to_array(argv[1]);
	if (!temp)
		return (ft_printf("The stadium is under construction.\n"), 0);
	if (character_check(temp, &game) == (0))
		return (free(temp), 0);
	game.map = ft_split(temp, '\n');
	free(temp);
	if (!floodfill(&game))
		return (free(game.map), 0);
	display_map(&game);
	mlx_key_hook(game.mlx, (void *)&pressed_key, &game);
	mlx_loop(game.mlx);
	if (game.map[game.y][game.x] == 'E' && game.collectibles == 0)
		ft_printf("The GOAT with yet another Ballon d'Or!\n");
	mlx_terminate(game.mlx);
	free_images(&game);
	return (free(game.map), 0);
}