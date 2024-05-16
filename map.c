/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:19:03 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/16 17:20:09 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	occurence_amount(char *map, char componenent)
{
	int	i;
	int	present_amount;

	i = 0;
	present_amount = 0;
	while (map[i])
	{
		if (map[i] == componenent)
			present_amount++;
		i++;
	}
	return (present_amount);
}

char	*character_check(char *map, struct t_data *game)
{
	game->collectibles = occurence_amount(map, 'C');
	if (occurence_amount(map, 'P') > 1)
	{
		ft_printf("Error\nA streaker entered the field.\n");
		return (NULL);
	}
	if (occurence_amount(map, 'P') == 0)
	{
		ft_printf("Error\nMessi has been injured.\n");
		return (NULL);
	}
	if (occurence_amount(map, 'E') != 1)
	{
		ft_printf("Error\n¿Por qué jugaría si no hay premios para ganar?\n");
		return (NULL);
	}
	if (game->collectibles < 1)
	{
		ft_printf("Error\n");
		ft_printf("Match has been cancelled due to a shortage of players.\n");
		return (NULL);
	}
	if (!measurements(map, game))
		return (NULL);
	return (map);
}

mlx_image_t	*map_indicator(struct t_data *game, int j, int i)
{
	if (game->map[j][i] == '0')
		return (game->img0);
	if (game->map[j][i] == '1')
		return (game->img1);
	if (game->map[j][i] == 'C')
		return (game->imgc);
	if (game->map[j][i] == 'E')
		return (game->imge);
	if (game->map[j][i] == 'P')
		return (game->imgp);
	return (NULL);
}

static void	make_img(struct t_data *game)
{
	mlx_texture_t	*texture0;
	mlx_texture_t	*texture1;
	mlx_texture_t	*texture_c;
	mlx_texture_t	*texture_e;
	mlx_texture_t	*texture_p;

	texture0 = mlx_load_png("textures/grass.png");
	texture1 = mlx_load_png("textures/leafwall.png");
	texture_c = mlx_load_png("textures/sergioramos.png");
	texture_e = mlx_load_png("textures/ballondor.png");
	texture_p = mlx_load_png("textures/messi.png");
	game->img0 = mlx_texture_to_image(game->mlx, texture0);
	game->img1 = mlx_texture_to_image(game->mlx, texture1);
	game->imgc = mlx_texture_to_image(game->mlx, texture_c);
	game->imge = mlx_texture_to_image(game->mlx, texture_e);
	game->imgp = mlx_texture_to_image(game->mlx, texture_p);
	mlx_delete_texture(texture0);
	mlx_delete_texture(texture1);
	mlx_delete_texture(texture_c);
	mlx_delete_texture(texture_e);
	mlx_delete_texture(texture_p);
}

int	display_map(struct t_data *game)
{
	int			i;
	int			j;
	mlx_image_t	*indicator;

	i = 0;
	j = 0;
	game->mlx = mlx_init((game->width * 64), (game->height * 64), "GTAVI", 1);
	make_img(game);
	norminette_function(game);
	while (j <= (game->height * 64) && i <= (game->width * 64))
	{
		while (i <= (game->width * 64))
		{
			if ((j / 64) == game->height)
				break ;
			if ((i / 64) == game->width)
				break ;
			indicator = map_indicator(game, (j / 64), (i / 64));
			mlx_image_to_window(game->mlx, indicator, i, j);
			i = i + 64;
		}
		i = 0;
		j = j + 64;
	}
	return (1);
}
